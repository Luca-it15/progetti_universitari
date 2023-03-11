<?php 
//server per aggiornare continuamente l'ultimo accesso degli utenti online 
 session_start();  
  require("serverClass.php"); 
  $nome = $_SESSION['username_login']; 
  $lista = new ServerClass($nome); 
  $aggiornamento = array(); 
  $aggiornamento = $lista->aggiornaUltimoAccesso(); 

  print json_encode($aggiornamento); 

?> 
