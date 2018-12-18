#include "header.h"

void Fornitore(Monitor* monitor, int* livelloScorte, int* scaffaliLiberi, Magazzino* magazzino){

	int i;
	for(int k = 0; k < 15; ++k){
		
		i = 0;
		enter_monitor(monitor);
		if(*scaffaliLiberi == 0){
			wait_condition(monitor, OK_PROD);
		}
		while(i < DIM && ((*magazzino)[i].stato == OCCUPATO || (*magazzino)[i].stato == IN_USO)){
			++i;		
		}
		(*magazzino)[i].stato = IN_USO;
		--(*scaffaliLiberi);
		
		leave_monitor(monitor);	

		sleep(2);
		printf("[FORNITORE] Fornitura effettuata da [%d]\n", getpid());
		(*magazzino)[i].IDFornitore = getpid();
		
		enter_monitor(monitor);

		(*magazzino)[i].stato == OCCUPATO;
		++(*livelloScorte);
		
		signal_condition(monitor, OK_CONS);
		leave_monitor(monitor);
	}

}

void Cliente(Monitor* monitor, int* livelloScorte, int* scaffaliLiberi, Magazzino* magazzino){
	
	int i;
	for(int k = 0; k < 15; ++k){
		
		i = 0;		
		enter_monitor(monitor);
		if(*livelloScorte == 0){
			wait_condition(monitor, OK_CONS);
		}
		while(i < DIM && ((*magazzino)[i].stato == LIBERO || (*magazzino)[i].stato == IN_USO)){
			++i;		
		}
		(*magazzino)[i].stato = IN_USO;
		--(*livelloScorte);
		
		leave_monitor(monitor);	

		sleep(2);
		printf("[CLIENTE] acquisto effettuato da [%d]\n", (*magazzino)[i].IDFornitore);
		printf("[CLIENTE] magazzino[%d].stato[%d]", i, (*magazzino)[i].stato);
		
		enter_monitor(monitor);

		(*magazzino)[i].stato == LIBERO;
		++(*scaffaliLiberi);
		
		signal_condition(monitor, OK_PROD);
		leave_monitor(monitor);
	}

}
