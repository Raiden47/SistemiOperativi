#ifndef __SEMAPHORE_H__
#define __SEMAPHORE_H__

#include <sys/wait.h>
#include <sys/type.h>
#include <sys/sem.h>
#include <sys/ipc.h>

int wait_sem (int id_sem, int num_sem);
int signal_sem (int id_sem, int num_sem);

#endif // __SEMAPHORE_H__
