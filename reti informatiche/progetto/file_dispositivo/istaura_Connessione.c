//funzione che mi permette di istaurare una connessione con un device 
//passando dal server, la funzione mi ritorna un intero che può assumere 
//i seguenti valori 
// -1: ci sono stati degli errori in fase di connessione, il server è spento
//  0: l'utente scelto per la connessione è offline
// > 0: è il descrittore di socket ottenuto dalla connessione.
//la modalità serve per descriminare se l'utente sta chiedendo di 
//istaurare la connessione per una chat normale o per un gruppo.
//dal punto di vista del server è ininfluente
//mode: 
//0: chat 
//1: group
//2: inGroup: modalità sempre relativa alla gestione dei gruppi
int istauraConnessioneDevice(int serverSock,int *fdmax, fd_set *m, char* username, 
      char* nomeUtente,char* sendGroup, int mode) {
  
  struct sockaddr_in srv_addr;  
  int ret, len, numPorta;
  int ris; //conterra il valore di ritorno
  int sd = 0; 
  char buffer[BUF_LEN];
  char risposta[RESPONSE_LEN];
  char porta[DIM_PORTA];  
  char cmd[CMD_LEN]; 
  uint16_t lmsg;
  
 memset(cmd, 0, sizeof(cmd)); 
 strcpy(cmd, "chat"); 
 ret = send(serverSock, cmd, strlen(cmd)+1, 0); 
 if(ret < 0) { 
   perror("Errore nella send\n");   
   // si è verificato un errore
   close(serverSock);
   // rimuovo il descrittore newfd da quelli da monitorare
   FD_CLR(serverSock, m); 
 }
 memset(buffer, 0, sizeof(buffer));   
 ret = recv(serverSock, (void*)risposta, RESPONSE_LEN, 0);  
 if(ret < 0) { 
   perror("Errore nella receive\n");   
   // si è verificato un errore
   close(serverSock);
   // rimuovo il descrittore newfd da quelli da monitorare
   FD_CLR(serverSock, m); 
 }
 else if(ret == 0) { 
   printf("chiusura server rilevata: impossibile connettersi con il device\n"); 
   ris = 0;    
   close(serverSock);
   // rimuovo il descrittore newfd da quelli da monitorare
   FD_CLR(serverSock, m); 
   ris = -1; 
   return ris; 
 } else { 
   //il server non è spento
   //invio le dimensioni del messaggio e il messaggio 
   //invio la dimensione di buffer 
   len = strlen(username) + 1;
   lmsg = htons(len); 

   ret = send(serverSock, (void*)&lmsg, sizeof(uint16_t), 0); 
   if(ret < 0) {
     perror("Errore nella send: \n");
     exit(-1);  
    }  
    //invio il messaggio contente il nome
    ret = send(serverSock, (void*)username, len, 0); 
    if(ret < 0) {
    perror("Errore nella send: \n"); 
    exit(-1); 
    }
     memset(risposta, 0, sizeof(risposta));
     //qui è il server che ci dice se l'utente è online oppure no
    ret = recv(serverSock, (void*)risposta, RESPONSE_LEN, 0); 
    if(ret < 0) { 
     perror("Errore nella receive\n");   
     // si è verificato un errore
     close(serverSock);
     // rimuovo il descrittore newfd da quelli da monitorare
     FD_CLR(serverSock, m); 
    }
    else if(ret == 0) { 
     printf("chiusura server rilevata: impossibile connettersi con il device\n"); 
     close(serverSock);
     ris = -1; 
     return ris; 
    } else { 
     if(strcmp(risposta, "online") == 0) { 
         printf("l'utente %s è online, instauro una connessione con lui\n", username);  
         //qui ricevero il numero di porta 
       ret = recv(serverSock, (void*)porta,DIM_PORTA, 0); 
       if(ret < 0) { 
        perror("Errore nella receive\n");   
        // si è verificato un errore
        close(serverSock);
       // rimuovo il descrittore newfd da quelli da monitorare
        FD_CLR(serverSock, m); 
       }
       //mando la conferma al server
       memset(risposta, 0, RESPONSE_LEN); 
       strcpy(risposta, "porta ricevuta\0"); 
       ret = send(serverSock, (void*)risposta, strlen(risposta),0); 
      if(ret < 0) { 
       perror("Errore nella receive\n");   
       // si è verificato un errore
       close(serverSock);
       // rimuovo il descrittore newfd da quelli da monitorare
       FD_CLR(serverSock, m); 
       }
       //ottengo il numero di porta 
       numPorta = atoi(porta);  
       //creo una connessione con il device con cui voglio parlare 
       sd = socket(AF_INET,SOCK_STREAM,0);
       /* Creazione indirizzo del server */
       memset(&srv_addr, 0, sizeof(srv_addr));
       srv_addr.sin_family = AF_INET;
       srv_addr.sin_port = htons(numPorta);
       inet_pton(AF_INET, "127.0.0.1", &srv_addr.sin_addr);
       
       ret = connect(sd, (struct sockaddr*)&srv_addr, sizeof(srv_addr)); 
       if(ret < 0){
        perror("Errore in fase di connessione: \n");
        exit(1);
       }
       FD_SET(sd, m);
       if(*fdmax < sd) 
        *fdmax = sd; 
       ris = sd; 
       memset(buffer, 0, sizeof(buffer));
       if(mode == 0)
       sprintf(buffer, "_chat %s", nomeUtente);
       else if(mode == 1) 
       sprintf(buffer, "_group %s %s",sendGroup, nomeUtente);
       else if(mode == 2)
       sprintf(buffer, "_inGroup %s %s",sendGroup, nomeUtente);
      len = strlen(buffer); 
      lmsg = htons(len);
      // Invio la dimensione dei dati che invierò
      ret = send(sd, (void*) &lmsg, sizeof(uint16_t), 0);
      if(ret < 0) {
       perror("Errore nella send: \n"); 
       exit(-1); 
      }
      ret = send(sd, (void*)buffer, len, 0); 
      if(ret < 0) {
       perror("Errore nella send: \n"); 
       exit(-1); 
      } 
     } 
     else
     //l'utente è offline, quindi provvedo ad avvisare 
      ris = 0;
    } 
   }
   return ris; 
}
