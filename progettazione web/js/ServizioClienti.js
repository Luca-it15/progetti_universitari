//gestore per la casella di testo al'interno di servizio clienti 
//serve per limitare l'inserimento dei caratteri nel commento in modo 
//che sia possibile inserirlo nel DB 

var MAX_CHAR = document.formmail.contatore.value; // inizializzato la prima volta

function reverse(str) {
  var newStr = '';
  for (var i = str.length - 1; i >= 0; i--)
    newStr += str[i];
  return newStr;
}

function update(form) {
    if (form.msg.value.length > MAX_CHAR) {
		form.msg.value = form.msg.value.replace(/\s+/g, " ");
    	if (form.msg.value.length > MAX_CHAR){
			//quando l'utente supera la lunghezza consentita 
			//togliamo quello che scrive in piu 
    		var start = reverse(form.formmail.value.substring(MAX_CHAR, 
    						form.formmail.value.length));
    		var end = form.formmail.value.substring(0, MAX_CHAR-start.length)
        	form.formmail.value = start + end;
       	 	form.contatore.value = 0;
       	 	return;
       	 } 
	}
	form.contatore.value = MAX_CHAR - form.msg.value.length;
	
}
