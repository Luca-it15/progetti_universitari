<?php
 session_start();
//la maggior parte dei controlli sono stati fatti lato utente
//ci limitiamo a controllare che il nome utente inserito non sia gia prsente nel database 
 include("confDb.php");

 if ( !isset($_POST['username_registrazione'], $_POST['birthDate'], $_POST['email'],
  $_POST['password']) ) {
    header( "Location: ../Registrazione.html"); 
    exit;
    }
  $utente = $_POST['username_registrazione'];
  $nome = $_POST['name']; 
  $cognome = $_POST['surname']; 
  $datanascita = $_POST['birthDate']; 
  $email = $_POST['email']; 
  $password = $_POST['password']; 


  if ($stmt = $mysqli->prepare('SELECT NomeUtente, Password FROM Utenti WHERE  NomeUtente = ?')) {
	//inizializzo i parametri da passare alla query
	$stmt->bind_param('s', $utente);
	$stmt->execute();
	//conservo il risultato per fare un controllo sull'account
	$stmt->store_result();
    if ($stmt->num_rows > 0) {
        $stmt->close();
        $mysqli->close();
        echo '<script>';
        echo 'alert("Nome utente gia presente, inserirne uno diverso ");';
        echo 'location.href="../Registrazione.html"';
        echo '</script>'; 
        exit;
    }
    else {
    //rimango dentro l'if per essere sicuro che il controllo sia andato a buon fine
    $stmt->close();
    //codifico la password per renderla più sicura 
    $hashpassword = password_hash($password, PASSWORD_BCRYPT); 
    if($stmt = $mysqli->prepare("INSERT INTO `bingo`.`utenti`(NomeUtente, Nome, Cognome,
                                 DataNascita, Email, Password) VALUES (?, ?, ?, ?, ?, ?);"))
    {
     $stmt->bind_param('ssssss',$utente, $nome, $cognome, $datanascita, $email, $hashpassword); 
     $stmt->execute();
     $stmt->close();
     //Creo il savadanaio per l'utente registrato, 
     //avviene solo se la registrazione è andata a buon fine
     $stmt = $mysqli->prepare("INSERT INTO`bingo`.`salvadanaio` ( NomeUtente, 
                               Saldo) VALUES ( ?, ?);"); 

     $saldo = 10; //all'atto della registrazione un utente riceve 10 crediti per inizare a giocare
     $stmt->bind_param('sd', $utente, $saldo); 
     $stmt->execute();
     $stmt->close();
     $mysqli->close();
     echo '<script>';
     echo 'alert("Registrazione avvenuta con successo!");';
     echo 'location.href="../index.html"';
     echo '</script>';
    exit;
   }
   else {
    $stmt->close();
    $mysqli->close();
    echo '<script>';
    echo 'alert("Registrazione non avvenuta, si prega di riprovare");';
    echo 'location.href="../index.html"';
    echo '</script>';
   exit;

   }
  }
 } 
?> 







