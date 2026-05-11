#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h> igé
#include "com.h"

pthread_mutex_t outils[NB_MAX_OUTILS];

void afficher_log(char* message, int o1, int o2) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    printf("[%02d:%02d:%02d] %s %d et %d\n", tm->tm_hour, tm->tm_min, tm->tm_sec, message, o1, o2);
}

void* gerer_connexion(void* arg) {
    int sock = *(int*)arg;
    free(arg);
    TrameReseau msg;

    while(recv(sock, &msg, sizeof(TrameReseau), 0) > 0) {
        int premier = (msg.id1 < msg.id2) ? msg.id1 : msg.id2;
        int second = (msg.id1 > msg.id2) ? msg.id1 : msg.id2;

        if(msg.type == 1) {
            pthread_mutex_lock(&outils[premier]);
            pthread_mutex_lock(&outils[second]);
            afficher_log("Le serveur a alloue les outils", premier, second);

            int rep = 1;
            send(sock, &rep, sizeof(int), 0);
        } else if (msg.type == 2) {
            pthread_mutex_unlock(&outils[premier]);
            pthread_mutex_unlock(&outils[second]);
            afficher_log("Le serveur a libere les outils", premier, second);
        }
    }
    close(sock);
    return NULL;
}

int main() {
    for(int i = 0; i < NB_MAX_OUTILS; i++) {
        pthread_mutex_init(&outils[i], NULL);
    }

    int sock_srv = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = {AF_INET, htons(PORT), INADDR_ANY};
    bind(sock_srv, (struct sockaddr*)&adr, sizeof(adr));
    listen(sock_srv, 5);

    printf("Serveur d'outils demarre...\n");

    while(1) {
        int* client = malloc(sizeof(int));
        *client = accept(sock_srv, NULL, NULL);
        pthread_t tid;
        pthread_create(&tid, NULL, gerer_connexion, client);
        pthread_detach(tid);
    }
    return 0;
}
