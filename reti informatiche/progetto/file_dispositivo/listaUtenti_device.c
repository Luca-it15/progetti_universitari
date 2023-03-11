//questo file conterrà la funzione che mi permette di ricevere dal server la lista 
//degli utenti attualmente online e stamparli
//nel caso il server fosse offline, verrà usata la lista tenuta dal singolo device
//il server su nostra richiesta ci invierà la lista degli utenti online.
//tale lista verrà confrontata con i nomi utenti presenti nella rubrica utente
//quindi andremo a stampare solo i nomi utenti online che sono sono presenti
//anche nella nostra rubrica.
//quando riceviamo come comando "_fine" allora il server ci avrà inviato 
//tutta la lista degli utenti
int listaUtenti_device(int serverSock,int * status, char* userUtente,
            fd_set* master, struct utenteApplicazione* uo) { 
       
 char buffer[DIM_MAX]; //la dimensione massima di un username è DIM_MAX 
 char cmd[CMD_LEN] = "\\u"; 
 char fine[CMD_LEN] = "_fine\0"; 
 char continua[CMD_LEN] = "_cont\0"; 
 int ret; /*trovato: 1 se il nome è presente in rubrica, 0 altrimenti*/ 
 FILE *fptr;   
 char path[DIM_MAX + DIM_PATH]; 
   

   
   printf("\nlista degli utenti online\n");
   if(*status == 0) {
     stampaNomeUtenti(uo);
     return 0;   
   }
   
   //invio il comando al server
   strcpy(buffer, cmd);   
   ret = send(serverSock, (void*)buffer, CMD_LEN, 0); 
   if(ret < 0) { 
       perror("Errore nella send: \n");
       exit(1);
   }

   while(1) { 
     //ricevo il nome e stampo
     memset(buffer, 0, DIM_MAX); 
     fflush(stdout); 
     ret = recv(serverSock, (void*)buffer, DIM_MAX, 0);
     if(ret < 1) { 
         perror("Errore nella recv: \n");  
         exit(1); 
     } else if(ret == 0) { 
         printf("il server si è spento\n"); 
         *status = 0; 
         FD_CLR(serverSock, master);
         //uso la lista degli utenti online che possiede il device 
         stampaNomeUtenti(uo); 
         break;
     } else { 
       if(strcmp(buffer, fine) != 0) {  
           //controllo in rubrica se il nome è presente 
           sprintf(path, "utenti_device/%s_device/rubrica.txt", userUtente); 

           fptr = fopen(path, "rt"); 

           if(fptr == NULL) {
            printf("La rubrica utente non è ancora stata creata\n"); 
            return 1; 
           } 
          if(controllaUsername(fptr, buffer))          
           printf("\n- %s \n", buffer); 
       } else 
         break; 

         //rimetto il puntatore del file all'inizio
         if(fseek(fptr,0,SEEK_SET) != 0) {
           perror("errore nella fseek\n"); 
           exit(1); 
         }
     } 

     //mando l'ack di continuazione
     ret = send(serverSock, (void*)continua, 6, 0); 
     if(ret < 0) {
         perror("Errore nella send: \n"); 
         exit(1); 
     }
    
   }

   fclose(fptr); 
   return 1; 
}
