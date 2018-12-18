#include "header.h"

typedef struct {
	int identificativo;
	GestioneVoli* gestore;
} Parametri;



int main(){

	pthread_t threads[5];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	GestioneVoli* gestore = (GestioneVoli*) malloc(sizeof(GestioneVoli));
	Init(gestore);
	
	Parametri params[5];

	for(int i = 0; i < 5; ++i){
		params[i].identificativo = i;
		params[i].gestore = gestore;
		pthread_create(&threads[i], &attr, Gestore, (void*) &params[i]);
	}

	for(int i = 0; i < 5; ++i){
		pthread_join(threads[i], NULL);
	}

	Remove(gestore);
	return 0;
}

void* Gestore(void* arg){

	Parametri* params = (Parametri*) arg;
	int identificativo = params->identificativo;
	GestioneVoli* gestione = params->gestore;

	InserisciVolo(gestione, identificativo);
	printf("[GESTORE INSERIMENTO] Inserimento Volo [%d] \n", identificativo);

	AggiornaVolo(gestione, identificativo, 1000);
	printf("[GESTORE AGGIORNAMENTO] Aggiornamento Volo [%d] a 1000\n", identificativo);

	AggiornaVolo(gestione, identificativo, 2000);
	printf("[GESTORE AGGIORNAMENTO] Aggiornamento Volo [%d] a 2000\n", identificativo);

	AggiornaVolo(gestione, identificativo, 1000);
	printf("[GESTORE AGGIORNAMENTO] Aggiornamento Volo [%d] a 1000\n", identificativo);

	RimuoviVolo(gestione, identificativo);
	printf("[GESTORE RIMOZIONE] Rimozione Volo [%d]\n", identificativo);
	
	pthread_exit(NULL);
}
