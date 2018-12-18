#include "header.h"

void InserisciVolo(GestioneVoli* gestione, int identificativo){
		
	pthread_mutex_lock(&(gestione->mutex));
	while(gestione->postiLiberi == 0){
		pthread_cond_wait(&(gestione->goProd), &(gestione->mutex));
	}
	
	int IDLibero = CercaVoloLibero(gestione);
	gestione->vettore_stato[IDLibero] = IN_USO;
	--(gestione->postiLiberi);

	pthread_mutex_unlock(&(gestione->mutex));

	sleep(1);
	gestione->vettore_voli[IDLibero].identificativo = identificativo;
	gestione->vettore_voli[IDLibero].quota = 0;
	printf("[INSERIMENTO VOLO] Volo Inserito [ID %d]\n", identificativo);

	pthread_mutex_lock(&(gestione->mutex));
	gestione->vettore_stato[IDLibero] = OCCUPATO;
	pthread_mutex_unlock(&(gestione->mutex));
}

void RimuoviVolo(GestioneVoli* gestione, int identificativo){

	pthread_mutex_lock(&(gestione->mutex));
	int IDBuffer = CercaVolo(gestione, identificativo);

	if(IDBuffer == -1){
		pthread_mutex_unlock(&(gestione->mutex));
		return;
	}

	gestione->vettore_stato[IDBuffer] = IN_USO;
	pthread_mutex_unlock(&(gestione->mutex));

	printf("[RIMOZIONE] Rimozione Volo [%d] in [%d] \n", identificativo, IDBuffer);
	sleep(1);	

	pthread_mutex_lock(&(gestione->mutex));
	++(gestione->postiLiberi);
	gestione->vettore_stato[IDBuffer] = LIBERO;

	pthread_cond_signal(&(gestione->goProd));
	pthread_mutex_unlock(&(gestione->mutex));
}

void AggiornaVolo(GestioneVoli* gestione, int identificativo, int quota){
	
	pthread_mutex_lock(&(gestione->mutex));
	int IDBuffer = CercaVolo(gestione, identificativo);
	
	if(IDBuffer == -1){
		pthread_mutex_unlock(&(gestione->mutex));
		return;
	}
	
	gestione->vettore_stato[IDBuffer] = IN_USO;
	pthread_mutex_unlock(&(gestione->mutex));

	printf("[AGGIORNAMENTO] Aggiornamento Volo [%d] in [%d] \n", identificativo, IDBuffer);
	gestione->vettore_voli[IDBuffer].quota = quota;
	sleep(1);

	pthread_mutex_lock(&(gestione->mutex));
	gestione->vettore_stato[IDBuffer] = OCCUPATO;
	pthread_mutex_unlock(&(gestione->mutex));
}

int CercaVolo(GestioneVoli* gestione, int identificativo){

	int i = 0;
	int IDBuffer = -1;
	while( i < BUFFER && IDBuffer==-1 ) {

		if(gestione->vettore_stato[i] == OCCUPATO &&
		   gestione->vettore_voli[i].identificativo == identificativo) {

			IDBuffer = i;
		}
		i++;
	}
	return IDBuffer;
}

int CercaVoloLibero(GestioneVoli* gestione){
	
	int i = 0;
	while( gestione->vettore_stato[i] != LIBERO ) {	i++; }
	return i;
}

void Init(GestioneVoli* gestore){

	pthread_cond_init(&(gestore->goProd), NULL);
	pthread_mutex_init(&(gestore->mutex), NULL);
	gestore->postiLiberi = BUFFER;

	for(int i = 0; i < BUFFER; ++i){
		gestore->vettore_stato[i] = LIBERO;
	}
}
void Remove(GestioneVoli* gestore){
	
	free(gestore);
	pthread_cond_destroy(&(gestore->goProd));
	pthread_mutex_destroy(&(gestore->mutex));
}


































