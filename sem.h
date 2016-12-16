/***************************************************************************************
 * Authors:		Jeffrey Cirka, Andy Pat
 * Date:		03/19/2013
 * ASU email:	jscirka@asu.edu, apat1@asu.edu
 * Course:		CSE 430 TTH 4:30-5:45
 * Prject#:	    2
 * Language:	c
 * Compiler:	gcc
 * Description:
 * 		This file contains our semaphore implementation. Note: All methods are atomic
 *      since there is no preemptive scheduling.
 ***************************************************************************************
 */

#include "threads.h"

//Semaphore data structure with a value field and a queue of TCBs.
typedef struct Semaphore{
    int count;
    TCB_t * Q;
} Sem;

//Initializes the semaphore
void InitSem(Sem * sem, int value){
	sem->count = value;
	InitQueue(&(sem->Q));
}

//The P routine decrements the semaphore, and if the value is less than zero then
//blocks the process in the queue associated with the semaphore.
void P(Sem * sem){

    sem->count--;

    if(sem->count < 0){
        TCB_t * temp = DelQueue(&ReadyQ);
        AddQueue(&(sem->Q), temp);

        //context switch from this process 'temp' (now in the blocked Q) to the head of the ready Q
        swapcontext(&(temp->context), &(ReadyQ->context));
    }

}

//The semaphore V routine, releases a blocked tcb (if any), increments semaphore counter
//and yields to another thread in the ReadyQ.
void V(Sem * sem){

	sem->count++;

	//There exists a tcb in the sem.Q when count <= 0.
	//Note (for future reference): if count == 0 then it means
	//1 tcb is in the sem.Q because count was -1 and was just incremented to 0 in the
	//previous line of code. Removing the tcb from sem.Q and adding it to ReadyQ unblocks it.

	if(sem->count <= 0){
		TCB_t * temp = DelQueue(&(sem->Q));
		AddQueue(&ReadyQ, temp);
	}

	yield();
}
