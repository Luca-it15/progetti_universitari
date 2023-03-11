#include"costanti.c"
//file che contiene tutti i controlli che verranno fatti nel progetto.

//funzione per controllare se la porta inserita nel device e nel server è corretta 
//nel caso una porta sia occupata dal server, ce lo dirà la bind 
//mode: 0 -> server
//mode: 1 -> device
int controllaPorta(int argc, char* argv[], int mode){
    int porta; 
    if(argc>2){
        printf("numero eccessivo di parametri, ne servono 2\n");
        return -1;
    } else if(argc<2 && mode == 1){
         printf("Si prega di fornire un numero di porta in ingresso\n");
        return -1;
    } else if(argc == 2)
       porta = atoi(argv[1]);
// porte da 1024 a (2 alla 16) -1
    if(porta<1024 || porta > 65535 || (mode == 1 && porta == 4242 )){
        printf("Numero di porta errato, inserire un numero commpreso fra 1024 e 65535;\n");
        if(mode == 1) 
         printf("La porta N. 4242 è riservata!\n"); 
        return -1;
    }

    return 0;
}

//controlla se un username è presente all'interno del file 
//puntato da fptr
int controllaUsername(FILE* fptr, char * username) { 
 
 int presente = 0; //sarà il valore ritornato
 char* res; 
 char riga[DIM_MAX_RIGA]; 
 char rigaUsername[DIM_MAX]; 
 char rigaPassword[DIM_MAX]; 
     
     //controllo che se il nome utente inserito è gia usato
     while (1) {
        res = fgets(riga, DIM_MAX_RIGA, fptr); 
        if(res == NULL) 
           break; 
         sscanf(riga, "%s %s", rigaUsername, rigaPassword);  
        if (strcmp(rigaUsername,username) == 0) {  
        presente = 1; 
    }
  }
  return presente; 
}