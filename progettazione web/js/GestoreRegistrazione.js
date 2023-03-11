//inizializzo le variabili per i controlli, per sottomettere la form devono essere tutte vere
var uguali = false;
var us = false;
var dat = false;
var mail = false;
var pass = false;
var termini = false;
var click = 0;
var confronto = false; //serve per abilitare il confronto nel controllo password

//Gestione degli input all'interno della form
//controllo del corretto inserimento dei dati e della password con conferma richiesta
//la form viene sottomessa solo se non ci sono errori e i termini e condizioni vengono accettati

function controllaUsername() {
  var nomeutente = document.getElementById("username").value;
  var campouser = document.getElementById("username");
  var userparent = campouser.parentNode;
  console.log("fin qui")
  var k = /[\,\.\s\\\|\/\(\)\[\]\{\}]+/;
  if(k.test(nomeutente) || !nomeutente) {
  	us = false;
  	userparent.className = "error";
  	document.getElementById("messaggio_username0").style.display = "block";
    document.getElementById("messaggio_username1").style.display = "none ";
  	campouser.setCustomValidity("Il nome utente non deve contenere i seguenti caratteri: punto, virgola, i backslash" +
  	 " e qualunque parentesi ");
  }
  else {
  	us = true;
  	campouser.setCustomValidity('');
    userparent.className = "okay";
    document.getElementById("messaggio_username0").style.display = "none ";
    document.getElementById("messaggio_username1").style.display = "block ";
 }
}

//controllo che il nome inserito non contenga numeri
function controllaNome() {
  var nome = document.getElementById("nome").value;
  if(nome) { //controllo solo se l'utente vuole inserire il nome 
  var camponome = document.getElementById("nome");
  var parent = camponome.parentNode;
  console.log("fin qui")
  var x = /^[A-Za-z\s]+$/;
  if(!x.test(nome) || nome == " ") {
  	parent.className = "error"; 
  	camponome.setCustomValidity('Inserisci un nome senza numeri');
  }
  else {
  	camponome.setCustomValidity('');
    parent.className = "okay";
  } 
 }
}

//controllo che il cognome inserito non contenga numeri
function controllaCognome() {
  var cognome = document.getElementById("cognome").value;
  if(cognome) { //se il cognome è nullo non mi importa dei controli 
  var campocognome = document.getElementById("cognome");
  var coparent = campocognome.parentNode;
  console.log("fin qui")
  var y = /^[A-Za-z\s]+$/;
  if(!y.test(cognome) || cognome == " ") {
  	coparent.className = "error"; 
  	campocognome.setCustomValidity('Inserisci un cognome senza numeri');
  }
  else {
  	campocognome.setCustomValidity('');
    coparent.className = "okay";
  }
 }
}
//controllo della data
//per registrarsi bisogna essere maggiorenni
// il range di età andrà dai 18 anni in su
function controllaData() {
 var valoredata = document.getElementById("data").value;
 var campodata = document.getElementById("data");
 var fatherdata = campodata.parentNode;
 if(!valoredata){
    dat = false;
  	return;
 }
 var datacorrente = new Date(); 
 var datenascita = new Date(valoredata);
 var annonascita = datenascita.getFullYear();
 var annocorrente = datacorrente.getFullYear();
 var mesenascita = datenascita.getMonth();
 var mesecorrente = datacorrente.getMonth();
 var giornonascita = datenascita.getDate();
 var giornocorrente = datacorrente.getDate();
 
 if((annocorrente - annonascita) < 18 ){
 	dat = false;
  	fatherdata.className = "errorDate"; 
  	campodata.setCustomValidity('Devi essere maggiorenne per poterti registrare');
  	document.getElementById("messaggio_date0").style.display = "block";
    document.getElementById("messaggio_date1").style.display = "none ";
 }
 else if((annocorrente - annonascita) == 18){
 	if(mesecorrente >= mesenascita) {
 	  if(giornocorrente >= giornonascita) {
        dat = true;
  	    campodata.setCustomValidity('');
        fatherdata.className = "okayDate";
        document.getElementById("messaggio_date0").style.display = "none ";
        document.getElementById("messaggio_date1").style.display = "block ";
 	   }
 	   else {
 	   	dat = false;
  	   fatherdata.className = "errorDate"; 
  	   campodata.setCustomValidity('Devi essere maggiorenne per poterti registrare');
  	   document.getElementById("messaggio_date0").style.display = "block";
       document.getElementById("messaggio_date1").style.display = "none ";
 	   }
      }
    else {
     dat = false;
  	fatherdata.className = "errorDate"; 
  	campodata.setCustomValidity('Devi essere maggiorenne per poterti registrare');
  	document.getElementById("messaggio_date0").style.display = "block";
    document.getElementById("messaggio_date1").style.display = "none ";
    }
 }
 else {
   dat = true;
   campodata.setCustomValidity('');
   fatherdata.className = "okayDate";
    document.getElementById("messaggio_date0").style.display = "none ";
    document.getElementById("messaggio_date1").style.display = "block ";
 }
}


//controlla la correttezza della mail inserita
function controllaEmail() {
  var email = document.getElementById("email").value;
  var campoemail = document.getElementById("email");
  var fatheremail = campoemail.parentNode;
  var k = /^[a-zA-Z0-91\.]{1,}@[a-zA-Z\-]{2,}[.][a-zA-Z]{2,}$/;
  if(!k.test(email)) {
  	mail = false;
  	fatheremail.className = "error"; 
  	campoemail.setCustomValidity('Inserisci un cognome senza numeri');
  }
  else {
  	mail = true;
  	campoemail.setCustomValidity("");
    fatheremail.className = "okay";

  }
}

//controlla la correttezza della password. 
//per ragioni di sicurezza è richiesta una password di almeno 6 caratteri alfanumerici
//controlla se le password inserite nei due campi sono uguali
//il controllo password viene disabilitato se la password non rispetta i criteri
//la correttezza delle due parti è necessaria per poter sottomettere la form
function controllaPassword() {
 var password = document.getElementById("password").value 
 var campoconf = document.getElementById("conf_password");
 var campopass = document.getElementById("password");
 var fatherconf = campoconf.parentNode;
 var fatherpass = campopass.parentNode;
 var w = /[A-Za-z]+/;
 var x = /[0-9]+/;
 if(!password)
 	return;
 if(w.test(password) && x.test(password)  && (password.length >= 6)) {
  pass = true;
  document.getElementById("messaggio_passwordOk0").style.display = "none ";
  document.getElementById("messaggio_passwordOk1").style.display = "block ";
  fatherpass.className = "okay";
  confronto = true;
  campopass.setCustomValidity("");
  }
  else {
  pass = false;
  confronto = false;
  fatherpass.className = "error";
  campopass.setCustomValidity('Inserisci una password con almeno 6 caratteri alfanumerici');
  document.getElementById("messaggio_passwordOk0").style.display = "block";
  document.getElementById("messaggio_passwordOk1").style.display = "none ";
  }
  if(!confronto && !password) {
  	campoconf.disabled = true;
    document.getElementById("conf_password").value = null;
    document.getElementById("messaggio_password0").style.display = "none";
    document.getElementById("messaggio_password1").style.display = "none ";
    fatherconf.className = "error";
  	return;
   }
   else {
   	campoconf.disabled = false;
   }
 } 



function controllaConfrontoPassword() {
 var campoconf = document.getElementById("conf_password");
 var password = document.getElementById("password").value 
 var fatherconf = campoconf.parentNode;
  
  if(password != document.getElementById("conf_password").value) {
   uguali = false;
   fatherconf.className = "error";
   campoconf.setCustomValidity("le password non sono uguali");
   document.getElementById("messaggio_password0").style.display = "block";
   document.getElementById("messaggio_password1").style.display = "none ";
  } 
  else {    
   uguali = true;
   document.getElementById("messaggio_password0").style.display = "none ";
   document.getElementById("messaggio_password1").style.display = "block ";
   fatherconf.className = "okay";
   campoconf.setCustomValidity("");  
 }
}


//se vengono accettati i termini e condizioni vieni abilitato il bottone per registrarsi 
function Acconsenti() {
  console.log("qui"); 
 var div = document.getElementsByTagName("img"); 
 var img1 = div[1];
 if(click % 2 == 0) {
 img1.src="./immagini/termini1.jpeg";
 document.getElementById("buttons").disabled = false;
 termini = true;
 click++;
 }
 else {
 img1.src="./immagini/termini0.jpeg";
 document.getElementById("buttons").disabled = true;
 termini = false;
 click++;
 }
 console.log(click);
}

	
function confermaRegistrazione(){
	console.log("qui"); 
 if(uguali && us  && dat && pass && mail && termini) {
  document.getElementById("buttons").type = "submit";
  var tipo = document.getElementById("buttons").type;
  console.log(tipo); 
 }
 else 
  alert("ATTENZIONE: tutti i campi devono essere compilati correttamente per registrarsi");
}



// Assegnamo le funzioni agli eventi 
document.getElementById("data").addEventListener("blur", controllaData);
document.getElementById("username").addEventListener("input", controllaUsername);
document.getElementById("nome").addEventListener("input", controllaNome);
document.getElementById("cognome").addEventListener("input", controllaCognome);
document.getElementById("email").addEventListener("input", controllaEmail);
document.getElementById("conf_password").addEventListener("input", controllaConfrontoPassword);
document.getElementById("password").addEventListener("input", controllaPassword);
document.getElementById("termini_img").addEventListener("click", Acconsenti); 
//ulteriore controllo sulle condizioni 
document.getElementById("username").addEventListener("focus", controllaUsername);
document.getElementById("nome").addEventListener("focus", controllaNome);
document.getElementById("cognome").addEventListener("focus", controllaCognome);
document.getElementById("data").addEventListener("focus", controllaData);
document.getElementById("email").addEventListener("focus", controllaEmail);
document.getElementById("conf_password").addEventListener("focus", controllaConfrontoPassword);
document.getElementById("password").addEventListener("focus", controllaPassword);
document.getElementById("buttons").addEventListener("click", confermaRegistrazione);

