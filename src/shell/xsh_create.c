#include <xinu.h>
#include <stdio.h>
#include <string.h>

shellcmd xsh_create(int nargs, char *args[])
{

    char *chptr;    /* walks through argument	*/
    char ch;        /* next character of argument	*/
    int32 priority; /* stores the priority value     */
    pid32 pid;

    if (nargs == 1)
    {
        priority = 20;
    }
    else if(nargs == 2)
    {

        chptr = args[1];
        ch = *chptr++;
        priority = 0;
        while (ch != NULLCH)
        {
            if ((ch < '0') || (ch > '9'))
            {
                fprintf(stderr, "%s: nondigit in argument\n",
                        args[0]);
                return 1;
            }
            priority = 10 * priority + (ch - '0');
            ch = *chptr++;
        }
    }
    pid = create(mycreate, 1024, priority, "FanionProcess", 0);

    return 0;
}