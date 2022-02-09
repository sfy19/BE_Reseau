//sfy_omom: /* librairie standard ... */
#include <stdlib.h>
/* pour getopt */
#include <unistd.h>
/* déclaration des types de base */
#include <sys/types.h>
/* constantes relatives aux domaines, types et protocoles */
#include <sys/socket.h>
/* constantes et structures propres au domaine UNIX */
#include <sys/un.h>
/* constantes et structures propres au domaine INTERNET */
#include <netinet/in.h>
/* structures retournées par les fonctions de gestion de la base de
données du réseau */
#include <netdb.h>
/* pour les entrées/sorties */
#include <stdio.h>
/* pour la gestion des erreurs */
#include <errno.h>
 //sfy_omom: #include <sys/types.h>
/* constantes relatives aux domaines, types et protocoles */
#include <sys/socket.h>
/* constantes et structures propres au domaine UNIX */
#include <sys/un.h>
/* constantes et structures propres au domaine INTERNET */
#include <netinet/in.h>
/* structures retournées par les fonctions de gestion de la base de
données du réseau */
#include <netdb.h>
/* pour les entrées/sorties */
#include <stdio.h>
/* pour la gestion des erreurs */
#include <errno.h>

void construire_message (char *msg, char motif, int lg_message) {
    int i;
    for (i=0 ; i<lg_message; i++) msg[i] = motif; 
}

void afficher_message (char *message, int lg) {
    int i;
    printf("message construit : ");
    for (i=0 ; i<lg ; i++) printf("%c", message[i]) ; printf("\n"); 
}


void puits_udp(int port, int lg_message, int nbre_messages) {
    // Création socket
    int sock; 
    sock=socket(AF_INET,SOCK_DGRAM,0);
    if ( sock == -1) {
        printf("PUITS : Erreur de création de socket \n"); 
        exit(-1); 
    }
    // D&finition @ locale
    //declaration
    struct sockaddr_in adr_local;
    int lg_adr = sizeof(adr_local); 
    memset ((char*)&adr_local,0,sizeof(adr_local));
    adr_local.sin_family = AF_INET;
    adr_local.sin_port=htons(port);
    adr_local.sin_addr.s_addr=INADDR_ANY; 
    // association @locale & socket local
    int res_bind = bind (sock,(struct sockaddr *) &adr_local,lg_adr); 
    if (res_bind == -1) {
        printf("Erreur bind \n");
        exit(1); 
    }
    // réception msgs 

    char * msg = malloc(sizeof(lg_message));
    struct sockaddr_in adr_em; 
    int lg_adr_em= sizeof(adr_em);
    int octets_recus; 

    if (nbre_messages == -1) { // Reception infinie
        while (1) {
            octets_recus= recvfrom(sock,msg,lg_message,0,(struct sockaddr *) &adr_em, &lg_adr_em);
            if (octets_recus == -1) {
                printf("Erreur recevfrom \n");
                exit(1); 
            }
            afficher_message(msg, lg_message);  
        }
    } else {
        for (int i=0; i < nbre_messages; i++) {
            octets_recus= recvfrom(sock,msg,lg_message,0,(struct sockaddr *) &adr_em, &lg_adr_em);
            if (octets_recus == -1) {
                printf("Erreur recevfrom \n");
                exit(1); 
            }
            afficher_message(msg, lg_message);  
        }
    }

    // destruction du socket
    close(sock); 
}

void source_udp(int port, char* destination, int lg_message, int nbre_messages) {
// Création socket
  int sock; 
    sock=socket(AF_INET,SOCK_DGRAM,0);
    if ( sock == -1) {
        printf("PUITS : Erreur de création de socket \n"); 
        exit(-1); 
    }
    // D&finition @ locale
    //declaration
    struct sockaddr_in adr_local;
    int lg_adr = sizeof(adr_local); 
    memset ((char*)&adr_local,0,sizeof(adr_local));
    adr_local.sin_family = AF_INET;
    adr_local.sin_port=htons(port);
// Définition @ distante
    struct hostent *hp;
    struct sockaddr_in adr_distant;
    int lg_adrd = sizeof(adr_distant);
    memset((char*)&adr_distant,0,sizeof(adr_distant));
    adr_distant.sin_port=9000;
    if((hp = gethostbyname("dumas.insa-tlse.fr")) == NULL){
    printf("erreur gethostbyname\n");
    exit(1);
    
    }
    memcpy((char*)&(adr_distant.sin_addr.s_addr),hp->h_addr,hp->h_length);
    
//envoi msg vers @distancte
    if {
    sendto(sock,*msg,lg_message,0,*adr_distant,lg_adr);
    print("%d",lg_message);}
    else{
    print("-1");}
// affichage msg 
// destruction du socket
    close(sock);
}

void main (int argc, char **argv)
{
	int c;
	extern char *optarg;
	extern int optind;
	int nb_message = -1; /* Nb de messages à envoyer ou à recevoir, par défaut : 10 en émission, infini en réception */
	int source = -1 ; /* 0=puits, 1=source */
	int tcp =1; 
	int lg =30; 
	int port = atoi(argv[argc-1]);
	while ((c = getopt(argc, argv, "upn:s")) != -1) {
		switch (c) {
		case 'p':
			if (source == 1) {
				printf("usage: cmd [-p|-s][-n ##]\n");
				exit(1);
			}
			source = 0;
			break;

		case 's':
			if (source == 0) {
				printf("usage: cmd [-p|-s][-n ##]\n");
				exit(1) ;
			}
			source = 1;
			break;

		case 'n':
			nb_message = atoi(optarg);
			break;
			
	    case 'u': 
	        tcp = 0; 
	        break; 

		default:
			printf("usage: cmd [-p|-s][-n ##]\n");
			break;
		}
	}

	if (source == -1) {
		printf("usage: cmd [-p|-s][-n ##]\n");
		exit(1) ;
	}

    char * dest = argv[argc-2]; 
	if (source == 1)
		printf("on est dans le source\n");
		
	else
		printf("on est dans le puits\n");

	if (nb_message != -1) {
		if (source == 1)
			printf("nb de tampons à envoyer : %d\n", nb_message);
		else
			printf("nb de tampons à recevoir : %d\n", nb_message);
	} else {
		if (source == 1) {
			nb_message = 10 ;
			printf("nb de tampons à envoyer = 10 par défaut\n");
		} else
		printf("nb de tampons à recevoir = infini\n");

	}
	
	if (source ==0) { //puits 
	    if (tcp == 0) {
	        puits_udp(port, lg, nb_message);  
	       }
	} 
}

