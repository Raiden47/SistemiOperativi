#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

//Shmem Libraries
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>

int main () {

  //Shared memory key
  key_t k = IPC_PRIVATE;

  //shmget (key_t , sizeof(<type>) , <ipc_config>);
  //  -key_t -> chiave per identificare la shm
  //  -size -> dimensione in byte della memoria condivisa
  //  -shm_config -> modalità di creazione e permessi intervallati da |
  //      (IPC_CREAT, IPC_EXCL, permessi).
  //La funzione restituisce un intero identificatore per l'utilizzo dellla
  //memoria condivisa.
  int shm = shmget(k, sizeof(int), IPC_CREAT|0664);

  if (shm < 0) {
    perror ("\n<--- ERRORE SHMGET [1]--->");
    exit(1);
  }

  //shmat (shm_id , const void *address, shm_config);
  //  -shm_id -> identificatore del segmento di memoria
  //  -shm_address -> indirizzo dell'area di memoria del processo
  //      al quale collegare il il segmento di memoria condivisa.
  //      Il kernel proverà a trovare una regione di memoria non mappata.
  //La funzione restituisce l'inddirizzo di memoria nello spazio di
  //indirizzamento del processo chiamante
  int *p = (int*) shmat(shm,NULL,0);
  if(p==(void*)-1) {
    perror ("\n<--- ERRORE SHMGET [2]--->");
    exit(1);
  }
  *p = 111;

  printf("Dettagli shared memory creata:\n");
  printf("...Chiave IPC shm: %d\n", k);
  printf("...Descrittore shm: %d\n", shm);
  printf("...Inizializzazione shm: %d\n", *p);
  printf("...Indirizzo dopo l'attach: %p\n", p);


  key_t pid = fork();

  if (pid < 0){
    perror ("\n<--- ERRORE --->\n");
  } else if (pid == 0 ) {
    //processo figlio
    *p = 242;
    exit (0);
  }  if (pid > 0) {
    wait(NULL);
    printf ("Contenuto SHM: %d\n", *p);
  }

  //shmctl (shm_id, int cmd, struct shmid_ds *buf);
  //  -shm_id -> descrittore della memoria condivisa
  //  -cmd -> specifica il comando da eseguire:
  //      IPC_STAT copia le informazioni di stato della memoria
  //          condivisa shm_id in shmid_ds puntata da *buf
  //      IPC_SET permette di scrivere i valori di qualche membro della
  //          struttura shmid_ds puntata da *buf
  //      IPC_RMID marca da eliminare la shared memory rimuovendola quando
  //          non ci sono processi collegati
  //      SHM_LOCK impedisce che il segmento di memoria condiviso
  //          swappato
  //  -shmid_ds *buf -> puntatore ad un astruttura di tipo shmid_ds
  //      parametro da utilizzare nel caso di comando di:
  //           comando in ingresso IPC_SET
  //           comando in uscita IPC_STAT
  //Rimozione della shared memory
  shmctl(shm,IPC_RMID, NULL);

  return 0;
}
