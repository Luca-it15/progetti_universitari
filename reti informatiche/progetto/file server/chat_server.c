//funzione per la gestione di una chat da parte del server.
//il server si limiterà a svolgere le seguenti azioni; 
//1) si mette in ricezione del nome utente da parte del device
//2) una volta ottenuto il nome, controlla se l'utente è online
//3) manda al device un messaggio dicendo se l'utente è online oppure no
//3.1) se l'utente è online
//3.1.a) prova a contattarlo e gli invia il messaggio
//3.1.a.a) nel caso fosse online invia il numero di porta al device che ha richiesto la chat con lui
//3.1.a.b) se non fosse piu online allora lo rimuove dalla lista degli utenti online e lo 
//         inserisce nella lista degli utenti disconnessi dopo aver assegnato il timestamp di logout
//3.1.b) l'utente si è disconnesso quindi possiamo gia dire al device che l'utente è offline
//3.2) sia nei casi 3.1.a.b sia nel caso 3.1.b il server inizia a bufferizzare i messaggi 
void chat_server(int i, char* nome,fd_set* fdchat, fd_set* master, struct utenteApplicazione* uo, struct utenteApplicazione* uno) { 
   
int ret, len;      
char username[DIM_MAX];
char buffer[BUF_LEN]; 
char risposta[RESPONSE_LEN]; 
uint16_t lmsg; 

time_t rawtime; 
struct tm* timeinfo;

char cmd[CMD_LEN];  
 //variabili per la porta e il socket dell'utente con cui 
//il device vuole comunicare 
char porta[DIM_PORTA]; 

int sd;

struct utenteApplicazione* utente;

 fflush(stdout);
 strcpy(buffer, "Richiesta di chat\0"); 
 ret = send(i, (void*) buffer, strlen(buffer)+1, 0);
 if(ret < 0) {
   perror("Errore in fase di comunicazione: \n");
 }
 fflush(stdout); 
 //ricevo la dimensione dal client 
 ret = recv(i, (void*)&lmsg, sizeof(uint16_t), 0); //il device mi manderà la lunghezza del messaggio
 if(ret < 0) { 
   perror("Errore nella receive\n");   
   // si è verificato un errore
   close(i);
   // rimuovo il descrittore newfd da quelli da monitorare
   FD_CLR(i, master); 
 }
 len = ntohs(lmsg); /*dimensione del messaggio che il server riceverà*/ 
 //riceviamo il nome utente con cui la persona vuole parlare 
 //tramite questo nome possiamo andare a vedere se l'utente è 
 //online oppure no
 //printf("1)\n"); 
 ret = recv(i, (void*)buffer, len, 0);
 /*controllo che il client non si sia disconesso, lo potrebbe fare in qualsiasi momento*/ 
 if(ret == 0){
    printf("CHIUSURA2 client rilevata!\n");
    fflush(stdout);
    //aggiungo il device nella lista dei disconnessi
    //mettendoli il logout 
    //nel caso non fosse piu online, termino la funzione
    time(&rawtime); 
    timeinfo = localtime(&rawtime);
   memset(buffer, 0, sizeof(buffer)); 
    printf("l'utente %s non è piu online\n", nome);
    sprintf(buffer, "%d-%d-%d %d:%d:%d", 
    timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday,
    timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec); 
    utente = aggiungiLogout(nome,buffer); 
    if(utente != NULL){   
    aggiungiUtenteDisconnesso(utente); 
    }
    // il client ha chiuso il socket, quindi
    // chiudo il socket connesso sul server
    close(i);
    // rimuovo il descrittore newfd da quelli da monitorare
    FD_CLR(i, master);
       return; 
 }
 else if(ret < 0){
   perror("ERRORE! \n");
   // si è verificato un errore
   close(i);
   // rimuovo il descrittore newfd da quelli da monitorare
   FD_CLR(i, master);
   } else {  
   //verifico se l'utente è online oppure no
   strcpy(username, buffer);
   memset(buffer, 0, sizeof(buffer)); 
    //recupero il socket dell'utente con cui il device vuole parlare
    //se sd == -1 allore l'utente non è online
    sd =  socketUtenteConnesso(username); 
  //  printf("2)\n");
    if(sd > -1) {  
    //  printf("3)\n"); 
      strcpy(cmd, "chat"); 
      sprintf(buffer,"%s %s", cmd, username); 
      //l'utente ci risulta online, quindi proviamo ad inviargli un messaggi
     // printf("3.1)\n");
      ret = send(sd, (void*)buffer, strlen(buffer)+1, 0); 
      if(ret < 0) {
        perror("Errore in fase di comunicazione: \n");
        // si è verificato un errore
         close(sd);
         // rimuovo il descrittore newfd da quelli da monitorare
         FD_CLR(sd, master);
       }
       //aspetto il presence ack da parte del destinatario
       ret = recv(sd, (void*)risposta, RESPONSE_LEN, 0);
       if(ret > 0) {  
         // printf("3.1.a)\n"); 
          //l'utente è online, quindi devo mandare il numero di porta al device
          //che mi ha richiesto il collegamento 
          strcpy(porta,portaUtenteConnesso(username)); 
          porta[DIM_PORTA - 1] = '\0'; 
          memset(buffer, 0, sizeof(buffer)); 
          //dico al device che è online
         // printf("4)\n");
          strcpy(risposta, "online\0"); 
          ret = send(i, (void*)risposta, strlen(risposta), 0); 
          //mando il numero di porta
           
          ret = send(i,(void*)porta, DIM_PORTA, 0); 
          if(ret < 0) { 
             perror("Errore nella send\n"); 
             close(i);
             FD_CLR(i, master); 
          }
          memset(risposta, 0, RESPONSE_LEN); 
          ret = recv(i, (void*)risposta, RESPONSE_LEN, 0); 
          if(ret < 0){
          perror("ERRORE! \n");
          // si è verificato un errore
          close(i);
          // rimuovo il descrittore newfd da quelli da monitorare
          FD_CLR(i, master);
           return; 
          } 
          else if(ret == 0) { 
           printf("CHIUSURA2 client rilevata!\n");
           fflush(stdout);
           //aggiungo il device nella lista dei disconnessi
           //mettendoli il logout 
           //nel caso non fosse piu online, termino la funzione 
           time(&rawtime); 
           timeinfo = localtime(&rawtime);
           sprintf(buffer, "%d-%d-%d %d:%d:%d", 
           timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday,
           timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec); 
           utente = aggiungiLogout(nome,buffer); 
           if(utente != NULL){  
            aggiungiUtenteDisconnesso(utente); 
            }
          }
        } 
        else if(ret == 0) { 
        //l'utente non è piu online, devo comunicarlo e 
        //prepararmi per bufferizzare i messaggi che mi invierà l'utente
          printf("CHIUSURA2 client rilevata!\n");
          fflush(stdout);
          //aggiungo il device nella lista dei disconnessi
         //mettendoli il logout 
         //nel caso non fosse piu online, termino la funzione 
          time(&rawtime); 
          timeinfo = localtime(&rawtime);
          printf("l'utente %s non è piu online\n", nome);
          sprintf(buffer, "%d-%d-%d %d:%d:%d", 
          timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday,
          timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec); 
          utente = aggiungiLogout(username,buffer); 
          if(utente != NULL) {   
            aggiungiUtenteDisconnesso(utente); 
           }
          // il client ha chiuso il socket, quindi
          // chiudo il socket connesso sul server
            close(sd);
          // rimuovo il descrittore newfd da quelli da monitorare
            FD_CLR(sd, master);

            //aggiungo i a quelli che vogliono chattare con il server per 
            //poter salvare i messaggi che sarebbero indirizzati all'utente che 
            //è offline 
            FD_SET(i, fdchat); 
            strcpy(risposta, "offline\0"); 
            ret = send(i, (void*)risposta, strlen(risposta), 0); 
            if(ret < 0) { 
             perror("Errore nella send\n"); 
             close(i);
             FD_CLR(i, master); 
             }
           }
          } 
      else {     
            //aggiungo i a quelli che vogliono chattare con il server per 
            //poter salvare i messaggi che sarebbero indirizzati all'utente che 
            //è offline 
             FD_SET(i, fdchat); 
            strcpy(risposta, "offline\0"); 
            ret = send(i, (void*)risposta, strlen(risposta), 0); 
            if(ret < 0) { 
             perror("Errore nella send\n"); 
             close(i);
             FD_CLR(i, master); 
             }              
           }
          }      
}



