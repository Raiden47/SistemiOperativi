#include "stack.h"

#include <stdlib.h>

void StackInit(Stack * s, int dim) {
	//init da spostare dal main qui
	//s->dati = (Elem * ) malloc(sizeof(Elem)*dim);

	s->dim = dim;
	s->testa = 0;
	s->coda = 0;
}


void StackRemove(Stack * s) {
	//free (dati)
}

void StackPush(Stack * s, Elem e) {
	// da fare il lock sul mutex e le wait e
	// signal sulle condition variables 
	pthread_mutex_lock(&s->cv_prod, &s->mutex);
	//while (testa == dim) {fai la wait}
	s->dati[s->testa] = e;
	s->testa += 1;
	pthread_mutex_unlock(&s->cv_cons);
}


Elem StackPop(Stack * s) {

	int elemento;

	pthread_mutex_lock(&s->cv_cons, &s->mutex);
	elemento = s->dati[s->coda];
	for (int i = 0 ; i < s->testa ; i++){
		s->dati[i] = s->dati[i+1];
	}
	s->testa -= 1;
	pthread_mutex_unlock(&s->cv_prod);

	return elemento;
}

int StackSize(Stack * s) {
	int size;



	return size;
}
