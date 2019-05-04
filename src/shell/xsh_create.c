/* xsh_create.c - xsh_create */
#include <xinu.h>
#include <stdio.h>
#include <string.h>

/*------------------------------------------------------------------------
 * xsh_create - shell command to createeeeee
 *------------------------------------------------------------------------
 */
shellcmd xsh_create(int nargs, char *args[])
{
    pri16 priority;
    char ch;
    char *chprio;
    pid32 pid;

    kprintf("xsh_create() called\n");

    if (nargs == 1)
    {
        priority = INITPRIO;
        pid = create(runforever, 1024, priority, "Test", 1, priority);
        sleep(1);
        kprintf("xhs_create(), #args: %d PID: %d Priority: %d\n", nargs, pid, priority);
        resume(pid);
    }
    else if (nargs == 2)
    {
        chprio = args[1];
        ch = *chprio++;
        priority = 0;
        while (ch != NULLCH)
        {
            if ((ch < '0') || (ch > '9'))
            {
                kprintf("%s: non-digit in priority\n", args[1]);
                return 1;
            }
            priority = 10 * priority + (ch - '0');
            ch = *chprio++;
        }

        if (priority < (pri16)MINKEY || priority > (pri16)MAXKEY)
        {
            kprintf("%s: invalid priority\n", args[1]);
            return 1;
        }
        else
        {
            pid = create(runforever, 1024, priority, "Test", 1, priority);
            sleep(1);
            kprintf("xhs_create(), #args: %d PID: %d Priority: %d\n", nargs, pid, priority);
            resume(pid);
        }
    }

    else
    {
        kprintf("Too many arguments\n");
        return 1;
    }

    return 0;
}
