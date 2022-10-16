#include <stdio.h>
#include <unistd.h>

int main(){
	
	int pid;
	pid = getpid();
	
	printf("hello, sono il processo %d\n", pid);
	printf("Il pid di mio padre e': %d\n", getppid());
	
	sleep(100);
	
	return 0;
}
