#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int main (){
	
	int pid;
	int st;
	int a;
	
	a = 10;
	
	pid = fork();
	
	if (pid == -1){
		printf("\nProcesso di creazione fallito\n");
		return -1
	}
	
	if (pid == 0){
		a += 5;
		printf("\nSono il processo figlio: a=%d\n", a);
		printf("Mio PID: %d\n", getpid());
		printf("Il PID di mio padre e': %d\n", getppid());
		sleep(20);
		_exit(1);				//Ricongiungimento delle fork, ritorna il valore tra parentesi
	} else if (pid > 0){
		a -= 5;
		printf("\nSono il processo padre: n=%d\n", a);
		printf("\nMio PID: %d", getpid());
		printf("\nI PID di mio padre: %d\n", getppid());
		sleep(10);
		//wait(NULL);
		wait (&st);
		printf("Il figlio %d ha terminato ", pid);
		if ((char)st==0){							//trucchetto per beccare il byte meno significativo 
			printf("con stato %d \n\n", st>>8)		// st >> 8 : shift bitwise, fa lo shift della variabile 
		} else {
			printf("involontariamente");
		}
	}	
	
	return 0;
}
	
