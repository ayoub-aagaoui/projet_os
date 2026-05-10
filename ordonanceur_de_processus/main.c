#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "politiques/politiques.h"

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Erreur : specifiez le fichier de config.\nUsage : ./ordonnanceur config.txt\n");
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if(f == NULL) {
        perror("Erreur d'ouverture du fichier");
        return 1;
    }

    Processus liste[50];
    int cpt = 0;
    char ligne[100];

    while(fgets(ligne, sizeof(ligne), f) != NULL) {
        if(ligne[0] == '\n' || ligne[0] == '#') continue;
        sscanf(ligne, "%s %d %d", liste[cpt].nom, &liste[cpt].arrivee, &liste[cpt].temps_cpu);
        cpt++;
    }
    fclose(f);

    int choix;
    printf("Choix de la politique :\n1. FIFO\n2. SJF\n3. Round-Robin\nVotre choix : ");
    scanf("%d", &choix);

    if(choix == 2) algorithme_sjf(liste, cpt);
    else if(choix == 3) algorithme_rr(liste, cpt, 2);
    else algorithme_fifo(liste, cpt);

    return 0;
}
