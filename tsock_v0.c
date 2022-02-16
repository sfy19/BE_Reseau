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


void udp_puits(int port, int nbre_messages,int lg_message ) {
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

void udp_source (int port, int nb_message, int lg_msg, char* nom_station)
{
    char message[lg_msg];
	int sock;
	struct hostent *hp;
	struct sockaddr_in adr_distant;
	char motif = 'a';



        printf("source UDP\n");
 		/*création d'un socket local*/
	  	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
       	{
        	printf("Echec de la creation du socket source UDP");
            exit(1);
      	}
      	memset((char*)&adr_distant,0,sizeof(adr_distant));
	    adr_distant.sin_family = AF_INET;
	    adr_distant.sin_port = htons(port);
	    //Affectation adresse IP
        if ((hp= gethostbyname(nom_station))==NULL)
        {
            printf("erreur gethostbyname");
            exit(1);
        }
        memcpy((char*)&(adr_distant.sin_addr.s_addr),hp->h_addr,hp->h_length);

        /*Création du message*/
        printf("SOURCE : lg_mess_emis=%d, port=%d, nb_envois=%d, TP=udp, dest=%s\n",lg_msg,port,nb_message,nom_station);
		for (int i=1; i<=nb_message; i++)
	    {
	    	construire_message(message, motif++,lg_msg);	
			afficher_message(message, lg_msg);			
			/*Envoi d'un message*/
	    		if ((sendto(sock, message, lg_msg, 0, (struct sockaddr*)&adr_distant, sizeof(adr_distant))) == -1)
				{
			  	printf("Erreur lors de l'envoi du message (sendto).\n");
				exit(1);
				}
	    }


        /*Fermeture du socket et libération de la mémoire*/
		if (close(sock) == -1)	
		{
			printf("Echec de destruction du socket\n");
			exit(1);
		}
		else
		{
			printf("SOURCE : fin\n");
		}
 
}
void tcp_source(int port, int nb_message, int lg_msg, char* nom_station)
{
    char message[lg_msg];
	/*Declarations*/
	int sock; //Représentation interne du socket local
	struct sockaddr_in adr_distant; //Adresse du socket distant
	int lg_adr_distant = sizeof(adr_distant);
	struct hostent *hp;
	char motif = 'a';

	/*Phase d'etablissement de connexion*/

	/*Création d'un socket local*/
       	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
       	{
               	printf("Echec de la creation du socket source TCP\n");
               	exit(1);
       	}

    	/*Construction de l'adresse de socket distant*/
    	//Affectation domaine et numero de port
       	memset((char*)&adr_distant, 0, sizeof(adr_distant));
       	adr_distant.sin_family = AF_INET; //domaine internet
       	adr_distant.sin_port = htons(port); //num de port
   		//Affectation adresse IP
    	if((hp = gethostbyname(nom_station)) == NULL)
      	{
            printf("Erreur lors de la requete de l'adresse IP (gethostbyname).\n");
        	exit(1);
      	}
    	memcpy((char*)&(adr_distant.sin_addr.s_addr), hp->h_addr, hp->h_length);

	/*Demande de connexion*/
	if(connect(sock,(struct sockaddr*) &adr_distant, lg_adr_distant) == -1)
	{
		perror("Erreur lors de la demande de la connexion (connect).\n");
		exit(1);
	}

	printf("SOURCE : lg_mess_emis=%d, port=%d, nb_envois=%d, TP=tcp, dest=%s\n",lg_msg,port,nb_message,nom_station);

	/*Phase de transfert de donnees*/
	for (int i=1; i<=nb_message; i++)
	{
  		/*Creation du message*/
	    construire_message(message, motif++,lg_msg);
		afficher_message(message, lg_msg);

		/*Envoi d'un message*/
    	if ((write(sock, message, lg_msg)) == -1)
		{
		  	printf("Erreur lors de l'envoi du message (write).\n");
			exit(1);
		}
	}


	/*Phase de fermeture d'une connexion*/
	if (shutdown(sock, 2) == -1)
	{
		printf("Erreur lors de la fermeture de la connexion (shutdown).\n");
		exit(1);
	}

	/*Destruction du socket*/
	if (close(sock) == -1)	
	{
		printf("Echec de destruction du socket");
		exit(1);
	}
	else
	{
		printf("SOURCE : fin\n");
	}
}


/*-----------------------------------Gestion TCP puits------------------------------*/
void tcp_puits(int port, int nb_message, int lg_msg, char* nom_station)
{

    char message[lg_msg];
	/*Declarations*/
	int sock; //Représentation interne du socket local
	int sock_bis; //Représention interne socket local dédié échange 
	struct sockaddr_in adr_distant; //Adresse du socket distant
	struct sockaddr_in adr_local; //Adresse du socket local
	int lg_adr_distant = sizeof(adr_distant);
	int lg_adr_local = sizeof(adr_local);
	int lg_msg_recu = -1; 
	//int taille_max_msg = 30;

	/*Phase d'etablissement de connexion*/

	/*Création d'un socket local*/
       	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
       	{
               	printf("Echec de la creation du socket puits TCP\n");
               	exit(1);
       	}

	/*Construction de l'adresse de socket local*/
	//Affectation domaine et numero de port
	memset((char*)&adr_local, 0, sizeof(adr_local));
	adr_local.sin_family = AF_INET; //domaine internet
	adr_local.sin_port = htons(port); //num de port
	adr_local.sin_addr.s_addr = INADDR_ANY; //toutes les adresses IP de la machine

	//Affectation de l'adresse au socket local à la représentation interne
	if (bind(sock, (struct sockaddr*) &adr_local, lg_adr_local) == -1)
	{
		printf("Echec du bind.\n");
		exit(1);
	}

	/*Dimensionnement de la file d'attente des demandes de connexion entrantes*/
	if (listen(sock, 5) == -1)
	{
		printf("Erreur de listen.\n");
		exit(1);
	}

	if (nb_message == -1){
            printf("PUITS : lg_mess_lu_max=%d, port=%d, nb_receptions=infini, TP=tcp\n",lg_msg,port);
        } else printf("PUITS : lg_mess_lu=%d, port=%d, nb_receptions=%d, TP=tcp\n",lg_msg,port,nb_message);

	while(1)
	{
    		/*Acceptation d'une demande de connexion*/
		if ((sock_bis = accept(sock, (struct sockaddr*) &adr_distant, (socklen_t *) &lg_adr_distant)) == -1)
		{
			printf("Echec du accept.\n");
			exit(1);
		}


		int i = 1;
        while ((lg_msg_recu = read(sock_bis, message, lg_msg)) > 0) { 
            afficher_message (message, lg_msg_recu);
            i++;
        }


		/*Phase de fermeture d'une connexion*/
		if (shutdown(sock_bis, 2) == -1)
		{
			printf("Erreur lors de la fermeture de la connexion (shutdown).\n");
			exit(1);
		}

		/*Destruction du socket*/
		if (close(sock_bis) == -1)	
		{
			printf("Echec de destruction du socket");
			exit(1);
		}
	}
}
/*---------------------------Emetteur TCP--------------------------------------*/
void emetteur_tcp(int port, int nb_message, int lg_msg, char* serveur_BAL)
{
    char message[lg_msg];
	/*Declarations*/
	int sock; //Représentation interne du socket local
	struct sockaddr_in adr_distant; //Adresse du socket distant
	int lg_adr_distant = sizeof(adr_distant);
	struct hostent *hp;
	char motif = 'a';

	/*Phase d'etablissement de connexion*/

	/*Création d'un socket local*/
       	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
       	{
               	printf("Echec de la creation du socket source TCP\n");
               	exit(1);
       	}

    	/*Construction de l'adresse de socket distant*/
    	//Affectation domaine et numero de port
       	memset((char*)&adr_distant, 0, sizeof(adr_distant));
       	adr_distant.sin_family = AF_INET; //domaine internet
       	adr_distant.sin_port = htons(port); //num de port
   		//Affectation adresse IP
    	if((hp = gethostbyname(nom_station)) == NULL)
      	{
            printf("Erreur lors de la requete de l'adresse IP (gethostbyname).\n");
        	exit(1);
      	}
    	memcpy((char*)&(adr_distant.sin_addr.s_addr), hp->h_addr, hp->h_length);

	/*Demande de connexion*/
	if(connect(sock,(struct sockaddr*) &adr_distant, lg_adr_distant) == -1)
	{
		perror("Erreur lors de la demande de la connexion (connect).\n");
		exit(1);
	}

	printf("SOURCE : lg_mess_emis=%d, port=%d, nb_envois=%d, TP=tcp, dest=%s\n",lg_msg,port,nb_message,nom_station);

	/*Phase de transfert de donnees*/
	for (int i=1; i<=nb_message; i++)
	{
  		/*Creation du message*/
	    construire_message(message, motif++,lg_msg);
		afficher_message(message, lg_msg);

		/*Envoi d'un message*/
    	if ((write(sock, message, lg_msg)) == -1)
		{
		  	printf("Erreur lors de l'envoi du message (write).\n");
			exit(1);
		}
	}


	/*Phase de fermeture d'une connexion*/
	if (shutdown(sock, 2) == -1)
	{
		printf("Erreur lors de la fermeture de la connexion (shutdown).\n");
		exit(1);
	}

	/*Destruction du socket*/
	if (close(sock) == -1)	
	{
		printf("Echec de destruction du socket");
		exit(1);
	}
	else
	{
		printf("SOURCE : fin\n");
	}
}











/*---------------------------Programme Principal-------------------------------*/


void main (int argc, char **argv)
{
	int c;
	extern char *optarg;
	extern int optind;
	int lg_msg=30;
	//char message[lg_msg];
	int protocole = 0; /* 0=tcp, 1=udp */
	int port;
	char *nom_station;
	int nb_message = -1; /* Nb de messages à envoyer ou à recevoir, par défaut : 10 en émission, infini en réception */
	int source = -1 ; /* 0=puits, 1=source */
	
	while ((c = getopt(argc, argv, "pn:su")) != -1) {
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
		case 'u':
		    protocole = 1;
		    printf("on est dans le protocole UDP");
			break;
			
		case 'n':
			nb_message = atoi(optarg);
			break;
			
		default:
			printf("usage: cmd [-p|-s][-n ##]\n");
			break;
		}
	}

    /*Recuperation du numero de port en dernier paramètre passé*/
	port = atoi(argv[argc-1]);
	
	
	/*Recuperation du nom de station */
	//if (source == 1)
	//    strcpy(nom_station,argv[argc-2]);
	
	if (source == -1) {
		printf("usage: cmd [-p|-s][-n ##]\n");
		exit(1) ;
	}

	if (source == 1)
	{
		printf("on est dans la source\n");
		if (nb_message == -1) {nb_message=10; strcpy(nom_station,argv[argc-2]);}
		if (protocole == 1) /*Gestion source UDP*/
		{
			udp_source(port, nb_message, lg_msg, nom_station);
		}
		else if (protocole == 0)/*Gestion source TCP*/
		{
			tcp_source(port, nb_message, lg_msg, nom_station);
		}
		else
		{
			printf("Erreur dans le choix de protocole.\n");
			exit(1);
		}  
     }   
	else
	{   
		printf("on est dans le puits\n");
		if (protocole == 1) /*Gestion puits UDP*/
		{
			udp_puits(port, nb_message, lg_msg);
		}
		else if (protocole == 0) /*Gestion source TCP*/
		{
			tcp_puits(port, nb_message, lg_msg, nom_station);
		}
		else
		{
			printf("Erreur dans le choix de protocole.\n");
			exit(1);
		}
	}	

	/*if (nb_message != -1) {
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

	}*/
	
    
}

