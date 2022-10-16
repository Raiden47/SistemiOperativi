#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>


int main (){
	
	char *argv;
	int pid;
	
	
	while (1){
	
		printf("Shell>");
		argv = scanf("%s",argv);
		printf("%s",argv);
		
		
		}
		
	return 0;
}
	
	/*
	if (pid	== -1){
		printf("processo di creazione fallito");
		return -1;
	} else if (pid == 0){
		a += 5;
		printf("\nSono il processo figlio: a=%d\n\n", a);
		printf("processo padre - %d\n",getppid());
		printf("il mio processo . %d\n",getpid());
		printf("processo figlio - %d\n",pid);
		sleep(20);
		_exit(1);
	} else if (pid > 0) {
		a -= 5;
		printf("\nSono il processo padre: a=%d\n\n", a);
		printf("processo figlio - %d\n", pid);
		printf("mio processo - %d\n", getpid());
		printf("processo padre - %d\n", getppid());
		//sleep (20);
		//wait (NULL);
		//sleep (10);
	}
	
	//sleep(100);
	*/
	
