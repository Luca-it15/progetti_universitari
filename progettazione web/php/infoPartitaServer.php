<?php
  //chiamata al server per ottenere le informazioni della partita in corso 
  session_start();  
  require("serverClass.php"); 
  $nome = $_SESSION['username_login'];
  $partita = new serverClass($nome); 
  $infoPartita = array(); 
  $infoPartita = $partita->getPartita(); 
  print json_encode($infoPartita); 

  ?>