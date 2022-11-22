#include <stdio.h>
#include <errno.h>

int wait_sem (int id_sem, int num_sem){
  int err;
  struct sembuf sem_buf;

  sem_buf.sem_num = num_sem;
  sem_buf.sem_flg = 0;
  sem_buf.sem_op = -1;
}
