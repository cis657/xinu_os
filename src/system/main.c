/*  main.c  - main */

/* What we want is to be able to alternate between process 'm1' and process 'm2'.
   An attempt was made to use a single semaphore, but the results were not reliable 
   as there was no guarantee the order for which process would be allowed to enter the critical
   section, hence the use of two semaphores.

*/

#include <xinu.h>

void m1();
void m2();

sid32 m1_mutex, m2_mutex;
pid32 m1pid, m2pid;

int main(void){
	
	// will allow one process to run after acquiring the lock()
	m1_mutex = semcreate(1);
    
	// will block other processes if the lock() is acquired.
	m2_mutex = semcreate(0);

    // create two processes that have equal priority
	m1pid = create(m1, 1024, 20, "m1", 0);
	m2pid = create(m2, 1024, 20, "m2", 0);
	resume(m1pid);
	resume(m2pid);

	return OK;
}

void m2(){

    int32 k;

	// store the start range from 101
	// and we will be decrementing by 3 each time
	//
	int32 j = 101; 
	kprintf("m2 is running\n");
	// keep going until j is not greater than 0
	//
	while(j > 0){
		
		// store the current j-th number which we start at (i.e. 101)
		int l = j;
		
		// since this mutex has a starting value of 1, we will not block 
		// allowing this process to run and m1 to block.
		//
		wait(m1_mutex); 

		// loop three times and print the numbers in descending order
		// by decrementing our 'l' variable which decrements by 3
		//
		for(k = 0; k < 3; k++){
		    kprintf("\t%d - \n", l--);
		}
		
		// take the current 'l' value and feed it into the next
		// j, our next starting point (i.e. 98, etc)
		//
		j = l;

		// we are done, so signal the other process to continue printing
		// two values
		//
		signal(m2_mutex);
	}
	
}

void m1(){
	int32 k;
	int32 j = 1;

	// track the range (1-20) using 'j'
	kprintf("m1 is running\n");
	while(j < 20){
        
		// will block after process starts running
		wait(m2_mutex);

		// print 'j+2' times, if j = 1, up to 3
		for(k = j; k < j+2; k++){
            kprintf("%d - \n", k);
		}

		j+=2;
		signal(m1_mutex);
		// now that we've printed two numbers
		// increment j by two for the next set of two
		
		// let us block here, so the other process can run
		// and print a set of three numbers
		//
		
	}
}