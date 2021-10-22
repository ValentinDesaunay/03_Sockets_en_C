/* 
 * File:   main.c
 * Author: vdesaunay
 *
 * Created on 6 octobre 2021, 11:48
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <signal.h>

#define TAILLE_MAX_PSEUDO 25
#define TAILLE_MAX_MSG 255

typedef struct {
    char pseudo[TAILLE_MAX_PSEUDO]; //le pseudo du client
    char texteMessage[TAILLE_MAX_MSG]; //Le message du client
} message;

int main(int argc, char** argv) {

    int fdSocket;
    struct sockaddr_in informationServeur;
    int retour;
    int tailleClient;
    char msgRecu[TAILLE_MAX_MSG];
    int pid;

    if (argc != 2) {
        printf("Usage : %s pseudo IpDuServeur port\n", argv[0]);
        exit(EXIT_SUCCESS);
    }
    printf("client de tchat tcp port 5678\n");
    informationServeur.sin_family = AF_INET;
    informationServeur.sin_port = htons(5678);
    informationServeur.sin_addr.s_addr = inet_addr(argv[1]);

    fdSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (fdSocket == -1) {
        printf("pb socket : %s\n", strerror(errno));
        exit(errno);
    }
    message msg1;
    strcpy(msg1.pseudo, &msg1);
    strcpy(msg1.texteMessage, &msg1);

    //demande de connexion au serveur
    retour = connect(fdSocket, (struct sockaddr *) &informationServeur, sizeof (informationServeur));
    if (retour == -1) {
        printf("pb connect : %s\n", strerror(errno));
        exit(errno);
    }
    pid = fork();

    if (pid == 0) //boucle d'envoie
    {
        // envoyer donnees au serveur
        do {
            printf("votre pseudo : ");
            printf("votre message : ");
            gets(msg1);
            retour = write(fdSocket, &msg1, TAILLE_MAX_MSG);
            if (retour == -1) {
                printf("pb write : %s\n", strerror(errno));
                exit(errno);
            }

        } while (strcmp("quit", msg1) != 0);
        //arreter le processus de reception
        kill(getppid(), SIGTERM);
        close(fdSocket);

    } else //boucle de réception
    {
        while (1) {
            memset(msgRecu, '\0', TAILLE_MAX_MSG);
            retour = read(fdSocket, msgRecu, TAILLE_MAX_MSG);
            if (retour == -1) {
                printf("pb read : %s\n", strerror(errno));
                exit(errno);
            }
        }
    }
    // reception en provenance du serveur

    printf("msg provenant du serveur :%s\n", msgRecu);

    return (EXIT_SUCCESS);
}

