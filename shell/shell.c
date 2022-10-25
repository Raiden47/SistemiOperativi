#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define N 128

int main (){

	char cmd [N];
	char *token;
	char *argv [N];

	int argc;

	int pid;

	while (1) {
		printf("Shell> ");

		//input dell'intera stringa
		fgets(cmd,N,stdin);

		token = strtok(cmd, " ");

		//tokenizzazione del comando da shell
		while (token != NULL) {
			argv[argc] = token;
			printf("argv[%d] = %s\n", argc,argv[argc]);
			argc += 1;
			token = strtok(NULL, " ");
		}

		//creazione di un processo
		pid = fork ();

		if (pid == -1){
			printf("processo di creazione fallito \n");
			return -1;
		} else if (pid == 0) {
			//processo figlio
			char *path = "/bin/";

			execv(strcat(path, argv[0]),argv);
			//execvp(argv[0],argv);
			fprintf(stderr,"Exec fallita\n");

			_exit(1);
		} else if (pid > 0) {
			//processo padre
			wait (NULL);
			printf("Esecuzione del comando terminata!\n");
		}

		argc = 0;
		sleep(1);
	}


	return 0;
}
