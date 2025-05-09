#ifndef LOG_H
#define LOG_H

#define LOG_INFO 1
#define LOG_WARN 2
#define LOG_ERR  3

void log_init();
void log_msg(int level, const char *fmt);

#endif // LOG_H
