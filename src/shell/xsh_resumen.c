/* xsh_resume.c */

#include <xinu.h>
#include <stdlib.h>
#include <stdio.h>

shellcmd xsh_resumen(int argc, char *args[]){

    char * currentReadProcessId;
    pid32 processIdNumber;
    int32 idx = 0;

    // how many process Id's we want to release
    int32 numberOfProcessIds = argc -1;

    if(argc == 1)
    {
        kprintf("No process Id's have been provided!\n");
        return 1;
    }
    else if( argc >= 2)
    {
        while( idx <= numberOfProcessIds)
        {
            currentReadProcessId = args[idx];
            // convert the read process Id to an integer
            processIdNumber = atoi(currentReadProcessId);

            // let's resume the current process Id number
            resume(processIdNumber);
            idx++;
        }
    }
    else{
        kprintf("Too many arguments provided, please try again\n");
        return 1;
    }

    return 0;
}