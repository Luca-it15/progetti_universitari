//funzione di risposta alla richiesta della lista degli utenti online dai device 
//inviamo la lista degli utenti online usando la lista uo, quando raggiungo la fine 
//della lista inviamo il comando di terminazione "_fine"

int listaUtenti_server(int sd, struct utenteApplicazione* uo, fd_set* master) { 
    char buffer[DIM_MAX]; 
    char fine[CMD_LEN] = "_fine\0"; 
    char conferma[CMD_LEN]; 
    int ret;
    char* nome; 
    struct utenteApplicazione* utente = NULL; 

    while(uo != NULL) {
      
      strcpy(buffer, uo->user_dest); 
      ret = send(sd, (void*)buffer, DIM_MAX, 0); 
      if(ret < 0) {
          perror("Errore nella send: \n"); 
          return 0; 
      }
      //ack di conferma per capire se il device che 
      //sta ricevendo la lista è ancora online oppure no
      ret = recv(sd,(void*)conferma, CMD_LEN, 0); 
      if(ret < 0) {
          perror("Errore nella recv: \n"); 
          return 0; 
      } else if(ret == 0) {
          FD_CLR(sd, master); 
          nome = nomeUtenteConnesso(sd); 
          utente = aggiungiLogout(nome, getTimestamp()); 
          aggiungiUtenteDisconnesso(utente); 
          return 1; //ritorniamo 1 perchè non è una situazione di errore
      } else { 
          //avanzo il puntatore 
         uo = uo->next; 
      }


    } 
     //comunico al device che ho finito la lista
     ret = send(sd, (void*)fine, CMD_LEN, 0); 
      if(ret < 0) {
          perror("Errore nella send: \n"); 
          return 0; 
      }

      return 1; 
}
