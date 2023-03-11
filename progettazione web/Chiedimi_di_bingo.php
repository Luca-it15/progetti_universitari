<?php 
 session_start();//controllo che l'utente sia entrato tramite login  
if($_SESSION['loggedin'] != TRUE){ 
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
  <title>Chiedimi di Bingo! - Bingo!</title>
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
         <a href="#"><img src="./immagini/logo_menu.png" alt="logo del menu" title="Apri menu" ></a>
     <ul> 
    <li><a href="home.php">HOME</a></li>
    <li><a href="#">CHIEDIMI DI BINGO!</a></li>
    <li><a href="ServizioClienti.php">SERVIZIO CLIENTI</a></li>
    <li><a href="Impostazioni.php">IMPOSTAZIONI</a></li> 
    <li><a href="php/attesalogout.php">LOGOUT</a></li>
    </ul> 
    </li> 
  </ul>
 </nav>
      <img src="./immagini/BingoLogo.png" class="logo" alt="logo">
  </header>
  	<h1 class="titolo" id="cosebingo"> CHIEDIMI DI BINGO!</h1>
   <article>
   <div class="container_border">
   	<ul>
   	<li><h2>Cos'&egrave; Bingo!</h2>
   	<p>Bingo &egrave; un servizio online che permette agli utenti di giocare al Bingo anche se non hanno molto tempo da perdere e non possono incontrarsi
      con i propri amici 
     e/o parenti per giocare.
      Bingo! riunisce gli appassionati del noto gioco che non vogliono rinunciare a una piacevole partita e vogliono provare a fare bingo
      con un colpo di fortuna!</p><br>
   	<strong>Esempio di scheda del bingo</strong><br>
   	<img src="./immagini/schedabingo.jpg" title="scheda bingo" alt="scheda bingo">
   	 <li><h2 >Regole del Bingo!</h2>
   	 <p>In questa sezione si trovano le regore del bingo per chi si vuole avvicinare per la prima volta al bingo e per quelli 
      che si vogliono spolverare un po' la memoria.
   	 Il gioco che si pratica in Italia deriva dal lotto e segue
     quasi integralmente le regole del tradizionale gioco della tombola con l'unica variante che si vince solo 
      con la cinquina ed il bingo.</p> 
   	 <h3>Le cartelle</h3>
     <p>Prima di cominciare ogni partita ai giocatori vengono vendute le cartelle con stampate tre file di cinque numeri ciascuna per un totale 
     di quindici numeri. 
     La distribuzione dei numeri sulla cartella segue uno schema che garantisce cinque numeri per fila ed almeno un numero per ogni colonna.
     Le cartelline hanno il solo scopo di permettere all'utente di tenere traccia dei propri numeri usciti. 
     Per fare Bingo o Cinquina deve essere l'utente a dichiarare la possibile vincita, tramite gli appositi 
     pulsanti, come si farebbe in una partita reale. 
     </p> 
     <h3>L'estrazione</h3>
     <p>L'estrazione dei numeri viene effettuata con delle macchine, nel nostro caso è il computer che genera casualmente dei numeri.</p> 
     <h3>Bingo</h3>
     <p>Il giocatore che per primo annulla tutti i quindici numeri presenti sulla sua cartella si aggiudica 
     il premio "Bingo", al momento corrispondente al 75% del montepremi.</p>
     <h3>Cinquina</h3>
     <p>Il giocatore che per primo annulla tutti i cinque numeri presenti su una delle tre file della sua cartella si aggiudica il premio "Cinquina", 
     al momento corrispondente al 15% del montepremi.
     </p></li>
     <li><h2 id="salvadanaio">Salvadanaio virtuale</h2>
     <p>Il salvadanaio virtuale permette agli utenti di mantenere  le proprie vincite sotto forma di moneta virtuale e di sapere in 
     ogni momento quante monete hanno a disposizione per poter giocare. 
     Per giocare una partita, l'utente ha bisogno di una cartellina che ha un costo di 5 monete a partita.
      Tale costo va a formare il montepremi  che viene diviso tra cinquina e bingo,
      ovviamente il montepremi del bingo sar&agrave; pi&ugrave; alto.<br>
     L'utente riceve ogni giorno una ricompensa di 5 monete per poter continuare a giocare, 
     <em>sappiamo che non tutti possono essere fortunati!</em>
     <strong>Ricordatevi di non spendere tutti i soldi che avete a disposizione nel salvadanio 
     in un giorno e giocare con moderazione!</strong>.<br></p>
      </li>
   </ul>
 </div>
</article>
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
 <script src="js/utentiOnlineAjax.js" ></script>
 <script src="js/aggiornamentoAccessoAjax.js" ></script>
 <script src="js/premioGiornalieroAjax.js"  ></script> 
 <script src="js/GestioneGiocoAjajx.js" ></script> 
 <script src="js/GestioneGiocoAdminAjax.js" ></script> 
 <script src="js/getMontepremi.js"></script> 
  </div>
</body>
</html>