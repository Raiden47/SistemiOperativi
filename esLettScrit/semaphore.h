#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_

#include <sys/sem.h>
#include <sys/types.h>
#include sys/ipc.h>

#define MUTEXL 0
#define SYNCH 1

void wait_sem (int ds_sem, int num_sem);
void signal_sem (int ds_sem, int num_sem);

#endif //_SEMAPHORE_H_
