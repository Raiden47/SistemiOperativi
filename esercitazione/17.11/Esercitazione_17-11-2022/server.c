#include "common.h"
#include <stdio.h>

void server(int msgq_guest, int msgq_print)
{
	int i;
	
	/* TODO Definizione Messaggio da ricevere dal proc. client */

	/* TODO Definizione Messaggio da inviare al proc. printer */


	printf("[server ] Server ready...\n");
	while(1)
	{
		for(i=0; i<BUFFER_DIM; i++)
		{
			/*TODO Ricezione del messaggio di richiesta*/
			
			/*TODO se il messaggio è di tipo fine, inserisce -1 in posizione i-ma e termina

			/*TODO Accodamento della richiesta nel buffer */
			
		}
		
	/*TODO Invio del messaggio con il buffer completo al proc. printer */
		
	}
}
