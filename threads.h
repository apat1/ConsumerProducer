/***************************************************************************************
 * Authors:		Jeffrey Cirka, Andy Pat
 * Date:		03/19/2013
 * ASU email:	jscirka@asu.edu, apat1@asu.edu
 * Course:		CSE 430 TTH 4:30-5:45
 * Prject#:	    2
 * Language:	c
 * Compiler:	gcc
 * Description:
 * 		This file contains the context switching and thread related code for our
 *      user thread application
 ***************************************************************************************
 */

#include "q.h"

void start_thread(void (*function)(void))
{
    // allocate a stack (via malloc) of a certain size (choose 8192)
    size_t const stack_size = 8192;
    void * stackP = malloc(stack_size);
    // allocate a TCB (via malloc)
    TCB_t * newTCB = NewItem();


    // call init_TCB with appropriate arguments
    init_TCB (newTCB, function, stackP, stack_size);

    // call addQ to add this TCB into the “ReadyQ” which is a global header pointer
    AddQueue(&ReadyQ,newTCB);
}

void run()
{   //creating parent context to store the main context prior to switching the context with the swapcontext method
    ucontext_t parent;     // get a place to store the main context, for faking
    //getcontext creates the context
    getcontext(&parent);   // magic sauce
    //swapcontext swaps the context to the context stored in the ready Q and executes its associated function
    swapcontext(&parent, &(ReadyQ->context));  // start the first thread
	//code from my notes
	//swapcontext(from, to);
	//from = malloc(sizeof(u_context_t));
	//to = &(ReadyQ->tcb);
}

void yield() // similar to run
{
	//rotate the run Q;
	//swap the context, from previous thread to the thread pointed to by runQ
	ucontext_t *from, *to;
	from = &(ReadyQ->context);
	RotateQ(&ReadyQ);
	to = &(ReadyQ->context);
	swapcontext(from, to);
}