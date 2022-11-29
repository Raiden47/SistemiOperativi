#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "semaphore.h"

int wait_sem(int ds_sem, int num_sem){
  int err;
  struct sembuf sem_buf;
  sem_buf.sem_num = num_sem;
  sem_buf.sem_flg = 0;
  sem_buf.sem_op = -1;
  err=semop(ds_sem,&sem_buf,1);
  return err;
}

int signal_sem(int ds_sem, int num_sem){
  int err;
  struct sembuf sem_buf;
  sem_buf.sem_num = num_sem;
  sem_buf.sem_flg = 0;
  sem_buf.sem_op = 1;
  err=semop(ds_sem,&sem_buf,1);
  return err;
}
