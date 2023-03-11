//file che contiene le direttive utili per i file del progetto
//essendo costanti o librerie che si ripetono spesso è conveniente 
//riunirle in un unico file
//include per le funzioni di libreria 
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h> 
#include <sys/stat.h> 

//direttive per le costanti
/*********************
***+++generale++++***/
/********************/
//indica il numero di porta su cui si avvia inizialmente il server
#define PORTA_SERVER 4243
//dimensione massima di messaggio 
#define BUF_LEN 512 
//dimensione massima dei comandi 
#define CMD_LEN 12
//dimenzione massima che prevediamo per un username e per una password(100 e 100), 
//infatti una password o un username superiori a 100 caratteri sarebbero ingestibili per un utente
#define DIM_MAX 100 
//dimesione massima in caratteri per una porta(al massimo 65536)
#define DIM_PORTA 7
//dimensione massima di un timestamp 
#define DIM_TIMESTAMP 20

#define REQUEST_LEN 5

//dimensione massima di un blocco di byte inviato durante la share file
#define DIM_BLOCCO 128
//dimensione massima di una riga letta da un file
#define DIM_MAX_RIGA 256

//lunghezza massima delle risposte del server
#define RESPONSE_LEN 60

#define DIM_INPUT 208
//dimensione del path standard dei file 
//ovvero la dimensione di "utenti_device/" + nomeUtente_device
//o la dimensione di "rubrica"
//oppure "utenti_server/" + nomeUtente_server o mittenti.txt
#define DIM_PATH 40
//costante per le risposte brevi
#define DIM_RESPONSE 7 
