//la funzione invia il nome dell'utente connesso sul device
//in modo tale da chiedere al server se ci sono notiche per lui.
//tali notifiche riguaderanno il fatto se altri utenti hanno 
//letto i messaggi inviati dall'utente connesso quando erano offline.
void controllaNotifiche(int socketServer, char* userUtente) {

  char cmd[CMD_LEN]; 
  int ret; 
  
  strcpy(cmd, "_notifiche\0"); 
  ret = send(socketServer, (void*)cmd, CMD_LEN, 0);
  if(ret < 0) {
    perror("Errore nella send\n"); 
    exit(-1); 
  } 

  ret = send(socketServer, (void*)userUtente, strlen(userUtente) + 1, 0);
  if(ret < 0) {
    perror("Errore nella send\n"); 
    exit(-1); 
  } 

}