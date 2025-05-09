#ifndef PROCESS_H
#define PROCESS_H

#define MAX_PROCESSES 16

struct process {
    int pid;
    char name[32];
    int running;
    void (*entry)();
};

void process_init();
struct process *process_create(const char *name, void (*entry)());
void process_kill(int pid);
void process_list();
struct process *process_get(int pid);

#endif // PROCESS_H
