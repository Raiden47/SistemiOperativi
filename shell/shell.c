#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define N 100

int main (){

	char argv[N];
	
	while (1){
		printf ("Shell>");
		scanf("%s",argv);
		printf("%s\n",argv);
	}
	return 0;
}
