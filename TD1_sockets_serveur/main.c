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

/*
struct sockaddr_in {
sa_family_t sin_family; //famille d'adresses : AF_INET  sur 16 bits    
u_int16_t sin_port; // port dans l'ordre d'octets réseau 
struct in_addr sin_addr; // adresse Internet                 
char sin_zero[8]; // initialise à zéro 
};

struct in_addr {
u_int32_t s_addr; // Adresse dans l'ordre d'octets réseau 
  // INADDR_ANY afin d'ecouter sur toutes 
// les interface presentes 
};*/

int main(int argc, char** argv) {
    int sock;
    int valEnvoyee, valRecu;
    int retour;
    struct sockaddr_in infosServeur;
    struct sockaddr_in infosClient;
    char*client;
    socklen_t taille;

    //creation de la socket
    sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == -1) {
        printf("pb socket : %s\n", strerror(errno));
        exit(errno);
    }
    //init de la structure pour communiquer avec le serveur
    
    infosServeur.sin_family = AF_INET;
    infosServeur.sin_port = htons(4444); //port dans ordre reseau
    infosServeur.sin_addr.s_addr = inet_addr("172.18.58.101");
    

    // Associer l'adresse IP et le nro de port
    retour = bind(sock, (struct sockaddr *)&infosServeur, sizeof (infosServeur));
    if (retour == -1) {
        printf("pb bind : %s\n", strerror(errno));
        exit(errno);
    }
    
        //recevoir l'entier en provenance du client
    while (1){
        retour = recvfrom(sock, &valRecu, sizeof (valRecu), 0, (struct sockaddr *) &infosServeur, &taille);
    if (retour == -1) {
        printf("pb recvfrom : %s\n", strerror(errno));
        exit(errno);
    }
    //affiche l'entier
   
    
    
    //renvoyer un entier au client
    valEnvoyee = -valRecu;
    client= inet_ntoa(infosClient.sin_addr);
    retour = sendto(sock, &valEnvoyee, sizeof (valEnvoyee), 0, (struct sockaddr *) &infosServeur, sizeof (infosServeur));
    if (retour == -1) {
        printf("pb sendto : %s\n", strerror(errno));
        exit(errno);
    }
 printf("Message reçu du client %s : %d\n",infosClient, valRecu);
    }

    return (EXIT_SUCCESS);
}

