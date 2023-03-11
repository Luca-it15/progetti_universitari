<?php 
//server che mi restituisce i numeri della cartellina dell'utente chiamante
//serve per mantenere la persistenza della cartellina  
 session_start();  
  require("serverClass.php"); 
  $nome = $_SESSION['username_login']; 
  $cartellina = new ServerClass($nome); 
  $numeri = array(); 
  $numeri = $cartellina->getCartellina(); 

  print json_encode($numeri); 

?> 