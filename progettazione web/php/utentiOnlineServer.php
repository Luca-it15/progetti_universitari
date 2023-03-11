<?php
 //server per la gestione degli utenti online 
 //ritorna in json il nome utenti di chi sta giocando
  session_start();  
  require("serverClass.php"); 
  $nome = $_SESSION['username_login']; 
  $lista = new ServerClass($nome);  
  $utenti = array(); 
  $utenti = $lista->utentiOnline();  

  print json_encode($utenti); 
?> 
