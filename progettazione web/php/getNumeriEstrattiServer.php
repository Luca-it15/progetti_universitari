<?php 
 session_start(); 
//chiamata al server per recuperare i numeri estratti nella partita in corso 
require("serverClass.php"); 
$nome = $_SESSION['username_login'];
$num = array();
$num[0] = TRUE; 
$partita = new serverClass($nome); 
$infoPartita = array(); 
$infoPartita = $partita->getPartita();
//se le informazioni sono state prese eseguo il resto dell'operazioni
//senno ritorno $num[0] = false; 
if($infoPartita[0]) {
  $id = $infoPartita[1]; 
   if($id) { //estraggo solo se ci sono partite in corso
   $orario = $infoPartita[2];
   $num = $partita->getNumeriEstratti($id, $orario); 
  } 
 } else 
  $num[0] = FALSE;  
  
  print json_encode($num); 
  
?>