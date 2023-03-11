<?php 
session_start(); 
 //chiamata al server per terminare la partita in corso 
 require("serverClass.php"); 
 $nome = $_SESSION['username_login'];
 $partita = new serverClass($nome);  
 $term = true; 
 $infoPartita = array(); 
 $vincitori = array(); 
 $infoPartita = $partita->getPartita(); 
 if($infoPartita[0]) { 
     $id = $infoPartita[1]; 
    if($id) { //estraggo solo se ci sono partite in corso
    $orario = $infoPartita[2]; 
    $vincitori = $partita->getVincitore($id, $orario); 
    //ulteriore controllo nel caso la chiamata a termina venisse forzata 
    if($vincitori[0]) { 
     if($vincitori[1] && $vincitori[2]) {
    $term = $partita->termina($id, $orario);
     }  
   } 
 } 
else 
 $term = false; 
 } else 
  $term = false; 

print json_encode($term); 
?>