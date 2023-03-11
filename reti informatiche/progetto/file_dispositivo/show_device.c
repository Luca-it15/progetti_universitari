//funzione per gestire la richiesta di show username lato device
//la funzione si occuperà di inviare l'opportuno comando al server
//e si metterà in attesa di ricevere il contenuto del file dei messaggi pendenti
//tali messaggi verranno aggiunti al file di chat con username
int show_device(int i, char* nomeUtente, char* userUtente, fd_set* master,int * status){

 char riga[DIM_BLOCCO]; 
 char comando[CMD_LEN];
 char path[DIM_PATH + DIM_MAX]; 
 char dest[DIM_PATH + 2*DIM_MAX]; 
 char risposta[RESPONSE_LEN]; 
 int ret, len; 
 uint16_t lmsg;
 int messaggio = 0; //se 0 indica che non mi ha inviato nessun messaggio, 1 altrimenti
 FILE* fd = NULL; 
 int primo = 1; //se sono alla prima riga del file
 //questa variabile mi servirà per evitare di stampare 
 //lo spazio all'inizio del file

 struct stat st = {0};
 
 //assumo che inizialmente il server sia online
 *status = 1; 


      //invio il comando al server
      strcpy(comando, "_show"); 
      ret = send(i, (void*)comando,CMD_LEN, 0); 
      if(ret < 0) {
          perror("Errore nella send\n"); 
          exit(-1); 
      }
      

      ret = send(i, (void*)nomeUtente,DIM_MAX, 0); 
      if(ret < 0) {
          perror("Errore nella send\n"); 
          exit(-1); 
      }


      //controllo se la directory è gia stata fatta, altrimenti
      //la creo 
      sprintf(path, "utenti_device/%s_device/", userUtente);
      if(stat(path, &st) == -1){
          mkdir(path, 0700);
      } 
              
      sprintf(dest, "%s%sChat.txt", path, nomeUtente);

      fd = fopen(dest, "a+t");
      if(fd == NULL){
        printf("Impossibile ricevere il file: percorso file errato\n");
        return 0;
      }  
      
      printf("\nL'utente %s mi ha inviato i seguenti messaggi pendenti:\n\n", nomeUtente);

      while(1) {           
        ret = recv(i, (void*)&lmsg, sizeof(uint16_t), 0); 
         if(ret == 0) {
         printf("il server si è disconnesso prima di aver terminato l'invio\n"); 
         *status = 0; 
         FD_CLR(i, master); 
       } else if(ret < 0) {
         perror("Errore nella recv\n"); 
         *status = 0; 
         FD_CLR(i, master);
         return 0; 
       } 
        len = ntohs(lmsg); 
        memset(riga, 0, DIM_BLOCCO);  
        ret = recv(i, (void*)riga,len, 0); 
        if(ret < 0) {
         perror("Errore nella recv\n"); 
         *status = 0; 
         FD_CLR(i, master);
         return 0;
        }     

        if(strncmp(riga, "_showfine",5) == 0) {
         break;    
        }

        messaggio = 1;        
        //vado a scrivere su file ciò che ho ricevuto
       
        if(!primo && spazioDaStampare(nomeUtente, strlen(nomeUtente), riga)) {
         fprintf(fd, "\n%s", riga);
          printf("\n%s", riga);
        }
        else {
         fprintf(fd, "%s", riga);
         printf("%s", riga); 
        }
        primo = 0; 
        memset(riga, 0, DIM_BLOCCO);  
        memset(risposta, 0, RESPONSE_LEN); 
        lmsg = 0; 
        strcpy(risposta, "okay\0"); 
        ret = send(i,(void*)risposta, RESPONSE_LEN, 0); 
        if(ret < 0) {
         perror("Errore nella send\n"); 
         *status = 0; 
         FD_CLR(i, master);
         return 0;
        }  
       }
      
        if(!messaggio) 
         printf("Non ho ricevuto nessun messaggio pendente\n");
        else 
         fprintf(fd, "\n");
         
        printf("\n\n"); 

        memset(risposta, 0, RESPONSE_LEN);
        strcpy(risposta, "finito\0"); 
        ret = send(i,(void*)risposta, RESPONSE_LEN, 0); 
        if(ret < 0) {
         perror("Errore nella send\n"); 
         *status = 0; 
         FD_CLR(i, master);
         return 0;
        }  
       fflush(stdout); 
      fclose(fd); 
    return 1;
}

