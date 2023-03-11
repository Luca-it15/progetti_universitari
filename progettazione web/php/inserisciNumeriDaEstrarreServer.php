<?php 
 session_start(); 
 //chiamata al server per inserire nel DB i numeri da estrarre 
 require("adminServerClass.php"); 
 require("serverClass.php"); 
 $nome = $_SESSION['username_login'];
 $ris = array(); 
 if($nome == "Admin") { 
 $ris[0] = TRUE; 
 $partita = new serverClass($nome); 
 $infoPartita = array(); 
 $infoPartita = $partita->getPartita();
 //se le informazioni sono state prese eseguo il resto dell'operazioni
 //senno ritorno $ris[0] = false; 
 if($infoPartita[0]) {
  $id = $infoPartita[1]; 
  $ris[1] = TRUE; 
  $ris[2] = TRUE; 
    if($id) { //estraggo solo se ci sono partite in corso
    $orario = $infoPartita[2];
    $es = new adminServerClass(); 
    $ris[2] = $es->insericiNumeriDaEstrarre($id, $orario); 
   } 
  } else 
   $ris[1] = FALSE; 
} else 
 $ris[0] = FALSE; 
 //l'indice 0 di $ris mi dice se c'e stata una situazione di errore(chiamante diverso dall'admin )
 //mentre l'indice n 1 contiene il risultato dell'esecuzione di getPartita
 // che se è true, la funzione è stata eseguita correttamente, false altrimenti
 //se getPartita è stata eseguita correttamente allora dall'indice 2 avrò il risultato 
 //della funzione inserisciNumeriDaEstrarre 
 //che se è true allora l'esecuzione ha avuto 
 //successo, false altrimenti. 
 print json_encode($ris); 

 ?>