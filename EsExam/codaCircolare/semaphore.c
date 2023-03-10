#include "semaphore.h"


int wait_sem (int id_sem, int num_sem){
  int res;
  struct sembuf sem_buf;

  sem_buf.sem_num = num_sem;
  sem_buf.sem_flg = 0;
  sem_buf.sem_op = -1;

  res = semop(id_sem, &sem_buf, 1);

  return res;
}


int signal_sem (int id_sem, int num_sem){
  int res;
  struct sembuf sem_buf;

  sem_buf.sem_num = num_sem;
  sem_buf.sem_flg = 0;
  sem_buf.sem_op = 1;

  res = semop(id_sem, &sem_buf, 1);

  return res;
}
