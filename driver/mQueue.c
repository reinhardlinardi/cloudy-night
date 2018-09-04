#include "game/util/Queue.h"
#include "game/util/Stack.h"
#include <stdio.h>
#include "assert.h"
int main()
{
	//Test General cases
	printf("LET'S CHECK OUR QUEUE AND STACK! :D\n");
	printf("Testing basic assumptions..\n");
	printf("Testing empty cases..\n");
	Stack S;
	Queue Q;
	Queue_CreateEmpty(&Q);
	Stack_CreateEmpty(&S);
	assert(Stack_IsEmpty(S));
	assert(Queue_IsEmpty(Q));
	assert(Queue_NbElmt(Q)==0);

	printf("Testing All functions in Queue...\n");
	printf("Adding elements to queue..\n");
	Queue_Add(&Q,'a');
	assert(Queue_NbElmt(Q)==1);
	assert(!Queue_IsEmpty(Q));
	Queue_Add(&Q,'b');
	Queue_Add(&Q,'c');
	Queue_Add(&Q,'d');
	assert(!Queue_IsEmpty(Q));
	printf("Deleting elements in queue..\n");
	char cc;
	Queue_DelFirst(&Q,&cc);
	assert(cc=='a');
	Queue_DelLast(&Q,&cc);
	assert(cc=='d');
	Queue_DelFirst(&Q,&cc);
	Queue_DelFirst(&Q,&cc);
	assert(Queue_IsEmpty(Q));

	//Testing stack
	Queue_Add(&Q,'w');
	Queue_Add(&Q,'e');
	Queue_Add(&Q,'n');
	Queue_Add(&Q,'n');
	Queue_Add(&Q,'y');
	printf("Testing all functions in stack...\n");
	assert(Queue_NbElmt(Q)==5);
	printf("Pushin the stack...\n");
	Stack_Push(&S,Q);
	assert(!Stack_IsEmpty(S));
	Queue P;
	printf("Poppin the stack..\n");
	Stack_Pop(&S,&P);
	assert(Queue_NbElmt(P)==5);
	Queue_DelFirst(&P,&cc);
	assert(cc=='w');
	Queue_DelFirst(&P,&cc);
	Queue_DelFirst(&P,&cc);
	Queue_DelFirst(&P,&cc);
	Queue_DelFirst(&P,&cc);
	assert(Queue_IsEmpty(P));

	printf("ALL DONE :)\n");

	return 0;
}
