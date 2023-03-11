//questo file raccoglie le funzioni utili per poter eseguire 
//operazioni su file
#include"costanti.c"



//salvo i messaggi che avvengono in una chat su file, tale file viene 
//creato all'interno di una directory con il nome dell'utente che sta 
//usando l'applicazione, in tal modo possiamo avere cartelle 
//divise per gli account registrati sul device 
//il flag p indica se il messaggio è stato ricevuto(0) oppure inviato(1) 

int salvaMessaggioSuFile(FILE* fd, char* userUtente,char* nomeUtente, char* username, char* timestamp, 
                          char* buffer, int p){ 
    
    char path[DIM_MAX + DIM_PATH]; //nome della path in cui verrà creata la directory 
    char nomeFile[2*DIM_MAX + DIM_PATH]; //nome del file(percorso relativo)
    //messaggio che verrà salvato 
    //nella forma: 
    //nomeUtente
    //messaggio
    //timestamp di ricezione
    char messaggio[BUF_LEN + DIM_MAX + DIM_TIMESTAMP]; 
    struct stat st = {0};
    char giorno[9]; 
    char orario[9];  
    char data[DIM_TIMESTAMP]; 
    sscanf(timestamp, "%s %s", giorno, orario); 
    sprintf(path, "utenti_device/%s_device/", userUtente);
    
    if(stat(path, &st) == -1){
        mkdir(path, 0750);
    }
 
    sprintf(nomeFile, "%s%sChat.txt", path,username); 
    fd = fopen(nomeFile, "a+"); 
    if(fd == NULL) {
      printf("Impossibile aprire il file\n"); 
      return 0; 
    }
    if(p == 0) {
     sprintf(data, "ricevuto alle %s del %s\n", orario, giorno);   
     sprintf(messaggio, "-%s\n%s%s", nomeUtente, buffer, data);
    } 
    else if(p == 1) {
      sprintf(data, "inviato alle %s del %s\n", orario, giorno); 
     sprintf(messaggio, "**\n-%s\n%s%s", "Tu", buffer, data);
    } 
    else if(p == 2) { 
     sprintf(data, "inviato alle %s del %s\n", orario, giorno); 
     sprintf(messaggio, "*\n-%s\n%s%s", "Tu", buffer, data); 
    }

    fprintf(fd, "%s\n",messaggio);
    fclose(fd);

    return 1; 
}

//funzione che mi permette di recuperare i messaggi di un chat che 
//sono stati salvati in precedenza 
int caricaMessaggiDaFile(FILE* fd, char* userUtente, char * username) {
   char mess[DIM_MAX_RIGA];
   char nomeFile[2*DIM_MAX + DIM_PATH];


   sprintf(nomeFile, "utenti_device/%s_device/%sChat.txt", userUtente,username); 
    fd = fopen(nomeFile, "rt"); 
    if(fd == NULL) {
      return 0; 
    }


   //faccio l'accesso al file dall'inizio
  if(fseek(fd,0,SEEK_SET) != 0) {
    printf("errore nella fseek\n"); 
    return 0; 
  }

  while( fgets(mess, DIM_MAX_RIGA, fd) ){
      printf("%s", mess);
  }

   printf("\n");
   fclose(fd); 
   return 1; 
}

//funzione per salvare su file per il server
int bufferizzaMessaggioSuFile(FILE* fd, char* userUtente, char* username, char* timestamp, 
                          char* buffer){ 
    
    char path[DIM_MAX + DIM_PATH]; //nome della path in cui verrà creata la directory 
    char nomeFile[2*DIM_MAX + DIM_PATH]; //nome del file(percorso relativo)
    //messaggio che verrà salvato 
    //nella forma: 
    //nomeUtente
    //messaggio
    //timestamp di ricezione
    char messaggio[BUF_LEN + DIM_MAX + DIM_TIMESTAMP]; 
    char giorno[9]; 
    char orario[9];  
    char data[DIM_TIMESTAMP]; 
    
    struct stat st = {0};
    
    sprintf(path, "utenti_server/%s_server/",username);
    if(stat(path, &st) == -1){
        mkdir(path, 0750);
    }

    sscanf(timestamp, "%s %s", giorno, orario); 
    sprintf(data, "ricevuto alle %s del %s\n", orario, giorno);  
    sprintf(nomeFile, "%s%sPendenti.txt", path,userUtente); 
    fd = fopen(nomeFile, "a+"); 
    if(fd == NULL) {
      printf("Impossibile bufferizzare il messaggio\n"); 
      return 0; 
    } 

    sprintf(messaggio, "-%s\n%s%s", userUtente, buffer, data); 
    fprintf(fd, "%s",messaggio); 
    fclose(fd);

    return 1; 
}

