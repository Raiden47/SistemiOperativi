#ifndef __HEADER__
#define __HEADER__

#define N_THREAD 5

#include <pthread.h>

typedef int Elem;

typedef struct Stack {
	Elem * dati;	// puntatore ad un vettore dinamico di elementi
	int dim;		// dimensione dello Stack

	int testa;
	int coda;

	pthread_mutex_t mutex;
	pthread_cond_t cv_prod;
	pthread_cond_t cv_cons;

} Stack;

void StackInit(Stack * s, int dim);	// alloca dinamicamente "dim" elementi
void StackRemove(Stack * s);		// dealloca gli elementi
void StackPush(Stack * s, Elem e);	// inserimento nello Stack
Elem StackPop(Stack * s);		// estrazione dallo Stack
int StackSize(Stack * s);		// ritorna il numero attuale di elementi


#endif
