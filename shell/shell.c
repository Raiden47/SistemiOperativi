#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define N 100

typedef char string [N];

int main (){

	string s;
	string argv[N];
	int i = 0;
	
	while (1){
		printf ("Shell>");
		scanf("%s",s);
		
		/*
		while (s != '\0'){
			//strcpy(s, argv[i]);
			//argv[i] = s;
			//i += 1;
			
		}
		*/
		
		
//		printf("%s\n",s);
		
		
		sleep(1);
	}
	return 0;
}
