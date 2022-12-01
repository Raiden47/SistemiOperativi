#include "semaphore.h"

void wait_sem (int ds_sem, int num_sem) {
	struct sembuf sem_buf;
	sem_buf.sem_num = num_sem;
	sem_buf.sem_flg = 0;
	sem_buf.sem_op = -1;
	semop(ds_sem, &sem_buf,1);
}

void signal_sem (int ds_sem, int num_sem) {
	struct sembuf sem_buf;
	sem_buf.sem_num = num_sem;
	sem_buf.sem_flg = 0;
	sem_buf.sem_op = 1;
	semop(ds_sem, &sembuf, 1);
}
