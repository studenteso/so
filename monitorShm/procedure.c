#include "header.h"

void Init(MScheduler* monitor){

	monitor->testa = monitor->coda = monitor->nelem = 0;
	init_monitor(&(monitor->monitor), 2);
}

void Remove(MScheduler* monitor){ remove_monitor(&(monitor->monitor)); }

void PushRichiesta(MScheduler* monitor, Richiesta* richiesta){
	enter_monitor(&(monitor->monitor));

	if(monitor->nelem == DIM_QUEUE){
		wait_condition(&(monitor->monitor),OK_UTENTE);
	}
	
	monitor->queue[monitor->coda].position = richiesta->position;
	monitor->queue[monitor->coda].processo = richiesta->processo;
	monitor->coda = (monitor->coda + 1) % DIM_QUEUE;
	++(monitor->nelem);
	
	signal_condition(&(monitor->monitor), OK_SCHED);
	leave_monitor(&(monitor->monitor));
}

void PopRichiesta(MScheduler* monitor, Richiesta* richiesta){

	enter_monitor(&(monitor->monitor));

	if(monitor->nelem == 0){
		wait_condition(&(monitor->monitor),OK_SCHED);
	}
	
	richiesta->position = monitor->queue[monitor->testa].position;
	richiesta->processo = monitor->queue[monitor->testa].processo;
	monitor->testa = (monitor->testa + 1) % DIM_QUEUE;
	--(monitor->nelem);
	
	signal_condition(&(monitor->monitor), OK_UTENTE);
	leave_monitor(&(monitor->monitor));
}

void Utente(MScheduler* monitor){
	
	for(int i = 0; i < N_UTENTI; ++i){
		Richiesta richiesta;
		richiesta.position = rand() % N_POS;
		richiesta.processo = getpid();
		PushRichiesta(monitor, &richiesta);
		printf("[UTENTE PRODUTTORE] ha inserito in posizione [%d] il processo [%d]\n", richiesta.position, richiesta.processo);
	}
}

void Schedulatore(MScheduler* monitor){

	pid_t disco[N_POS];
	int currentPos = 0;

	for(int i = 0; i < N_UTENTI * N_RICHIESTE; ++i){

		Richiesta richiesta;		
		PopRichiesta(monitor, &richiesta);
		printf("[SCHEDULATORE CONSUMATORE] ha prelevato in posizione [%d] il processo [%d]\n", richiesta.position, richiesta.processo);

		sleep(abs(richiesta.position - currentPos)); 
		currentPos = richiesta.position;  					//salvo la posizione
		disco[currentPos] = richiesta.processo;				//sovrascrivo il valore della richiesta alla posizione corrente
		printf("[DISCO] ha aggiornato in posizione [%d] il processo [%d]\n", richiesta.position, richiesta.processo);
	}
}
























