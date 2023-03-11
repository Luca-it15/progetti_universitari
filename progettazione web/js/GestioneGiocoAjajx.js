
function richiestaInfo() {  
  $.ajax({ 
       type: 'POST', 
       url: 'php/infoUtenteServer.php', 
       datatype: "json", 
       success: function(datainfo) { 
           //avrò un array contenente il nome utente( indice 0) e il saldo (indice 1) 
           var jsoninfo = JSON.parse(datainfo); 
           $('#info').empty(); 
          $('#info').append('<p><img src="immagini/utente.PNG" id="utenti"' +
          ' alt="utenti"  >'
          +  ' ' + 
          jsoninfo[0] + '</p><p>' + jsoninfo[1] + 
        '<img src="immagini/monete.jpg" id="moneta" alt="monete"></p>');   
         }, 
       error: function() {
           alert("Impossibile contattare il server di supporto"); 
       }
     });  
 }
 
 $( document ).ready(function() {
    richiestaInfo();  
  }); 

//mi permette di cambiare il colore alle caselle selezionate e poterle deselezionare, 
$("#Cartellina").click(function(event) { 
  var id =  event.target.id; 
  var nomeclasse = $("#"+id).attr('class'); 
  console.log(nomeclasse); 
  if(nomeclasse != "Trovato") { 
   $("#" + id).attr('class', 'Trovato'); 
   $("#" + id).css("background", "#ffd700"); 
   $("#" + id).css("border-bottom", "10px ridge black"); 
   } else { 
    $("#" + id).attr('class', 'NonTrovato'); 
    $("#" + id).css("background-color", "#ffffff"); 
    $("#" + id).css("border-bottom", "2px solid black");
   } 
  }  
 );  

 function orarioPartita() { 
  $.ajax({ 
    type: 'POST', 
    url: 'php/infoPartitaServer.php', 
    datatype: "json", 
    success: function(values) { 
        //avrò un array contenente lo stato delle query(indice 0), l'id della partita (indice 1), 
        //la data e l'orario della partita (indice 2)
        var info = JSON.parse(values); 
        if(info[0]) {
           if(info[1]) {  //ci sono partite programmate 
             $('#orariopartita').empty(); 
             //divido la stringa contenete la data e l'orario della partita
             var dataOrario = info[2].split(" ");  
             //divido la data per avere il formato giorno-mese-anno 
             var data = dataOrario[0].split('-');
             var tempolocaleDate = new Date; 
             console.log(tempolocaleDate); 
             var tempolocaleString = tempolocaleDate.toString()
             console.log(tempolocaleString); 
             var infoLocale = tempolocaleString.split(' ');
             var orarioLocale = infoLocale[4]; 
             console.log(orarioLocale); 
             console.log(dataOrario[1]);
             if(orarioLocale >= dataOrario[1]) {
               $('#orariopartita').append('<h3>Partita N: ' + info[1] + '</h3>'); 
               $('#orariopartita').append('<h3>La partita &egrave; in corso </h3>'); 
               }
              else {
                $('#orariopartita').append('<h3>PROSSIMA PARTITA: Partita N. ' 
                + info[1] + '</h3>');
               $('#orariopartita').append('<h3> inizia alle ' + dataOrario[1] + 
               ' di oggi: ' + data[2] + '-' + data[1] + '-' + data[0] + '</h3>');
                } 
              } else { 
                $('#orariopartita').empty(); 
                $('#orariopartita').append('<h3>Non ci sono partite programmate</h3>'); 
              } 
            } else 
              alert("Errore: informazioni della partita non recuperate");   
       }, 
    error: function() {
        alert("Impossibile contattare il server di supporto"); 
     }
   }); 
  }

  $(document).ready(function() { 
    orarioPartita(); 
    setInterval(orarioPartita, 1000); 
  }); 

 function getNumeriEstratti() { 
   //chimata ajax che mi restituisce i numeri estratti 
  $.ajax({ 
    type: 'POST', 
    url: 'php/getNumeriEstrattiServer.php', 
    datatype: "json", 
    success:  function(estratti) { 
      var num =  JSON.parse(estratti); 
      if(num[0]) { //condizione di errore
        if(num[1]) { //restituisco in numeri solo se l'utente è in gioco 
        var dim = num.length; //recupero il numero dei numeri estratti 
        $('#numeriestratti').empty(); 
        $('#ultimoestratto').empty(); 
        if((dim > 3) && (num[2] != 0)) { //sono stati estratti numeri oltre al primo
          $('#numeriestratti').append('<h2>NUMERI ESTRATTI</h2>'); 
         for(var i = 2; i < (dim - 1); i++) { 
           $('#numeriestratti').append('<div class="estratto">' + 
           num[i] + '</div>'); 
         }
           $('#ultimoestratto').append('<h2>ULTIMO NUMERO ESTRATTO</h2>'); 
           $('#ultimoestratto').append('<div class="estratto">' + 
            num[dim - 1] + "</div>" ); 
         } else if((dim == 3) && (num[dim - 1] != 0)) { 
          $('#ultimoestratto').append('<h2>ULTIMO NUMERO ESTRATTO</h2>'); 
          $('#ultimoestratto').append('<div class="estratto">' + 
           num[dim - 1] + "</div>" ); 
         } else { 
          $('#numeriestratti').append("<h2>NESSUN NUMERO ESTRATTO</h2>");  
           } 
          } else { 
            $('#numeriestratti').empty(); 
            $('#ultimoestratto').empty(); 
            $('#numeriestratti').append("<h2>NON SEI IN GIOCO</h2>"); 
          } 
        } else { 
          alert("Errore: Numeri estratti non recuperati"); 
        }
      }, 
       error: function() {
      alert("Impossibile contattare il server di supporto");
    } 
  });
 } 

 $(document).ready(function() {  
  setInterval(getNumeriEstratti, 1000);
 }); 

 function puliscizona() { 
       //se l'utente non è piu in gioco a seguito di un Bingo(azione che 
           //non dipende dall'utente stesso), ripulisco la zona di gioco, 
           //ciò è dovuto al fatto che non posso lasciare che sia l'utente ad 
           //occuparsi di chiamare la funzione con un eventuale tasto 
           //perche potrebbe riusare la cartellina e ciò non è consentito 
           $('#Cartellina').empty();  
          $('#Zona_Gioco_bottoni').empty(); 
          $('#Zona_Gioco_Cartella').empty(); 
          $('#Zona_Gioco_Cartella').append('<h2>Per poter giocare &egrave; neccessario ' + 
        'acquistare una cartellina.</h2> ' +  '<h3>una cartellina costa 5 monete</h3>'); 
          $('#acquisto').empty(); 
          $('#acquisto').append('<button type="button" '
           + 'value="Acquista" >Acquista</button> '); 
 }

 function getVincitore() { 
   //chiamata ajax che mi restituisce i vincitori della partita 
  $.ajax({ 
    type: 'POST', 
    url: 'php/getVincitoreServer.php', 
    datatype: "json", 
    success: function(data) { 
      var vincitori = JSON.parse(data); 
      var nome = $('#nomeutente').val(); 
      console.log(nome); 
      if(vincitori[0]) { 
        $('#vincitori').empty(); 
        $('#vincitori').append("<h4>VINCITORI</h4>"); 
        if(vincitori[1] && !vincitori[2]) { //non è false e contiene il nome 
          //dell'utente che ha fatto cinquina  
            $('#vincitori').empty(); 
            $('#vincitori').append("<h4>VINCITORI</h4>"); 
            $('#vincitori').append("<p>CINQUINA: " + vincitori[1] + "</p>" );
          } 
          else if(vincitori[2]) { 
              $('#vincitori').empty(); 
              $('#vincitori').append("<h4>VINCITORI</h4>"); 
              $('#vincitori').append("<p>CINQUINA: " + vincitori[1] + "</p>" ); 
              $('#vincitori').append("<p>BINGO: " + vincitori[2] + "</p>" );
              puliscizona();
              if(nome != "Admin" && nome != vincitori[2]) {   
               alert("L'utente " + vincitori[2] + " ha fatto bingo ");
                
              } 
              if(nome != "Admin")
               alert("la partita e' terminata");
             } 
            else 
           $('#vincitori').append("<h5>NESSUN VINCITORE</h5>"); 
       } 
      else 
       alert("ERRORE: impossibile recuperare informazione dei vincitori"); 
      },  
  error: function() {
   alert("Impossibile contattare il server di supporto");
   } 
  });
 } 

 $(document).ready(function() { 
  getVincitore(); 
  setInterval(getVincitore, 6000);
 });                                          

 function termina() { 
   //chiamata ajax per terminare la partita in corso 
  $.ajax({ 
    type: 'POST', 
    url: 'php/terminaServer.php', 
    datatype: "json", 
    success: function(esito) { 
      var risu = JSON.parse(esito); 
      if(!risu) { 
        alert("ERRORE: partita non terminata");

      }
    },   error: function() {
      alert("Impossibile contattare il server di supporto");
    } 
  });
 } 


 function vincita(tipo) { 
  $.ajax({ 
    type: 'POST', 
    url: 'php/vincitaServer.php', 
    data: "vincita=" + tipo, 
    datatype: "json", 
    success: function(data) { 
      var risu = JSON.parse(data); 
      if(risu[0]) { //verifico che tutte le query siano state eseguite correttamente 
        if(risu[1]) { 
          if(risu[2]) { 
            if(risu[3]) {
              alert("COMPLIMENTI! HAI FATTO " + tipo + 
               "!" + " hai ottenuto " + risu[4]); 
               richiestaInfo();  
               if(tipo == "BINGO") { 
                 setTimeout(termina, 6000); 
               }
             } else 
             alert("Peccato! i numeri trovati sono insufficienti"); 

          } else {
           alert("Premio " + tipo + " gia riscosso, consultare la tabella vincitori");
          }  
        } else 
         alert("i numeri usciti  sono insufficienti per " + tipo); 

      } else 
        alert("ERRORE: non &egrave; stato possibile verificare la vincita" + 
        " contattare il servizio clienti"); 
     }, 
     error: function() {
      alert("Impossibile contattare il server di supporto");
    } 
  });
 } 

 $("#Zona_Gioco_bottoni").click(function(event) { 
  var id =  event.target.id; 
  var tipovincita = $("#"+id).val();  
  vincita(tipovincita); 
  });  

 