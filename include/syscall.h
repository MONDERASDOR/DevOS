#ifndef SYSCALL_H
#define SYSCALL_H

// Syscall numbers
#define SYS_GETPID   1
#define SYS_KILL     2
#define SYS_ALLOC    3
#define SYS_FREE     4
#define SYS_TIME     5
#define SYS_LOG      6

// Argument structures
struct syscall_kill_args {
    int pid;
};
struct syscall_alloc_args {
    unsigned int size;
    void **result;
};
struct syscall_free_args {
    void *ptr;
};
struct syscall_log_args {
    int level;
    const char *msg;
};

int syscall(int callno, void *arg);

#endif // SYSCALL_H
