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

	char *path = "/bin/ls";

	int argc = 0;

	int pid;
	int st;

	while (1) {
		printf("Shell> ");

		//input dell'intera stringa
		fgets(cmd,N,stdin);

		token = strtok(cmd, " ");

		//tokenizzazione del comando da shell
		while (token != NULL) {
			argv[argc] = token;
			// strcpy(argv[argc], token);
			printf("argv[%d] = %s\n", argc,argv[argc]);
			argc += 1;
			token = strtok(NULL, " ");
		}

		//inserisce null in ultima posizione
		// argv[argc] = NULL;
		// printf("Stampo il comando per intero dall'array\n\t");
		for (int i = 0 ; i < argc ; i += 1)
			printf("[%d]%s \n",i,argv[i]);
		// printf("\n");
/*
		//creazione di un processo
		pid = fork ();

		if (pid == -1){
			printf("processo di creazione fallito \n");
			return -1;
		} else if (pid == 0) {
			//processo figlio
			// execv(path,argv);
			execvp(argv[0],argv);
			fprintf(stderr,"Exec fallita\n");
			_exit(1);
		} else if (pid > 0) {
			//processo padre
			sleep(20);
			wait (&st);
			printf("Esecuzione del comando terminata ");
			if ((char)st==0)
				printf("con stato: %d\n\n",st>>8);
			else
				printf("involontariamente!\n\n");
*/
		argc = 0;
		sleep(1);
	}


	return 0;
}
