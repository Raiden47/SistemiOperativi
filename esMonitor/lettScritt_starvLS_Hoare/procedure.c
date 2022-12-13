#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "procedure.h"

void init_buffer (struct lettScritt * ls){
  ls->l_buffer = 0;
  ls->s_buffer = 0;
}


void inizio_lettura (struct lettScritt * ls){
  printf("|- [%d] Sono entrato nel monitor -|\n", getpid());
  enter_monitor(&ls->m);

  if (&ls->s_buffer > 0){
    wait_condition(&ls->m, CV_LETT);
    printf("... Attendo che gli scrittori lascino il buffer\n");
  }

  ls->l_buffer += 1;
  signal_condition(&ls->m,CV_LETT);
  leave_monitor(&ls->m);
}


void fine_lettura (struct lettScritt * ls){
  enter_monitor(&ls->m);
  ls->l_buffer -= 1;

  if (ls->l_buffer == 0){
    signal_condition(&ls->m, CV_SCRITT);
  }

  leave_monitor(&ls->m);
  printf("|- [%d] Sono uscito dal monitor -|\n", getpid());
}


void inizio_scrittura (struct lettScritt * ls){
  printf("|- [%d] Sono entrato nel monitor -|\n", getpid());
  enter_monitor(&ls->m);

  if (&ls->l_buffer > 0){
    wait_condition(&ls->m,CV_SCRITT);
    printf("... Attendo che i lettori lascino il buffer\n");
  }

  ls->s_buffer += 1;
  signal_condition(&ls->m,CV_SCRITT);
  leave_monitor(&ls->m);
}


void fine_scrittura (struct lettScritt * ls){
  enter_monitor(&ls->m);
  ls->s_buffer -= 1;

  if(queue_condition(&ls->m,CV_SCRITT)){
    signal_condition(&ls->m,CV_SCRITT);
  } else {
    signal_condition(&ls->m, CV_LETT);
  }

  leave_monitor(&ls->m);
  printf("|- [%d] Sono uscito dal monitor -|\n", getpid());

}

void lettura (struct lettScritt * ls){
  inizio_lettura(ls);

  sleep(2);
  printf("<--- Valore letto [%d] --->\n", ls->buffer);

  fine_lettura(ls);
}


void scrittura (struct lettScritt * ls, int valore){
  inizio_scrittura(ls);

  sleep(2);
  ls->buffer = valore;
  printf("<--- Valore scritto [%d] --->\n", ls->buffer);

  fine_scrittura(ls);
}



int genera_numero (){
  return (rand()%90+10);
}
