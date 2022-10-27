#include <stdio.h>

#define N 50

int main (){
	char *pString;
	char string [50];

	printf("inserisci una stringa in pString: ");
	scanf("%s",pString);
	printf("inserisci una stringa in string: ");
	scanf("%s",string);

	printf("\npstring: %s", pString);
	printf("\nstring: %s\n", string);

	return 0;
}

