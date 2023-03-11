<?php 
//server che mi restituisce il nome utente e il saldo 
 session_start();  
  require("serverClass.php"); 
  $nome = $_SESSION['username_login']; 
  $saldo = new ServerClass($nome); 
  $infoutente = array(); 
  $infoutente[0] = $nome; 
  $infoutente[1] = $saldo->utenteSaldo();  
 //ritorno in json il nome utente e il saldo, 
 //infoutente[0] contiene il nome utente 
 //infoutente[1] contiene il saldo dell'utente
  print json_encode($infoutente); 

?> 
