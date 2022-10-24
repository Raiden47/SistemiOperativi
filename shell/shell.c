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


	while (1) {
		printf("Shell> ");
		fgets(cmd,N,stdin);

		token = strtok(cmd, " ");

		while (token != NULL) {
			printf("%s\n", token);
			token = strtok(NULL, " ");
		}




		sleep(1);
	}


	return 0;
}
