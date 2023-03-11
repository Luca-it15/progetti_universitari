//il file contiene la funzione per rimuovere un utente dalla 
//rubrica, il controllo sull'username inserito dall'utente
//viene fatto solo a livello locale dato che la correttezza
//degli username inseriti viene fatto durante l'inserimento
int remover(char* userUtente, char* username) {
 
  FILE* fd, *temp; 
  int res; 
  char riga[DIM_MAX_RIGA];  
  char path[DIM_MAX + DIM_PATH]; 
  char temp_path[DIM_MAX + DIM_PATH]; 
  char nome[DIM_MAX]; 
  char spazio[DIM_MAX_RIGA - DIM_MAX];//stringa che conterrà la riga meno il nome
  
   sprintf(path, "utenti_device/%s_device/rubrica.txt", userUtente);
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

  //ricopio le righe del file e aggiorno
   while(fgets(riga, DIM_MAX, fd) != NULL ){
     sscanf(riga, "%s %s", nome, spazio); 
     if(strcmp(nome,username) == 0)
         continue; 
     fprintf(temp, "%s\n", nome);
    
  }

  //elimino la rubrica non aggiornata
  res= remove(path);
  if( res < 0 ) {
    perror("Errore nella rimozione del file\n");
    return 0; 
  }
  

  //rinomino il file temp facendolo diventare la nuova
  //rubrica
  res = rename(temp_path, path); 
  if(res < 0) {
   perror("Errore nella rinominazione del file\n"); 
   return 0; 
  }

  fclose(temp); 

  return 1; 
} 