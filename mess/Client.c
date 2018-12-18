#include "header.h" 
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <wait.h>

int main(){
	
	printf("[CLIENT STARTED]\n");
	
	key_t queueClient = ftok(FTOK_PATH_CLIENT_OP, FTOK_CHAR_CLIENT_OP);

	int clientID = msgget(queueClient, IPC_CREAT | 0664);
	if(clientID == -1) { perror("msgget client fallita\n"); exit(1); }
	
	for(int i = 0; i < NUM_MSG; ++i){
	
		int result = 0;
		int clientOperation = getpid();

		struct MSGClient Client;
		size_t ClientOpDim = sizeof(struct MSGClient) - sizeof(long);
		
		//Sending to Balancer
		Client.process = CTOB;
		Client.operation = clientOperation;
		
		result = msgsnd(clientID, &Client, ClientOpDim, 0);
		if(result == -1) { perror("msgsend client fallita Client to Balancer [CTOB]\n"); exit(1); }	
	
		printf("[CLIENT] is sending operation [N %d] [Index: %d] to [BALANCER]\n",clientOperation, i);

	}

	return 0;
}
