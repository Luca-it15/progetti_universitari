<?php 
 session_start(); 
 //chiamata al server per verificare le vincite nella partita 
 require("serverClass.php"); 
 $nome = $_SESSION['username_login'];
 $vin = array(); 
 $vin[0] = TRUE; 
 $partita = new serverClass($nome); 
 $infoPartita = array(); 
 $infoPartita = $partita->getPartita();
 if($infoPartita[0]) { 
     $id = $infoPartita[1]; 
    if($id) { //estraggo solo se ci sono partite in corso
    $orario = $infoPartita[2]; 
    $vin = $partita->getVincitore($id, $orario); 
  }
} 
else 
 $vin[0] = FALSE; 

print json_encode($vin); 
?>