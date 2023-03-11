//funzione che permette al server di bufferizzare i messaggi che vengono inviati
//dal un device dopo che il destinatario di una chat è offline.
//prima di bufferizzare il messaggio su file mi vado a scrivere
//il nome del mittente nel file mittenti.txt.
//questo file contiene i nomi delle persone che hanno mandato 
//un messaggio a username 
int bufferizzaMessaggio(int sd, fd_set * master, char * nomeMittente) { 
  
uint16_t lmsg; 
int len, ret; 
char buffer[BUF_LEN]; 
char username[DIM_MAX]; 
char path[DIM_PATH + DIM_MAX + 12]; 
FILE* fd; 
  
  fd = NULL; 
     
     if(nomeMittente == NULL) {
       printf("Errore nella bufferizzazione, NomeMittente nullo\n"); 
       return 0; 
     }

     //ricevo il nome del destinatario
     ret = recv(sd, (void*)&lmsg, sizeof(uint16_t), 0);
     if(ret < 0) { 
       perror("Errore nella receive\n");   
       // si è verificato un errore
       close(sd);
       // rimuovo il descrittore newfd da quelli da monitorare
       FD_CLR(sd, master); 
       return 0; 
     }
     else if(ret == 0) { 
      printf("l'utente %s e' uscito\n",nomeMittente);   
      close(sd);
      FD_CLR(sd, master); 
      return 0; 
     }
     // Rinconverto la dimensione in formato host     
     len = ntohs(lmsg); 
     // Ricevo i dati
     ret = recv(sd,(void*)username,len,0); 
     if(ret < 0) { 
      perror("Errore nella receive\n");   
      // si è verificato un errore
      close(sd);
      // rimuovo il descrittore newfd da quelli da monitorare
      FD_CLR(sd, master);
      return 0;   
     } 

     //l'utente è uscito dalla chat
     if(strncmp(username, "\\q", 2) == 0) {
        printf("l'utente è uscito dalla chat con me\n"); 
        return 2; 
     }
     //ricevo il messaggio 
     ret = recv(sd, (void*)&lmsg, sizeof(uint16_t), 0);
     if(ret < 0) { 
       perror("Errore nella receive\n");   
       // si è verificato un errore
       close(sd);
       // rimuovo il descrittore newfd da quelli da monitorare
       FD_CLR(sd, master); 
       return 0; 
     }
     else if(ret == 0) { 
      printf("l'utente %s e' uscito\n", nomeMittente);   
      close(sd);
      FD_CLR(sd, master);
      return 0;  
     }
     // Rinconverto la dimensione in formato host     
     len = ntohs(lmsg); 
     // Ricevo i dati
     memset(buffer, 0, BUF_LEN); 
     ret = recv(sd,(void*)buffer,len,0); 
     if(ret < 0) { 
      perror("Errore nella receive\n");   
      // si è verificato un errore
      close(sd);
      // rimuovo il descrittore newfd da quelli da monitorare
      FD_CLR(sd, master);
      return 0;   
     } 
     
     //andiamo a controllare se nomeMittente fosse gia presente sul file
     //mittenti.txt
      sprintf(path, "utenti_server/%s_server/mittenti.txt",username);
      fd = fopen(path, "r"); 
      if(fd == NULL) {
        printf("Errore nell'apertura del file\n"); 
        return 0; 
      }

     if(!controllaUsername(fd,nomeMittente)) {
       fclose(fd); 
       fd = fopen(path, "a+"); 
       if(fd == NULL) {
         printf("Errore nell'apertura del file\n"); 
         return 0; 
       }
       fprintf(fd,"%s\n",nomeMittente);
     }

     fclose(fd); 
     //vado a salvare il messaggio su file
     if(!bufferizzaMessaggioSuFile(fd, nomeMittente, username, getTimestamp(), buffer)) {
         printf("Errore nella bufferizzazione del messaggio nel server\n"); 
         return 0; 
     }
    return 1; 
}
