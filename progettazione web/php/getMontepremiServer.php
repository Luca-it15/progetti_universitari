<?php
  //chiamata al server per ottenere le informazioni del montepremi
  session_start();  
  require("serverClass.php"); 
  $nome = $_SESSION['username_login'];
  $premi = new serverClass($nome); 
  $montepremi = array(); 
  $montepremi = $premi->getMontepremi(); 
  print json_encode($montepremi); 

  ?>