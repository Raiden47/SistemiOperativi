#include "common.h"

void printer(int msgq_print)
{
	int counter = 1, i;
	//TODO definizione messaggio da ricevere


	printf("[printer] Printer Ready...\n");

	while(1)
	{
		//TODO ricezione messaggio contenente il buffer

		for(i=0; i<BUFFER_DIM; i++)
		{
			// TODO se in posizione i-ma del buffer c'è un pid -1 il printer deve terminare

			printf("{printer}\t[%u] %u\n", counter++, /*TODO stampa elemento i-mo del buffer*/);
		}
	}
}
