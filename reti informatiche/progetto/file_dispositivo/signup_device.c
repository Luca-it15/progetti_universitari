//la funzione permette di registrarsi presso il servizio, 
//fa una connessione al server,invia nome utente e password al server, 
//quest'ultimo controlla se il nome utente è disponibile, in caso affermativo
//l'utente viene registrato.
//viene fatta ogni volta la connessione con il 
//server perchè se la registrazione non va a buon fine almeno 
//il device non resta connesso con il server 
//o perchè dopo la registrazione l'utente potrebbe decidere di non 
//usare il servizio'
#include"../lib-1.0/costanti.c" 

void signup_device(int porta, char* cmd, char* username, char* password){
  
 
 struct sockaddr_in srv_addr;  
 int ret, len, sd;
 char buffer[BUF_LEN];
 uint16_t lmsg;
 
 
 sd = socket(AF_INET,SOCK_STREAM,0);

 /* Creazione indirizzo del server */
 memset(&srv_addr, 0, sizeof(srv_addr));
 srv_addr.sin_family = AF_INET;
 srv_addr.sin_port = htons(porta);
 inet_pton(AF_INET, "127.0.0.1", &srv_addr.sin_addr);
  
 
 ret = connect(sd, (struct sockaddr*)&srv_addr, sizeof(srv_addr)); 
 if(ret < 0){
  perror("Porta del server errata, si prega di riprovare!"); 
  exit(1); 
 }

 // invio del comando in modo tale che il server possa gestire 
 //questa richiesta di registrazione 
 ret = send(sd, cmd, strlen(cmd)+1, 0);

 if(ret < 0){
 perror("Errore in fase di invio comando: \n");
 exit(1);
 }

 // Attendo risposta
 ret = recv(sd, (void*)buffer, RESPONSE_LEN, 0);
 

 if(ret < 0){
 perror("Errore in fase di ricezione: \n");
 exit(1);
 } else if(ret == 0) {
   printf("Il server è spento, Impossibile registrarsi\n"); 
   return; 
 }

 printf("%s\n", buffer);
 fflush(stdout);; 
 //preparo il messaggio per il controllo
 sprintf(buffer, "%s %s", username, password); 
 //invio la dimensione di buffer 
 len = strlen(buffer) + 1;
 lmsg = htons(len); 

 ret = send(sd, (void*)&lmsg, sizeof(uint16_t), 0); 
 if(ret < 0) {
     perror("Errore nella send: \n");
     exit(-1);  
 } 
 //invio il messaggio 
 ret = send(sd, (void*)buffer, len, 0); 
 if(ret < 0) {
  perror("Errore nella send: \n"); 
  exit(-1); 
 }

 memset(buffer, 0, BUF_LEN); 
 fflush(stdout);
 //aspetto il messaggio di conferma della registrazione da parte del server 
 ret = recv(sd, (void*)buffer, RESPONSE_LEN, 0); 
 if(ret < 0) {
     perror("Errore in fase di ricezione: \n"); 
     exit(-1); 
 }  
 printf("%s\n", buffer); 
 fflush(stdout);
 close(sd); 
}
