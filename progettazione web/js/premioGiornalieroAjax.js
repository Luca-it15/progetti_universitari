//richesta al server per sapere se l'utente ha diritto al premio giornaliero.
//Importante per la continuita del gioco 
function richiestaPremio() { 
    console.log("richiesta inviata"); 
  $.ajax({ 
       type: 'POST', 
       url: 'php/premioGiornalieroServer.php', 
       datatype: "json", 
       success: function(data) { 
           var json = JSON.parse(data); 
            if(!json[0])
            alert("ERRORE: Impossibile verificare gli accessi,  contattare l'assistenza"); 
            else { 
              if(json[1]) 
              alert("Hai ricevuto il premio giornaliero di 5 crediti!"); 
            } 
      }, 
       error: function() {
           alert("ERRORE: Impossibile contattare il server di supporto"); 
       }
     }); 
 }

 //la chiamata avviene solo al caricamento della pagina  
 $( document ).ready(function() {
    richiestaPremio();    
  }); 
  