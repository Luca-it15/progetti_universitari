 //richiesta per sapere quali utenti online in gioco ci sono 
 function Richiesta() { 
 $.ajax({  
      type: 'POST', 
      url: 'php/utentiOnlineServer.php', 
      datatype: "json", 
      success: function(data) { 
          var json = JSON.parse(data); 
          $('#tabellamici').empty(); 
          $('#tabellamici').append('<img src="immagini/amici.PNG" alt="amici online">' +
          '<strong>Utenti Online in gioco: </strong>'); 
          $('#tabellamici').append(  '<p>' );
          for(var i = 0; i < json.length; i++){ 
            console.log(json[i]); 
            if(json.length >= 1) {  
            $('#tabellamici').append('<img src="immagini/online.png" alt="online">'
            + json[i] + '<br>');
          }
          else 
           $('#tabellamici').append('<p>Nessun utente online</p>'); 
          $('#tabellamici').append( '</p>' );
       }
     }, 
      error: function() {
          alert("Impossibile contattare il server di supporto"); 
      }
    }); 
}

//al caricamento della pagina dopo ogni 10 secondi viene inviata la richiesta al server 
$( document ).ready(function() {
  Richiesta();  
 var funct = setInterval(Richiesta, 10000); 
}); 



