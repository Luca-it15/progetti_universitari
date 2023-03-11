//file che contiene la funzione per gestire la richiesta di 
//controllo di un username quando l'utente vuole 
//aggiungere in rubrica un nome utente
int addr_server(int i) {
  
 char buffer[DIM_MAX];
 char risp[RESPONSE_LEN];  
 int ret;  
 FILE* fptr; 
  //ricevo dall'utente il nome utente 
 ret = recv(i, (void *)buffer, DIM_MAX, 0); 
 if(ret < 0) {
     perror("Errore nella recv: \n"); 
     exit(0); 
 }

    
 fptr = fopen("file_server/registrati.txt","a+"); 
 if(fptr == NULL) {
  printf("Errore nell'apertura del file\n"); 
  exit(1); 
 }
  
 if(controllaUsername(fptr, buffer)) 
    strcpy(risp,"_valido"); 
 else 
    strcpy(risp,"_nonvalido"); 
 
 ret = send(i, (void*)risp, RESPONSE_LEN, 0); 
 if(ret < 0) {
     perror("Errore nella send: \n"); 
     return 0; 
 } 
 
 return 1; 
}