<?php session_start();  
if($_SESSION['loggedin'] != TRUE) {
  header("Location: index.html"); 
  echo 'utente non loggato'; 
 }
 ?>

<!DOCTYPE html>
 <html lang="it">
 <head>
  <meta charset="UTF-8">
  <meta name="author" content="istruzioni">
   <meta name="Bingo!" lang="it" content="gioco">
  <link rel="stylesheet" href="./stili/Bingo.css" media="screen">
  <link rel="shortcut icon" href="./immagini/B.jpeg" class="head_logo">
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
  <title>Impostazioni - Bingo!</title>
 </head>
 <body>
   <div class="container">
  <header>
   <!--menu a tendina --> 
    <nav id="hormenu">
      <ul>
        <li>
         <a href="#"><img src="./immagini/logo_menu.png" alt="logo del menu" title="Apri menu" width="50" height="50"></a>
       <ul> 
      <li><a href="home.php">HOME</a></li>
      <li><a href="Chiedimi_di_bingo.php">CHIEDIMI DI BINGO!</a></li>
      <li><a href="ServizioClienti.php">SERVIZIO CLIENTI</a></li>
      <li><a href="#">IMPOSTAZIONI</a></li> 
      <li><a href="php/attesalogout.php">LOGOUT</a></li>
      </ul> 
      </li> 
      </ul>
      </nav>
     <img src="./immagini/BingoLogo.png" class="logo" alt="logo">
     </header> 
      <div class="cambia_credenziali">
        <img src="immagini/impostazioni.png"  alt="impostazioni"> 
        <h2>Impostazioni account</h2> 
        <p>Qui &eacute; possibile cambiare le proprie impostazioni dell'accout.</p>
        <p> Si prega di attendere l'avvenuta conferma del cambio di impostazioni.</p>
         <p> Nel caso di problemi persistenti si prega di contattare il servizio clienti. 
        </p>
        <?php 
        //nell'impostazioni non è possibile cambiare il nome utente perchè nel database del progetto 
        //è chiave in alcune tabelle 
         echo '<h3 >Nome Utente: '.$_SESSION['username_login'].'</h3>'; 
         include('php/confDB.php'); 
         if($stmt = $mysqli->prepare('SELECT  Email 
                              FROM `bingo`.`utenti` 
                              WHERE  NomeUtente = ?')) { 
	       //inizializzo i parametri da passare alla query
         $nome = $_SESSION['username_login']; 
        	$stmt->bind_param('s', $nome);
        	$stmt->execute();
	     //conservo il risultato per fare un controllo sull'account
	      $stmt->store_result();
		    $stmt->bind_result($email);
	      $stmt->fetch(); 
         echo '<h3>Email: '.$email.'</h3>'; 
         } else 
          echo "Problemi a recuperare l'email";  
          //serve per recuperare il nome all'interno dei file JS 
          echo '<input type="text" id="nomeutente" value="'.$_SESSION['username_login'].'">'; 
        ?>
        <div class="cambia"> 
          <form method="post" action="php/cambiaemail.php" >
            <h3>Desideri cambiare l'email associata al tuo account?</h3>
            <label> <br>
              Inserisci l'email attuale   
            <input type="email" name="vecchiaemail" placeholder="mario.rossi@gmail.com">
            </label>
            <label> <br>
              Inserisci la nuova email 
            <input type="email" name="nuovaemail" id="emailI" > 
            </label>
            <input type="button" name="cambiaemail" value="Cambia" id="cambiaEmail"> 
         </form>
        </div>  
        <div class="cambia"> 
          <form method="post" action="php/cambiapassword.php" >
            <h3>Desideri cambiare la password associata al tuo account?</h3>
            <label> <br> 
              Inserisci la password attuale 
            </label>  
            <input type="password" name="vecchiapassword">
            <label> <br>
              Inserisci la nuova password 
            <input type="password" name="nuovapassword" id="passwordI"> 
            </label>
            <div id="messaggio_passwordOk0I">
            <p> Password troppo semplice </p>
           </div>
            <div id="messaggio_passwordOk1I">
            <p> Password sicura </p>
          </div>
            <label> <br>
            Conferma la nuova password 
            <input type="password" name="confermapassword" id="conf_passwordI" > 
            </label>
            <div id="messaggio_password0I">
          	<p> Le password inserite non sono uguali </p>
          </div>
          <div id="messaggio_password1I">
          	<p> Le password inserite sono uguali </p>
          </div>
            <input type="button" name="cambiapassword" id="cambiaPassword" value="Cambia"> 
         </form>
        </div>  
      </div>
     <footer>
    <div class="footer_img">
   <img src="immagini/fire.png" alt="fuoco"> 
  <h2>-POWERED BY LUCA CHIOCCHETTI-</h2>
    <h3>Non sai come si gioca? Clicca <a href="Comesigioca.html" target="_blank">qui!</a></h3>
  </div>
  <article class="contatti">
    <div class="info">
    <h2>Contatti:</h2>
    <ul>
    <li><label>Email:</label>
    <p><a href="mailto:chiocchettiluca15@gmail.com">chiocchettiluca15@gmail.com</a></p></li>
    <li><label>Numero di telefono:</label><p>345***7387</p></li>
    </ul>
    </div>
    <aside class="social">
       <h3>Seguiteci anche sui Social!</h3>
      <a href="https://www.facebook.com/" target="_blank" ><img src="immagini/Facebook.png" alt="Facebook"></a>
      <a href="https://www.instagram.com/" target="_blank" ><img src="immagini/instagram.jpg" alt="instagram"></a>
    </aside>
 </article>
 </footer>
  <script src="./js/GestoreImpostazioni.js"></script> 
  <script src="js/utentiOnlineAjax.js" ></script>
 <script src="js/aggiornamentoAccessoAjax.js" ></script>
 <script src="js/premioGiornalieroAjax.js"  ></script> 
 <script src="js/GestioneGiocoAjajx.js" ></script> 
 <script src="js/GestioneGiocoAdminAjax.js" ></script> 
 <script src="js/getMontepremi.js" ></script> 
  
  </div>
</body>
</html>