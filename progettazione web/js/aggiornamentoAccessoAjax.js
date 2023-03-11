//richiesta al server per aggiornare l'ultimo accesso, questo file verrà incluso 
//in ogni file del progetto accessibile all'utente in modo che l'ultimo accesso 
//venga mantenuto sempre aggiornato 
function richiestaAggiorna() { 
    console.log("richiesta inviata"); 
  $.ajax({ 
       type: 'POST', 
       url: 'php/aggiornaUltimoAccessoServer.php', 
       datatype: "json", 
       success: function(data) { 
           var json = JSON.parse(data); 
            if(!json[0])
            alert("Aggiornamento dell'ultimo accesso non riuscito!"); 
      }, 
       error: function() {
           alert("Impossibile contattare il server di supporto"); 
       }
     }); 
 }

 //aggiorno l'ultimo accesso dell'utente ogni 2 secondi 
 $( document ).ready(function() {
    richiestaAggiorna();  
   var funct = setInterval(richiestaAggiorna, 2000); 
  }); 
  