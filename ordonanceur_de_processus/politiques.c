#include <stdio.h>
#include "politiques.h"

void algorithme_fifo(Processus tab[], int nb_proc) {
    printf("\n=== Execution FIFO ===\n");
    int horloge = 0;
    for(int i = 0; i < nb_proc; i++) {
        if(horloge < tab[i].arrivee) horloge = tab[i].arrivee;
        printf("[t=%d] %s tourne pour %d cycles\n", horloge, tab[i].nom, tab[i].temps_cpu);
        horloge += tab[i].temps_cpu;
    }
}

void algorithme_sjf(Processus tab[], int nb_proc) {
    printf("\n=== Execution SJF ===\n");
    int horloge = 0, finis = 0;
    int etat[100] = {0};

    while(finis < nb_proc) {
        int idx = -1;
        int min_cpu = 9999;

        for(int i = 0; i < nb_proc; i++) {
            if(etat[i] == 0 && tab[i].arrivee <= horloge && tab[i].temps_cpu < min_cpu) {
                min_cpu = tab[i].temps_cpu;
                idx = i;
            }
        }

        if(idx != -1) {
            printf("[t=%d] %s tourne pour %d cycles\n", horloge, tab[idx].nom, tab[idx].temps_cpu);
            horloge += tab[idx].temps_cpu;
            etat[idx] = 1;
            finis++;
        } else horloge++;
    }
}

void algorithme_rr(Processus tab[], int nb_proc, int quantum) {
    printf("\n=== Execution Round-Robin (Quantum = %d) ===\n", quantum);
    int horloge = 0, finis = 0;

    for(int i = 0; i < nb_proc; i++) tab[i].temps_restant = tab[i].temps_cpu;

    while(finis < nb_proc) {
        int processeur_actif = 0;
        for(int i = 0; i < nb_proc; i++) {
            if(tab[i].temps_restant > 0 && tab[i].arrivee <= horloge) {
                processeur_actif = 1;
                int temps_execution = (tab[i].temps_restant > quantum) ? quantum : tab[i].temps_restant;

                printf("[t=%d] %s tourne pour %d cycles\n", horloge, tab[i].nom, temps_execution);
                horloge += temps_execution;
                tab[i].temps_restant -= temps_execution;

                if(tab[i].temps_restant == 0) finis++;
            }
        }
        if(processeur_actif == 0) horloge++;
    }
}
