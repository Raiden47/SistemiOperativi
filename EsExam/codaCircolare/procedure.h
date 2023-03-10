#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

#define DIM_BUFFER 8

#define N_CONS 8
#define N_PROD 8

typedef struct pc_buffer{
  int buffer [DIM_BUFFER];
  int testa;
  int coda;
};

void produci (struct pc_buffer *pc, int ds_sem);
void consuma (struct pc_buffer *pc, int ds_sem);

void init_buffer(struct pc_buffer *pc);
int num_generator ();

#endif //_PROCEDURE_H_
