<?php
//recupero la sessione e salvo nel database 
session_start();
 include("confDb.php");
 //inserisco nel database l'orario di fine sessione 
 //ogni sessione avviata instanzia un record nella tabella sessionlog 
 //inserendo il nome utente e l'orario di inizio. la chiave della tabella è un id auto increment
 $stmt = $mysqli->prepare("UPDATE `bingo`.` sessionlog` SET orariofine = ?
  WHERE nomeutente = ? AND orariofine IS NULL ");
 $date = date('Y/m/d H:i:s'); //prendo il timestamp dell'orario corrente
 $stmt->bind_param('ss',  $date , $_SESSION['username_login']);
 $stmt->execute(); //inserisco l'orario di login nel db 
 $stmt->close();
 $mysqli->close();
 
//cancello la sessione corrente 
unset($_SESSION['loggedin'],
$_SESSION['saluto'],
$_SESSION['username_login'],
$_SESSION['password']);
session_destroy();
header("location: ../index.html"); 
?>
</body> 
</html> 