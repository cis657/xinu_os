#include <xinu.h>

void runforever(pri16 priority){
    pid32 pid = getpid();
    
    kprintf("runforever() called..\n");
    kprintf("Created new process, PID: %d Priority: %d\n", pid, priority);
    while(TRUE);
}