//questo file contiene sia la funzione per inviare file 
//sia quella per riceverlo.

/*funzione per l'invio di file, può essere inviato a un utente con cui vorrei chattare
o con cui sto effettivamente chattando. */
int share_file(char * nomeFile, char* userUtente, fd_set* master,fd_set* socketChat) {
  
 char bufshare[CMD_LEN + 2*DIM_MAX]; 
 char path[DIM_PATH + DIM_MAX]; 
 char risposta[RESPONSE_LEN]; 
 uint16_t lmsg; 
 int ret, len; 
 struct Gruppo* g; 
 char riga[DIM_BLOCCO]; 
 FILE* fd = NULL; 


    sprintf(path,"utenti_device/%s_device/%s", userUtente, nomeFile); 
   
   //apro il file in binario, in modo tale da poter inviare
   //qualsiasi tipo di file
   fd = fopen(path, "rb"); 
   if(fd == NULL) {
     printf("Inserire un nome di file valido\n"); 
     return 0; 
   }

   memset(bufshare, 0, CMD_LEN + DIM_MAX); 
   sprintf(bufshare, "_share %s %s", nomeFile, userUtente); 
   len = strlen(bufshare) + 1; 
   lmsg = htons(len); 

   g = group; 
           
   while(g != NULL) {
     if(FD_ISSET(g->sd, socketChat)) {
       ret = send(g->sd, (void*)&lmsg, sizeof(uint16_t), 0); 
       if(ret < 0) {
         perror("Errore nella send\n"); 
          aggiungiLogout(nomeUtenteConnesso(g->sd), " "); 
         rimuoviDalGruppo(g->sd); 
         FD_CLR(g->sd, socketChat); 
         FD_CLR(g->sd, master);
         return 0;
       }
       ret = send(g->sd, (void*)bufshare, len, 0); 
       if(ret < 0) {
         perror("Errore nella send\n"); 
          aggiungiLogout(nomeUtenteConnesso(g->sd), " "); 
         rimuoviDalGruppo(g->sd); 
         FD_CLR(g->sd, socketChat); 
         FD_CLR(g->sd, master);
         return 0;
       }
      }
      g = g->next; 
     }
     memset(bufshare, 0, CMD_LEN + DIM_MAX); 
     memset(&lmsg, 0, sizeof(uint16_t));
     memset(path, 0,DIM_PATH + DIM_MAX);

     while(!feof(fd)) {
      memset(riga, 0,DIM_BLOCCO); 
      fgets(riga, DIM_BLOCCO, fd);  
     // fread(riga, 1, DIM_BLOCCO, fd);  
      g = group; 
      while(g != NULL) { 
      if(FD_ISSET(g->sd, socketChat)) {
       len = strlen(riga) + 1; 
       lmsg = htons(len); 

       ret = send(g->sd, (void*)&lmsg, sizeof(uint16_t), 0); 
       if(ret < 0) {
         perror("Errore nella send\n"); 
          aggiungiLogout(nomeUtenteConnesso(g->sd), " "); 
         rimuoviDalGruppo(g->sd); 
         FD_CLR(g->sd, socketChat); 
         FD_CLR(g->sd, master);
         return 0;
       }
       ret = send(g->sd, (void*)riga, len, 0); 
       if(ret < 0) {
         perror("Errore nella send\n"); 
          aggiungiLogout(nomeUtenteConnesso(g->sd), " "); 
         rimuoviDalGruppo(g->sd); 
         FD_CLR(g->sd, socketChat); 
         FD_CLR(g->sd, master);
         return 0;
       }
        
       memset(risposta, 0, RESPONSE_LEN); 
 
       ret = recv(g->sd, (void*)risposta, RESPONSE_LEN, 0); 
       if(ret == 0) {
         aggiungiLogout(nomeUtenteConnesso(g->sd), " "); 
         rimuoviDalGruppo(g->sd); 
         FD_CLR(g->sd, socketChat); 
         FD_CLR(g->sd, master); 
       } else if(ret < 0) {
         perror("Errore nella recv\n"); 
         aggiungiLogout(nomeUtenteConnesso(g->sd), " "); 
         rimuoviDalGruppo(g->sd); 
         FD_CLR(g->sd, socketChat); 
         FD_CLR(g->sd, master);
         return 0; 
       } 
      }
        g = g->next; 
       }
     }

//ho finito di mandare il file quindi mando il comando 
//di terminazioni a tutti quelli coinvolti nell'invio
     memset(bufshare, 0, CMD_LEN + DIM_MAX); 
     strcpy(bufshare, "_sharefine"); 
     len = strlen(bufshare); 
     lmsg = htons(len);

     g = group; 
    while(g != NULL) {
     if(FD_ISSET(g->sd, socketChat)) { 
      ret = send(g->sd, (void*)&lmsg, sizeof(uint16_t), 0); 
      if(ret < 0) {
         perror("Errore nella send\n"); 
          aggiungiLogout(nomeUtenteConnesso(g->sd), " "); 
         rimuoviDalGruppo(g->sd); 
         FD_CLR(g->sd, socketChat); 
         FD_CLR(g->sd, master);
         return 0;
       } 

     ret = send(g->sd, (void*)bufshare, len, 0); 
     if(ret < 0) {
         perror("Errore nella send\n"); 
          aggiungiLogout(nomeUtenteConnesso(g->sd), " "); 
         rimuoviDalGruppo(g->sd); 
         FD_CLR(g->sd, socketChat); 
         FD_CLR(g->sd, master);
         return 0;
       } 
     }
    g = g->next; 
   } 
  fclose(fd); 
  return 1; 
}

//funzione per ricevere il file, verrà chiamata
//quando l'utente riceverà il comando _share
int recv_file(int i, char* nomeFile, char* userUtente, fd_set* master,fd_set* socketChat){
  
 char path[DIM_PATH + DIM_MAX]; 
 char dest[DIM_PATH + 2*DIM_MAX]; 
 char risposta[RESPONSE_LEN]; 
 int ret, len; 
 uint16_t lmsg;
 FILE* fd = NULL; 

 struct stat st = {0};

 char riga[DIM_BLOCCO];
   

      //controllo se la directory è gia stata fatta, altrimenti
      //la creo 
      sprintf(path, "utenti_device/%s_device/", userUtente);
      if(stat(path, &st) == -1){
          mkdir(path, 0700);
      } 
              
      sprintf(dest, "%s%s ", path, nomeFile);

      fd = fopen(dest, "wb");
      if(fd == NULL){
        printf("Impossibile ricevere il file: percorso file errato\n");
        return 0;
      }  

      memset(dest, 0, DIM_PATH + 2*DIM_MAX); 
      memset(path, 0, DIM_PATH + DIM_MAX);  

      while(1) {            
        ret = recv(i, (void*)&lmsg, sizeof(uint16_t), 0); 
         if(ret == 0) { 
         aggiungiLogout(nomeUtenteConnesso(i), " "); 
         rimuoviDalGruppo(i); 
         FD_CLR(i, socketChat); 
         FD_CLR(i, master); 
       } else if(ret < 0) {
         perror("Errore nella recv\n"); 
         aggiungiLogout(nomeUtenteConnesso(i), " "); 
         rimuoviDalGruppo(i); 
         FD_CLR(i, socketChat); 
         FD_CLR(i, master);
         return 0; 
       } 
        len = ntohs(lmsg); 
        memset(riga, 0, DIM_BLOCCO); 
        ret = recv(i, (void*)riga,len, 0); 
        if(ret < 0) {
         perror("Errore nella recv\n"); 
         aggiungiLogout(nomeUtenteConnesso(i), " "); 
         rimuoviDalGruppo(i); 
         FD_CLR(i, socketChat); 
         FD_CLR(i, master);
         return 0;
        }
        if(strncmp(riga, "_sharefine",7) == 0) 
          break;           
        //vado a scrivere su file ciò che ho ricevuto
 
        //len = fwrite(riga, 1 ,len, fd); 
        len = fprintf(fd, "%s", riga); 
        memset(risposta, 0, RESPONSE_LEN); 
        strcpy(risposta, "okay\0"); 
        ret = send(i,(void*)risposta, RESPONSE_LEN, 0); 
        if(ret < 0) {
         perror("Errore nella send\n"); 
          aggiungiLogout(nomeUtenteConnesso(i), " "); 
         rimuoviDalGruppo(i); 
         FD_CLR(i, socketChat); 
         FD_CLR(i, master);
         return 0;
        }  
        memset(riga, 0,DIM_BLOCCO + 1); 
       }

      fclose(fd); 
    return 1;
}


    
