/*  HW2 main.c  */

#include <xinu.h>

/* Name: waiter
 * Description: This process will print numbers
 * Returns: Nothing
 * 
 */
void waiter();

/* Name: signaler
 * Description: This process will print a sentence
 * Returns: Nothing
 * 
 */
void signaler();

// Declare our semaphore which will help control the synchronization
// between our two processes.
//
sid32 semaphore_lock;

// Stores our waiter process ID
//
pid32 waiter_pid; 

// Store the signaler process ID
//
pid32 signaler_pid;

// Name: main
// 
// Description: Main driver program that creates our suspended processes
// and places them in a 'ready' state.
//
int main(int argc, char **argv)
{
	// create and initialize our semaphore to 20
	//
    semaphore_lock = semcreate(20);

	// create our waiter process
    waiter_pid = create(waiter, 1024, 40, "Waiter Process", 0);

	// create our signaler process
	signaler_pid = create(signaler, 1024, 20, "Signaler Process", 0);
	
	resume(waiter_pid);
	resume(signaler_pid);

	while(1);

	return OK;
}

/* Name: signaler
 *
 */
void signaler()
{
	// Once the waiter 'yields' the CPU by 'blocking',
	// our signaler will execute a print statement.
	// After the print statement executes, we shall use
	// the 'signaln()' to signal our semaphore five times.
	//
    while(TRUE){
		kprintf("Signaler is running now..\n");
        signaln(semaphore_lock, 5);
        
		// Used to slow up the output, but for your own sanity
		// we can comment it out and use at will
		//
		//sleep(1);
	}

}

/* Name: waiter
 *
 */
void waiter()
{
	// Initialize our index to count up to 2000
	int32 index = 1;

	while(index <= 2000){
		kprintf("%d - \n", index);
		// Wait performs a decrement each time we print the index value
		// and when our semaphore reaches a value less than one, we will block.
		// Upon blocking, the 'signaler' will be given a chance to run.
		wait(semaphore_lock);
        
		// increase our index value for the next "computation"
		index++;
	}
	
	// Since the 'signaler' process has no exit strategy, lets KILL it
    kill(signaler_pid);

	kprintf("Final exit from waiter..\n");
}

