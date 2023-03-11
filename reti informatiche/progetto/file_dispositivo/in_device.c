//funzione per la in che permette all'utente di effettuare il login. 
//l'utente manderà oltre all'username e la password anche il numero 
//di porta su cui è in ascolto.
//mi restituisce il socket di comunicazione con il server

#include"../lib-1.0/costanti.c" 

int in_device(int porta, int porta_user, char* cmd, char* username, char* password){
  
 
 struct sockaddr_in srv_addr;  
 int ret, len, sd;
 char buffer[BUF_LEN];
 uint16_t lmsg;
 int esito = 0; 
 
 
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

 // invio del comando al server in modo tale che possa gestire 
 //questa richiesta di login 
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
   printf("Il server è spento, Impossibile fare login\n"); 
   return 0; 
 }

 printf("%s\n", buffer);
 fflush(stdout);; 
 sprintf(buffer, "%s %s %d", username,password,porta_user); 
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

 memset(buffer, 0, sizeof(buffer));
 //aspetto il messaggio di conferma del login da parte del server 
 ret = recv(sd, (void*)buffer, RESPONSE_LEN, 0); 
 if(ret < 0) {
     perror("Errore in fase di ricezione: \n"); 
     exit(-1); 
 }  
 printf("%s\n", buffer); 
 if(strcmp(buffer,"Login effettuato!") == 0)
   esito = sd; 
 fflush(stdout);  
  return esito; 
}
