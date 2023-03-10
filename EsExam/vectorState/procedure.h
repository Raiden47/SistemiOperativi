#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

#define N_PROD 10
#define N_CONS 10

#define DIM_BUFFER 5

#define FREE 0
#define IN_USE 1
#define FULL 2

typedef struct pc_buffer{
  int buffer [DIM_BUFFER];
  int state [DIM_BUFFER];
};

void produci (int ds_sem, struct pc_buffer *pc);
void consuma (int ds_sem, struct pc_buffer *pc);

int num_gen();
void init_buffer (struct pc_buffer *pc);
int search_pos (struct pc_buffer *pc, int st);

#endif //_PROCEDURE_H_
