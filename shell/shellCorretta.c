#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define N 256

int main (){

	char cmd[N];
	char *token;
	char *argv [N];

	char *path = "/bin/";
	char *lib;

	int argc;
	int cont;

	int pid;
	int st;

	while (1) {
		printf("Shell> ");

		//input dell'intera stringa
		fgets(cmd,N,stdin);

		// rimuovo l'a capo finale di quando premo invio
		cmd[strcspn(cmd, "\r\n")] = 0;
    printf("%s\n", cmd);

		//resetto il numero di argomenti che ricevo in input quando
		// premo invio per il comando
		argc = 0;

		token = strtok(cmd, " ");

		if (token == NULL) // ho solo premuto invio, non ho comandi
			continue;

		//tokenizzazione del comando da shell
		// nell'argomento 0 metto il nome del programma, ovvvero il
		// primo token preso a riga 38
		argv[0]=token;

		// aggiorno il numero di argc per passare agli altri argomenti
		argc ++;

		// controllo sugli argomenti dal secondo in poi
		while (token != NULL) {
			token = strtok(NULL, " "); // metto in token il parametro successivo
			argv[argc] = token;
			printf("argv[%d] = %s\n", argc,argv[argc]);
			argc ++;
		}

		//inserisce null in ultima posizione
		argv[argc] = NULL;

		//printf("Stampo il comando per intero dall'array\n\t");
		//printf("\n[lib] %s\n", lib);
		for (int i = 0 ; i < argc ; i ++)
			printf("[%d]%s \n",i,argv[i]);

		//creazione di un processo
		pid = fork();

		if (pid == -1){
			printf("processo di creazione fallito \n");
			return -1;
		} else if (pid == 0) {
			//processo figlio
			execvp(argv[0],argv);
			fprintf(stderr,"Exec fallita\n");
			_exit(1);
		} else if (pid > 0) {
			//processo padre
			sleep(1);
			wait (&st);
			printf("Esecuzione del comando terminata ");
			if ((char)st==0)
				printf("con stato: %d\n",st>>8);
			else
				printf("involontariamente!\n\n");
		sleep(1);
	}
}

return 0;
}
