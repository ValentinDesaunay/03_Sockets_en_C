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

#define TAILLE_MAX 255

int main(int argc, char** argv) {
    int socketFileAttente;
    int socketCommunicationClient;
    struct sockaddr_in informationServeur;
    struct sockaddr_in informationClient;
    int retour;
    int tailleClient;
    char msgEnvoye[TAILLE_MAX];
    char msgRecu[TAILLE_MAX];
    pid_t pid;


    informationServeur.sin_family = AF_INET;
    informationServeur.sin_port = htons(5678);
    informationServeur.sin_addr.s_addr = htonl(INADDR_ANY);
    printf("serveur de tchat tcp port 5678\n");
    socketFileAttente = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketFileAttente == -1) {
        printf("pb socket : %s\n", strerror(errno));
        exit(errno);
    }
    retour = bind(socketFileAttente, (struct sockaddr*) &informationServeur, sizeof (informationServeur));
    if (retour == -1) {
        printf("pb bind : %s\n", strerror(errno));
        exit(errno);
    }
    // mise en place d'une file d'attente de 10
    retour = listen(socketFileAttente, 10);
    if (retour == -1) {
        printf("pb listen : %s\n", strerror(errno));
        exit(errno);
    }

    tailleClient = sizeof (informationClient);
    // attente de connexion
    socketCommunicationClient = accept(socketFileAttente, (struct sockaddr *) &informationClient, &tailleClient);
    if (socketCommunicationClient == -1) {
        printf("pb accept : %s\n", strerror(errno));
        exit(errno);
    }
    pid = fork();
    if (pid == 0) //boucle de lecture
    {
        do {

            // reception en provenance du client
            memset(msgRecu, '\0', TAILLE_MAX);
            retour = read(socketCommunicationClient, msgRecu, TAILLE_MAX);
            if (retour == -1) {
                printf("pb read : %s\n", strerror(errno));
                exit(errno);
            }
            printf("msg provenant du client :%s\n", msgRecu);
        } while (strcmp("a+", msgRecu) != 0);
        //arreter le processus d'envois
         kill(getppid(),SIGTERM);
        close(socketCommunicationClient);
        close(socketFileAttente);
        
    } else //boucle d'envoie
    {
        while (1) {
            printf("votre message : ");
            gets(msgEnvoye);
            retour = write(socketCommunicationClient, msgEnvoye, strlen(msgEnvoye));
            if (retour == -1) {
                printf("pb write : %s\n", strerror(errno));
                exit(errno);
            }
        }
    }


    return (EXIT_SUCCESS);
}
