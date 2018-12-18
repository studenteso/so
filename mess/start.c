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
	
	printf("[LOAD BALANCING PROGRAM STARTED]\n");

	pid_t pid;
	int status;

	key_t queueClient = ftok(FTOK_PATH_CLIENT_OP, FTOK_CHAR_CLIENT_OP);
	key_t queueServer = ftok(FTOK_PATH_SERVER_RIS, FTOK_CHAR_SERVER_RIS);

	int clientID = msgget(queueClient, IPC_CREAT | 0664);
	if(clientID == -1) { perror("msgget client fallita\n"); exit(1); }
	
	int serverID = msgget(queueServer, IPC_CREAT | 0664);
	if(serverID == -1) { perror("msgget server fallita\n"); exit(1); }
	
	for(int i = 0; i < 8; ++i){
		pid = fork();
		if(pid == 0){
			execl("./Client", "./Client", NULL);
			perror("Client Exec Failed\n");
			exit(1);

		} else if(pid < 0){ perror("Fork Client Failed"); exit(1); }
	}

	pid = fork();
	if(pid == 0){
		execl("./Balancer", "./Balancer", NULL);
		perror("Balancer Exec Failed\n");
		exit(1);	
	} else if(pid < 0){ perror("Fork Balancer Failed"); exit(1); }

	pid = fork();
	if(pid == 0){
		execl("./Server1", "./Server1", NULL);
		perror("Server1 Exec Failed\n");
		exit(1);	
	} else if(pid < 0){ perror("Fork Servers Failed"); exit(1); }
	
	pid = fork();
	if(pid == 0){
		execl("./Server2", "./Server2", NULL);
		perror("Server2 Exec Failed\n");
		exit(1);
	} else if(pid < 0){ perror("Fork Servers Failed"); exit(1); }
	
	pid = fork();
	if(pid == 0){
		execl("./Server3", "./Server3", NULL);
		perror("Server3 Exec Failed\n");
		exit(1);
	} else if(pid < 0){ perror("Fork Servers Failed"); exit(1); }

	for(int i = 0; i < 8; ++i){
		wait(&status);
	}
	
	msgctl(queueClient, IPC_RMID, 0);
	msgctl(queueServer, IPC_RMID, 0);

	return 0;
}
