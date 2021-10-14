/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: vdesaunay
 *
 * Created on 6 octobre 2021, 10:43
 */

#include <stdio.h>
#include <stdlib.h>
//include pour socket
#include <sys/types.h>
#include <sys/socket.h>
//include pour stockaddr_in
#include <netinet/in.h>
#include <arpa/inet.h>
//include gestion erreurs
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char** argv) {
/*    int sockCommClient;
    int sockFileAttente;
    float valEnvoyee, valRecue;
    float retour;
    struct sockaddr_in infosServeur;
    struct sockaddr_in infosClient;
    socklen_t taille;
    //datePerso date;

    //création socket udp
    sockFileAttente = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockCommClient == -1) {
        printf("pb création socket : %s\n", strerror(errno));
        exit(errno);
    }

    infosServeur.sin_addr.s_addr = htonl(INADDR_ANY);
    infosServeur.sin_family = AF_INET;
    infosServeur.sin_port = htons(5555);

    retour = bind(sockFileAttente, (struct sockaddr *) &infosServeur, sizeof (infosServeur));
    if (retour == -1) {
        printf("pb bind : %s\n", strerror(errno));
        exit(errno);
    }
    retour = listen(sockFileAttente, 20);
    if (retour == -1) {
        printf("pb listen : %s\n", strerror(errno));
        exit(errno);
    }
    while (1) {
        taille = sizeof (infosClient);
        sockCommClient = accept(sockFileAttente, (struct sockaddr *) &infosClient, &taille);
        if (sockCommClient == -1) {
            printf("pb accept : %s\n", strerror(errno));
            exit(errno);
        }
        retour = read(sockCommClient, &valRecue, sizeof (valRecue));

        if (retour == -1) {
            printf("pb accept : %s\n", strerror(errno));
            exit(errno);
        }


        valEnvoyee = -valRecue;


        retour = write(sockCommClient, &valEnvoyee, sizeof (valEnvoyee));

        if (retour == -1) {
            printf("pb accept : %s\n", strerror(errno));
            exit(errno);
        }

        printf("Message reçu de %s : %f\n", inet_ntoa(infosClient.sin_addr), valRecue);


    }
    
   */ 
    
    //Recevoir une date
    
    typedef struct{
	unsigned char jour;
	unsigned char mois;
	unsigned short int annee;
	char jourDeLaSemaine[10];	// le jour en toute lettre
    }datePerso;
    
    int sockCommClient;
    int sockFileAttente;
    unsigned char retour;
    struct sockaddr_in infosServeur;
    struct sockaddr_in infosClient;
    socklen_t taille;
    datePerso date;

    //création socket udp
    sockFileAttente = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockCommClient == -1) {
        printf("pb création socket : %s\n", strerror(errno));
        exit(errno);
    }

    infosServeur.sin_addr.s_addr = htonl(INADDR_ANY);
    infosServeur.sin_family = AF_INET;
    infosServeur.sin_port = htons(5555);

    retour = bind(sockFileAttente, (struct sockaddr *) &infosServeur, sizeof (infosServeur));
    if (retour == -1) {
        printf("pb bind : %s\n", strerror(errno));
        exit(errno);
    }
    retour = listen(sockFileAttente, 20);
    if (retour == -1) {
        printf("pb listen : %s\n", strerror(errno));
        exit(errno);
    }
    while (1) {
        taille = sizeof (infosClient);
        sockCommClient = accept(sockFileAttente, (struct sockaddr *) &infosClient, &taille);
        if (sockCommClient == -1) {
            printf("pb accept : %s\n", strerror(errno));
            exit(errno);
        }
        retour = read(sockCommClient, &date, sizeof (date));

        if (retour == -1) {
            printf("pb read : %s\n", strerror(errno));
            exit(errno);
        }


        printf("Message reçu de %s : %s %d %d %d\n", inet_ntoa(infosClient.sin_addr),date.jourDeLaSemaine,date.jour,date.mois,date.annee);


    }




    return (EXIT_SUCCESS);
}

