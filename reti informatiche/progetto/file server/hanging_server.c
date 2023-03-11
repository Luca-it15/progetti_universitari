//funzione che gestisce la richiesta di hanging. 
//Data una richiesta di un utente: calcoliamo il numero di messsaggi
//pendati inviati dagli altri utenti e inviamo all'utente richiedente
//l'username di chi lo ha contattato, il relativo numero di messaggi
//e il timestamp dell'ultimo messaggio. 
int hanging_server(int sd, fd_set* master, char* richiedente, fd_set *socketChat) {
 
 char folder[DIM_PATH + DIM_MAX]; //conterrà il path della cartella 
 char path[DIM_PATH + DIM_MAX + 12]; //conterrà il path del file mittenti.txt
 char dest[DIM_PATH + 2*DIM_MAX]; //conterrà i vari path dei messaggi pendenti
 char riga[DIM_MAX]; 
 char username[DIM_MAX];
 char strtmp[DIM_MAX];
 char penultima[DIM_MAX + 3 + DIM_TIMESTAMP]; 
 char userFile[DIM_MAX + 1]; 
 char risposta[RESPONSE_LEN];
 //assumiamo che al massimo avrò 999 messaggi pendenti
 char info[DIM_MAX + 3 + DIM_TIMESTAMP];
 FILE* fd, *tmp; 
 int ret, len; 
 int num; //conterrà il numero di messaggi pendenti

 sprintf(folder, "utenti_server/%s_server/", richiedente); 
 sprintf(path, "%smittenti.txt", folder); 
 

 fd = fopen(path, "rt"); 
 if(fd == NULL) {
     printf("Errore nell'apertura del file mittenti.txt\n"); 
     return 0; 
 }

 
 //ad ogni iterazione riga conterrà il nome di un mittente
 //per il quale andremo a contarre i messaggi
 //dopo ogni conto, invieremo al richiedente il nome, il
 //numero dei messaggi e il timestamp dell'ultimo messaggio,
 //dopo l'invio, attenderemo l'ack del richiedente
 while(fgets(username, DIM_MAX, fd) != NULL) {
   num = 0; 
   memset(dest, 0, DIM_PATH + 2*DIM_MAX); 
   memset(strtmp, 0, DIM_MAX); 
   len = strlen(username); 
   strncpy(strtmp, username, (len - 1)); 

   sprintf(dest, "%s%sPendenti.txt", folder, strtmp);  
   tmp = fopen(dest, "rt"); 
   if(tmp == NULL) {
       printf("Errore nell'aprire i messaggi pendenti di %s\n", username); 
       continue; 
   }
   //se il file è vuoto, num varrà 0, 
   //e, penultima conterrà la penultima riga del file
   //che è anche il timestamp dell'ultimo messaggio
   while(fgets(riga, DIM_MAX, tmp) != NULL) {  
    sprintf(userFile,"-%s", username);   
    strcpy(penultima, riga);  
     if(strcmp(riga, userFile) == 0)
      num++; 
   }
   //ho in num il numero di messaggi pendenti e in riga 
   //ho il timestamp dell'ultimo messaggio
   //DIM_TIMESTAMP < DIM_MAX 
   sprintf(info,"%s %d %s", strtmp, num, penultima); 
   ret = send(sd, (void*)info, DIM_MAX + 3 + DIM_TIMESTAMP, 0); 
   if(ret < 0) {
       perror("Errore nella send\n"); 
       FD_CLR(sd, master); 
       FD_CLR(sd, socketChat); 
       close(sd); 
       fclose(fd); 
       fclose(tmp); 
       return 0;
   }
   //attendo una risposta dell'host in modo tale da controllare
   //l'invio dell'informazione 
   ret = recv(sd, (void*)risposta,DIM_RESPONSE, 0); 
   if(ret < 0) {
       perror("Errore nella recv\n"); 
       FD_CLR(sd, master); 
       FD_CLR(sd, socketChat); 
       close(sd); 
       fclose(fd); 
       fclose(tmp); 
       return 0;
   } else if(ret == 0) {
       FD_CLR(sd, master); 
       FD_CLR(sd, socketChat); 
       close(sd); 
       fclose(fd); 
       fclose(tmp); 
       return 0; 
   }
 
   memset(riga, 0, DIM_MAX); 
   memset(risposta, 0, RESPONSE_LEN); 
   memset(username, 0, DIM_MAX); 
   fclose(tmp); 
 }
 
 fclose(fd);

//ho finito di inviare tutte le informazioni, 
//lo comunico al richiedente e termino 
 strcpy(risposta, "_hangingfine"); 
 ret = send(sd, (void*)risposta, RESPONSE_LEN, 0); 
   if(ret < 0) {
       perror("Errore nella send\n"); 
       FD_CLR(sd, master); 
       FD_CLR(sd, socketChat); 
       close(sd);  
       return 0;
   }
  return 1; 
}
