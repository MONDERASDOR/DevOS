#ifndef SCHEDULER_H
#define SCHEDULER_H

void scheduler_init();
void scheduler_tick();
void scheduler_add_process(void (*entry)(), const char *name);
void scheduler_run();

#endif // SCHEDULER_H
