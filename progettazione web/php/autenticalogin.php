<?php
 session_start(); 
 
include("confDb.php");
//ulteriore controllo sulle condizioni, il required negli input dovrebbe evitare una tale possibilita
//ma nel caso succedesse trattiamo questo caso 
if ( !isset($_POST['username_login'], $_POST['Password_login']) ) {
header( "Location: ../index.html"); 
exit;
}
 //preparo la query sql in modo da evitare le SQL injection.
if ($stmt = $mysqli->prepare('SELECT NomeUtente, Password, Email
                              FROM `bingo`.`utenti` 
                              WHERE  NomeUtente = ?')) {
	//inizializzo i parametri da passare alla query
	$stmt->bind_param('s', $_POST['username_login']);
	$stmt->execute();
	//conservo il risultato per fare un controllo sull'account
	$stmt->store_result();
	if ($stmt->num_rows > 0) {
		$stmt->bind_result($utente , $password, $email);
		$stmt->fetch(); 

		if (password_verify($_POST['Password_login'], $password))  {
			session_regenerate_id();
			$_SESSION['loggedin'] = TRUE;
			$_SESSION['saluto'] = TRUE; 
			$_SESSION['username_login'] = $_POST['username_login']; 
			//ogni sessione avviata instanzia un record nella tabella sessionlog inserendo il nome utente e l'orario di inizio, 
			//quindi ogni volta che un utente 
			//entra ci sarà un record che tiene traccia dell'accesso 
            $stmt = $mysqli->prepare("INSERT INTO `bingo`.` sessionlog`(NomeUtente,orarioinizio) 
			values(?, ?);");
            $date = date('Y/m/d H:i:s'); //prendo il timestamp dell'orario corrente
			$stmt->bind_param('ss', $_POST['username_login'], $date);
            $stmt->execute(); //inserisco l'orario di login nel db 
			$stmt->close();

			if($stmt = $mysqli->prepare("UPDATE  `bingo`.`utenti`
			SET  UltimoAccesso =  ?
			WHERE NomeUtente =  ?; " )){ 
			$stmt->bind_param('ss', $date, $_POST['username_login']);
			$stmt->execute(); 
			$stmt->close(); 
			} else { 
			 echo '<script>';
			 echo 'alert("ingresso non registrato, si prega di 
			 contattare il servizio clienti");';
			 echo '</script>';
			}
            //inizializzo premio a true in modo da tenere conto che questo è il primo
			//accesso dell'utente 
			if ($stmt = $mysqli->prepare('SELECT  Count(*)
           FROM `bingo`.` sessionlog`
          where  NomeUtente = ?  
          and ( year(current_timestamp) =  year(orarioinizio) 
          and   month(current_timestamp) =  month(orarioinizio) 
          and    day(current_timestamp) =  day(orarioinizio) ) ')) {
          $stmt->bind_param('s', $_POST['username_login']);
          $stmt->execute();
          $stmt->bind_result($numero);
          $stmt->fetch(); 
          $volte[0] = $numero; 
          $stmt->close(); 
          if($volte[0] == 1) { //è la prima volta che l'utente entra  
          if ($stmt = $mysqli->prepare('UPDATE  `bingo`.`salvadanaio`
          SET PremioGiornaliero = 1
          WHERE NomeUtente = ?' )) {
          $stmt->bind_param('s',$_POST['username_login']);
          $stmt->execute();
          $stmt->close();  
          } else { 
				echo '<script>';
				echo 'alert("Errore: premio giornaliero non accessibile, 
				contattare il servizio clienti");';
				echo '</script>';
			   }
            //ulteriore condizione di errore relativa al mancato 
           //aggiornamento del salvadanaio 
          }
        } else { 
			echo '<script>';
			echo 'alert("Errore: premio giornaliero non accessibile, 
			contattare il servizio clienti");';
			echo '</script>';
		   }
		
		  header('Location: ../home.php');
		  exit;
		} else {
			$mysqli->close();
			echo '<script>';
            echo 'alert("Password non corretta, si prega di riprovare ");';
            echo 'location.href="../index.html"';
            echo '</script>';
		}
	} else {
		$mysqli->close();
		echo '<script>';
            echo 'alert("Il Nome utente inserito non esiste, si prega di riprovare");';
            echo 'location.href="../index.html"';
            echo '</script>';
	}
	$mysqli->close();
 }
?>

