<?php
 session_start(); 
  //chiamata al server per terminare le partite rimaste in sospeso  
  require("adminServerClass.php"); 
  $nome = $_SESSION['username_login']; 
  //l'indice 0 di es conterrà True se il chiamante è l'admin, false altrimenti
  $es = array(); 
  if($nome == "Admin") { 
      $es[0] = TRUE; //il chiamante è l'admin
   $partita = new adminServerClass;  
   $es[1] = $partita->terminaPartiteInSospeso(); 
  } else 
   $es[0] = FALSE; 
 print json_encode($es); 

 ?>