//contiene le funzioni e le strutture dati di utilità per il progetto 
//di reti informatiche 
#include"costanti.c" 


//struttura dati che rappresenta il concetto di un utente nell'applicazione
//nel contesto di device
typedef struct utenteApplicazione {
  char user_dest[DIM_MAX]; 
  char porta[DIM_PORTA]; 
  char ts_login[DIM_TIMESTAMP]; 
  char ts_logout[DIM_TIMESTAMP]; 
  int sd; //socket su cui è collegato il device 
  struct utenteApplicazione* next; 
} aux; 

struct utenteApplicazione *uo = NULL; //lista degli utenti online
struct utenteApplicazione *uno = NULL; //lista degli utente disconnessi 
 

//funzioni per gestire la lista degli utenti online 
void aggiungiUtenteOnline(int sd, char* username,char* porta,char * ts_login){
	if(uo != NULL){
		struct utenteApplicazione* utenteApplicazionenext = uo;
		uo = (struct utenteApplicazione*) malloc(sizeof(struct utenteApplicazione));
		strcpy(uo->user_dest,username);
        strcpy(uo->porta,porta);
        strcpy(uo->ts_login,ts_login); 
        strcpy(uo->ts_logout,"\0");  
        uo->sd = sd; 
		uo-> next = utenteApplicazionenext;
	}
	else{
		uo = (struct utenteApplicazione*) malloc(sizeof(struct utenteApplicazione));
		strcpy(uo->user_dest,username);
        strcpy(uo->porta,porta);
        strcpy(uo->ts_login,ts_login);
        strcpy(uo->ts_logout,"\0"); 
        uo->sd = sd;
		uo -> next = NULL;
    }
      
}

//mi permette di aggiungere un utente alla lista degli utenti disconnessi
void aggiungiUtenteDisconnesso(struct utenteApplicazione* utente){
	if(uno != NULL){
		utente->next = uno; 
		uno = utente;
	}
	else{
		uno = utente;
    }  
}

//dato un descrittore di socket, ci permette di recuperare il relativo nome
//utente a cui è connesso 
char* nomeUtenteConnesso(int sd){
     
    if(uo == NULL) return NULL; 
    if(uo->sd == sd) return uo->user_dest; 
   
		struct utenteApplicazione* target = uo->next;
     
		while(target != NULL){
            if(target->sd == sd) 
              return target->user_dest; 
			target = target ->next;
		}
 
	return NULL;
}


//dato un nome utente, ci restituisce il descrittore socket associato, 
//tale funzione è utile al server per poter comunicare con i vari device 
//la funzione ritorna -1 in caso in cui l'utente non fosse più online
//nel caso in cui, l'utente venga inserito più volte, mi restituisce 
//il socket più aggiornato  
int socketUtenteConnesso(char* nome) { 
    if(uo == NULL) return -1; 
    if(strcmp(uo->user_dest, nome) == 0) return uo->sd; 
   
		struct utenteApplicazione* target = uo->next;
     
		while(target != NULL){
            if(strcmp(target->user_dest, nome) == 0)
              return target->sd; 
			target = target ->next;
		}
 
	return -1;

}
//funzione che mi permette di restituire il numero di porta di un device 
//che è attualmente online
char* portaUtenteConnesso(char* nome) { 
    if(uo == NULL) return NULL; 
    if(strcmp(uo->user_dest, nome) == 0) return uo->porta; 
   
		struct utenteApplicazione* target = uo->next;
     
		while(target != NULL){
            if(strcmp(target->user_dest, nome) == 0)
              return target->porta; 
			target = target ->next;
		}
 
	return NULL;

}




//dato un nome utente, mi ritorna il timestamp di logout di un utente disconnesso
//la funzione è utile per sapere da quanto un utente era offline 
char* logoutUtenteDisconnesso(char* nome) { 
    if(uo == NULL) return NULL; 
    if(strcmp(uo->user_dest, nome) == 0) return uo->ts_logout; 
   
		struct utenteApplicazione* target = uo -> next;
     
		while(target != NULL){
            if(strcmp(target->user_dest, nome) == 0)
              return target->ts_logout; 
			target = target ->next;
		}
 
	return NULL;

}


//la funzione ci permette di inserire il logout a un utente, prende in ingresso 
//il nome utente e il timestamp di logout, lo aggiunge e rimuove l'elemento dalla lista 
struct utenteApplicazione* aggiungiLogout(char* nomeUtente, char* ts_logout){
     
    if(uo == NULL || nomeUtente == NULL) return NULL; 


		struct utenteApplicazione* target, *previous; 

    if(uo->next) { 
       previous = uo; 
        
        if((strcmp(previous->user_dest, nomeUtente) == 0)) {
		 strcpy(previous->ts_logout, ts_logout); 
      //   printf("logout cambiato a %s\n", previous-> user_dest); 
         target = uo;
         uo = uo->next;   
         return target; 
        }
        
        target = uo->next; 
        while(target != NULL){
             if(strcmp(target->user_dest, nomeUtente) == 0) { 
               strcpy(target->ts_logout, ts_logout);
        //       printf("logout inserito a %s\n", target->user_dest);
               previous->next = target->next; 
               target->next = NULL;  
               return target;  
            }
            previous->next = target; 
			target = target->next;
		  }
     }
     
     //la lista ha un solo elemento 
     if((strcmp(uo->user_dest, nomeUtente) == 0)) {
		 strcpy(uo->ts_logout, ts_logout); 
      //   printf("logout cambiato a %s\n", uo->user_dest); 
         target = uo; 
         uo = NULL; 
         return target; 
     } 

	return 0;
}


//la funzione ci permette di rimuovare un utente dalla lista  
struct utenteApplicazione* rimuoviUtenteLista(char* nomeUtente){
     
    if(uo == NULL || nomeUtente == NULL) return NULL; 


		struct utenteApplicazione* target, *previous; 

    if(uo->next) { 
       previous = uo; 
        
        if((strcmp(previous->user_dest, nomeUtente) == 0)) { 
         target = uo;
         uo = uo->next;   
         return target; 
        }
        
        target = uo->next; 
        while(target != NULL){
             if(strcmp(target->user_dest, nomeUtente) == 0) { 
               previous->next = target->next; 
               target->next = NULL;  
               return target;  
            }
            previous->next = target; 
			target = target->next;
		}
     }
     
     //la lista ha un solo elemento 
     if((strcmp(uo->user_dest, nomeUtente) == 0)) {
         target = uo; 
         uo = NULL; 
         return target; 
     } 

	return NULL;
}

//la funzione ci permette di stampare gli elementi di una lista. 
//facciamo controllo sul logout, se non è vuoto lo stampiamo 
//viene usata nel comando list del server 
void stampaUtenti(struct utenteApplicazione* testa){
	if(testa != NULL){
		while(testa != NULL){
			printf("%s*",testa->user_dest);
            printf("%s*",testa->porta);
            printf("%s",testa->ts_login); 
            if(strcmp(testa->ts_logout,"\0") != 0)
               printf("*%s",testa->ts_logout);
            printf("\n"); 
			testa = testa ->next;
		}
	}
	else {
		printf("Nessun utente online\n");
	}
}

//funzione per stampare gli username degli utenti attualmento online 
void stampaNomeUtenti(struct utenteApplicazione* testa) {  
  if(testa != NULL) { 
    while(testa != NULL) { 
      printf("%s \n", testa->user_dest);
      testa = testa->next;  
    }
  } else { 
    printf("nessun utente online\n"); 
  }
}



//struttura dati che rappresenta il concetto di gruppo all'interno dell'applicazione
typedef struct Gruppo { 
  int sd; 
  char id[DIM_MAX]; //conterrà l'id del gruppo che sarà il nome utente di chi ha creato il gruppo
  struct Gruppo *next; 
} *g; 

//lista degli utenti che fanno parte del gruppo 
struct Gruppo *group = NULL; 

//funzione per aggiungere in testa un utente con socket sd al gruppo
void aggiungiAGruppo(int sd, char* id) { 
	if(group != NULL){
		struct Gruppo* groupnext = group;
		group = (struct Gruppo*) malloc(sizeof(struct Gruppo)); 
    group->sd = sd;
    strcpy(group->id,id); 
		group-> next = groupnext;
	}
	else{ 
		group = (struct Gruppo*) malloc(sizeof(struct Gruppo));
    group->sd = sd;
    strcpy(group->id,id); 
		group -> next = NULL;
    }
}

//funzione per rimuovere dal gruppo un utente.
//verrà invocata quando un utente lascia la chat.
//consideriamo che quando un utente si disconnette allora 
//smette automaticamente di far parte dei gruppo a cui sta partecipando 
struct Gruppo* rimuoviDalGruppo(int sd) { 
       
    if(group == NULL || sd == 0) return NULL; 
 
		struct Gruppo *target, *previous; 

    if(group->next) { 
       previous = group; 
        
        if(previous->sd == sd) {
         target = group;
         group = group->next;   
         return target; 
        }
        
        target = group->next; 
        while(target != NULL){
             if(target->sd == sd) { 
               previous->next = target->next; 
               target->next = NULL;  
               return target;  
            }
            previous->next = target; 
			target = target->next;
		}
     }
     
     //la lista ha un solo elemento 
     if(group->sd == sd) {
         target = group; 
         group = NULL; 
         return target; 
     } 
  
	return NULL;
}

//funzione che mi dice se un utente fa parte del gruppo 
int membroDelGruppo(int sd) { 

  int trovato = 0; 
  struct Gruppo* membro = group; 
  while(membro != NULL) { 
     if(membro->sd == sd) {
       trovato = 1; 
       break; 
     }

    membro = membro->next; 
  }

  return trovato;
}

//funzione che mi permette di stampare i membri del gruppo
//a solo scopo di debug
void stampaUtentiDelGruppo(struct Gruppo* testa, fd_set* m){
  printf("\nmembri del gruppo\n"); 
  struct Gruppo* membro = testa; 
	if(membro != NULL){
		while(membro != NULL){
      if(FD_ISSET(membro->sd, m))
		  printf("membro sd: %d\n",membro->sd); 
			membro = membro->next;
		}
	}
	else {
		printf("il gruppo è vuoto\n");
	}
}

//funzione che mi permette di stampare i membri di tutti i gruppi
//a solo scopo di debug
void stampaGruppi(struct Gruppo* testa){
  printf("\nmembri del gruppo\n"); 
	 struct Gruppo* membro = testa; 
	if(membro != NULL){
		while(membro != NULL){
		  printf("membro sd: %d\n",membro->sd); 
			membro = membro->next;
		}
	}
	else {
		printf("il gruppo è vuoto\n");
	}
}

//dato un descrittore di socket, ci permette di recuperare il relativo 
//id del gruppo a cui fa parte 
char* idGruppo(int sd){
     
    if(group == NULL) return NULL; 
    if(group->sd == sd) return group->id; 
   
		struct Gruppo* target = group->next;
     
		while(target != NULL){
            if(target->sd == sd) 
              return target->id; 
			target = target ->next;
		}
 
	return NULL;
}

//funzione di utilità che ritorna 1 se occorre stampare lo spazio
//di separazione tra i messaggi, viene chiamata quando 
//gestiamo la show a livello utente.
//funzione per stampare lo spazio tra due messaggi nella chat
int spazioDaStampare(char * username,int  len, char * buffer) {
 char* daConfrontare = (char *) malloc(sizeof(char) * len);
 sprintf(daConfrontare, "-%s", username);

 if(strstr(buffer, daConfrontare) != NULL) {
  free(daConfrontare);
  return 1; 
 }
 
 free(daConfrontare); 
 return 0;  
}
