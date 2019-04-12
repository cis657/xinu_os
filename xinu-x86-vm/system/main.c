

#define ORIGINAL 0
#define PART_III 0
#define PART_IV 1

#if ORIGINAL
*main.c - main * /

#include <xinu.h>
#include <stdio.h>

			  int main(int argc, char **argv)
{
	uint32 retval;

	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));

	/* Wait for shell to exit and recreate it */

	recvclr();
	while (TRUE)
	{
		retval = receive();
		kprintf("\n\n\rMain process recreating shell\n\n\r");
		resume(create(shell, 4096, 1, "shell", 1, CONSOLE));
	}
	while (1)
		;

	return OK;
}
#elif PART_III
/* hello.c - main*/
#include <xinu.h>
/* main - just say hello, then exit */
void main(void)
{
	printf("Hello, world!\n");
}
#elif PART_IV

// Example straight from the text book
/* ex3.c - main, sndch */
#include <xinu.h>
void sndch(char);
/*------------------------------------------------------------------------
* main - Example of 2 processes executing the same code concurrently
*------------------------------------------------------------------------
*/
void main(void)
{
	resume(create(sndch, 1024, 40, "send A", 1, 'A'));
	resume(create(sndch, 1024, 20, "send B", 1, 'B'));
}
/*------------------------------------------------------------------------
* sndch - Output a character on a serial device indefinitely
*------------------------------------------------------------------------
*/
void sndch(
	char ch /* The character to emit continuously */
)
{
	while (1)
		putc(CONSOLE, ch);
}
#endif
