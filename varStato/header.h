#ifndef _HEAEDER_H
#define _HEAEDER_H

#include "monitor.h"
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <time.h>

#define LIBERO 0
#define OCCUPATO 1
#define IN_USO 2

#define N_FORNITORI 10
#define N_CLIENTI 10
#define DIM 100

#define VAR_COND 2
#define OK_PROD 0
#define OK_CONS 1

typedef struct{
	unsigned int IDFornitore;
	unsigned int stato;

} Scaffale;

typedef Scaffale Magazzino[DIM];

void Fornitore(Monitor* monitor, int* livelloScorte, int* scaffaliLiberi, Magazzino* magazzino);
void Cliente(Monitor* monitor, int* livelloScorte, int* scaffaliLiberi, Magazzino* magazzino);

#endif
