//file che mi contiene le funzioni per effettuare le connessioni 
//device-device, device-server 
#include"costanti.c"

//funzione per accettare la richiesta e creare una socket connesso
 
void accettaConnessione(int listener, int* fdmax, fd_set* master) {
 socklen_t addrlen;
 struct sockaddr_in cl_addr;
 int newfd; 

 fflush(stdout);
 addrlen = sizeof(cl_addr);
 // faccio accept() e creo il socket connesso 'newfd'
 newfd = accept(listener,
 (struct sockaddr *)&cl_addr, &addrlen);
 FD_SET(newfd, master);
 // Aggiorno l'ID del massimo descrittore
 if(newfd > *fdmax){ 
   *fdmax = newfd; 
 }  
}