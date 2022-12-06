#ifndef _HEADER_
#define _HEADER_

#include <pthread.h>

#define DIM 3

#define NUM_CONS 5

#define LIBERO 0
#define INUSO 1
#define OCCUPATO 2

typedef struct VettoreProdCons{

    int buffer[DIM];

    int stato[DIM];

    // TODO: completare campi della struttura per la gestione in mutua esclusione del pool di buffer
    pthread_mutex_t mutex_p;
    pthread_mutex_t mutex_c;
    pthread_cond_t cv_prod;
    pthread_cond_t cv_cons;

} VettoreProdCons;

typedef struct BufferMutuaEsclusione{

    int buffer;
    int num_somme;

     // TODO: completare campi della struttura per la gestione in mutua esclusione del buffer
     pthread_mutex_t mutex_s_buffer;
     pthread_mutex_t mutex_l_buffer;
     pthread_cond_t cv_l;
     pthread_cond_t cv_s;

} BufferMutuaEsclusione;

void inizializza_vettore(VettoreProdCons * p);
void produci(VettoreProdCons * p, int valore);
int consuma(VettoreProdCons * p);
void rimuovi_vettore(VettoreProdCons * p);

void inizializza_buffer(BufferMutuaEsclusione * p);
void aggiorna_buffer(BufferMutuaEsclusione * p, int valore);
void rimuovi_buffer(BufferMutuaEsclusione * p);

int stampa_valore(BufferMutuaEsclusione * p);


#endif
