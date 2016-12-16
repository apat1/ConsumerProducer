/***************************************************************************************
 * Authors:		Jeffrey Cirka, Andy Pat
 * Date:		03/19/2013
 * ASU email:	jscirka@asu.edu, apat1@asu.edu
 * Course:		CSE 430 TTH 4:30-5:45
 * Prject#:	    2
 * Language:	c
 * Compiler:	gcc
 * Description:
 * 		This file is using the queuing routines and will implement the ability to run
 *      multiple functions as threads, using non-preemptive scheduling.
 ***************************************************************************************
 */

#include "tcb.h"

//function declarations ****************************************************************

TCB_t * NewItem();  // returns a pointer to a new q-element
void InitQueue(TCB_t ** head); // creates an empty queue, pointed to by the variable head.
void AddQueue(TCB_t ** head, TCB_t * item); // adds a queue item, pointed to by "item", to the queue pointed to by head.
TCB_t * DelQueue(TCB_t ** head); // deletes an item from head and returns a pointer to the deleted item
void RotateQ(TCB_t ** head); // Moves the header pointer to the next element in the queue. This is equivalent to AddQ(&head, DeleteQ(&head)), but is simpler to use and more efficient to implement.
void FreeItem(TCB_t ** item); //deallocates an item


//function definitions *****************************************************************


TCB_t * NewItem(){
	//sizeof(struct TCB_t) = 12 because the struct contains one integer
	//variable (which is 4 bytes) and two pointer variables.
	//Each pointer contains a 32-bit (4 byte) address. A 32-bit compiler was used
	//to compile and test this code. The size will be different with a 64-bit compiler

	TCB_t * element = (TCB_t *)malloc(sizeof(struct TCB_t));
	element->next = NULL;
	element->prev = NULL;
	return element;
}

void InitQueue(TCB_t ** head){
    // creates an empty queue that is pointed to by the head element that is passed in
    //NOTE: The requirements specify: " The header is null if the q is empty. "
    *head = NULL;
}

void AddQueue(TCB_t ** head, TCB_t * item){
	if(*head == NULL){
		//an item is being added to an empty queue
		*head = item;
		return;
	}

	//getting the last element of the list (beginning from the head)
	TCB_t * el = *head;
	while(el->next != NULL){
		el = el->next;
	}

	//adding the item to the tail of the queue
	el->next = item;
	item->prev = el;
	item->next = NULL;
}

TCB_t * DelQueue(TCB_t ** head){
    // deletes the element at the head of the queue that is pointed to by the head
    // and returns a pointer to the deleted item
    if(*head == NULL){
		//the queue was empty, returning NULL
        return NULL;
	}
    else
    {
        // make the head node point to the next element
        TCB_t * temp = *head;
        if((*head)->next == NULL)
        {
			//the head is the only element left in the queue, setting it to NULL since the element is now deleted from the queue
			*head = NULL;
		} else {
			//setting the head->next element as the new header of the queue
    	    (*head)->next->prev = NULL;
    	    *head = (*head)->next;
		}

		//the item deleted from the queue should not point to any other items in the queue
		temp->next = NULL;
		temp->prev = NULL;

        return temp;
    }
}

void RotateQ(TCB_t ** head){
	AddQueue(head, DelQueue(head));
}

void FreeItem(TCB_t ** item){
	//removes the element 'item' from the queue and then
    //frees the memory associated with the item that is passed in
    if((*item)->next != NULL){
    	(*item)->next->prev = (*item)->prev;
	}
	if((*item)->prev != NULL){
    	(*item)->prev->next = (*item)->next;
	}

    free(item);
}

//The ReadyQ
TCB_t * ReadyQ;
