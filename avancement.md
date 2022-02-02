Veuillez renseigner votre avancement à chaque étape achevée et testée et par défaut à la fin de chaque séance de TP 
# Avancement sur la Partie 1 du BE 

## Version 1 de tsock 
L'objectif principal de la 1ère séance est de développer la v1 de tsock: coder une version de la source et une version du puit capables d'échanger des messages en utilisant le service UDP.  Vous pouvez décomposer le travail en deux parties successives: la version "source" de "tsock" puis celle du "puit". Vous pouvez tester chaque étape de manière isolée, en utilisant la version enseignant de tsock (en la configurant comme puit, pour tester votre source ou en tant que sourcenetcat , pour votre version du puit).  Cela néanmoins suppose que vous soyez connecté(e) sur une machine INSA via le client VPN. A défaut, vous pouvez  utiliser l'utilitaire nc (netcat), disponible sous les différents systèmes d'exploitation. 

### Avancement sur la partie SOURCE UDP
veuillez cocher les seules cases qui correspondent aux étapes validées.  

[ ] la gestion des options -s, -u,  le nombre et Taille par défaut des messages , nom de la machine destinataire,  numéro de port du puit est opérationnelle

[ ] la création du socket UDP local et la construction de l'adresse du socket distant est correcte

[ ] l’envoi de  messages en utilisant l'appel système sendto (qui retourne une valeur >0 correspondant à la taille de chaque message envoyé) est fonctionnelle 

[ ] la réception côté puit (sur nc ou la version "enseignant" de tsock) des messages envoyés par votre client est correcte

### Avancement Point sur la partie puit UDP.

[ ] la prise en compte de l' option -p est correcte

[ ] la création du socket UDP local du puit et la construction de son adresse est correcte

[ ] la réception et l'affichage des messages reçus sont corrects

[ ] l'échange de messages tq décrits dans le cahier des charges entre vos versions source et puit de la version 1 de "tsock" est opérationnel

## Avancement sur la version 2 de tsock
La version 2 intègre l’utilisation de TCP pour l’échange des messages. Veuillez renseigner les étapes que vous avez traitées.  

[ ] la création du socket TCP local du puit et la construction de son adresse est correcte

[ ] l'acceptation de la demande d'établissement de connexion de la primitive "accept" est effective 

[ ] la réception et l'affichage des messages reçus  (en utilisant nc ou la version "enseignant" de tsock comme source)  sont corrects 

[ ] l'échange de messages entre vos versions source et puit de la version 1 de "tsock" est opérationnel

## Avancement version 3 de tsock

La version v3 de tsock intègre les fonctions de formatage et d'affichage des messages émis et reçus (selon le cahier des charges) ainsi que la gestion des options restantes : -n  et -l. Si toutes les fonctionnalités additionnelles de la version 3 sont validées par vos tests, vous devez cocher toutes les cases suivantes. Si ce n'est pas le cas, veuillez cocher les seules cases qui correspondent aux étapes validées.  

[ ] Le formattage et affichage des messages selon le cahier des charges sont opérationnels

[ ] la prise en compte de l'option -n en émission aussi bien avec UDP et TCP est correcte

[ ] la prise en compte de l'option -n en réception avec UDP est correcte

[ ] la prise en compte de l'option -n en réception avec TCP est correcte

[ ] la prise en compte de l'option -l est correcte


# PARTIE 2 du BE : Système de boites aux lettres 
## Travail à réaliser

Très grossièrement, comme indiqué dans la simplification du sujet de BE qui vous a été transmise vous aurez successivement à développer : 

- l’Emetteur  (l'option "-e" de tsock) : qui est une adaptation de la version v3 du "tsock" (de la première partie) pour principalement  demander l'établissement de connexion TCP avec le serveur BAL 
	
- Transmettre le PDU applicatif en charge de le déclarer en tant que émetteur et éventuellement indiquer la taille et nombre de messages qu'il émet
	
- Emettre les messages au serveur BAL clore la connexion TCP

Les fonctionnalités du serveur BAL (option "-b") relatives aux interactions avec les Emetteurs pour :

- accepter les demandes de connexions TCP et l'identification,par le traitement du PDU applicatif, du rôle "Emetteur" de l'application qui a initiée la demande de connexion et ses caractéristiques  (nombre et taille des messages) 

- prendre en charge les fonctions en lien avec la manipulation de la structure de données proposées (i.e. liste chaînée de boites aux lettres (BAL), d'une liste chaînée des messages d'une BAL) en réaction aux envois de messages d'une application "Emetteur"

- recherche de BAL relative à un récepteur

- creation/rajout de BAL d'un récepteur

- rajout d'un message dans une BAL d'un récepteur à la dernière position

Les fonctionnalités du serveur BAL (option "-b") relatives aux interactions avec les récepteurs pour :
- accepter les demandes de connexions TCP et l'identification, par le traitement du PDU applicatif, du rôle "Récepteur" de l'application qui a initiée la demande de connexion

- prendre en charge les fonctions en lien avec la manipulation de la structure de données pour le compte d'une application "Récepteur" :

- vérifier la présence d'une BAL associée à un récepteur et renvoyer l'accès à la liste des messages disponibles pour le récepteur  

- parcours des messages d'une BAL

Le Récepteur  (l'option "-r" de tsock) : qui est une adaptation de la version v3 du "tsock" (de la première partie) pour principalement : 

- demander l'établissement de connexion TCP avec le serveur BAL

- Transmettre le PDU applicatif en charge de le déclarer en tant que récepteur 	- prendre en charge la réception et affichage de ses éventuels messages transmis par le serveur BAL jusqu'à la fermeture de la connexion TCP déclenchée par le serveur BAL

## Avancement sur la partie 2

### Pour les fonctionnalités de l'émetteur (l'option "-e" de tsock)
 veuillez indiquer les étapes que vous avez validées.

[ ] demande d'établissement de connexion TCP avec le serveur BAL fonctionnelle

[ ] transmission du PDU applicatif en charge de le déclarer en tant que émetteur et éventuellement indiquer la taille et nombre de messages qu'il émet est fonctionnelle

[ ] émission des messages au serveur BAL fonctionnelle

[ ] cloture de la connexion TCP avec le serveur BAL fonctionnelle


### Pour les fonctionnalités du serveur BAL (option "-b") relatives aux interactions avec les Emetteur
veuillez indiquer étapes que vous avez validées

[ ] Acceptation des demandes de connexions TCP et l'identification,par le traitement du PDU applicatif, du rôle "Emetteur" de l'application qui a initiée la demande de connexion et ses caractéristiques  (nombre et taille des messages)  est fonctionnelle

[ ] recherche de la boîte aux lettres (BAL) relative à un récepteur fonctionnelle

[ ] creation/rajout de BAL d'un récepteur fonctionnelle

[ ] rajout d'un message dans une BAL d'un récepteur à la dernière position est fonctionnelle


### Pour les fonctionnalités du serveur BAL (option "-b") relatives aux interactions avec les Récepteurs
 veuillez indiquer les étapes que vous avez validées

[ ] acceptation des demandes de connexions TCP et l'identification, par le traitement du PDU applicatif, du rôle "Récepteur" de l'application qui a initiée la demande de connexion est fonctionnelle

[ ] vérification de la présence d'une BAL associée à un récepteur et renvoi de l'accès à la liste des messages disponibles pour le récepteur est fonctionnelle


### Pour les fonctionnalités du "Récepteur" (l'option "-e" de tsock) 
veuillez indiquer les étapes que vous avez validées.

[ ] demande de l'établissement de connexion TCP avec le serveur BAL est fonctionnelle

[ ] Transmission du PDU applicatif en charge de le déclarer en tant que récepteur  est fonctionnelle

[ ] prise en charge la réception et affichage de ses éventuels messages transmis par le serveur BAL jusqu'à la fermeture de la connexion TCP déclenchée par le serveur BAL est fonctionnelle

[ ] parcours des messages d'une BAL opérationnel
