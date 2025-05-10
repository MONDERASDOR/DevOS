#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <kernel.h>
#include <memory.h>
#include <process.h>

void sysinfo(void) {
    printf("System Information:\n");
    printf("-----------------\n");
    
    // Get system memory information
    struct memory_info mem_info;
    get_memory_info(&mem_info);
    printf("Memory Usage:\n");
    printf("  Total: %lu KB\n", mem_info.total / 1024);
    printf("  Used: %lu KB\n", mem_info.used / 1024);
    printf("  Free: %lu KB\n", mem_info.free / 1024);
    
    // Get process information
    struct process_info proc_info;
    get_process_info(&proc_info);
    printf("\nProcess Information:\n");
    printf("-------------------\n");
    printf("  Running Processes: %d\n", proc_info.running);
    printf("  Total Processes: %d\n", proc_info.total);
    
    // Get system uptime
    unsigned long uptime = get_uptime();
    printf("\nSystem Uptime:\n");
    printf("--------------\n");
    printf("  %lu seconds\n", uptime);
    
    // Get system version
    printf("\nSystem Version:\n");
    printf("---------------\n");
    printf("  devOS v1.0\n");
    printf("  Build Date: %s\n", __DATE__);
}

// Register this command
COMMAND(sysinfo, "Display system information");
