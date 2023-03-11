/**********************************************************************************/
 /*----------------------SEZIONE RISERVATA ALL'ADMIN ----------------------------*/
/*********************************************************************************/
 //chiamate eseguite dall'admin, il controllo del 
 //nome utente avviene sia lato client sia server 
 var INT_PARTITA = 11; //variabile che contiene l'intervallo da convertire in minuti con cui vengono giocate le partite 
 var INT_ESTRATTI = 5;  //variabile che contiene l'intervallo da convertire in secondi con cui vengono estratti i numeri 
 var INT_INIZIALE = 3; //variabile che contiene il tempo di attesa da convertire in minuti con cui viene giocata la partita iniziale 


 var nome = $('#nomeutente').val(); 
 if(nome == "Admin") {

  function terminaPartiteInSospeso() { 
    $.ajax({ 
      type: 'POST', 
      url: 'php/partiteInSospesoServer.php', 
     datatype: "json", 
     success: function(esito) { 
       var ris = JSON.parse(esito); 
       if(ris[0]) { 
         if(!ris[1]) { 
           alert("ERRORE: partite in sospeso non terminate"); 
         }
       }
     }, 
     error: function() {
      alert("Impossibile contattare il server di supporto");
     } 
    });
   }
   
  
   function creaPartita(num) { 
     //chiamata ajax per creare una partita tra num minuti
   $.ajax({ 
   type: 'POST', 
   url: 'php/creaPartitaServer.php',
   data: "intervallo=" + num,  
   datatype: "json", 
   success: function(esito) { 
     //avrò un array contenente l'esito della creazione della partita 
     var es = JSON.parse(esito); 
     if(!es) {  
      alert("ERRORE: Partita non creata"); 
      }
      console.log("Partita Creata");
     }, 
    error: function() {
     alert("Impossibile contattare il server di supporto");
    } 
    });
   }

   function inserisciNumeriDaEstrarre() { 
     //chiamata ajax per inserire i 90 numeri del bingo per una data partita 
   $.ajax({ 
   type: 'POST', 
    url: 'php/inserisciNumeriDaEstrarreServer.php', 
    datatype: "json", 
    success: function(esito) { 
     var es = JSON.parse(esito); 
    if(es[0]) {
     if(!es[1] || !es[2]) { 
      alert("ERRORE: Numeri non inseriti"); 
      } 
     }
    }, 
    error: function() {
     alert("Impossibile contattare il server di supporto");
    } 
    }); 
   }

   function estraiNumero() { 
     //chiamata ajax per estrarre un numero
    $.ajax({ 
     type: 'POST', 
     url: 'php/estraiNumeroServer.php', 
    datatype: "json", 
    success: function(esito) {  
     var es = JSON.parse(esito); 
     console.log(esito); 
    if(es[0]) {
     if(!es[1] || !es[2]) { 
      alert("ERRORE: Numero non estratto"); 
       } 
      }
     }, 
    error: function() {
     alert("Impossibile contattare il server di supporto");
    } 
   });
  }
  //funzione che inizializza la sessione di gioco dopo la prima partita 
  function iniziaPartita() {  
    creaPartita(INT_PARTITA);
    inserisciNumeriDaEstrarre(); 
    var interv;  
    setTimeout(function() { 
       interv = setInterval(estraiNumero, (INT_ESTRATTI * 1000));  
       },(INT_PARTITA * 60 * 1000));
    setTimeout(function() { 
      console.log("cancello l'intervallo " + interv); 
      clearInterval(interv);  
    }, ( (( 2 * INT_PARTITA ) - 1) * 60 * 1000)); 
  }

  //prima partita, tra le partite c'e un intervallo di tempo di dettato da INT_INIZIALE
  //in cui l'utente può acquistare la cartellina 
 $( document ).ready(function() { 
  terminaPartiteInSospeso(); 
  var int1; 
  setTimeout(function() {
    var data = new Date(); 
    console.log(data);  
    //ritardo la creazione della partita per essere sicuro che 
    //terminaPartiteInSospeso sia stata eseguita 
    creaPartita(INT_INIZIALE);}, 1000);
    //la prima partita che verrà creata sarà tra INT_INIZIALE minuti;
  setTimeout(inserisciNumeriDaEstrarre, 1500); 
  setTimeout(function() { 
    int1 =  setInterval(function() { 
      estraiNumero();   
    }, (INT_ESTRATTI * 1000)); 
    console.log("l'id dell'intervallo è: " + int1); 
  } , (3 * 60 * 1000));
   setTimeout(function() {
      console.log("intervallo cancellato: " + int1); 
      var dat = Date(); 
      console.log("l'intervallo è stato cancellato alle " + dat); 
     clearInterval(int1); 
   }, INT_PARTITA * 60 * 1000)
  }); 
  //partite successive alla prima  
  $( document ).ready(function() { 
    setTimeout(function() { 
      iniziaPartita(); 
      setInterval(iniziaPartita, (INT_PARTITA * 60 * 1000)); 
    }, (INT_INIZIALE * 60 * 1000)); 
   } 
  ); 

 } 
