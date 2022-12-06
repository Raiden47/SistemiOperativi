#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "header.h"

#define NUM_PRODUTTORI 2
#define NUM_CONSUMATORI 20

#define PRODUZIONI 10

void * produttore(void *);
void * consumatore(void *);
void * visualizza(void *);

typedef struct parametri_consumatore{

    //  TODO: completare con i parametri da passare ai thread consumatori
    VettoreProdCons * pBuffer;
    BufferMutuaEsclusione * sBuffer;

} parametri_consumatore;

int main() {

    pthread_t produttori[NUM_PRODUTTORI];

    pthread_t consumatori[NUM_CONSUMATORI];

    pthread_t visualizzatore;

    printf("|--- DEBUG ---|--- Strutture non allocate ---|\n");

    VettoreProdCons * vettore = malloc(sizeof(struct VettoreProdCons));

    BufferMutuaEsclusione * buffer = malloc(sizeof(struct BufferMutuaEsclusione));

    printf("|--- DEBUG ---|--- Strutture allocate ---|\n");

    srand(getpid());

    // TODO: inizializzare le strutture e i relativi campi
    inizializza_vettore (vettore);
    inizializza_buffer (buffer);

    printf("|--- DEBUG ---|--- Risorse inizializzate ---|\n");

    pthread_attr_t attr;
    pthread_attr_init(&attr);
	  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    parametri_consumatore * parametri = malloc (sizeof(struct parametri_consumatore));

    printf("|--- DEBUG ---|--- Struttura allocata ---|\n");

    for(int i=0; i<NUM_PRODUTTORI; i++) {

        // TODO: creare thread produttori
        pthread_create (&produttori[i], &attr, produttore, (void * ) vettore);

    }

    printf("|--- DEBUG ---|--- Produttori creati ---|\n");

    for(int i=0; i<NUM_CONSUMATORI; i++) {

        // TODO: creare thread consumatori
        pthread_create (&consumatori[i], &attr, consumatore, (void * ) parametri);
    }

    printf("|--- DEBUG ---|--- Consumatori creati ---|\n");

    // TODO: creare thread visualizzatore
    pthread_create (&visualizzatore, &attr, visualizza, (void * ) buffer);

    printf("|--- DEBUG ---|--- Visualizzatore creato ---|\n");

    // TODO: join delle 3 tipologie di thread
    for (int i = 0 ; i <= NUM_PRODUTTORI; i++)
      pthread_join (produttori[i],NULL);
    for (int i = 0 ; i <= NUM_CONSUMATORI; i++)
      pthread_join (consumatori[i],NULL);
    pthread_join (visualizzatore,NULL);

    // TODO: deallocazione strutture
    rimuovi_vettore (vettore);
    rimuovi_buffer (buffer);

    free(parametri);
    free(buffer);
    free(vettore);

    pthread_exit(0);
    return 0;

}

void * produttore(void * p) {

    VettoreProdCons * vettore = (VettoreProdCons * ) p;

    for(int i=0; i<PRODUZIONI; i++) {

        int valore = rand() % 10;

        printf("[PRODUTTORE] Produzione: %d\n", valore);

        produci(vettore, valore);
    }

    //return NULL;
    pthread_exit(0);
}

void * consumatore(void * p) {

    parametri_consumatore * parametri = (parametri_consumatore * ) p;

    int valore;

    // TODO: consumare
    valore = consuma (parametri->pBuffer);

    printf("[CONSUMATORE] Consumazione: %d\n", valore);

    // TODO: aggiornare
    aggiorna_buffer (parametri->sBuffer, valore);

    //return NULL;
    pthread_exit(0);
}

void * visualizza(void * p) {

     BufferMutuaEsclusione * buf = (BufferMutuaEsclusione * ) p;

     for (int i=0; i< (NUM_PRODUTTORI*PRODUZIONI)/NUM_CONS; i++) {

             int val;

             // TODO: stampare
             val = stampa_valore(buf);

             printf("[VISUALIZZATORE]: La somma degli elementi consumati è: %d\n",val);

     }

     //return NULL;
     pthread_exit(0);

}
