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
	
	printf("[BALANCER STARTED]\n");

	key_t queueServer = ftok(FTOK_PATH_SERVER_RIS, FTOK_CHAR_SERVER_RIS);
	key_t queueClient = ftok(FTOK_PATH_CLIENT_OP, FTOK_CHAR_CLIENT_OP);	

	int serverID = msgget(queueServer, IPC_CREAT | 0664);
	if(serverID == -1) { perror("msgget server fallita\n"); exit(1); }

	int clientID = msgget(queueClient, IPC_CREAT | 0664);
	if(clientID == -1) { perror("msgget client fallita\n"); exit(1); }

	int numProcessi = NUM_MSG * NUM_CLIENT;

	for(int i = 0; i < numProcessi; ++i){
	
		int result = 0;
		int clientOperation;

		struct MSGServer Server;
		struct MSGClient Client;

		size_t ServerOpDim = sizeof(struct MSGServer) - sizeof(long);
		size_t ClientOpDim = sizeof(struct MSGClient) - sizeof(long);
	
		
		//Receive from Client for Server 1
		result = msgrcv(clientID, &Client, ClientOpDim, CTOB, 0);
		if(result == -1) { perror("msgreceive balancer fallita Client to BALANCER [CTOB]\n"); exit(1); }
		printf("[BALANCER] is receiving operation from [CLIENT]\n");	

		//Sending to Server 1
		Server.process = BTOS1;	
		clientOperation = Client.operation;
		Server.operation = clientOperation;
		
		result = msgsnd(serverID, &Server, ServerOpDim, 0);
		if(result == -1) { perror("msgsend balancer fallita Balancer to Server [BTOS]\n"); exit(1); }
		printf("[BALANCER] is sending operation [N: %d] to [SERVER 1]\n", clientOperation);	

		//Receive from Client for Server 2
		result = msgrcv(clientID, &Client, ClientOpDim, CTOB, 0);
		if(result == -1) { perror("msgreceive balancer fallita Client to BALANCER [CTOB]\n"); exit(1); }
		printf("[BALANCER] is receiving operation from [CLIENT]\n");

		//Sending to Server 2
		Server.process = BTOS2;
		clientOperation = Client.operation;
		Server.operation = clientOperation;
				
		result = msgsnd(serverID, &Server, ServerOpDim, 0);
		if(result == -1) { perror("msgsend balancer fallita Balancer to Server [BTOS]\n"); exit(1); }
		printf("[BALANCER] is sending operation [N: %d] to [SERVER 2]\n", clientOperation);

		
		//Receive from Client for Server 3
		result = msgrcv(clientID, &Client, ClientOpDim, CTOB, 0);
		if(result == -1) { perror("msgreceive balancer fallita Client to BALANCER [CTOB]\n"); exit(1); }
		printf("[BALANCER] is receiving operation from [CLIENT]\n");

		//Sending to Server 3
		Server.process = BTOS3;
		clientOperation = Client.operation;
		Server.operation = clientOperation;
			
		result = msgsnd(serverID, &Server, ServerOpDim, 0);
		if(result == -1) { perror("msgsend balancer fallita Balancer to Server [BTOS]\n"); exit(1); }
		printf("[BALANCER] is sending operation [N: %d] to [SERVER 3]\n", clientOperation);
		
	}
	return 0;
}
















