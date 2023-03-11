//funzione che mi permette di recuperare il montempremi della partita.
//la funzione verrà chiamata ogni 2 minuti per aggiornare il montepremi della partita in corso. 
//il montepremi si forma con l'acquisto della cartelline e servirà come premio per la prossima partita
//che si andrà a giocare ma è indipendente da essa, ovvero un montepremi si forma con l'acquisto delle 
//cartelline anche se non ci sono partite da giocare,
//rimane invariato durante lo svolgimimento delle partite.
//tra una chiamata e l'altra il montepremi si aggiorna con i nuovi pagamenti e quando viene chiamata 
//restituisce il totale, se un giocatore decide di abbandonare, il montepremi non subisce variazioni 
//perchè le schedine non sono rimborsabili 

function getMontepremi() {
    $.ajax({ 
      type: 'POST', 
      url: 'php/getMontepremiServer.php', 
      datatype: "json", 
      success: function(premi) { 
        var montepremi = JSON.parse(premi); 
        if(montepremi[0]){ 
          $('#montepremi').empty();
          $('#montepremi').append('<h3>MONTEPREMI PARTITA</h3>');
          if(montepremi[1] > 0) { //qualcuno ha acquistato una cartellina  
          $('#montepremi').append('<h4>BINGO: ' + montepremi[1] + ' crediti</h4>');
          $('#montepremi').append('<h4>CINQUINA: ' + montepremi[2] + ' crediti</h4>');
          } else { 
            $('#montepremi').append('<h5>MONTEPREMI NON ANCORA FORMATO</h5>');
          }
         } else {
            alert("Errore: recupero del montepremi non avvenuto"); 
         } 
        }, 
        error: function() {
          alert("Impossibile contattare il server di supporto");
        }
      }); 
   } 

   $(document).ready(function() { 
     getMontepremi(); 
     setInterval(getMontepremi, 120000); 
   })