
 <?php session_start(); //controllo che l'utente sia entrato tramite login 
 if($_SESSION['loggedin'] != TRUE){
  header("Location: index.html"); 
  echo 'utente non loggato'; 
 }
 ?>
 <!DOCTYPE html>
 <html lang = "it">
 <head>
  <link rel="shortcut icon" href="./immagini/B.jpeg" class="head_logo">
   <title>Servizio clienti - Bingo!</title>
   <meta charset="UTF-8">
  <meta name="author" content="assistenza">
  <meta name="Bingo!" lang="it" content="gioco">
  <link rel="stylesheet" href="./stili/Bingo.css" media="screen">
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
 </head>
 <body>
 <?php 
    //serve per recuperare il nome all'interno dei file JS 
    echo '<input type="text" id="nomeutente" value="'.$_SESSION['username_login'].'">'; 
    ?>
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
  <li><a href="#">SERVIZIO CLIENTI</a></li>
  <li><a href="Impostazioni.php">IMPOSTAZIONI</a></li> 
  <li><a href="php/attesalogout.php">LOGOUT</a></li>
  </ul>  
  </li> 
</ul>
</nav>
      <img src="./immagini/BingoLogo.png" class="logo" alt="logo">
  </header>
 <section class="servizio titolo">
   <img src="immagini/assistenzaclienti.png" alt="assistenza"><h2>BENVENUTI NEL SERVIZIO CLIENTI</h2>
  <h3>Questa sezione &eacute; destinata al servizio clienti.</h3>
  <p>Qualora l'utente abbia riscontrato degli errori durante il gioco come: vincite non riscosse, numeri non segnati ecc...<br>
   Si consiglia di compilare i campi sottostanti specificando il tipo di problema.</p>
  <p>Il nostro team si metter&eacute; subito a lavoro per sistemare il problema.<br>
  Appena risolto vi verr&aacute; comunicato per email!<br>
  Grazie mille per il vostro aiuto!</p> 
 </section>
 <form id="serv" name="formmail" method="post" action="php/servizioclientiDB.php" >
  <label for="email">*Email</label>
  <input type="email" id="email" name="email" placeholder="Indirizzo di posta elettronica" required>

  <div class="choice">
  <label>*Seleziona il tipo di problema Riscontrato.<br>
  &egrave; permessa una sola scelta:<br>
  Nel caso di Altro... specificare il problema nei commenti.
  </label>
  <select name="problem" required> 
  <option value="">Scegliere un opzione</option> 
  <option value="Vincita non versata" > Vincita non versata</option>
  <option value="Casella non segnata" >Impossibilit&agrave; di marcare le caselle</option>
  <option value="Premio giornaliero non arrivato " >Premio giornaliero non arrivato</option>
  <option value="impostazioni password non funzionanti" >Non mi fa cambiare password nell'impostazioni</option>
  <option value="impostazioni email non funzionanti"  >Non mi fa cambiare l'email nell'impostazioni</option> 
  <option value="Altro... " >Altro...</option>
  </select>
 </div>
  <label for="msg">Scrivi un breve commento riguardarte il tuo problema(max 150 caratteri)</label>
  <textarea id="msg" name="msg" placeholder="Scrivi il tuo Commento:" 
   onKeyUp="update(document.formmail)" maxlength="150"></textarea>
				<label> Caratteri rimasti:
					<input name="contatore" type="text" value="150" size="3" readonly="readonly" 
								id="contatore"><br>
				</label><br>
  <p><strong class="postilla">* campi obbligatori</strong></p>
  <input type="submit" name="button" id="richiesta" value="Invia Richiesta">
  </form>
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
      <a href="https://www.facebook.com/" target="_blank" >
      <img src="immagini/Facebook.png" alt="Facebook"></a>
      <a href="https://www.instagram.com/" target="_blank" >
      <img src="immagini/instagram.jpg" alt="instagram"></a>
    </aside>
 </article>
 </footer>
 <script src="js/ServizioClienti.js" ></script> 
 <script src="js/utentiOnlineAjax.js" ></script>
 <script src="js/aggiornamentoAccessoAjax.js" ></script>
 <script src="js/premioGiornalieroAjax.js"  ></script> 
 <script src="js/GestioneGiocoAjajx.js" ></script> 
 <script src="js/GestioneGiocoAdminAjax.js" ></script> 
 <script src="js/getMontepremi.js" ></script> 
</div>
 </body>
</html>