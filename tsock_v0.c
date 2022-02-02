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

void main (int argc, char **argv)
{
	/* ---------------------------declaration des paramètre--------------------------------------- */ 
	int c;
	extern char *optarg;
      
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

void main (int argc, char **argv)
{
	/* ---------------------------declaration des paramètre--------------------------------------- */ 
	int c;
	extern char *optarg;
	extern int optind;
	int nb_message = -1; /* Nb de messages à envoyer ou à recevoir, par défaut : 10 en émission, infini en réception */
	int source = -1 ; /* 0=puits, 1=source */
	char *dest ;
	int lg =30; /* longueur du message par défaut */
	int tcp=1;
	int port;
	
	/*------------------------------Début--------------------------------*/ 
	while ((c = getopt(argc, argv, "pn:su")) != -1) {
		switch (c) {
		case 'p':
			if (source == 1) {
				printf("Warning :\n On ne peut être source et puits en même temps, Please enlever une des deux options -s ou -p\n\n");
				exit(1);
			}
			source = 0;
			break;

		case 's':
			if (source == 0) {
				printf("Warning :\n On ne peut être source et puits en même temps, Please enlever une des deux options -s ou -p\n\n");
				exit(1) ;
			}
			source = 1;
			break;
		case 'u':
			tcp=0;
			printf("l'envoi se fait via udp");
			break;
				       
		case 'n':
			nb_message = atoi(optarg);
			break;

		default:
			printf("usage: ./tsock [-p|-s][-n ##]\n");
			break;
		}
	}
	if ((port=atoi(argv[argc-1]))!=-1)   //récupération du numéro de port 
    {
        port=htons(port);         //   pour la précaution en utilise la fonction htons      
    }

  	
				       

	if (source == -1) {
		printf("usage: ./tsock [-p|-s][-n ##]\n");
		exit(1) ;
	}
	

	if (source == 1){
		printf("on est dans le source\n");
	}
	else
	  {
	    printf("on est dans le puits\n");
	  }
	
	if (tcp==1)
	  {
            printf("Protocole de transport : TCP | ");
	  }
        else
	  {
            printf("Protocole de transport : UDP | ");
	  }			       
	if (nb_message != -1) {
	  if (source == 1){
			printf("nb de tampons à envoyer : %d\n", nb_message);
	  }
	  else
			printf("nb de tampons à recevoir : %d\n", nb_message);
	} else {
		if (source == 1) {
			nb_message = 10 ;
			printf("nb de tampons à envoyer = 10 par défaut\n");
		} else
		printf("nb de tampons à envoyer = infini\n");

	}
	dest=argv[argc-2];
	printf("le nom de la machine est: %s \n",dest);
}
 

}

