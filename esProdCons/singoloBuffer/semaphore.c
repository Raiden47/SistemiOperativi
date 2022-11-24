#include <stdio.h>
#include <stdlib.h>

#include "semaphore.h"

int wait_sem(int id_sem, int num_sem){
  int err;
  struct sembuf sem_buf;

  sem_buf.sem_num = num_sem;
  sem_buf.sem_flg = 0;
  sem_buf.sem_op = -1;

  err = semop(id_sem, &sem_buf, 1);

  if (err < 0)
    perror("Errore Wait");

  return err;
}

int signal_sem (int id_sem, int num_sem){
  int err;
  struct sembuf sem_buf;

  sem_buf.sem_num = num_sem;
  sem_buf.sem_flg = 0;
  sem_buf.sem_op = 1;

  err = semop(id_sem, &sembuf, 1);
  if (err < 0)
    perror("Errore SIGNAL");

  return err;
}
