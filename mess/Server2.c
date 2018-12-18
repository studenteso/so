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
	
	printf("[SERVER 2 STARTED]\n");
	
	key_t queueServer = ftok(FTOK_PATH_SERVER_RIS, FTOK_CHAR_SERVER_RIS);
	
	int serverID = msgget(queueServer, IPC_CREAT | 0664);
	if(serverID == -1) { perror("msgget server fallita\n"); exit(1); }

	int numMsg = (NUM_MSG * NUM_CLIENT) / 3;

	for(int i = 0; i < numMsg; ++i){
	
		int result = 0;
		int clientOperation;

		struct MSGServer Server;
		size_t ServerOpDim = sizeof(struct MSGServer) - sizeof(long);
		
		//Receive from Balancer to Server 2	
		result = msgrcv(serverID, &Server, ServerOpDim, BTOS2, 0);
		if(result == -1) { perror("msgreceive balancer fallita Balancer to Server [BTOS]\n"); exit(1); }
		printf("[SERVER 2] is receiving operation [%d]  from [BALANCER]\n", result);
		printf("[SERVER 2] Receiving message successfully [%d]\n", result);
			
	}

	return 0;
}
