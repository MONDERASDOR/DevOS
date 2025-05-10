#include <kernel.h>
#include <memory.h>
#include <process.h>

#define PAGE_SIZE 4096
#define PAGE_TABLE_ENTRIES 1024

// Page table entry structure
struct page_table_entry {
    unsigned int present : 1;
    unsigned int rw : 1;
    unsigned int user : 1;
    unsigned int accessed : 1;
    unsigned int dirty : 1;
    unsigned int unused : 7;
    unsigned int frame : 20;
};

// Page directory entry structure
struct page_directory_entry {
    unsigned int present : 1;
    unsigned int rw : 1;
    unsigned int user : 1;
    unsigned int accessed : 1;
    unsigned int unused : 7;
    unsigned int table : 20;
};

// Global page directory
struct page_directory_entry page_directory[PAGE_TABLE_ENTRIES];

void init_vmm(void) {
    // Initialize page directory
    memset(page_directory, 0, sizeof(page_directory));
    
    // Map kernel memory
    for (int i = 0; i < (KERNEL_END / PAGE_SIZE); i++) {
        struct page_table_entry *pte = (struct page_table_entry *)
            (KERNEL_PAGE_TABLE + (i * sizeof(struct page_table_entry)));
        
        pte->present = 1;
        pte->rw = 1;
        pte->user = 0;
        pte->frame = i;
    }
    
    // Load page directory
    asm volatile("mov %0, %%cr3" : : "r"(page_directory));
    
    // Enable paging
    unsigned long cr0;
    asm volatile("mov %%cr0, %0" : "=r"(cr0));
    cr0 |= 0x80000000; // Set PG bit
    asm volatile("mov %0, %%cr0" : : "r"(cr0));
}

void *kmalloc(size_t size) {
    // Align size to page boundary
    size = (size + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1);
    
    // Find free pages
    for (int i = 0; i < (MEMORY_SIZE / PAGE_SIZE); i++) {
        if (!page_directory[i].present) {
            // Allocate page
            page_directory[i].present = 1;
            page_directory[i].rw = 1;
            page_directory[i].user = 0;
            page_directory[i].table = i;
            
            return (void *)(i * PAGE_SIZE);
        }
    }
    
    return NULL; // Out of memory
}

void kfree(void *addr) {
    if (!addr) return;
    
    unsigned int page = (unsigned int)addr / PAGE_SIZE;
    
    if (page_directory[page].present) {
        page_directory[page].present = 0;
    }
}

void *vmalloc(size_t size) {
    // Align size to page boundary
    size = (size + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1);
    
    // Find free virtual address space
    for (int i = USER_MEMORY_START; i < USER_MEMORY_END; i += PAGE_SIZE) {
        if (!page_directory[i / PAGE_SIZE].present) {
            // Allocate physical page
            unsigned int phys_page = find_free_phys_page();
            if (phys_page == -1) return NULL;
            
            // Map virtual to physical
            page_directory[i / PAGE_SIZE].present = 1;
            page_directory[i / PAGE_SIZE].rw = 1;
            page_directory[i / PAGE_SIZE].user = 1;
            page_directory[i / PAGE_SIZE].table = phys_page;
            
            return (void *)i;
        }
    }
    
    return NULL; // Out of memory
}

void vfree(void *addr) {
    if (!addr) return;
    
    unsigned int page = (unsigned int)addr / PAGE_SIZE;
    
    if (page_directory[page].present && page_directory[page].user) {
        page_directory[page].present = 0;
    }
}

void switch_page_directory(struct process *proc) {
    if (proc) {
        asm volatile("mov %0, %%cr3" : : "r"(proc->page_directory));
    } else {
        asm volatile("mov %0, %%cr3" : : "r"(page_directory));
    }
}

void handle_page_fault(unsigned int fault_addr) {
    // Handle page fault here
    // This is a basic implementation - you might want to add more sophisticated handling
    printf("Page fault at address: 0x%x\n", fault_addr);
    current_process->state = PROCESS_STATE_ZOMBIE;
}
