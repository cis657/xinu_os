/* mycreate.c */

#include <xinu.h>

extern sid32 semaphore_lock;

void mycreate(void){

   // print our process ID
    kprintf("Running pid: %d\n", getpid());
    
    // let's do nothing to keep our process running
    while(TRUE){
    }
    return OK;
}