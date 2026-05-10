#ifndef POLITIQUES_H
#define POLITIQUES_H

typedef struct {
    char nom[20];
    int arrivee;
    int temps_cpu;
    int temps_restant;
} Processus;

void algorithme_fifo(Processus tab[], int nb_proc);
void algorithme_sjf(Processus tab[], int nb_proc);
void algorithme_rr(Processus tab[], int nb_proc, int quantum);

#endif
