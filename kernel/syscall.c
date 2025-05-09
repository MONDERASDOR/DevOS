#include "../include/syscall.h"
#include "../include/process.h"
#include "../include/k_memory.h"
#ifndef NULL
#define NULL 0
#endif
#include "../include/timer.h"
#include "../include/log.h"
#include "../include/stdio.h"

// For demo, assume single process context
static int current_pid = 1;

int syscall(int callno, void *arg) {
    switch (callno) {
        case SYS_GETPID:
            return current_pid;
        case SYS_KILL: {
            struct syscall_kill_args *a = (struct syscall_kill_args*)arg;
            process_kill(a->pid);
            return 0;
        }
        case SYS_ALLOC: {
            struct syscall_alloc_args *a = (struct syscall_alloc_args*)arg;
            *a->result = k_malloc(a->size);
            return (*a->result != NULL) ? 0 : -1;
        }
        case SYS_FREE: {
            struct syscall_free_args *a = (struct syscall_free_args*)arg;
            k_free(a->ptr);
            return 0;
        }
        case SYS_TIME:
            return (int)timer_now();
        case SYS_LOG: {
            struct syscall_log_args *a = (struct syscall_log_args*)arg;
            log_msg(a->level, "[syscall] log message:");
kprint(a->msg);
kprint("\n");
            return 0;
        }
        default:
            log_msg(LOG_ERR, "[syscall] Unknown syscall.");
kprint("Callno: ");
// Optionally print callno as a string if you have an itoa or similar

            return -1;
    }
}
