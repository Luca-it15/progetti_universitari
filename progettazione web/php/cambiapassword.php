<?php 
    session_start(); 
    include("confDB.php"); 
   //controllo che i parametri siano tutti inseriti 
  if(isset($_POST['vecchiapassword'],$_POST['nuovapassword'], 
    $_POST['confermapassword'])) {
    //inizializzo i parametri da passare alla query
    //confronto la password dell'utente con quella inserita nella form 
    if ($stmt = $mysqli->prepare('SELECT Password 
                              FROM `bingo`.`utenti` 
                              WHERE  NomeUtente = ?')) {
	//inizializzo i parametri da passare alla query
	$stmt->bind_param('s', $_SESSION['username_login']);
	$stmt->execute();
	//conservo il risultato per fare un controllo sull'account
	$stmt->store_result(); //non faccio nessun controllo se l'utente è presente nel database perche
    //avviene gia al login e se chi accede prova ad andare sulla pagina impostazioni e non è loggato 
    //viene mandato alla pagina del login 
		$stmt->bind_result($password);
		$stmt->fetch(); 
        $stmt->close(); 
		if (password_verify($_POST['vecchiapassword'], $password))  {
         if($stmt = $mysqli->prepare("UPDATE `bingo`.`utenti` 
            SET Password = ? 
            WHERE NomeUtente = ? ")) { 
            $hashpassword = password_hash($_POST['nuovapassword'], PASSWORD_BCRYPT); 
            $stmt->bind_param('ss',$hashpassword, $_SESSION['username_login']);
            $stmt->execute(); 
            $stmt->close(); 
            echo '<script>';
            echo 'alert("Password cambiata con successo!");';
            echo 'location.href="../Impostazioni.php"';
            echo '</script>';
             } else { 
                echo '<script>';
                echo 'alert("Errore!Password non cambiata, si prega di riprovare 
                o di contattare il servizio clienti");';
                echo 'location.href="../Impostazioni.php"';
                echo '</script>';
             } 
            } else { 
              echo '<script>';
              echo 'alert("Password attuale non corretta, si prega di riprovare ");';
              echo 'location.href="../Impostazioni.php"';
              echo '</script>';
            }     
           } else { 
             echo '<script>';
             echo 'alert("Errore!Password non cambiata, si prega di riprovare 
             o di contattare il servizio clienti");';
             echo 'location.href="../Impostazioni.php"';
             echo '</script>';  
           }          
          } else { 
            echo '<script>';
            echo 'alert("Si prega di riempire tutti i campi");';
            echo 'location.href="../Impostazioni.php"';
            echo '</script>';
          } 
    ?>