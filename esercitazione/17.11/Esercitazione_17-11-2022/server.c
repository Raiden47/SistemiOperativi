#include "common.h"
#include <stdio.h>

void server(int msgq_guest, int msgq_print)
{
	int i;
	Buf buf;
	/* TODO Definizione Messaggio da ricevere dal proc. client */
	msg mess;
	/* TODO Definizione Messaggio da inviare al proc. printer */
	msg_buff mBuff;
	mBuff.type = PRINT_REQ;

	printf("[server ] Server ready...\n");
	while(1)
	{
		for(i=0; i<BUFFER_DIM; i++)
		{
			/*TODO Ricezione del messaggio di richiesta*/
			msgrcv(msgq_guest,&mess, SIZEOF(mess),0 ,0)
			if (mess.type == EXIT_REQ){
				
			}
			/*TODO se il messaggio è di tipo fine, inserisce -1 in posizione i-ma e termina

			/*TODO Accodamento della richiesta nel buffer */

		}

	/*TODO Invio del messaggio con il buffer completo al proc. printer */

	}
}
