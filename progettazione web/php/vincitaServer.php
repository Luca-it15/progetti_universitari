<?php 
 session_start(); 
 //chiamata al server per verificare la vincita della cinquina e del bingo 
 require("serverClass.php"); 
 $nome = $_SESSION['username_login'];
 $ris = array(); 
 $ris[0] = TRUE; 
 $partita = new serverClass($nome); 
 $infoPartita = array(); 
 $infoPartita = $partita->getPartita();
 //se le informazioni sono state prese eseguo il resto dell'operazioni
 //senno ritorno $ris[0] = false; 
 if($infoPartita[0] && isset($_POST['vincita']))  { 
   $id = $infoPartita[1]; 
    if($id) { //estraggo solo se ci sono partite in corso
    $orario = $infoPartita[2]; 
    $imp = $partita->getMontepremi(); 
   if($_POST['vincita'] == "BINGO" && $imp[0]) { 
    $ris = $partita->Vincita($id, $orario, 15 ,$_POST['vincita'], $imp[1]);
    $ris[4] = $imp[1]; //ritorno l'importo vinto
    } 
    else if($_POST['vincita'] == "CINQUINA" && $imp[0]) {
    $ris = $partita->Vincita($id, $orario, 5 , $_POST['vincita'] ,$imp[2]);
    $ris[4] = $imp[2];
    }  
   }
  } 
  else 
  $ris[0] = FALSE; 
 print json_encode($ris); 

?>