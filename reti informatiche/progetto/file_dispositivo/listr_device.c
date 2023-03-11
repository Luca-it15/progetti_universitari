//il file contiene la funzione che mi permette
//di visualizzare la rubrica dell'utente
//se la rubrica non è ancora stata creata, la crea
//facendo una scrittura con il path della rubrica
void listr(char * userUtente) {

  FILE* fptr; 
  char username[DIM_MAX_RIGA]; 
  char path[DIM_MAX + DIM_PATH]; 
  int vuota = 1; //variabile che mi dice se la rubrica è vuota

  sprintf(path, "utenti_device/%s_device/rubrica.txt", userUtente);
    
     fptr = fopen(path, "rt"); 
    if(fptr != NULL) {
      //faccio l'accesso al file dall'inizio
     if(fseek(fptr,0,SEEK_SET) != 0) {
      printf("errore nella fseek\n"); 
      return ; 
     }

    printf("\n\n***Rubrica dell'utente %s***\n\n", userUtente);  
    while( fgets(username, DIM_MAX_RIGA, fptr) ){
      vuota = 0; 
      printf("%s\n", username);
    }

    if(vuota) 
     printf("Nessun contatto in rubrica\n"); 

    fclose(fptr); 
  } else {
     printf("La rubrica non è ancora stata creata, la creo!\n"); 
     printf("Da qui in avanti sarà possibile utilizzare la rubrica\n"); 
       fptr = fopen(path, "w"); 
       if(fptr == NULL) { 
          printf("errore nella creazione del file rubrica.txt\n"); 
          return; 
         } 
  }
 

}