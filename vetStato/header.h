#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER 3
#define LIBERO 0
#define IN_USO 1
#define OCCUPATO 2


typedef struct{
	int identificativo, quota;
} Volo;

typedef struct{

	Volo vettore_voli[BUFFER];
	int vettore_stato[BUFFER];		
	int postiLiberi;

	pthread_cond_t goProd;
	pthread_mutex_t mutex;

} GestioneVoli;

void Init(GestioneVoli*);
void Remove(GestioneVoli*);
void InserisciVolo(GestioneVoli* gestione, int identificativo);
void RimuoviVolo(GestioneVoli* gestione, int identificativo);
void AggiornaVolo(GestioneVoli* gestione, int identificativo, int quota);
int CercaVolo(GestioneVoli* gestione, int identificativo);
int CercaVoloLibero(GestioneVoli* gestione);

void* Gestore(void* arg);

