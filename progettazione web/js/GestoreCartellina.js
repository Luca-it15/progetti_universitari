//si potrebbe creare piu layout diversi di cartelline ma ogni layout dovrà avere la propria 
//funzione php in ServerClass che inizializza i numeri della cartellina con i rispettivi numeri 
//di riga, tali numeri sono necessari al fine di controllare la correttezze di una 
//cinquina 

function richiestaCartellina() { 
    $.ajax({ 
     type: 'POST', 
     url: 'php/cartellinaServer.php', 
     datatype: "json", 
     success: function(numeri) { 
        //avrò un array in cui l'indice 0 mi indica se le query sono andate a buon fine 
        //mentre nell'indice 1 avrò 0 se non ci sono numeri altrimenti, se  > 1, 
        //nell'indice 1 avrò il primo numero e nei restanti indici gli altri numeri della 
        //cartellina  
        var numerijson = JSON.parse(numeri); 
        var numeri = numerijson; 
        if(numerijson[0]) {
         if(numerijson[1]) { 
          //se sono qui dentro vuol dire che ho i numeri della cartellina. 
          //crea la cartellina, data la struttura  che non segue un rigore 
          //si rende necessario replicare il codice con gli adeguati cambiamenti
         $('#Zona_Gioco_Cartella').empty(); 
         $('#Cartellina').empty(); 
         $('#acquisto').empty(); 
         $('#Zona_Gioco_Cartella').append('<p id="gioca"><strong>CARTELLINA DI GIOCO'
          + '<strong><p>');
         $('#Cartellina').append('<div id="1_9" class="cartellina">' + 
         '<input type="button" id="uno" class="NonTrovato"'  + 
         ' value="' + numerijson[0] + '" readonly>' + 
         '<input type="text" value=" " disabled>' + 
         '<input type="button" id="due" class="NonTrovato" value="' + numerijson[1] + 
           '"  readonly> </div>' 
         ); 
         $('#Cartellina').append('<div id="10_19" class="cartellina">' + 
         '<input type="text" value=" " disabled>' + 
         '<input type="button" id="tre" class="NonTrovato"'  + 
         ' value="' + numerijson[2] + '" readonly>'+
         '<input type="text" value=" " disabled> </div>'
         ); 
         $('#Cartellina').append('<div id="20_29" class="cartellina" >' + 
         '<input type="button" id="quattro" class="NonTrovato" '  + 
         ' value="' + numerijson[3] + '" readonly>' + 
         '<input type="text" value=" " disabled>' + 
         '<input type="button" id="cinque" class="NonTrovato" value="' + numerijson[4] + 
           '"  readonly> </div>'
         ); 
         $('#Cartellina').append('<div id="30_39" class="cartellina">' + 
         '<input type="text" value=" " disabled>' + 
         '<input type="button" id="sei" class="NonTrovato" '  + 
         ' value="' + numerijson[5] + '" readonly>'+
         '<input type="text" value=" " disabled> </div>'
          );  
          $('#Cartellina').append('<div id="40_49" class="cartellina" >' + 
          '<input type="text" value=" " disabled>' + 
          '<input type="button" id="sette" class="NonTrovato" '  + 
          ' value="' + numerijson[6] + '" readonly>'+
          '<input type="text" value=" " disabled> </div>'
         ); 
         $('#Cartellina').append('<div id="50_59" class="cartellina">' + 
         '<input type="button" id="otto" class="NonTrovato" '  + 
         ' value="' + numerijson[7] + '" readonly>' + 
         '<input type="text" value=" " disabled>' + 
         '<input type="button" id="nove" class="NonTrovato" value="' + numerijson[8] + 
           '"  readonly> </div>'
         ); 
         $('#Cartellina').append('<div id="60_69" class="cartellina" >' + 
         '<input type="button" id="dieci" class="NonTrovato" '  + 
         ' value="' + numerijson[9] + '" readonly>' + 
         '<input type="text" value=" " disabled>' + 
         '<input type="button" id="undici" class="NonTrovato" value="' + numerijson[10] + 
           '"  readonly> </div>'
         ); 
         $('#Cartellina').append('<div id="70_79" class="cartellina" >' + 
         '<input type="text" value=" " disabled>' + 
         '<input type="button" id="dodici" class="NonTrovato" '  + 
         ' value="' + numerijson[11] + '" readonly>' +  
         '<input type="button" id="tredici" class="NonTrovato" value="' + numerijson[12] + 
           '"  readonly> </div>'
         );
         $('#Cartellina').append('<div id="80_89" class="cartellina">' + 
         '<input type="button" id="quattordici" class="NonTrovato" '  + 
         ' value="' + numerijson[13] + '" readonly>' + 
         '<input type="button" id="quindici" class="NonTrovato" value="' + numerijson[14] + 
           '"  readonly> ' + 
           '<input type="text" value=" " disabled></div>' );
          $('#Zona_Gioco_bottoni').empty(); 
          $('#Zona_Gioco_bottoni').append('<input type="button" id="cinquina" value="CINQUINA">'); 
          $('#Zona_Gioco_bottoni').append('<input type="button" id="bingo" value="BINGO">');   
         richiestaInfo();
        } else { 
          $('#Cartellina').empty(); 
          $('#Zona_Gioco_bottoni').empty(); 
          $('#Zona_Gioco_Cartella').empty(); 
          $('#Zona_Gioco_Cartella').append('<h2>Per poter giocare &egrave; neccessario ' + 
          'acquistare una cartellina.</h2> '    
           + ' <h3>una cartellina costa 5 monete</h3>'); 
           $('#acquisto').append('<button type="button" '
           + 'value="Acquista">Acquista</button> '); 
        }
      } else 
       alert("Errore: Cartellina non creata, contattare il servizio clienti");   
    }, 
    error: function() {
        alert("Impossibile contattare il server di supporto"); 
    }
  });
 }
//mi serve per mantenere la cartellina anche nel caso l'utente ricaricasse la pagina o perdesse 
//la connessione 

$( document ).ready(function() {
  richiestaCartellina();  
}); 


$('#acquisto').click(function() { 
  var bool = confirm("Sei sicuro di voler acquistare la Cartellina?"); 
  if(bool) { 
    //chiamata ajax per acquistare una cartellina 
  $.ajax({ 
      type: 'POST', 
      url: 'php/PagamentoCartellaServer.php', 
      datatype: "json", 
      success: function(data) { 
          var json = JSON.parse(data); 
          if(json[0]) {
            if(json[1]) {
             if(json[2]) {  
               richiestaInfo();
                richiestaCartellina(); 
              } else 
              alert("La partita è gia cominciata, si prega di attendere la prossima"); 
             } else 
             alert("Saldo non sufficiente!");
           } else 
            alert("Errore: pagamento non riuscito, contattare il servizio clienti");   
         }, 
      error: function() {
          alert("Impossibile contattare il server di supporto"); 
      }
    });
  }
 }); 