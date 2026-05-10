#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "commun.h"

int ma_socket;

void* thread_reflexion(void* arg) {
    (void)arg;
    printf("[Bras] Analyse de la tache...\n");
    sleep(1);
    return NULL;
}

void* thread_reseau(void* arg) {
    (void)arg;
    TrameReseau demande = {1, 2, 5};
    printf("[Bras] Envoi requete outils...\n");
    send(ma_socket, &demande, sizeof(TrameReseau), 0);

    int ack;
    recv(ma_socket, &ack, sizeof(int), 0);
    printf("[Bras] Outils 2 et 5 verrouilles !\n");
    return NULL;
}

void* thread_assemblage(void* arg) {
    (void)arg;
    printf("[Bras] Assemblage en cours...\n");
    sleep(2);

    TrameReseau libere = {2, 2, 5};
    send(ma_socket, &libere, sizeof(TrameReseau), 0);
    printf("[Bras] Termine, outils relaches.\n");
    return NULL;
}

int main() {
    ma_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv = {AF_INET, htons(PORT)};
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(ma_socket, (struct sockaddr*)&serv, sizeof(serv));

    pthread_t t1, t2, t3;
    pthread_create(&t1, NULL, thread_reflexion, NULL);
    pthread_join(t1, NULL);

    pthread_create(&t2, NULL, thread_reseau, NULL);
    pthread_join(t2, NULL);

    pthread_create(&t3, NULL, thread_assemblage, NULL);
    pthread_join(t3, NULL);

    close(ma_socket);
    return 0;
}
