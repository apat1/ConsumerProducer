/***************************************************************************************
 * Authors:		Jeffrey Cirka, Andy Pat
 * Date:		04/09/2013
 * ASU email:	jscirka@asu.edu, apat1@asu.edu
 * Course:		CSE 430 TTH 4:30-5:45
 * Project#:	3
 * Language:	c
 * Compiler:	gcc
 * Description:
 * 		This file contains an implemention of a set of thread to test the semaphores.
 ***************************************************************************************
 */

#include <stdio.h> //for various i/o operations
#include <stdlib.h> //for malloc

extern void* memset(void*, int, size_t); //resolves compile warning: implicit declaration of function ‘memset’ in tcb.h

#include "sem.h"

// Method 1
// Each thread is an infinite loop, and has a critical section using a mutex semaphore.
// The thread gets into the CS, prints values of global and local variables (like proj1), sleeps and exists the CS.
// Then it prints a message and sleeps and then repeats.

// Function prototypes
void t1();
void t2();
void t3();
void t4();
void consume1(Item * item);
void consume2(Item * item);

Sem sem;
int x = 0;
Sem full;
full->count = N;
Sem empty;
empty->count = 0;
Sem mutex;
mutex->count = 1;

int main(){
    InitSem(&sem, 1);

    printf("Method1: Starting threads t1, t2, t3, t4.\n");
	start_thread(&t1);
	start_thread(&t2);
	start_thread(&t3);
	start_thread(&t4);
	run();
	return 0;
}

void t1(){
	int y = 0;
    while(1){
		printf("t1 entering CS...\n");

        P(&sem);

        //BEGIN CS
        printf("t1 entered CS\n");
        x++;
        y++;
        printf("t1 incremented global x: x=%d\n", x);
        printf("t1 incremented local y: y=%d\n", y);
        sleep(1);
        printf("t1 exit CS\n");
        //END CS

        V(&sem);
    }
}

void t2(){
	int y = 0;
    while(1){
		printf("t2 entering CS...\n");

        P(&sem);

        //BEGIN CS
        printf("t2 entered CS\n");
        x++;
        y++;
        printf("t2 incremented global x: x=%d\n", x);
        printf("t2 incremented local y: y=%d\n", y);
        sleep(1);
        printf("t2 exit CS\n");
        //END CS

        V(&sem);
    }
}

void t3(){
	int y = 0;
    while(1){
		printf("t3 entering CS...\n");

        P(&sem);

        //BEGIN CS
        printf("t3 entered CS\n");
        x++;
        y++;
        printf("t3 incremented global x: x=%d\n", x);
        printf("t3 incremented local y: y=%d\n", y);
        sleep(1);
        printf("t3 exit CS\n");
        //END CS

        V(&sem);
    }
}

void t4(){
	int y = 0;
    while(1){
		printf("t4 entering CS...\n");

        P(&sem);

        //BEGIN CS
        printf("t4 entered CS\n");
        x++;
        y++;
        printf("t4 incremented global x: x=%d\n", x);
        printf("t4 incremented local y: y=%d\n", y);
        sleep(1);
        printf("t4 exit CS\n");
        //END CS

        V(&sem);
    }
}

// Method 2
// Write a producer consumer solution, using the code given in class (see notes).
// Run 2 producers and 2 consumers.

void consume1(Item * item){
    while(1){
        P(empty);
        printf("Consumer 1 obtaining mutex...\n");
        P(mutex);
        printf("Consumer 1 obtained mutex...\n");
        item = buffer[out];
        printf("Consumer 1 got item from buffer...Item: item->value=%d\n", item->value);
        out = (out + 1)mod(N);
        V(mutex);
        printf("Consumer 1 released mutex...\n");
        V(full);
    }
}

void consume2(Item * item){
    while(1){
        P(empty);
        printf("Consumer 2 obtaining mutex...\n");
        P(mutex);
        printf("Consumer 2 obtained mutex...\n");
        item = buffer[out];
        printf("Consumer 2 got item from buffer...Item: item->value=%d\n", item->value);
        out = (out + 1)mod(N);
        V(mutex);
        printf("Consumer 2 released mutex...\n");
        V(full);
    }
}

