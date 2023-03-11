<?php
 //server per la gestione del premioGiornaliero
 //ritorna in json se l'utente chiamante ha avuto diritto al premio giornaliero 
  session_start();  
  require("serverClass.php"); 
  $nome = $_SESSION['username_login']; 
  $premio = new ServerClass($nome);  
  $esiti = array(); 
  $esiti = $premio->PremioGiornaliero(); 

  print json_encode($esiti); 
?> 