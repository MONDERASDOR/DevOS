#include <kernel.h>
#include <process.h>
#include <memory.h>
#include <scheduler.h>
#include <syscall.h>
#include <vmm.h>

#define MAX_PROCESSES 256
#define TIME_QUANTUM 100 // 100ms time slice

struct process {
    pid_t pid;
    struct process *parent;
    struct process *children[MAX_PROCESSES];
    int num_children;
    void *stack;
    size_t stack_size;
    struct process_state state;
    struct process_priority priority;
    struct process_stats stats;
    void *page_directory;
    struct process_context context;
    struct process_resources resources;
    unsigned int time_slice;
    unsigned int last_run_time;
    unsigned int nice;
};

static struct process processes[MAX_PROCESSES];
static pid_t next_pid = 1;
static unsigned int current_time = 0;

void init_scheduler(void) {
    memset(processes, 0, sizeof(processes));
    
    // Initialize the idle process
    struct process *idle = &processes[0];
    idle->pid = 0;
    idle->state = PROCESS_STATE_RUNNING;
    idle->priority = PROCESS_PRIORITY_IDLE;
    idle->nice = 0;
    idle->time_slice = TIME_QUANTUM;
    current_process = idle;
    
    // Initialize virtual memory
    init_vmm();
    
    // Start timer interrupt
    init_timer();
}

pid_t create_process(void *entry_point, void *stack, size_t stack_size) {
    if (next_pid >= MAX_PROCESSES) {
        return -1; // No more process slots available
    }
    
    struct process *proc = &processes[next_pid];
    
    proc->pid = next_pid;
    proc->parent = current_process;
    proc->stack = stack;
    proc->stack_size = stack_size;
    proc->state = PROCESS_STATE_READY;
    proc->priority = PROCESS_PRIORITY_NORMAL;
    proc->nice = 0;
    proc->time_slice = TIME_QUANTUM;
    
    // Allocate page directory
    proc->page_directory = kmalloc(PAGE_SIZE);
    if (!proc->page_directory) {
        return -1; // Out of memory
    }
    
    // Copy parent's page directory
    memcpy(proc->page_directory, current_process->page_directory, PAGE_SIZE);
    
    // Map process stack
    void *stack_addr = vmalloc(stack_size);
    if (!stack_addr) {
        kfree(proc->page_directory);
        return -1; // Out of memory
    }
    
    // Initialize process context
    proc->context.sp = (unsigned int)stack_addr + stack_size;
    proc->context.pc = (unsigned int)entry_point;
    
    // Initialize process resources
    proc->resources.memory_limit = MEMORY_SIZE / 2;
    proc->resources.current_memory = stack_size;
    
    // Initialize process state
    proc->stats.start_time = get_uptime();
    proc->stats.cpu_time = 0;
    proc->last_run_time = current_time;
    
    // Add to parent's children list
    if (proc->parent) {
        proc->parent->children[proc->parent->num_children] = proc;
        proc->parent->num_children++;
    }
    
    next_pid++;
    return proc->pid;
}

void destroy_process(pid_t pid) {
    if (pid <= 0 || pid >= next_pid) {
        return;
    }
    
    struct process *proc = &processes[pid];
    
    // Free process resources
    if (proc->page_directory) {
        kfree(proc->page_directory);
    }
    
    if (proc->stack) {
        vfree(proc->stack);
    }
    
    // Free allocated memory
    free_process_memory(proc);
    
    // Remove from parent's children list
    if (proc->parent) {
        for (int i = 0; i < proc->parent->num_children; i++) {
            if (proc->parent->children[i] == proc) {
                proc->parent->children[i] = NULL;
                break;
            }
        }
    }
    
    // Free process slot
    memset(proc, 0, sizeof(struct process));
}

void switch_to_process(struct process *proc) {
    if (!proc) {
        return;
    }
    
    // Switch page directory
    switch_page_directory(proc);
    
    // Update process state
    if (current_process) {
        current_process->state = PROCESS_STATE_READY;
        current_process->time_slice = TIME_QUANTUM;
    }
    
    current_process = proc;
    proc->state = PROCESS_STATE_RUNNING;
    
    // Update process stats
    proc->stats.cpu_time += get_uptime() - proc->stats.last_time;
    proc->stats.last_time = get_uptime();
    
    // Switch to process context
    asm volatile(
        "mov %0, %%esp\n"
        "mov %1, %%ebp\n"
        "jmp *%2\n"
        : 
        : "r"(proc->context.sp), "r"(proc->context.bp), "r"(proc->context.pc)
        : "memory"
    );
}

void schedule(void) {
    if (!current_process) {
        return;
    }
    
    // Check if current process has used its time slice
    unsigned int time_used = current_time - current_process->last_run_time;
    if (time_used >= current_process->time_slice) {
        current_process->state = PROCESS_STATE_READY;
        current_process->time_slice = TIME_QUANTUM;
    }
    
    // Find next process to run
    struct process *next = NULL;
    unsigned int highest_priority = -1;
    
    for (int i = 0; i < next_pid; i++) {
        if (processes[i].pid > 0 && 
            processes[i].state == PROCESS_STATE_READY && 
            processes[i].priority > highest_priority) {
            next = &processes[i];
            highest_priority = processes[i].priority;
        }
    }
    
    if (next && next != current_process) {
        switch_to_process(next);
    }
}

void handle_timer_interrupt(void) {
    current_time++;
    schedule();
}

void set_process_priority(pid_t pid, int priority) {
    if (pid <= 0 || pid >= next_pid) return;
    
    struct process *proc = &processes[pid];
    if (proc->state != PROCESS_STATE_RUNNING && 
        proc->state != PROCESS_STATE_READY) {
        return;
    }
    
    proc->priority = priority;
    proc->nice = 0;
    proc->time_slice = TIME_QUANTUM;
}

void nice_process(pid_t pid, int value) {
    if (pid <= 0 || pid >= next_pid) return;
    
    struct process *proc = &processes[pid];
    if (proc->state != PROCESS_STATE_RUNNING && 
        proc->state != PROCESS_STATE_READY) {
        return;
    }
    
    proc->nice += value;
    if (proc->nice < -20) proc->nice = -20;
    if (proc->nice > 19) proc->nice = 19;
    
    // Adjust priority based on nice value
    proc->priority = 20 - proc->nice;
    
    // Adjust time slice
    proc->time_slice = TIME_QUANTUM * (20 - proc->nice) / 20;
}

void get_process_info(struct process_info *info) {
    if (!info) return;
    
    info->running = 0;
    info->total = 0;
    info->memory_usage = 0;
    info->total_cpu_time = 0;
    
    for (int i = 0; i < next_pid; i++) {
        if (processes[i].pid > 0) {
            info->total++;
            if (processes[i].state == PROCESS_STATE_RUNNING) {
                info->running++;
            }
            info->memory_usage += processes[i].resources.current_memory;
            info->total_cpu_time += processes[i].stats.cpu_time;
        }
    }
}

void get_memory_info(struct memory_info *info) {
    if (!info) return;
    
    info->total = MEMORY_SIZE;
    info->used = 0;
    info->free = 0;
    info->page_faults = 0;
    
    // Calculate used memory
    for (int i = 0; i < (MEMORY_SIZE / PAGE_SIZE); i++) {
        if (page_directory[i].present) {
            info->used += PAGE_SIZE;
            if (page_directory[i].accessed) {
                info->page_faults++;
            }
        } else {
            info->free += PAGE_SIZE;
        }
    }
}
