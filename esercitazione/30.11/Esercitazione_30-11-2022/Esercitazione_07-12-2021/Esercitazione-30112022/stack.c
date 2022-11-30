#include "stack.h"

#include <stdlib.h>
#include <stdio.h>

void StackInit(Stack * s, int dim) {
	//init da spostare dal main qui
	s->dati = (Elem * ) malloc(sizeof(Elem)*dim);
	pthread_mutex_init(&s->mutex, NULL);
	pthread_cond_init(&s->cv_prod, NULL);
	pthread_cond_init(&s->cv_cons, NULL);

	s->dim = dim;
	s->testa = 0;
	s->coda = 0;

	// printf("DEBUG\t->\ts->dim = %d\tdim = %d \n",s->dim, dim );
}


void StackRemove(Stack * s) {
	free (s->dati);
	pthread_mutex_destroy(&s->mutex);
	pthread_cond_destroy(&s->cv_prod);
	pthread_cond_destroy(&s->cv_cons);
}

void StackPush(Stack * s, Elem e) {

	pthread_mutex_lock(&s->mutex);

	while(s->testa == s->dim)
		pthread_cond_wait(&s->cv_prod, &s->mutex);

	// printf("<--- DEBUG\ts->testa = %d --->\n", s->testa);
	s->dati[s->testa] = e;
	s->testa++;
	// printf("<--- DEBUG\ts->testa = %d --->\n", s->testa);
	pthread_cond_signal(&s->cv_cons);
	pthread_mutex_unlock(&s->mutex);
}


Elem StackPop(Stack * s) {

	int elemento;

	pthread_mutex_lock(&s->mutex);

	while (s->testa == s->coda)
		pthread_cond_wait(&s->cv_cons, &s->mutex);

	elemento = s->dati[s->coda];
	for (int i = 0 ; i < s->testa ; i++){
		s->dati[i] = s->dati[i+1];
	}
	s->testa--;
	pthread_cond_signal(&s->cv_prod);
	pthread_mutex_unlock(&s->mutex);

	return elemento;
}

int StackSize(Stack * s) {
	// int size;

	return s->testa;

	// return size;
}
