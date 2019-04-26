/*  main.c  - main */

/* What we want is to be able to alternate between process 'm1' and process 'm2'.
*/

#include <xinu.h>

void m1();
void m2();

sid32 sem;
pid32 m1pid, m2pid;

int main(void){
	
	// single semaphore
	sem = semcreate(0);

    // create two processes that have equal priority
	m1pid = create(m1, 1024, 20, "m1", 0);
	m2pid = create(m2, 1024, 20, "m2", 0);
	resume(m1pid);
	resume(m2pid);

	return OK;
}

void m2(){
	int32 i;
	int32 k=101;

	for(i = k; i >= 0; i--){
		kprintf("\n");
		for(k = i; k > k-3; k--)
		    kprintf("%d - \n", k);
		signal(sem);
		
		
	}
}

void m1(){
	int32 i, k;
	
	for(i = 1; i <= 20; i++){
		wait(sem);
        for(k = i; k < i+2; k++)
		    kprintf("    %d - \n", k);
	}
}

/*void m2(){

    int32 k;

	// store the start range from 101 that we will be decrementing by 3 each time
	//
	int32 j = 101; 

	// simple print to indicate we are running process 'm2'
	kprintf("m2 is running\n");

	// keep going until j is not greater than 0
	//
	while(j > 0){
		
		// since the other process will block (i.e. semaphore < 0), this code will run first
        // and signal the blocked process to run.

		// store the current j-th number which we start at (i.e. 101)
		int l = j;

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
		signal(mutex);
	}
	
}

void m1(){
	int32 k;
	int32 j = 1;

	// track the range (1-20) using 'j'
	kprintf("m1 is running\n");
	while(j < 20){
        
		// will block after process starts running ( we only need one process to block, so let's choose this one)
		wait(mutex);

		// print 'j+2' times, if j = 1, up to 3
		for(k = j; k < j+2; k++){
            kprintf("%d - \n", k);
		}

        // now that we've printed two numbers
		// increment j by two for the next set of two
		j+=2;
	}
}*/