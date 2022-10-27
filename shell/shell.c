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
	char *lib;

	int argc = 0;
	int cont;

	int pid;
	int st;

	while (1) {
		printf("Shell> ");

		//input dell'intera stringa
		fgets(cmd,N,stdin);

		token = strtok(cmd, " ");

		//creo il path
		// strcat(path,token);
		// printf("il path e': %s", path);

		//tokenizzazione del comando da shell
		cont = 0;
		argv[0]=NULL;
		while (token != NULL) {
			// strcpy(argv[argc], token);
			if (cont > 0){
				argv[argc] = token;
				printf("argv[%d] = %s\n", argc,argv[argc]);
				argc += 1;
			} else
				lib = token;
			cont += 1;
			token = strtok(NULL, " ");

		}

		//inserisce null in ultima posizione
		argv[argc] = NULL;
		// argc += 1;
		// printf("Stampo il comando per intero dall'array\n\t");
		printf("\n[lib] %s\n", lib);
		for (int i = 0 ; i < argc ; i += 1)
			printf("[%d]%s \n",i,argv[i]);
		// printf("\n");

		//creazione di un processo
		pid = fork ();

		if (pid == -1){
			printf("processo di creazione fallito \n");
			return -1;
		} else if (pid == 0) {
			//processo figlio
			// execv(path,argv);
			execvp(lib,argv);
			fprintf(stderr,"Exec fallita\n");
			_exit(1);
		} else if (pid > 0) {
			//processo padre
			sleep(1);
			wait (&st);
			printf("Esecuzione del comando terminata ");
			if ((char)st==0)
				printf("con stato: %d\n\n",st>>8);
			else
				printf("involontariamente!\n\n");

		argc = 0;
		sleep(1);
	}
}

return 0;
}
