<?php 
//classe in php che contiene i metodi che vengono chiamati solo dall'admin 
 class adminServerClass { 
    public function creaPartita($intervallo) { 
        require("confDB.php");
        $esito = array(); 
         //creo una partita che avverrà tra intervallo minuti 
         $orario = date("Y/m/d H:i:s", + strtotime("+ ".$intervallo." minutes"));  
         if ($stmt = $mysqli->prepare('INSERT INTO `bingo`.`partita`(OrarioPartita)
           VALUES(?) 
           ')) {
              $stmt->bind_param('s', $orario);
              $stmt->execute();
              $stmt->close(); 
              $mysqli->close(); 
              $esito[0] = true; 
        } else 
         $esito[0] = false; 
         return $esito; 
       }
      public function insericiNumeriDaEstrarre($ID, $orario) {
       //creo un array contenente tutti i numeri che possono essere estratti. 
       //Dopo averne mescolato gli elementi li inserisco nel database con un Idnumero crescente
       // in modo tale da sapere il primo numero messo 
        require("confDB.php"); 
        $esito = false; 
        $numeri = array();
        $dim = 90; 
        //creo un array con i numeri da 1 a 90 
        for($i = 1; $i <= $dim; $i++ )
        $numeri[$i - 1] = $i; 
        //mescolo gli elementi dell'array in modo da averli casuali 
        shuffle($numeri);  
        $j = 0; 
        while($j < 90) {
        if($stmt = $mysqli->prepare('INSERT INTO `bingo`.`estratti`
                                   (Idpartita, OrarioPartita,NumeroEstratto, Estratto)  
                                     VALUES(?, ?, ?, 0);')) {
         $numero = $numeri[$j]; 
         $stmt->bind_param('isi',$ID,$orario, $numero);
         $stmt->execute(); 
         $stmt->close();
         $j++;   
         $esito = true; 
        } else {
          $esito = false;
          break; 
        } 
       }                      
         return $esito; 
      }
      public function estraiNumero($ID, $orario) { 
        //funzione che dato un Idpartita estrae un numero ogni INT_ESTRATTI secondi
        //ogni numero estratto viene contrassegnato dal fatto che ha il
        // campo estratto a 1 
        //la funzione ritorna un array contente tutti i numeri estratti  
        require("confDB.php"); 
        //esito conterrà i risultati della query, se la query è andata a buon fine
        //allora conterrà true, false altrimenti 
        $esito = array(); 
        //recupero le informazioni del primo numero 
        if($stmt = $mysqli->prepare("SELECT Idnumero, NumeroEstratto 
                                     FROM `bingo`.`estratti`
                                     WHERE Idpartita = ? 
                                      AND OrarioPartita = ?  
                                      AND Estratto = 0
                                     ORDER BY  Idnumero 
                                     LIMIT 1")) { 
         $stmt->bind_param('is',$ID,$orario);
         $stmt->execute(); 
         $stmt->store_result();   
         $stmt->bind_result($idnumero, $numero);
         $stmt->fetch(); 
         $stmt->close();    
        
         //segnalo che il numero è stato estratto 
         if($stmt = $mysqli->prepare("UPDATE `bingo`.`estratti`
                                      SET Estratto = 1
                                      WHERE Idpartita = ? 
                                       AND  OrarioPartita = ? 
                                       AND Idnumero = ? 
                                       AND NumeroEstratto = ? ")) {
           $esito[0] = TRUE; 
           $stmt->bind_param('isii',$ID,$orario, $idnumero, $numero);
           $stmt->execute(); 
           $stmt->close(); 
           //recupero tutti i numeri estratti fin ora,
           //i numeri estratti avranno Estratto = 1
           
          } else 
           $esito[0] = FALSE; 
      } else 
        $esito[0] = FALSE; 
        return $esito; 
    }
    public function terminaPartiteInSospeso() { 
      require("confDB.php");
      //funzione che termina le partite rimaste in sospeso 
      //settandone il campo Finita 
      $esito = array(); 
      $esito = TRUE; 
      if($stmt = $mysqli->prepare("UPDATE `bingo`.`partita`
      SET Finita = 1 
      WHERE  (YEAR(OrarioPartita) = YEAR(CURRENT_TIMESTAMP)
      AND MONTH(OrarioPartita) = MONTH(CURRENT_TIMESTAMP) 
       AND DAY(OrarioPartita) = DAY(CURRENT_TIMESTAMP)) 
       AND  HOUR(OrarioPartita) < HOUR(CURRENT_TIMESTAMP) 
       OR ( HOUR(OrarioPartita) = HOUR(CURRENT_TIMESTAMP) 
       AND  ( MINUTE(OrarioPartita) - MINUTE(CURRENT_TIMESTAMP)) < 10) ")) {

      $stmt->execute(); 
      $stmt->close(); 
      $mysqli->close();                            
     } else 
      $esito = FALSE; 
      return $esito; 
    }
 }



 ?>