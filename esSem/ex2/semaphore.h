
#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_

#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>

#define MUTEX 1

int wait_sem (int id_sem, int num_sem);
int signal_sem (int id_sem, int num_sem);

#endif //_SEMAPHORE_H_
