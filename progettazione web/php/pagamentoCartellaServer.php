<?php 
//server per aggiornare il saldo dopo il pagamento della cartellina  
 session_start();  
  require("serverClass.php"); 
  $nome = $_SESSION['username_login']; 
  $Pagamento = new ServerClass($nome); 
  $credito = array(); 
  $credito = $Pagamento->utenteSaldo(); 
  $esito = array(); 
  $esito = $Pagamento->pagamentoCartellina($credito[0]); 

  print json_encode($esito); 

?> 
