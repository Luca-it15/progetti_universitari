//file che contiene le funzioni di stampa all'interno del progetto
#include"costanti.c"

void stampaMenuInizialeDevice(int porta) { 
     printf("\n\nBenvenuto!\n\n"); 
    printf("\nporta: %d\n", porta);
    printf("\nporta del server: %d\n", PORTA_SERVER); 
    printf("\n\ni comandi disponibili sono:\n\n"); 
    printf("signup srv_port username password (per registarsi)\n\n"); 
    printf("in srv_port username password (per il login)\n\n"); 
    printf("esc (per uscire)\n\n");  
}



void stampaMenuServer() {
    fflush(stdout); 
    printf("\n\n******************SERVER STARTED*****************\n\n"); 
    printf("Digita un comando: \n\n"); 
    printf("1)help --> mostra i dettagli dei comandi\n"); 
    printf("2)list --> mostra un elenco degli utenti connessi\n"); 
    printf("3)esc  --> chiude il server\n");
    fflush(stdout); 
}

void help() {
    fflush(stdout); 
    printf("\n\nComando help: fornisco le decrizioni sui comandi\n\n"); 
    printf("\n\n2)list: Mostra l'elenco degli utenti connessi alla rete\n"); 
    printf("        indicando username, timestamp di connesione e numero\n"); 
    printf("        di porta nel formato 'username*timestamp*porta'\n\n");
    printf("\n\n3)esc: termina il server chiudendo il socket di ascolto e termina il processo\n\n");
    fflush(stdout);   
}


void stampaMenuDevice(char * userUtente) {
    fflush(stdout); 
    printf("\n\nBenvenuto %s\n\n", userUtente); 
    printf("i comandi disponibili sono: \n\n"); 
    printf("1)hanging: ricevi la lista dei messaggi pendenti mentre eri offline\n\n"); 
    printf("2)show username: ricevi i messaggi pendenti da username\n\n"); 
    printf("3)chat username: avvia una chat con l'utente username\n\n"); 
    printf("4)share file_name: invia il file file_name agli utenti con cui\n"); 
    printf("                   stai chattando\n\n");
    printf("5)addr username: ti permette di aggiungere un utente alla rubrica\n\n"); 
    printf("6)listr: mostra la rubrica dell'utente\n\n"); 
    printf("7)remover username: rimuovo l'username della rubrica dell'utente\n\n");
    printf("8)out: esci dall'applicazione\n\n");
    fflush(stdout); 
}

//funzione che mi restituisce il timestamp
char* getTimestamp() { 

 char *buffer; 
 time_t rawtime; 
 struct tm* timeinfo;
 
 buffer = (char*)malloc(sizeof(char)*DIM_TIMESTAMP); 
 time(&rawtime); 
 timeinfo = localtime(&rawtime);
 sprintf(buffer, "%d-%d-%d %d:%d:%d", 
       timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday,
       timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
  
  return buffer; 
}

//funzione che mi permette di stampare il messaggio nel formato
//nome utente mittente
//"messaggio"
//timestamp di invio
void stampaMessaggio(char* buffer, char* username, int mode) {

 char timestamp[DIM_TIMESTAMP]; 
 char giorno[9]; 
 char orario[9]; 
 strcpy(timestamp , getTimestamp()); 
 sscanf(timestamp, "%s %s", giorno, orario); 
 
 
 printf("\n"); 

 if(mode == 1) 
  printf("**\n");
 else if(mode == 2) 
  printf("*\n");  
 printf("- %s\n", username);
 printf(">> "); 
 printf("%s", buffer); 
 if(mode == 0)
  printf("ricevuto alle %s del %s\n", orario, giorno);
 else
  printf("inviato alle %s del %s\n", orario, giorno);
 printf("\n");
}

//funzione per la gestione delle notifiche all'interno dell'applicazione
void notifica(int mode, char* username) { 
    printf("\n**************\nhai una nuova notifica\n"); 
    switch(mode) { 
        case 0: { 
            printf("l'utente %s vuole iniziare una chat con te", username); 
            break; 
        }
        case 1: { 
            printf("l'utente %s ti ha inviato un messaggio", username); 
            break; 
        }
        case 2: {
            printf("l'utente %s ti ha aggiunto al suo gruppo ", username); 
            printf("per poterti unire digita il comando chat %s", username); 
            break; 
        }
        case 3: {
            printf("hai un nuovo messaggio dal gruppo %s", username); 
            break; 
        }
        case 4: {
            printf("hai ricevuto un nuovo file da %s", username); 
            break; 
        }
        case 5: {
            printf("l'utente %s ha ricevuto i tuoi messaggi", username); 
            break; 
        }
    }
    printf("\n**************\n"); 
}

void stampaMenuChat() {
 printf("\n\n------ BENVENUTO NELLA CHAT ------\n\n"); 
 printf("Sono disponibili i seguenti comandi:\n\n"); 
 printf("\n-) \\u : per richiedere la lista degli utenti \n"); 
 printf("           presenti in rubrica che sono online\n");
 printf("\n-) \\a username: per aggiungere un utente alla chat \n"); 
 printf("                   formando un gruppo\n"); 
 printf("\n-) share nomeFile: per inviare agli utenti con cui stai parlando\n"); 
 printf("                     o con cui vuoi parlare, un file\n");
 printf("--------------------------------------------------------\n"); 
 printf("----- PREMI UN LETTERA + INVIO PER CONTINUARE -----\n\n"); 
 getchar(); 
 fflush(stdout);
}

