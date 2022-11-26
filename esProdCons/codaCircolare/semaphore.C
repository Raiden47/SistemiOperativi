#include <errno.h>
#include <stdlib.h>

#include "semaphore.h"

int wait_sem (int id_sem, int num_sem){
  int err;
  struct sembuf sem_buf;

  sem_buf.sem_num = num_sem;
  sem_buf.sem_flg = 0;
  sem_buf.sem_op = -1;

  err = semop(id_sem, &sem_buf, 1);

  if (err < 0) {perror("Errore WAIT");_exit(1);}

  return err;
}

int signal_sem (int id_sem, int num_sem){
  nt err;
  struct sembuf sem_buf;

  sem_buf.sem_num = num_sem;
  sem_buf.sem_flg = 0;
  sem_buf.sem_op = 1;

  err = semop(id_sem, &sem_buf, 1);

  if (err < 0) {perror("Errore SIGNAL");_exit(1);}

  return err;
}
