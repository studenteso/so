#include "header.h"

int main(){

	pid_t pid;
	int status;

	int shmID  = shmget(IPC_PRIVATE, sizeof(MScheduler), IPC_CREAT | 0664);
	if(shmID < 0) { perror("shmget error\n"); exit(1); }

	MScheduler* mscheduler = (MScheduler*) shmat(shmID, 0, 0);
	Init(mscheduler);

	for(int i = 0; i < N_UTENTI; ++i){
		pid = fork();
		if(pid ==  0){
			Utente(mscheduler);
		}
		else if(pid < 0){ perror("Utente Fork Failed"); exit(1); }
	}

	pid = fork();
	if(pid ==  0){
		Schedulatore(mscheduler);
	}
	else if(pid < 0){ perror("Schedulatore Fork Failed"); exit(1); }

	for(int i = 0; i < 6; ++i){
		wait(&status);
	}

	Remove(mscheduler);
	shmctl(shmID, IPC_RMID, NULL);
	return 0;
}
