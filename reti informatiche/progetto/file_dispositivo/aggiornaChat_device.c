//la funzione mi permette di aggiornare le spunte da singole 
//a doppie. 
//la procedura prevede di creare un file temporaneo e di copiarci
//il contenuto aggiornato del file di chat, cancellare quest'ultimo
//ed rinominare il file

int aggiornaChat(char* userUtente, char* username) {
 
  FILE* fd, *temp; 
  int res; 
  char riga[DIM_MAX_RIGA];  
  char path[2*DIM_MAX + DIM_PATH]; 
  char temp_path[DIM_MAX + DIM_PATH]; 
  
   sprintf(path, "utenti_device/%s_device/%sChat.txt", userUtente, username);
  //apro il file in sola lettura 
   fd = fopen(path, "rt"); 
    if(fd == NULL) {
      printf("Impossibile aprire il file\n"); 
      return 0; 
    }

   sprintf(temp_path, "utenti_device/%s_device/temp.txt", userUtente); 
   temp = fopen(temp_path, "a+"); //creo il file temp e lo apro in append

   //faccio l'accesso al file dall'inizio
  if(fseek(fd,0,SEEK_SET) != 0) {
    printf("errore nella fseek\n"); 
    return 0; 
  }
   
   //ricopiamo il contenuto e aggiorniamo
   while(fgets(riga, DIM_MAX_RIGA, fd) != NULL ){
     if(strcmp(riga,"*\n") == 0)
     fprintf(temp, "**\n");
     else 
     fprintf(temp, "%s", riga);
  }

  //elimino il file di chat non aggiornato
  res = remove(path);
  if( res < 0 ) {
    perror("Errore nella rimozione del file\n");
    return 0; 
  }
  

  //rinomino il file temp facendolo diventare la nuova
  //chat
  res = rename(temp_path, path); 
  if(res < 0) {
   perror("Errore nella rinominazione del file\n"); 
   return 0; 
  }

  fclose(temp); 

  return 1; 
} 