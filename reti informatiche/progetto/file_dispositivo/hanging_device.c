//funzione hanging: l'utente richiede al 
//server le seguenti informazioni 
//per ogni utente che ha contattato 
//il richiedente quando era offline: 
//- nome utente
//- numero dei messaggio
//- timestamp dell'ultimo messaggio
void hanging(int serverSocket, int *serverStatus, fd_set * master) {
  
  char* risposta = "ok\0"; 
  char buffer[DIM_MAX + 3 + DIM_TIMESTAMP]; 
  char username[DIM_MAX]; 
  char num[3]; 
  char timestamp[DIM_TIMESTAMP]; 
  char* cmd = "_hanging\0"; //conterra il comando _hanging 
  int ret;
  int numMess; 
  int messaggi = 0; //vale 0 se non ho messaggi pendenti, 1 altrimenti

  //inviamo il comando
  
  ret = send(serverSocket, (void*)cmd, CMD_LEN, 0); 
  if(ret < 0) {
   perror("Errore nella send\n");
   exit(-1); 
  }

  printf("\n\n/-------------- HANGING -------------- \\\n"); 
  //entriamo nel ciclo dove ricevemo le
  //informazioni dei messaggi pendenti
  numMess = 0; 
  while(1) {
      numMess = 0; 
      ret = recv(serverSocket,(void*)buffer,DIM_MAX + 3 + DIM_TIMESTAMP , 0); 
      if(ret == 0) {
          //il server si è spento
          serverStatus = 0; 
          FD_CLR(serverSocket, master); 
          printf("Il server si è disconnesso, impossibile terminare la hanging\n"); 
          return; 
      }
     //controllo se ho ricevuto il carattere di terminazione
     //nel caso esco
     if(strncmp(buffer, "_hangingfine",12) == 0)
       break; 
     
     sscanf(buffer,"%s %s %s", username, num, timestamp); 
     if(num != NULL) {
      numMess = atoi(num); 
      if(numMess != 0) {
       messaggi = 1; 
       printf("\n***************************************\n"); 
       printf("%s\n", buffer); 
       printf("***************************************\n");
      }
    }
     ret = send(serverSocket, (void*)risposta, DIM_RESPONSE, 0); 
     if(ret < 0) {
      perror("Errore nella send\n");
      exit(-1); 
     }

     memset(buffer, 0, DIM_MAX + 3 + DIM_TIMESTAMP); 
     memset(username, 0, DIM_MAX); 
     memset(num, 0, 3); 
     memset(timestamp, 0, DIM_TIMESTAMP); 
    }

    if(!messaggi) {
      printf("Nessun messsaggio pendente\n"); 
    }
    
    printf("\n\\----------------------------------------/\n\n"); 
    fflush(stdout);

}
