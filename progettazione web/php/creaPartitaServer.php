<?php 
//server per la creazione di partite 
  session_start(); 
  require("adminServerClass.php"); 
  $nome = $_SESSION['username_login']; 
  $partita = new adminServerClass(); 
  $esito = array();
  if($nome == "Admin") {
   if(isset($_POST['intervallo'])) {  
  $esito = $partita->creaPartita($_POST["intervallo"]);   
 //ritorno l'esito della creazione della partita 
 //true se la creazione è andata a buon fine altrimenti false
   } else 
   $esito = false; 
  }  
  else 
  $esito = 2; //numero arbitrario che mi dice che chi ha fatto la chiamata non è l'admin  
  print json_encode($esito); 

?> 