#ifndef _HEADER_H
#define _HEADER_H

#include "monitor.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <wait.h>

#define DIM_QUEUE 10
#define N_UTENTI 5
#define N_RICHIESTE 5
#define N_POS 20
#define OK_UTENTE 0
#define OK_SCHED 1

typedef struct{
	unsigned int position;
	pid_t processo;

} Richiesta;

typedef struct {
	Richiesta queue[DIM_QUEUE];
	int testa, coda, nelem;
	Monitor monitor;

} MScheduler;

void Init(MScheduler* monitor);
void Remove(MScheduler* monitor);
void PushRichiesta(MScheduler* monitor, Richiesta* richiesta);
void PopRichiesta(MScheduler* monitor, Richiesta* richiesta);

void Utente(MScheduler* monitor);
void Schedulatore(MScheduler* monitor);

#endif
