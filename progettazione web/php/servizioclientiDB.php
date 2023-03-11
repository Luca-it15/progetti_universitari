<?php
 session_start(); 
 
include("confDb.php"); 
if ( !isset( $_POST['email'], $_POST['problem']) ) {
header( "Location: ../ServizioClienti.php"); 
exit;
}
 //preparo la query sql in modo da evitare le SQL injection.
if ($stmt = $mysqli->prepare('SELECT NomeUtente, Email 
                              FROM `bingo`.`utenti` 
                              WHERE  NomeUtente = ?')) {
	//inizializzo i parametri da passare alla query
    $nome = $_SESSION['username_login']; 
	$stmt->bind_param('s', $nome);
	$stmt->execute();
	//conservo il risultato per fare un controllo sull'account
	$stmt->store_result();
	if ($stmt->num_rows > 0) {
		$stmt->bind_result($utente , $email);
		$stmt->fetch(); 

		if ($_POST['email'] == $email)  {
            $stmt = $mysqli->prepare("INSERT INTO `bingo`.`servizioclienti`(Data,NomeUtente, Email, 
            Richiesta, Messaggio)
			values( CURRENT_TIMESTAMP, ? , ?, ?, ?);");
            $stmt->bind_param('ssss', $nome ,$_POST['email'], $_POST['problem'],
             $_POST['msg']) ;
            $stmt->execute(); 
            $stmt->close();
            $mysqli->close();
            echo '<script>';
            echo 'alert("Richiesta inviata con successo!");';
            echo 'location.href="../ServizioClienti.php"';
            echo '</script>';
		} else {
			$mysqli->close();
			echo '<script>';
            echo 'alert("email non collegata al nome utente ");';
            echo 'location.href="../ServizioClienti.php"';
            echo '</script>';
		}
	} else {
		$mysqli->close();
		echo '<script>';
            echo 'alert("Il Nome utente inserito non esiste, si prega di riprovare");';
            echo 'location.href="../ServizioClienti.php"';
            echo '</script>';
	}
    $mysqli->close();	
 }
?>

