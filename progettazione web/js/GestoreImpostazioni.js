var mail = false; 
var pass = false; 
var uguali = false; 

//controlla la correttezza della mail inserita
function controllaEmail() {
    var email = document.getElementById("emailI").value;
    var campoemail = document.getElementById("emailI");
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


//funzioni di controllo password per il file impostazioni 
function controllaPassword() {
    var password = document.getElementById("passwordI").value 
    var campoconf = document.getElementById("conf_passwordI");
    var campopass = document.getElementById("passwordI");
    var fatherconf = campoconf.parentNode;
    var fatherpass = campopass.parentNode;
    var w = /[A-Za-z]+/;
    var x = /[0-9]+/;
    if(!password)
        return;
    if(w.test(password) && x.test(password)  && (password.length >= 6)) {
     pass = true;
     document.getElementById("messaggio_passwordOk0I").style.display = "none ";
     document.getElementById("messaggio_passwordOk1I").style.display = "block ";
     fatherpass.className = "okay";
     confronto = true;
     campopass.setCustomValidity("");
     }
     else {
     pass = false;
     confronto = false;
     fatherpass.className = "error";
     campopass.setCustomValidity('Inserisci una password con almeno 6 caratteri alfanumerici');
     document.getElementById("messaggio_passwordOk0I").style.display = "block";
     document.getElementById("messaggio_passwordOk1I").style.display = "none ";
     }
     if(!confronto && !password) {
         campoconf.disabled = true;
       document.getElementById("conf_passwordI").value = null;
       document.getElementById("messaggio_password0I").style.display = "none";
       document.getElementById("messaggio_password1I").style.display = "none ";
       fatherconf.className = "error";
         return;
      }
      else {
          campoconf.disabled = false;
      }
    } 
   
   
   
   function controllaConfrontoPassword() {
    var campoconf = document.getElementById("conf_passwordI");
    var password = document.getElementById("passwordI").value 
    var fatherconf = campoconf.parentNode;
     
     if(password != document.getElementById("conf_passwordI").value) {
      uguali = false;
      fatherconf.className = "error";
      campoconf.setCustomValidity("le password non sono uguali");
      document.getElementById("messaggio_password0I").style.display = "block";
      document.getElementById("messaggio_password1I").style.display = "none ";
     } 
     else {    
      uguali = true;
      document.getElementById("messaggio_password0I").style.display = "none ";
      document.getElementById("messaggio_password1I").style.display = "block ";
      fatherconf.className = "okay";
      campoconf.setCustomValidity("");  
    }
   }
   
   function confermaCambiaEmail(){  
   if( mail) {
    document.getElementById("cambiaEmail").type = "submit";
    var tipo = document.getElementById("cambiaEmail").type;
   }
   else 
    alert("ATTENZIONE: Riempire tutti i campi correttamente");
  }

  function confermaCambiaPassword(){  
    if(uguali & pass) {
     document.getElementById("cambiaPassword").type = "submit";
     var tipo = document.getElementById("cambiaPassword").type;
    }
    else 
     alert("ATTENZIONE: Riempire tutti i campi correttamente");
   }

//eventi legati al file impostazioni.php 
document.getElementById("conf_passwordI").addEventListener("input", controllaConfrontoPassword);
document.getElementById("conf_passwordI").addEventListener("focus", controllaConfrontoPassword);
document.getElementById("passwordI").addEventListener("focus", controllaPassword);
document.getElementById("passwordI").addEventListener("input", controllaPassword);
document.getElementById("emailI").addEventListener("input",  controllaEmail); 
document.getElementById("cambiaEmail").addEventListener("click",confermaCambiaEmail ); 
document.getElementById("cambiaPassword").addEventListener("click",confermaCambiaPassword ); 

