#include"../lib-1.0/costanti.c"
//per ogni nuovo utente che effettua il login, la funzione lo aggiunge alla 
//lista degli utenti online  
void in_server(int i, fd_set *master, struct utenteApplicazione* uo){
    int ret,  len;
    uint16_t lmsg; //mi servirà per ottenere la lunghezza del messaggio
    char username[DIM_MAX]; 
    char password[DIM_MAX]; 
    char riga[DIM_MAX_RIGA]; 
    char porta[DIM_PORTA]; 
    char rigaPassword[DIM_MAX]; 
    char rigaUsername[DIM_MAX]; 
    char * res;

    time_t rawtime; 
    struct tm* timeinfo; 

    int presente = 0; 
    FILE *fptr; 
    char buffer[BUF_LEN];
    char risposta[RESPONSE_LEN]; 
 
        fflush(stdout);
        /*operazione di login, il device ci invia username e password e noi dobbiamo 
         confrontarlo con quanto inserito nel file di registazione.
         se il confronto va a buon fine allora inseriamo l'utente nella lista degli
         utenti online dandoli il timestamp di login */
        strcpy(buffer, "Richiesta di login\0"); 
        ret = send(i, (void*) buffer, strlen(buffer)+1, 0);
        if(ret < 0) {
         perror("Errore in fase di comunicazione: \n");
        }
        fflush(stdout); 
        //ricevo la dimensione dal client 
        ret = recv(i, (void*)&lmsg, sizeof(uint16_t), 0); //il device mi manderà la lunghezza del messaggio
        if(ret < 0) perror("Errore nella receive\n");   

        len = ntohs(lmsg); /*dimensione del messaggio che il server riceverà*/ 
        ret = recv(i, (void*)buffer, len, 0);
        /*controllo che il client non si sia disconesso, lo potrebbe fare in qualsiasi momento*/ 
        if(ret == 0){
        printf("CHIUSURA2 client rilevata!\n");
        fflush(stdout);
        // il client ha chiuso il socket, quindi
        // chiudo il socket connesso sul server
        close(i);
        // rimuovo il descrittore newfd da quelli da monitorare
         FD_CLR(i, master);
         }
        else if(ret < 0){
         perror("ERRORE! \n");
        // si è verificato un errore
         close(i);
         // rimuovo il descrittore newfd da quelli da monitorare
         FD_CLR(i, master);
         } else {  
             fptr = fopen("file_server/registrati.txt","a+"); 
             if(fptr == NULL) {
                 printf("Errore nell'apertura del file\n"); 
                 exit(1); 
             }
             sscanf(buffer,"%s %s %s",username, password, porta); 
              memset(buffer, 0, sizeof(buffer));
             //controllo se il nome utente e la password sono corretti
             while (1) {
              res = fgets(riga, DIM_MAX_RIGA, fptr); 
              if(res == NULL) 
               break; 
              sscanf(riga, "%s %s", rigaUsername, rigaPassword);
              if (strcmp(rigaUsername,username) == 0 && strcmp(rigaPassword,password) == 0) {  
              presente = 1; 
             }
            }
             if(presente) {
              strcpy(risposta, "Login effettuato!\0");
              //creao il timestamp da inserire all'interno del struttura utentiOnline
              time(&rawtime); 
              timeinfo = localtime(&rawtime); 
      
              sprintf(buffer, "%d-%d-%d %d:%d:%d", 
               timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday,
                timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);   
               aggiungiUtenteOnline(i,username, porta, buffer); 
              }
              else {
              strcpy(risposta, "username o password errati, si prega di riprovare\0");  
              }
            fclose(fptr); 
        ret = send(i, (void*) risposta, strlen(risposta)+1, 0);
        if(ret < 0){
         perror("Errore in fase di comunicazione \n");
         FD_CLR(i, master); 
         aggiungiUtenteDisconnesso(aggiungiLogout(username, getTimestamp())); 
         return; 
        } 

          

    }
}