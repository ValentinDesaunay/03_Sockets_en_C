/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: vdesaunay
 *
 * Created on 6 octobre 2021, 11:48
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

int main(int argc, char** argv) {

      typedef struct{
	unsigned char jour;
	unsigned char mois;
	unsigned short int annee;
	char jourDeLaSemaine[10];	// le jour en toute lettre
    }datePerso;
    
    int sock;
    int retour;
    struct sockaddr_in infosServeur;
    socklen_t taille;
    ssize_t retour2;
    //création socket udp
    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == -1) {
        printf("pb création socket : %s\n", strerror(errno));
        exit(errno);
    }

    //Init de la struct pour communiquer avec le serveur
    infosServeur.sin_family = AF_INET;
    //infosServeur.sin_port = htons(7777); 
    infosServeur.sin_port = htons(5555);
    // Port dans ordre serveur (host to network short)
    infosServeur.sin_addr.s_addr = inet_addr("172.18.58.101");
    
    //Init de la struct pour communiquer avec le serveur
     // Port dans ordre serveur (host to network short)
    
    datePerso date;
    date.annee = 2021;
    date.jour = 14;
    date.mois = 10;
    strcpy(date.jourDeLaSemaine,"Jeudi");
    
    //Communication avec le serveur
    retour=connect(sock,(struct sockaddr *)&infosServeur,sizeof(infosServeur));
    
    //envoyer la date au serveur    
    retour2 =write(sock,&date,sizeof(date));
    if(retour2==-1){
         printf("pb write: %s\n",strerror(errno));
        exit(errno);
    }
    
    return (EXIT_SUCCESS);
}

