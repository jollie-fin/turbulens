#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> 

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define PORT 2001
#define closesocket(param) close(param)

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

static SOCKADDR_IN sin;
static SOCKET sock;
static SOCKADDR_IN csin;
static SOCKET csock;
extern double X;
extern double Y;
extern double B;

int sock_init()
{
   int yes = 1;
    socklen_t recsize = sizeof(sin);
    
    /* Socket et contexte d'adressage du client */

    socklen_t crecsize = sizeof(csin);
    
    int sock_err;
    
    
   /* Création d'une socket */
    sock = socket(AF_INET, SOCK_STREAM, 0);
    


#ifdef SERVEUR
    /* Si la socket est valide */
    if(sock != INVALID_SOCKET)
    {
        printf("La socket %d est maintenant ouverte en mode TCP/IP\n", sock);
        
        /* Configuration */
        sin.sin_addr.s_addr = htonl(INADDR_ANY);  /* Adresse IP automatique */
        sin.sin_family = AF_INET;                 /* Protocole familial (IP) */
        sin.sin_port = htons(PORT);               /* Listage du port */

        if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
          perror("setsockopt");
          exit(4);
        }
        sock_err = bind(sock, (SOCKADDR*)&sin, recsize);
        
        /* Si la socket fonctionne */
        if(sock_err != SOCKET_ERROR)
        {
            /* Démarrage du listage (mode server) */
            sock_err = listen(sock, 5);
            printf("Listage du port %d...\n", PORT);
            
            /* Si la socket fonctionne */
            if(sock_err != SOCKET_ERROR)
            {
                /* Attente pendant laquelle le client se connecte */
                printf("Patientez pendant que le client se connecte sur le port %d...\n", PORT);
                csock = accept(sock, (SOCKADDR*)&csin, &crecsize);
                printf("Un client se connecte avec la socket %d de %s:%d\n", csock, inet_ntoa(csin.sin_addr), htons(csin.sin_port));
            }
            else
                perror("listen");
        }
        else
            perror("bind");
    }
    else
        perror("socket");


    SOCKET sock;
    SOCKADDR_IN sin;

    /* Création de la socket */
    sock = socket(AF_INET, SOCK_STREAM, 0);

#else
    /* Configuration de la connexion */
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");
    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORT);

    /* Si le client arrive à se connecter */
    if(connect(sock, (SOCKADDR*)&sin, sizeof(sin)) != SOCKET_ERROR)
        printf("Connexion à %s sur le port %d\n", inet_ntoa(sin.sin_addr), htons(sin.sin_port));
    else
    {
        perror("Impossible de se connecter\n");
        exit (1);
    }
#endif
}

int sock_desinit()
{
#ifdef SERVEUR            
    /* Fermeture de la socket client et de la socket serveur */
shutdown(csock, 2);
    printf("Fermeture de la socket client\n");
    closesocket(csock);
    printf("Fermeture de la socket serveur\n");
    closesocket(sock);
    printf("Fermeture du serveur terminée\n");
#else
shutdown(sock, 2);
    /* On ferme la socket précédemment ouverte */
    closesocket(sock);
#endif
}

int echange()
{
#ifdef SERVEUR 
    send(csock,&X,sizeof(double),0);
    send(csock,&Y,sizeof(double),0);
    send(csock,&B,sizeof(double),0);
#else
    recv(sock,&X,sizeof(double),MSG_WAITALL);
    recv(sock,&Y,sizeof(double),MSG_WAITALL);
    recv(sock,&B,sizeof(double),MSG_WAITALL);
#endif
}
    
