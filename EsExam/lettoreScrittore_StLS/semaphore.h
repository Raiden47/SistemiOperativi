#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_

#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>

#define MUTEX_L 0
#define MUTEX_S 1
#define MUTEX 2
#define SYNCH 3

int wait_sem (int ds_sem, int num_sem);
int signal_sem (int ds_sem, int num_sem);

#endif //_SEMAPHORE_H_
