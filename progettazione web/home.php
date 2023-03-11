<!DOCTYPE html>
<?php 
   session_start();  
  ?>
<html lang="it">
 <head>
  <meta charset="UTF-8">
  <meta name="author" content="istruzioni">
   <meta name="Bingo!"  content="gioco">
  <link rel="stylesheet" href="./stili/Bingo.css" media="screen">
  <link rel="shortcut icon" href="./immagini/B.jpeg" class="head_logo">
  <title>HOME - Bingo!</title>
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script> 
 </head>
 <body>
  <?php
     if($_SESSION['loggedin'] == TRUE){
      if($_SESSION['saluto']) { 
      $_SESSION['saluto'] = FALSE; 
     echo '<script>';
     echo 'alert("Benvenuto in Bingo! '.$_SESSION['username_login'].'");';
     echo '</script>'; 
     } 
    } else {
     header("Location: index.html"); 
     echo 'Utente non loggato'; 
    }
    //serve per recuperare il nome all'interno dei file JS 
    echo '<input type="text" id="nomeutente" value="'.$_SESSION['username_login'].'">'; 
   ?>
   <div class="container">
  <header>
   <!--menu a tendina --> 
    <nav id="hormenu">
      <ul>
        <li>
         <a href="#"><img src="./immagini/logo_menu.png" alt="logo del menu" 
          title="Apri menu" width="50" height="50"></a>
       <ul> 
      <li><a href="#">HOME</a></li>
      <li><a href="Chiedimi_di_bingo.php">CHIEDIMI DI BINGO!</a></li>
      <li><a href="ServizioClienti.php">SERVIZIO CLIENTI</a></li>
      <li><a href="Impostazioni.php">IMPOSTAZIONI</a></li> 
      <li><a href="php/attesalogout.php">LOGOUT</a></li>
      </ul> 
      </li> 
      </ul>
      </nav>
     <img src="./immagini/BingoLogo.png" class="logo" alt = "logo">
     </header> 
     <div id="zona_Gioco">
     <div id="zona_Gioco_info">
      <div id="orariopartita"></div> 
      <div id="info"></div> 
      <div id="tabellone"> 
       <h1>TABELLONE NUMERI </h1>   
       <div id="numeriestratti"></div>
       <div id="ultimoestratto"></div> 
      </div> 
      <div id="infoutente">
      <div id="montepremi"></div>
      <div id="vincitori"></div> 
      <aside id="tabellamici"></aside>
      </div>
      </div>  
      <div id="Zona_Gioco_Cartella"></div>
      <div id="acquisto"></div>
       <div id="Cartellina"></div> 
       <div id="Zona_Gioco_bottoni"></div> 
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
      <a href="https://www.facebook.com/" target="_blank"><img src="immagini/Facebook.png" alt="Facebook"></a>
      <a href="https://www.instagram.com/" target="_blank" ><img src="immagini/instagram.jpg" alt="instagram"></a>
    </aside>
 </article>
 </footer>
 <script src="js/utentiOnlineAjax.js" ></script>
 <script src="js/aggiornamentoAccessoAjax.js" ></script>
 <script src="js/premioGiornalieroAjax.js"  ></script> 
 <script src="js/GestioneGiocoAjajx.js" ></script> 
 <script src="js/GestioneGiocoAdminAjax.js"></script> 
 <script src="js/GestoreCartellina.js" ></script> 
 <script src="js/getMontepremi.js"></script> 
  </div>
</body>
</html>