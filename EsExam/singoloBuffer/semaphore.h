#ifndef __SEMAPHORE_H__
#define __SEMAPHORE_H__

#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>

#define PRODUCI 0
#define CONSUMA 1

int wait_sem (int id_sem, int num_sem);
int signal_sem (int id_sem, int num_sem);

#endif //__SEMAPHORE_H__
