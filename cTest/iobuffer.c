#include <stdio.h>

//il buffer deve essere coerente con il riempimento 
//della stringa che dichiariamo
#define BUFFER 50

int main (){
	char *pString;
	char string [50];

	printf("inserisci una stringa in pString: ");
	//fgets(<variabile>, <buffer>, <standardInput>); 
	fgets(pString,BUFFER,stdin);
	printf("\n");
	printf("inserisci una stringa in string: ");
	fgets(string, BUFFER, stdin);
	printf("\n");


	printf("\npstring: %s", pString);
	printf("\nstring: %s\n", string);

	return 0;
}

