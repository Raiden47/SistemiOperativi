#include <stdio.h>
#include <unistd.h>

#include "header.h"

void inizializza_vettore(VettoreProdCons * p) {
  pthread_mutex_init (&p->mutex_p,NULL);
  pthread_mutex_init (&p->mutex_c,NULL);
  pthread_cond_init (&p->cv_prod,NULL);
  pthread_cond_init (&p->cv_cons,NULL);

  // TO_CHECK: Inizializzazione vettore di stato
  for (int i = 0 ; i < DIM ; i++)
    p->stato[i] = LIBERO;
}

void produci(VettoreProdCons * p, int valore) {
  pthread_mutex_lock (&p->mutex_p);

  int pos = 0;
  while (p->stato[pos] != LIBERO && pos < DIM)
    pos++;
  while (pos == DIM)
    pthread_cond_wait (&p->cv_prod, &p->mutex_p);

  p->stato[pos] = INUSO;
  sleep(2);

  pthread_cond_signal (&p->cv_cons);
  pthread_mutex_unlock(&p->mutex_p);

  p->buffer[pos] = valore;
  p->stato[pos] = OCCUPATO;
}

int consuma(VettoreProdCons * p) {
  pthread_mutex_lock (&p->mutex_c);

  int pos = 0;
  int valore;
  while (p->stato[pos] != OCCUPATO && pos < DIM)
    pos++;
  while (pos == DIM)
    pthread_cond_wait (&p->cv_cons, &p->mutex_c);

  p->stato[pos] = INUSO;
  sleep(2);

  pthread_cond_signal (&p->cv_prod);
  pthread_mutex_unlock(&p->mutex_c);

  valore = p->buffer[pos];
  p->stato[pos] = LIBERO;

  return valore;
}

void rimuovi_vettore(VettoreProdCons * p) {
  pthread_mutex_destroy (&p->mutex_p);
  pthread_mutex_destroy (&p->mutex_c);
  pthread_cond_destroy (&p->cv_prod);
  pthread_cond_destroy (&p->cv_cons);
}


void inizializza_buffer(BufferMutuaEsclusione * p) {
  pthread_mutex_init (&p->mutex_s_buffer,NULL);
  pthread_mutex_init (&p->mutex_l_buffer,NULL);
  pthread_cond_init (&p->cv_l,NULL);
  pthread_cond_init (&p->cv_s,NULL);

  p->num_somme = 0;
}

void aggiorna_buffer(BufferMutuaEsclusione * p, int valore) {
  // TODO: incrementa il contenuto del buff
  pthread_mutex_lock (&p->mutex_s_buffer);

  while(p->num_somme == NUM_CONS)
    pthread_cond_wait (&p->cv_s,&p->mutex_s_buffer);

  sleep(2);
  p->buffer += valore;
  p->num_somme += 1;

  pthread_cond_signal (&p->cv_l);
  pthread_mutex_unlock (&p->mutex_s_buffer);
}

int stampa_valore(BufferMutuaEsclusione * p) {
  // TODO: Attendi il completamento di NUM_CONS consumazioni e stampa valore
  pthread_mutex_lock(&p->mutex_l_buffer);

  int valore;
  while (p->num_somme != NUM_CONS)
    pthread_cond_wait (&p->cv_l,&p->mutex_l_buffer);

  sleep(2);
  valore = p->buffer;
  p->num_somme = 0;

  pthread_cond_signal (&p->cv_s);
  pthread_mutex_unlock (&p->mutex_l_buffer);

  return valore;
}

void rimuovi_buffer(BufferMutuaEsclusione * p) {
  pthread_mutex_destroy (&p->mutex_s_buffer);
  pthread_mutex_destroy (&p->mutex_l_buffer);
}
