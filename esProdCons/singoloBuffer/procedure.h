#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

#define SPAZIO_DISPONIBILE 0
#define MESSAGGIO_DISPONIBILE 1

void consumatore (int *shm_buffer, int ds_sem);
void produttore (int *shm_buffer, int ds_sem);

#endif //_PROCEDURE_H_
