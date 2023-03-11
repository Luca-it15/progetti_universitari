/*funzione lato server che mi permette di gestire le notifiche
da mandare ai vari device. le notifiche riguardano 
l'avvenuta ricezione da parte degli utenti di messaggi pendenti
inviati quando quest'ultimi erano offline*/

void controllaNotificheServer(int i, fd_set* master) {

 char path[DIM_MAX + DIM_PATH + 12]; 
 char riga[DIM_MAX]; 
 char comando[CMD_LEN + DIM_MAX]; 
 char risposta[RESPONSE_LEN]; 
 char username[DIM_MAX]; 
 int ret; 
 FILE* fptr; 



        strcpy(username, nomeUtenteConnesso(i)); 
        sprintf(path, "utenti_server/%s_server/daNotificare.txt", username); 
          fptr = fopen(path, "r"); 
          if(fptr == NULL) {
              printf("errore nell'apertura del file daNotificare.txt\n");
              return;  
          }
          
          memset(riga, 0, DIM_MAX); 
          while(fgets(riga, DIM_MAX, fptr) != NULL) {
            //costruiamo il comando da inviare al device
            sprintf(comando,"_showAck %s", riga); 

            ret = send(i, (void*)comando, CMD_LEN + DIM_MAX, 0); 
            if(ret < 0) {
                perror("Errore nella send\n"); 
                FD_CLR(i, master); 
               aggiungiUtenteDisconnesso(aggiungiLogout(username, getTimestamp())); 
               return; 
            }

            memset(risposta, 0, RESPONSE_LEN); 
            ret = recv(i, (void*)risposta, DIM_RESPONSE, 0);
            if(ret < 0) {
                 perror("Errore nella recv\n"); 
                FD_CLR(i, master); 
               aggiungiUtenteDisconnesso(aggiungiLogout(username, getTimestamp())); 
               return; 
            } else if(ret == 0) {
                perror("Errore nella send\n");
                FD_CLR(i, master); 
               aggiungiUtenteDisconnesso(aggiungiLogout(username, getTimestamp())); 
               return;
            }
        //    printf("ho ricevuto: %s\n", risposta);
          }

          //dopo aver inviato tutto il contenuto del file,
          //lo cancelliamo in modo tale da non rinviare le stesse
          //notifiche
          fclose(fptr); 
           fptr = fopen(path, "w"); 
          if(fptr == NULL) {
              printf("errore nell'apertura del file daNotificare.txt\n");
              return;  
          }
          
        //  printf("cancellato il contenuto del file %s\n", path); 
          fclose(fptr); 

}