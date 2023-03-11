/*funzione per gestire la chat. consideriamo la chat singola come chat di gruppo 
 formato da due persone. inizialmente viene chiamata la show per recuperare i messaggi
 pendenti inviati dall'utente con cui voglio fare la chat, dopo di che carichiamo tutta la chat
 e cerchiamo di istaurare con connessione con lui, se risulta online la chat prosegue 
 normalmente, sennò la chat avverrà con il server. 
 tramite il comando \u è possibile visualizzare gli utenti presenti nella nostra rubrica 
 che sono online.
 tramite il comando \a nomeUtente è possibile aggiungere un partecipante al gruppo*/
#include"istaura_Connessione.c"
#include"listaUtenti_device.c"

void chat_device(int serverSocket,int listener,int* fdmax, fd_set *master, char* username, 
  fd_set* socketChat, char* userUtente,int* status) {

   int len, ret, i; 
   uint16_t lmsg; 
   char buffer[BUF_LEN]; 
   char nomeUtente[DIM_MAX]; 
   char risposta[CMD_LEN + DIM_MAX]; 
   char comando[CMD_LEN]; 
   char nomeGruppo[DIM_MAX];
  
   char* nome; 
   int sd; //sd della persona con cui parlo
   fd_set read_fds;  
   struct Gruppo* g; 
   struct utenteApplicazione *ua; 
   int esci, offline;  
   FILE *fd = NULL; 

   FD_ZERO(&read_fds);
   offline = 0; //vale 1 se l'utente con cui voglio chattare è offline, 0 altrimenti

   stampaMenuChat(); 
   //chiamo la show device per controllare se ho messaggi
   //pendenti con username, nel caso li recupero e aggiorno
   //il file di chat
   show_device(serverSocket,username, userUtente, master, status); 
   //il server è spento, non posso iniziare una nuova conversazione
   if(!status) {
     printf("Server disconnesso, impossibile iniziare una nuovo conversazione\n"); 
     return; 
   }
   if(!caricaMessaggiDaFile(fd, userUtente, username))
     printf("Nessun messaggio da caricare\n");  

    //istauro una connessione con lui

    sd = socketUtenteConnesso(username);   
    if(sd <= 0) {
     sd = istauraConnessioneDevice(serverSocket,fdmax, master, username,
           userUtente," ", 0);  
     aggiungiUtenteOnline(sd, username, " ", " "); //se offline vale -1
    }
    
   //se dopo la istauraConnessione, sd è ancora a -1 allora vuol dire che 
   //il server è spento 
   if(sd == -1) { 
       //il server è disconnesso 
       *status = 0; 
       printf("Impossibile iniziare nuova chat: server spento\n"); 
       return; 
   } 
   if(sd == 0) { 
       //l'utente target della chat è offline quindi 
       //provvedo a fare bufferizzare i messaggi al server
       //rendendo il server un partecipante alla chat
     printf("utente offline, mando i messaggi al server\n"); 
     sd = serverSocket;
     offline = 1; 
   }
   
   //che sia il server o l'utente, lo aggiungo ai descrittori
   //con cui posso parlare
   FD_SET(sd, socketChat);  
   
   if(membroDelGruppo(sd) == 0)
   aggiungiAGruppo(sd, username); 
  
      while(1){ 
        read_fds = *master; 
        select(*fdmax+1, &read_fds, NULL, NULL,NULL);
        // scorro  i descrittori
        for(i=0; i<=*fdmax; i++){
         if(FD_ISSET(i, &read_fds)){   
             if(i==serverSocket){ 
                 memset(risposta, 0, RESPONSE_LEN);
                 memset(buffer, 0, BUF_LEN);  
                  ret = recv(i, (void*)risposta, RESPONSE_LEN, 0); 
                  if(ret < 0) {
                     perror("Errore in fase di ricezione del messaggio: \n");
                     exit(-1);
                  } else if(ret == 0) {
                      status = 0;
                      printf("il server si è disconnesso\n"); 
                      FD_CLR(serverSocket, master);
                      close(serverSocket);
                      continue;
                  }
                  memset(comando, 0, CMD_LEN); 
                  memset(nomeUtente, 0, DIM_MAX); 
            
                  sscanf(risposta, "%s %s", comando, nomeUtente); 
                  if(strcmp(comando, "chat") == 0) { 
                    //mando il presence ack
                    memset(risposta, 0, CMD_LEN + DIM_MAX);
                    strcpy(risposta, "presence ack\0"); 
                    ret = send(i, (void*) risposta, strlen(risposta), 0); 
                    if(ret < 0) { 
                      perror("errore in fase di invio della risposta: \n"); 
                    }
                  } else if(strcmp(comando, "_showAck") == 0) {
                     notifica(5, nomeUtente);
                      if(!aggiornaChat(userUtente, nomeUtente))
                      printf("Errore nell'aggiornamento della chat\n"); 
                  }
                } 
           else if(i == listener) 
                 accettaConnessione(listener, fdmax, master);  
           else if(i==0){
                  //preparo il messaggio e invio la dimensione
                memset(buffer, 0, sizeof(buffer)); 
                memset(nomeUtente, 0, sizeof(nomeUtente));
                memset(comando, 0, CMD_LEN); 
                fflush(stdout);  
                 read(STDIN_FILENO, buffer,BUF_LEN);
                fflush(stdout);
                sscanf(buffer, "%s %s", comando, nomeUtente);
                if(strncmp(buffer, "\\u", 2) == 0) { 
                  printf("richiedo la lista degli utenti online al server\n"); 
                  if(!listaUtenti_device(serverSocket, status, userUtente, master, uo)) {
                    printf("Errore nel richiedere la lista degli utenti connessi\n"); 
                    return; 
                  } 
                  continue; 
                }
                else if(strncmp(comando, "\\a", 2) == 0) {
                  //aggiungo un utente al gruppo
                 sd = istauraConnessioneDevice(serverSocket,fdmax, master, nomeUtente, userUtente,
                                               userUtente,2); 
                 if(sd == 0) {
                   printf("Devi aggiungere un utente online\n"); 
                   continue; 
                 }
                 aggiungiUtenteOnline(sd, nomeUtente, " ", " "); 
                 printf("hai aggiunto %s al gruppo\n", nomeUtente);   
                 if(membroDelGruppo(sd) == 0)
                 aggiungiAGruppo(sd, userUtente);  
                 FD_SET(sd, master);  
                 *fdmax = (*fdmax < sd) ? sd : *fdmax; 
                 g = group; 
                 //mando ad ogni membro del mio gruppo il comando
                 //_makegroup, in modo tale da far conoscere a tutti i 
                 //partecipanti chi sto mettendo nel gruppo
                 while(g != NULL) {
                    if(FD_ISSET(g->sd, socketChat)) {
                       memset(buffer, 0, sizeof(buffer)); 
                       sprintf(buffer,"_makegroup %s", nomeUtente); 
                       len = strlen(buffer); 
                       lmsg = htons(len);
                     // Invio la dimensione dei dati che invierò
                    ret = send(g->sd, (void*) &lmsg, sizeof(uint16_t), 0);
                    if(ret < 0) {
                     perror("Errore nella send: \n"); 
                     exit(-1); 
                   }
                   // Invio i dati
                   ret = send(g->sd, (void*) buffer, len, 0);
                   if(ret < 0) {
                    perror("Errore nella send: \n"); 
                     exit(-1); 
                   }

                  }
                    g = g->next; 
                 }  
                 FD_SET(sd, socketChat);
                 continue;
                
                } else if(strcmp(comando, "share") == 0) {
                 fflush(stdout); 
                 printf("condivido un file\n"); 
                if(share_file(nomeUtente, userUtente, master, socketChat) == 0)
                  printf("impossibile fare share\n");   
                 continue; 
               } 
               else if(strcmp(comando, "\\q") == 0) {  
                  printf("Sto uscendo dalla chat\n"); 
                  esci = 1; 
                  break; 
                }
                stampaMessaggio(buffer, "Tu",(offline + 1)); 
               //inviamo il messaggio a tutti i partecipanti del gruppo
               //se non abbiamo aggiunto nessuno al gruppo lo invieremo 
               //solo alla persona con cui volevamo parlare all'inizio
                g = group; 
               
              while(g != NULL) { 
                if(FD_ISSET(g->sd, socketChat)) {
                 if(offline){ 
                 printf("utente offline, mando messaggio al server\n"); 
                 //sto parlando con il server perchè l'utente è offline
                 //quindi invierò ogni volta il nome del destinatario
                 len = strlen(username); 
                 lmsg = htons(len);
                 ret = send(g->sd, (void*) &lmsg, sizeof(uint16_t), 0);
                 if(ret < 0) {
                 perror("Errore nella send: \n"); 
                 exit(-1); 
                 }
                 // Invio i dati
                 ret = send(g->sd, (void*) username, len, 0);
                 if(ret < 0) {
                 perror("Errore nella send: \n"); 
                 exit(-1); 
                 }        
                }
                len = strlen(buffer); 
                lmsg = htons(len); 
                // Invio la dimensione dei dati che invierò
                ret = send(g->sd, (void*) &lmsg, sizeof(uint16_t), 0);
                if(ret < 0) {
                 perror("Errore nella send: \n"); 
                 exit(-1); 
                }
                // Invio i dati
                ret = send(g->sd, (void*) buffer, len, 0);
                if(ret < 0) {
                 perror("Errore nella send: \n"); 
                 exit(-1); 
                }       
              }
              g = g->next;
             } 
            if(strncmp(buffer, "\\q", 2) != 0) 
                 if(!salvaMessaggioSuFile(fd, userUtente, " ", username, getTimestamp(),
                      buffer, offline + 1)) { 
                       printf("impossibile salvare messaggio su file\n");

                  }
            }else { 
                fflush(stdout); 
                memset(buffer, 0, sizeof(buffer)); 
                ret = recv(i, (void*)&lmsg, sizeof(uint16_t), 0);
                if(ret < 0) { 
                  perror("Errore nella receive\n");   
                  // si è verificato un errore
                  close(i);
                   // rimuovo il descrittore newfd da quelli da monitorare
                  FD_CLR(i, master); 
                  printf("esco; errore nella receive\n"); 
                  exit(0); 
                 }
                else if(ret == 0) { 
                   nome = nomeUtenteConnesso(i); 
                 if(nome != NULL) 
                 printf("l'utente %s e' uscito dalla chat\n",nome);   
                 printf("se non sei in un gruppo, per poter inviare altri messaggi\n"); 
                 printf("all'utente uscito, devi uscire e rientrare nella chat\n\n"); 
                 fflush(stdout); 
                 close(i);
                  FD_CLR(i, master);
                  rimuoviDalGruppo(i); 
                  aggiungiLogout(username, " ");  
                  continue; 
                 }
                 // Rinconverto la dimensione in formato host     
                 len = ntohs(lmsg); 
                 // Ricevo i dati
                 ret = recv(i,(void*)buffer,len,0); 
                if(ret < 0) { 
                  perror("Errore nella receive\n");   
                  // si è verificato un errore
                  close(i);
                  // rimuovo il descrittore newfd da quelli da monitorare
                  FD_CLR(i, master); 
                  exit(0);  
                 } 
                 sscanf(buffer, "%s %s %s", comando, nomeUtente, nomeGruppo); 
               if(nomeUtenteConnesso(i) != NULL) {  //i fa parte di chi vuole chattare con me 
                //o di chi lo sta gia facendo
                //controllo se i fa parte del gruppo
                //siamo nella parte dei messaggi che provengono
                //dai membri della chat
                if(FD_ISSET(i, socketChat)) { 
                 if(strcmp(comando, "_makegroup") == 0) {
                   printf("ho ricevuto la makegroup\n"); 
                   sd = istauraConnessioneDevice(serverSocket,fdmax, master,nomeUtente, nomeUtenteConnesso(i),
                                                 userUtente, 1); 
                   aggiungiUtenteOnline(sd, nomeUtente, " ", " ");
                   if(membroDelGruppo(sd) == 0)
                   aggiungiAGruppo(sd,nomeUtenteConnesso(i));
                   FD_SET(sd, socketChat);
                   printf("%s è stato aggiunto al gruppo \n", nomeUtente); 
                   continue; 
                 }
                  else if(strcmp(comando, "_share") == 0) {
                    notifica(4, nomeUtenteConnesso(i)); 
                    printf("Hai ricevuto il file %s da %s\n", nomeUtente,nomeUtenteConnesso(i) ); 
                    recv_file(i,nomeUtente, userUtente,master,socketChat);
                 continue; 
                  
                } 
                 else if(strncmp(buffer, "\\q", 2) != 0)  {
                   stampaMessaggio(buffer,nomeUtenteConnesso(i), 0); 
                  //chi parlava con me ha chiuso la chat
                 } else {
                   printf("l'utente %s è uscit* dalla chat\n", nomeUtenteConnesso(i)); 
                   printf("se non sei in un gruppo, per poter inviare altri messaggi\n"); 
                   printf("all'utente uscito, devi uscire e rientrare nella chat\n\n"); 
                   fflush(stdout);
                   //rimuoviamo l'utente dalla lista degli utenti con cui sto parlando
                   aggiungiLogout(nomeUtenteConnesso(i), " "); 
                   rimuoviDalGruppo(i);  
                   continue; 
                   }
                }else { 
                  if(strncmp(buffer, "\\q", 2) != 0)
                  notifica(1,nomeUtenteConnesso(i)); 

                 }
               }else {
                 //siamo nella parte dei messaggi che provengono da 
                 //chi non fa parte della chat
                 if(strcmp(comando,"_chat") == 0) {  
                    aggiungiUtenteOnline(i, nomeUtente, " ", " ");
                    notifica(0, nomeUtente); 
                      continue;   
                  } 
                  else if(strcmp(comando,"_group") == 0 || 
                              strcmp(comando,"_inGroup") == 0) {  
                    aggiungiUtenteOnline(i,nomeUtente , " ", " ");
                    if(membroDelGruppo(i) == 0)
                     aggiungiAGruppo(i, nomeGruppo); 
                    if(strcmp(username, nomeGruppo) == 0)
                    FD_SET(i, socketChat);
                    if(strcmp(comando,"_inGroup") == 0)
                    notifica(2, nomeGruppo); 
                      continue;    
                  } 
                   else if(strcmp(comando, "_share") == 0) {
                    notifica(4, nomeUtenteConnesso(i)); 
                    printf("Hai ricevuto il file %s da %s\n", nomeUtente,nomeUtenteConnesso(i) ); 
                    recv_file(i, nomeUtente, userUtente,master,socketChat); 
                    continue; 
                 } 
                }
                //qualunque sia il tipo di messaggio lo vado a salvare
               if(strncmp(buffer, "\\q", 2) != 0) {  
                if(membroDelGruppo(i) == 1) {
                 if(!salvaMessaggioSuFile(fd, userUtente,nomeUtenteConnesso(i),username, getTimestamp(),
                   buffer, 0)) { 
                   printf("impossibile salvare messaggio su file\n");
                  }
                 } else {
                   if(!salvaMessaggioSuFile(fd, userUtente,nomeUtenteConnesso(i), nomeUtenteConnesso(i), getTimestamp(),
                   buffer, 0)) { 
                   printf("impossibile salvare messaggio su file\n");
                  }
                 }   
                }
              }            
            } 
           
         }
         if(esci == 1) {
          printf("sono uscito\n");
          break;  
         }
       }
     g = group; 
     while(g != NULL) {
       if(FD_ISSET(g->sd, socketChat)) { 
        //prima di uscire comunico che ho finito di chattare
     len = strlen(buffer); 
     lmsg = htons(len);
     // Invio la dimensione dei dati che invierò
     ret = send(g->sd, (void*) &lmsg, sizeof(uint16_t), 0);
     if(ret < 0) {
      perror("Errore nella send: \n"); 
      exit(-1); 
     }
     ret = send(g->sd, (void*)buffer, len, 0); 
     if(ret < 0) {
      perror("Errore nella send: \n"); 
      exit(-1); 
     } 
    }
    g = g->next; 
  }
  //vado ad eliminare i membri del gruppo perchè ho finito di parlare con loro
  //se volessi riparlare con loro dovrei essere riaggiunto.
  //quando un utente esce, per potergli inviare altri messaggi devo uscire a rientrare nella chat
  g = group; 
  while(g != NULL) {
    if(FD_ISSET(g->sd, socketChat)) 
     rimuoviDalGruppo(g->sd); 
    g = g->next; 
  }

  //elimino i membri della chat che sono presenti 
  //tra gli utenti online, questo mi permette di 
  //riniziare le chat con loro e di controllare 
  //ogni volta che l'utente con cui voglio chattare 
  //è sempre online prima di cominciare la chat
  ua = uo; 
  while(ua != NULL) {
   if(FD_ISSET(ua->sd,socketChat))
    aggiungiLogout(nomeUtenteConnesso(ua->sd), " ");
   ua = ua->next; 
  }
  
  esci = 0;

  //ripulisco il set dei descrittori che parlano con me 
  FD_ZERO(socketChat); 
}
