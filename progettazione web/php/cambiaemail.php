<?php 
   session_start(); 
   
   include('confDB.php'); 
   //sono nel caso in cui l'utente voglia cambiare email  
   //controllo che tutti i paramentri siano stati inseriti 
   if(isset($_POST['vecchiaemail'], $_POST['nuovaemail'])) { 
   if ($stmt = $mysqli->prepare('SELECT Email 
    FROM `bingo`.`utenti` 
    WHERE  NomeUtente = ?')) {
    //inizializzo i parametri da passare alla query
    $stmt->bind_param('s', $_SESSION['username_login']);
    $stmt->execute();
    //non controllo che l'utente sia nel database in quanto avviene gia al login e nelle pagine 
    $stmt->store_result();
    $stmt->bind_result($email);
    $stmt->fetch(); 
    if($email == $_POST['vecchiaemail']) {
      $stmt->close();  
      if($stmt = $mysqli->prepare("UPDATE `bingo`.`utenti` 
        SET Email = ? 
        WHERE NomeUtente = ? ")) { 
        $stmt->bind_param('ss',$_POST["nuovaemail"], $_SESSION['username_login']);
        $stmt->execute(); 
        $stmt->close(); 
        echo '<script>';
        echo 'alert("Email cambiata con successo!");';
        echo 'location.href="../Impostazioni.php"';
        echo '</script>';
        } else { 
            echo '<script>';
            echo 'alert("Errore! Email non cambiata, si prega di riprovare 
             o di contattare il servizio clienti");';
            echo 'location.href="../Impostazioni.php"';
            echo '</script>';
         } 
        } else { 
            echo '<script>';
            echo 'alert("Email attuale non corretta, si prega di riprovare ");';
            echo 'location.href="../Impostazioni.php"';
            echo '</script>';
         }    
        } else { 
          echo '<script>';
          echo 'alert("Errore! Email non cambiata, si prega di riprovare 
          o di contattare il servizio clienti");';
          echo 'location.href="../Impostazioni.php"';
          echo '</script>';
        }    
       } else { 
        echo '<script>';
        echo 'alert("Si prega di riempire entrambi i campi");';
        echo 'location.href="../Impostazioni.php"';
        echo '</script>';
       } 
  ?> 