#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

#define N_LETTORI 5
#define N_SCRITTORI 5

typedef long msg;

typedef struct {
	int num_lettori;
	msg messaggio;
}buffer;

void lettore (int, buffer*);
void scrittore (int, buffer*);


#endif //_PROCEDURE_H_
