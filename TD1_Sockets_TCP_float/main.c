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



int main(int argc, char** argv) {
    int sock;
    float valEnvoyee,valRecu;
    float retour;
    struct sockaddr_in infosServeur;
    //struct sockaddr_in infosReception;
    socklen_t taille;
    
    //creation de la socket
    sock = socket (PF_INET,SOCK_STREAM, IPPROTO_TCP);
    if (sock ==-1)
    {
        printf("pb socket : %s\n",strerror(errno));
        exit(errno);
    }
    //init de la structure pour communiquer avec le serveur
    infosServeur.sin_family = AF_INET;
    infosServeur.sin_port = htons (6666); //port dans ordre reseau
    infosServeur.sin_addr.s_addr= inet_addr("172.18.58.92");
    
    //Communication avec le serveur
    retour=connect(sock,(struct sockaddr *)&infosServeur,sizeof(infosServeur));
   
    valEnvoyee=16.06;
    retour =write(sock,( void *)&valEnvoyee,sizeof(valEnvoyee));
    if(retour==-1){
         printf("pb write: %s\n",strerror(errno));
        exit(errno);
    }
    
    //recevoir l'entier en provenance du ser6
    retour=read(sock,(void *)&valRecu,sizeof(valRecu));
    if(retour==-1){
         printf("pb read: %s\n",strerror(errno));
        exit(errno);
    }
   
    //affiche l'entier
    printf("Message reçu du serveur : %f\n",valRecu);
    

    return (EXIT_SUCCESS);
}

