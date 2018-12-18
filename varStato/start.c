#include "header.h"

int main(){
	
	pid_t pid;
	int status;	
	Monitor monitor;

	int IDScorte = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0664);
	int IDLiberi = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0664);
	int IDMagazzino = shmget(IPC_PRIVATE, sizeof(Magazzino), IPC_CREAT | 0664);

	int *livelloScorte = (int*) shmat(IDScorte, 0, 0);
	int *scaffaliLiberi = (int*) shmat(IDLiberi, 0, 0);
	Magazzino* magazzino = (Magazzino*) shmat(IDMagazzino, 0, 0);

	//init
	*livelloScorte = 0;
	*scaffaliLiberi = DIM;
	init_monitor(&(monitor), VAR_COND);
	
	for(int i = 0; i < DIM; ++i){
		(*magazzino)[i].stato = LIBERO;
	}

	//fornitori

	for(int i = 0; i < N_FORNITORI; ++i){

		pid = fork();
		if(pid == 0){
			Fornitore(&monitor, livelloScorte, scaffaliLiberi, magazzino);
		}
		else if(pid < 0){ perror("Fork Fornitore fallita\n"); exit(1); }
	}
	
	//clienti
	for(int i = 0; i < N_CLIENTI; ++i){
		pid = fork();
		if(pid == 0){
			Cliente(&monitor, livelloScorte, scaffaliLiberi, magazzino);
		}
		else if(pid < 0){ perror("Fork Cliente fallita\n"); exit(1); }
	}
	

	//ending
	for(int i = 0; i < N_CLIENTI + N_FORNITORI; ++i){
		wait(&status);
	}
	
	shmctl(IDScorte, IPC_RMID, 0);
	shmctl(IDLiberi, IPC_RMID, 0);	
	shmctl(IDMagazzino, IPC_RMID, 0);
	return 0;
}
