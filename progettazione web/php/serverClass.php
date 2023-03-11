<?php 
//classe in php contenente metodi utili per l'utente
class ServerClass {
  private  $nome = ""; //nome utente da passare ai metodi della classe  
  public function __construct($nome) { //costruttore della classe  
     $this->nome = $nome; 
   }  
   public function utentiOnline() { 
    require("confDB.php"); 
    //controllo che la differenza di tempo tra l'ultimo accesso non sia maggiore
    //di un minuto cosi sono sicuro di prendere tutti gli utenti online 
    if ($stmt = $mysqli->prepare('SELECT U.NomeUtente
    FROM `bingo`.`utenti` U
          INNER JOIN 
          `bingo`.`salvadanaio` S
          ON U.NomeUtente = S.NomeUtente 
    WHERE  
          minute(current_timestamp) - minute(UltimoAccesso) <= 1 
          AND  (year(current_timestamp) =  year(UltimoAccesso) 
          AND    month(current_timestamp) =  month(UltimoAccesso) 
          AND     day(current_timestamp) =  day(UltimoAccesso) 
          AND     hour(current_timestamp) =  hour(UltimoAccesso) )
          AND InGioco = 1;  ')) {
    //inizializzo i parametri da passare alla query
    $stmt->execute();
    $elencoAmici = array();
    //mi conservo il risultato per stampare gli utenti online 
    $stmt->store_result();
     if ($stmt->num_rows > 1) {
    $numUtenti = $stmt->num_rows; 
    $j = 0; 
    for($i = 0; $i < $numUtenti; $i++ ) {
    $stmt->bind_result($utente);
    $stmt->fetch();
    if($utente == $this->nome || $utente == "Admin") 
      continue; 
    else {
    $elencoAmici[$j] = $utente; 
     $j++; 
     } 
    } 
    if($j == 0)
    $elencoAmici[0] = "Nessun utente online";
   }
    else if($stmt->num_rows == 1) { 
     $stmt->bind_result($utente);
    $stmt->fetch();
    if($utente != $this->nome && $utente != "Admin" ) 
    $elencoAmici[0] = $utente; 
    else 
     $elencoAmici[0] = "Nessun utente online"; 
    }
   else {
    $elencoAmici[0] = "Nessun utente online"; 
   }
  } else { 
    $stmt->close();
    $mysqli->close();
    $mess = array(); 
    $mess[0] = "Errore nell'esecuzione del metodo"; 
    return $mess; 
   } 
   $stmt->close();
   $mysqli->close();
   return $elencoAmici;
  }
   public function aggiornaUltimoAccesso() { 
    require("confDB.php"); 
    $mess = array(); 
       if($stmt = $mysqli->prepare("UPDATE `bingo`.`utenti`
       SET UltimoAccesso = current_timestamp
       where NomeUtente = ?")) { 
       $stmt->bind_param('s', $this->nome);
        $stmt->execute(); 
        $stmt->close(); 
        $mysqli->close(); 
        $mess = array(); 
        $mess[0] = TRUE; 
       } else { 
        $mess[0] = FALSE; 
       }
       return $mess; 
   }
   public function PremioGiornaliero() { 
    require("confDB.php"); 
    $volte = array(); 
    //nell'indice 0 di volte avrò true se entrambe le query sono andate a buon fine altrimenti false. 
    //nel secondo indice avrò true se l'utente ha ricevuto il premio, false altrimenti 
    if ($stmt = $mysqli->prepare('SELECT PremioGiornaliero FROM `bingo`.`salvadanaio`
      WHERE NomeUtente = ?; 
    ')) {
       $volte[0] = true; 
       $stmt->bind_param('s', $this->nome);
       $stmt->execute();
       $stmt->bind_result($ritirato);
       $stmt->fetch(); 
       $volte[1] = $ritirato; 
       $stmt->close(); 
       if($volte[1] == 1) {
         $volte[1] = true;  //è la prima volta che l'utente entra  
        if ($stmt = $mysqli->prepare('UPDATE  `bingo`.`salvadanaio`
         SET Saldo = Saldo + 5.0, 
             PremioGiornaliero = 0
         WHERE NomeUtente = ?' )) {
          $volte[0] = true; 
         $stmt->bind_param('s', $this->nome);
         $stmt->execute();
         $stmt->close(); 
         } else 
           $volte[0] = false; //ulteriore condizione di errore relativa al mancato 
           //aggiornamento del salvadanaio 
       } else 
       $volte[1] = false; 
       } else 
     $volte[0] = false; //verrà trattato come un booleano, 
     //nel caso in cui la query non sia andata
     //a buon fine 
   $mysqli->close();
   return $volte; 
 }
 public function utenteSaldo() {
  require("confDB.php"); 
  //funzione che mi ritorna un array contente il saldo dell'utente chiamante 
  $info = array();
  if ($stmt = $mysqli->prepare('SELECT Saldo FROM `bingo`.`salvadanaio`
    WHERE NomeUtente = ?; 
  ')) {
     $stmt->bind_param('s', $this->nome);
     $stmt->execute();
     $stmt->bind_result($credito);
     $stmt->fetch(); 
     $info[0] = $credito; 
    
  } else 
   $info[0] = "false";
   $stmt->close(); 
   $mysqli->close();
   return $info;   
 }
 public function pagamentoCartellina($credito) { 
  require("confDB.php");
  $esito = array();  
 //funzione che mi ritorna se l'aggiornamento della cartellina è andata a buon fine
//controllo che non ci siano partite in corso 
//nel caso, non autorizzo all'acquisto di cartelline da parte dell'utente
//l'array esito conterrà tre valori che rappresenteranno lo stato della chiamata: 
//indice 0 = true, se tutte le chiamate al db sono state fatte correttamente, false altrimenti
// 1 = true, se l'utente ha il credito sufficiente, false altrimenti.  
//2 = true, se non ci sono partite in corso, false
  if($credito >= 5) {
    //query per controllare che non ci siano partite in corso 
    if($stmt = $mysqli->prepare('SELECT COUNT(*) 
                                 FROM `bingo`.`partita`
                                 WHERE Finita = 0  AND  
                                ((YEAR(OrarioPartita) = YEAR(CURRENT_TIMESTAMP)
                                 AND MONTH(OrarioPartita) = MONTH(CURRENT_TIMESTAMP) 
                                 AND DAY(OrarioPartita) = DAY(CURRENT_TIMESTAMP)) 
                                 AND  HOUR(OrarioPartita) < HOUR(CURRENT_TIMESTAMP) 
                                 OR (  HOUR(OrarioPartita) = HOUR(CURRENT_TIMESTAMP) 
                                 AND MINUTE(OrarioPartita) < MINUTE(CURRENT_TIMESTAMP))
                                 OR ( HOUR(OrarioPartita) = HOUR(CURRENT_TIMESTAMP) 
                                 AND MINUTE(OrarioPartita) =  MINUTE(CURRENT_TIMESTAMP) 
                                 AND SECOND(OrarioPartita) <= SECOND(CURRENT_TIMESTAMP)));                                
     ')) {   
     $stmt->execute();
     $stmt->bind_result($incorso);
     $stmt->fetch(); 
     $stmt->close(); 
     if($incorso == 0) { //non ci sono partite in corso             
      $esito[1] =  true;
      $esito[2] = true; 
      //query che aggiorna il saldo dell'utente dopo aver acquistato la cartellina 
      if ($stmt = $mysqli->prepare('UPDATE `bingo`.`salvadanaio`
      SET Saldo = Saldo - 5.0, InGioco = 1
      WHERE NomeUtente = ?; ')) {
       $stmt->bind_param('s', $this->nome);
       $stmt->execute();
       $stmt->close(); 
       if($stmt = $mysqli->prepare("SELECT MAX(Idcartellina) FROM `bingo`.`cartellina`
                                    WHERE NomeUtente = ?")) {  
        $stmt->bind_param('s', $this->nome);
        $stmt->execute();
        $stmt->bind_result($ID); 
        $stmt->fetch(); 
        $stmt->close(); 
       //while per l'inserimento 
       $i = 1;
       $dim = 15;  
       $ID++; //incremento il numero della cartellina dell'utente 
       //l'utente avrà sempre la cartellina con il numero di ID piu alto
       //utilizzo un while in modo da controllare che tutti gli inserimenti avvengano correttamente.
       //le condizioni da rispettare per la creazione della cartellina che sia conforme al gioco del 
       //bingo, quindi 3 righe con 5 numeri ciascuna e 9 colonne di cui ogni colonna contiene 
       //almeno un numero compreso nell'intervallo [1, 9] * numero colonna e un numero non si deve mai
       //ripetere all'interno della cartellina, rendono l'inserimento non generalizzabile in una 
       //sola query
         while($i < $dim) { 
         if($i == 1){ 
           $_uno = rand(1, 5); 
           $riga_uno = 1; 
           $riga_due = 3;
           ; $_due = rand(6, 9); 
           } 
           else if($i == 3) {
            $_uno = rand(10, 19);
            $riga_uno = 2;  
           }
           else if($i == 4) {
            $riga_uno = 1; 
            $riga_due = 3;
            $_uno = rand(20,24); $_due = rand(25, 29); 
           }
          else if($i == 6) { 
           $_uno = rand(30, 39);
           $riga_uno = 2;  
          } 
          else if($i == 7) { 
            $_uno = rand(40, 49);
            $riga_uno = 2;  
          }
          else if($i == 8) { 
            $riga_uno = 1; 
            $riga_due = 3;
            $_uno =  rand(50, 54); $_due = rand(55, 59);
          }
          else if($i == 10) {
            $riga_uno = 1; 
            $riga_due = 3;
            $_uno =  rand(60, 64); $_due = rand(65, 69);
          }
           else if($i == 12) { 
            $riga_uno = 2; 
            $riga_due = 3;
            $_uno =  rand(70, 74); $_due = rand(75, 79);
           }
           else if($i == 14) {
            $riga_uno = 1; 
            $riga_due = 2;
            $_uno =  rand(80, 84); $_due = rand(85, 90); 
           }
          //uscito dagli if avro in $uno ed eventualmente in $due i numeri da inserire
          //in i la posizione del numero all'interno della cartellina 
          //dividendo i casi in cui ho uno o due inserimenti
           if($i == 3 || $i == 6 || $i == 7 ) { 
            if($stmt = $mysqli->prepare('INSERT INTO  `bingo`.`cartellina` 
              VALUES(? , ?, ?,  ?, ?)
             ')) {
             $stmt->bind_param('isiii',$ID, $this->nome, $_uno, $i, $riga_uno); 
             $stmt->execute();
             $stmt->close(); 
             $i++; 
             $esito[0] = true;
             } else { //else per controllare che la query sia stata eseguita correttamente 
              $esito[0] = false;
              break;  
             }
            } else { 
            if($stmt = $mysqli->prepare('INSERT INTO  `bingo`.`cartellina` 
              VALUES(? , ?, ?,  ?, ? ), (? , ?, ?,  ?, ?)
             ')) {
               $i2 = $i + 1; 
             $stmt->bind_param('isiiiisiii',$ID, $this->nome, $_uno, $i, $riga_uno, $ID, $this->nome, $_due,$i2, $riga_due); 
             $stmt->execute();
             $stmt->close(); 
             $i += 2; 
             $esito[0] = true;
             } else { //else per controllare che la query sia stata eseguita correttamente 
              $esito[0] = false;
              break;  
             }
            }
           if($esito == false) break; //una query non è stata correttamente eseguita quindi esco
         }  

         } else {  //Errata esecuzione della query che restituisce l'Idcartellina massimo 
         $esito = [false, true, true]; 
          } 
         } else //Errata esecuzione della query che aggiorna il saldo
         $esito = [false, true, true]; 
        } else //ci sono partite in corso 
        $esito = [true, true, false];  
       } else //Errata esecuzione della query che restituisce se ci sono partite in corso 
       $esito = [false, true, true]; 
      } else //l'utente non ha il credito necessario per acquistare la cartellina
       $esito = [true, false, false]; 
      $mysqli->close(); 
     return $esito; 
   }
 public function getCartellina() { 
  require("confDB.php");
  $numeri = array(); 
    if ($stmt = $mysqli->prepare('SELECT InGioco FROM  `bingo`.`salvadanaio`
    WHERE NomeUtente = ?; 
  ')) {
     $stmt->bind_param('s', $this->nome);
     $stmt->execute();
     $stmt->bind_result($gioco);
     $stmt->fetch(); 
     $stmt->close();
    if($gioco) { //se l'utente è in gioco allora ritorno nell'array i numeri della cartellina
    //nel caso l'utente non fosse in gioco numeri, conterrà false 
     //mi salvo l'ID dell'ultima cartellina creata 
     
     if ($stmt = $mysqli->prepare('SELECT Numero
     FROM `bingo`.`cartellina` C1 INNER JOIN  (
     SELECT MAX(Idcartellina) AS CartellinaTarget
     FROM `bingo`.`cartellina` 
      WHERE NomeUtente = ? ) AS C2  
       ON  C1.Idcartellina = C2.CartellinaTarget 
     WHERE  NomeUtente = ?
     ORDER BY  Idcartellina, PosizioneNumero')) {
     $stmt->bind_param('ss', $this->nome, $this->nome);
     $stmt->execute();
     $i = 0; 
     while($i < 15) { 
     $stmt->bind_result($numero); 
     $stmt->fetch(); 
     $numeri[$i] = $numero; 
     $i++; 
     } 
     $stmt->close(); 
    } else 
    $numeri = [false, true]; //l'indice 0 di numeri uguale a false indica che c'e stato un errore nel
    //eseguire le query mentre l'indice 1 false indica che l'utente non è in gioco 
    } else //l'utente sta giocando 
     $numeri = [true, false]; 
  } else //Errore nella quary che mi restituisce il valore di Ingioco 
    $numeri[0] = [false, false]; 
    $mysqli->close();   
  return $numeri; 
 }
 public function getPartita() {
   //funzione che mi permette di recuperare le informazioni della partita che sta per iniziare
   //l'indice 0 di info mi segnala se la query è andata a buon fine   
  require("confDB.php");
  $info = array(); 
  if($stmt = $mysqli->prepare('SELECT IdPartita, OrarioPartita 
                               FROM `bingo`.`partita`
                               WHERE Finita = 0 
                               AND (YEAR(CURRENT_TIMESTAMP) = YEAR(OrarioPartita)
                               AND MONTH(CURRENT_TIMESTAMP) = MONTH(OrarioPartita)
                               AND DAY(CURRENT_TIMESTAMP) <= DAY(OrarioPartita))
                               ORDER BY OrarioPartita 
                               Limit 1;' )) { 
  $info[0] = true; 
  $stmt->execute(); 
  $stmt->store_result();
  $dim = $stmt->num_rows;
  if($dim >= 1) { 
  $stmt->bind_result($ID, $orario);
  $stmt->fetch(); 
  $stmt->close(); 
  $mysqli->close(); 
  $info[1] = $ID; 
  $info[2] = $orario; 
   } 
   else  
    $info[1] = false; //non ci sono partite da giocare, la funzione non farà nulla 
  } else 
   $info = [false, false]; //mi segnala che la query non è andata a buon fine 
   //so che tanto $ID conterrà un numero maggiore di 0  
  return $info; 
 }
 public function getNumeriEstratti($id, $orario) {
   //recupero i numeri estratti, nell'indice 0 di $numeri avrò l'esito della query, 
   //se è stato eseguita correttamente avrò true, false altrimenti
   //nel resto degli indici avrò i numeri estratti
   //se il giocatore non è in gioco l'indice 1 conterrà false 
   //se non sono stati estratti ancora i numeri allora l'indice 2 conterrà false 
   require("confDB.php");
   $estratti = array(); 
   $estratti[0] = true; 
   if ($stmt = $mysqli->prepare('SELECT InGioco FROM  `bingo`.`salvadanaio`
   WHERE NomeUtente = ?; 
 ')) {
    $stmt->bind_param('s', $this->nome);
    $stmt->execute();
    $stmt->bind_result($gioco);
    $stmt->fetch(); 
    $stmt->close();
   if($gioco) { //restituisco i numeri solo se il giocatore è in gioco 
     $estratti[1] = true; 
     if($stmt = $mysqli->prepare("SELECT NumeroEstratto 
     FROM `bingo`.`estratti`
     WHERE Estratto = 1 
     AND Idpartita = ? 
     AND OrarioPartita = ? 
     ORDER BY Idnumero")) {
     $stmt->bind_param('is',$id , $orario);
     $stmt->execute();
     $stmt->store_result();
     $dim = $stmt->num_rows; 
     if($dim) { 
     $i = 1; 
     if($dim > 90) { 
     $dim = 90; 
     }
     while($i <= $dim) {    
     $stmt->bind_result($numero);
     $stmt->fetch(); 
     $estratti[$i + 1] = $numero;  
     $i++; 
     }
     } else 
     $estratti[2] = 0; 
    $stmt->close(); 
    } else 
    $estratti[0] = false; 
   } else 
   $estratti[1] = false; 
  } else 
  $estratti[0] = false; 
  
   $mysqli->close();
   return $estratti; 
 } 
 public function getMontepremi() {
  //funzione che restituisce il montepremi della partita 
  //il montepremi sarà cosi distribuito 
  //bingo: 75% del totale dell'incasso della partita( 5 crediti per schedina a giocatore)
  //cinquina: 15% del totale dell'incasso 
  //la funzione restituisce nell'indice 0 il risultato della corretta esecuzione delle
  //query e negli indici 2 e 3 i corrispettivi premi di bingo e cinquina 
  //chi sta giocando lo ricavo dal flag Ingioco, che viene opportunatamente aggiornato 
  require("confDB.php");
  $ris = array(); 
  if($stmt = $mysqli->prepare('SELECT COUNT(DISTINCT NomeUtente) 
                               FROM `bingo`.`salvadanaio`
                               WHERE InGioco = 1; ')) {
  $ris[0] = true; //la query è stata eseguita correttamente
  $stmt->execute(); 
  $stmt->store_result(); 
  $stmt->bind_result($numero); //in numero avrò il numero dei giocatori 
  $stmt->fetch(); 
  $stmt->close(); 
  $imp = ($numero * 5 * 0.75); 
  //arrotondo a due cifre decimali il numero ottenuto 
  $ris[1] = round($imp,2); 
  $imp = ($numero * 5 * 0.15); 
  $ris[2] = round($imp, 2); 
  } else 
   $ris[0] = false; 
   $mysqli->close();
   return $ris; 
  }
  public function Vincita($id, $orario, $NumMinino, $tipo, $importo) { 
    require("confDB.php");
    //dato un id e un orario controllo, se i numeri estratti sono più di 5 o 15
    //nell'indice 0 di esiti avrò true se le query sono state tutte eseguite correttamente, 
    //false altrimenti
    //nell'indice 1 avrò true se i numeri usciti sono piu di 5 o piu di 15, false altrimenti 
    //nell'indice 2 avrò true se nessuno ha fatto gia bingo o cinquina, false altimenti
     //nell'indice 3 avrò se l'utente ha fatto cinquina/bingo o meno quindi true o false 
    //rispettivamente 
    $esito = array(); 
    $esito[0] = true; //viene messo a false solo se una query fallisce 
    if($stmt = $mysqli->prepare("SELECT COUNT(*)
                                 FROM `bingo`.`estratti`
                                 WHERE Estratto = 1 
                                 AND Idpartita  = ? 
                                 AND OrarioPartita = ?")) { 
                                   
    $stmt->bind_param('is',$id , $orario);
    $stmt->execute();
    $stmt->store_result(); 
    $stmt->bind_result($numEstratti); 
    $stmt->fetch();
    $stmt->close();  
    if($numEstratti >= $NumMinino)  { 
      $esito[1] = true; 
      //5 sono i numeri estratti minimi per fare cinquina 
      //mentre 15 per il bingo 
      //controllo che nessuno abbia gia fatto cinquina o bingo nella partita in corso
      //mi basta contare le righe e se risulta essere uguale a 1 allora qualcuno ha gia 
      //fatto cinquina, dal momento che uno fa bingo la partita termina quindi il suo 
      //controllo non viene fatto
       if($stmt = $mysqli->prepare("SELECT COUNT(*)
                                    FROM `bingo`.`vincita`
                                    WHERE Idpartita = ? 
                                     AND OrarioPartita  = ? 
                                     AND TipoVincita = ?")) { 
       $stmt->bind_param('iss',$id , $orario, $tipo);
       $stmt->execute();
       $stmt->store_result(); 
       $stmt->bind_result($presente); 
       $stmt->fetch();
       $stmt->close(); 
        if($presente == 0)   { 
          $esito[2] = true; 
          //nessuno ha gia fatto cinquina o bingo, allora procedo con il controllo delle righe 
          //almeno una riga deve avere tutti i numeri estratti combacianti  per la cinquina
          //mentre tutte le righe devono avere tutti numeri estratti combacianti per il bingo
          //conterrà il valore true solo se sono stati trovati tutti i numeri 
          //per quella riga , ogni indice rappresenta una riga  
          $rigapresa = array();  
          $rigapresa = [FALSE, FALSE, FALSE]; 
          //devo eseguire tre query, una per ogni colonna della cartellina 
          //query riga i 
          $i = 1; 
          while($i <= 3) { 
            if($stmt = $mysqli->prepare(" SELECT COUNT(DISTINCT NumeroEstratto) 
                                          FROM 
                                       ( SELECT * 
                                         FROM `bingo`.`estratti`
                                        WHERE Idpartita = ?
                                       AND OrarioPartita = ?
                                       AND Estratto = 1 ) AS E 
                                      INNER JOIN (
                                      SELECT *
                                      FROM ( 
                                     SELECT * 
                                     FROM `bingo`.`cartellina`
                                     WHERE NomeUtente = ? 
                                     AND Riga = ? ) AS C1 
                                      INNER JOIN
                                  (SELECT MAX(Idcartellina) AS idtarget
                             FROM `bingo`.`cartellina`
                          where NomeUtente = ? )  AS C2
                           ON C1.Idcartellina = C2.idtarget  ) AS C3
                         ON E.NumeroEstratto = C3.Numero")) {
             $stmt->bind_param('issis', $id , $orario, $this->nome ,$i,  $this->nome );
             $stmt->execute();
             $stmt->store_result(); 
             $stmt->bind_result($presi); 
             $stmt->fetch();
             $stmt->close();  
             if($presi == 5) { 
               $rigapresa[$i - 1] = true; //ho fatto cinquina nella riga 1 
             } else 
              $rigapresa[$i - 1] = false; 
            } else 
            $esito[0] = false; 
           //query riga 2 
           $i++; 
         } 
         //uscito dal while avrò i risultati dei confronti in rigapresa 
         //se contiene tutti true allora l'utente ha fatto bingo, se contiene almeno un true 
         //l'utente ha fatto cinquina, se non contiene nemmeno un true l'utente non ha vinto 
         //nessun premio. 
          $vincita = false; //se assume valore true allora l'utente ha fatto bingo o cinquina
          if($tipo == "BINGO") {  
           if($rigapresa[0] && $rigapresa[1] && $rigapresa[2])
             $vincita = true; 
            } 
           else if($tipo == "CINQUINA") {  
            if($rigapresa[0] || $rigapresa[1] || $rigapresa[2]) 
               $vincita = true;  
           } 
            if($vincita) { 
             if($stmt = $mysqli->prepare("INSERT `bingo`.`vincita`(Idpartita, OrarioPartita, 
                                         NomeUtente, TipoVincita, Importo) 
                                        VALUES(? , ?, ?, ?, ?)")) { 
            $stmt->bind_param('isssd',$id , $orario, $this->nome, $tipo, $importo);
            $stmt->execute(); 
            $stmt->close(); 
            } else 
             $esito[0] = false; 
            //Recupero il saldo dell'utente 
            if($stmt = $mysqli->prepare("SELECT Saldo 
                                         FROM  `bingo`.`salvadanaio`
                                         WHERE NomeUtente = ?")) { 
             $stmt->bind_param('s', $this->nome);
             $stmt->execute();
             $stmt->store_result(); 
             $stmt->bind_result($saldo); 
             $stmt->fetch();
             $stmt->close();  
            } else 
            $esito[0] = false; 

             //aggiorno il saldo dell'utente con il premio                           
            if($stmt = $mysqli->prepare("UPDATE `bingo`.`salvadanaio`
                                         SET Saldo =  ?
                                         WHERE NomeUtente = ?")) { 
             $newsaldo = $saldo + $importo; 
             $stmt->bind_param('ds',  $newsaldo , $this->nome);
             $stmt->execute(); 
             $stmt->close(); 
             $esito[3] = true;
            } else //errore nell'eseguire una query
             $esito[0] = false;  
          } else //non sono usciti abbastanza numeri presi per ritirare il premio 
           $esito[3] = false;            
      } else //qualche utente ha gia fatto cinquina 
        $esito[2] = false; 
     } else //errore nell'eseguire una query 
      $esito[0] = false;          
    } else //i numeri estratti non sono sufficienti
     $esito[1] = false; 
  } else  //errore nell'eseguire una query 
   $esito[0] = false;
   $mysqli->close(); 
   return $esito; 
 }
 public function getVincitore($id, $orario) { 
   //funzione che mi ritorna i nomi di chi ha fatto cinquina e bingo 
   //nell'indice 0 dell'array ritornato avrò l'esito delle query 
   //nell'indice 1 avrò il Nome utente di chi ha fatto cinquina 
   //nell'indice 2 avrò il Nome Utente di chi ha fatto bingo 
   //se non è presente nessun vincitore avrò false nell'indice 1
   //mentre se nessuno ha fatto bingo avrò false nell'indice 2
  require("confDB.php");
  $esito = array(); 
  $esito[0] = true; 
  if($stmt = $mysqli->prepare("SELECT NomeUtente
                               FROM `bingo`.`vincita`
                               WHERE Idpartita = ? 
                                AND  OrarioPartita = ?
                                ORDER BY TipoVincita DESC")) { 
   $stmt->bind_param('is',$id , $orario);
   $stmt->execute();
   $stmt->store_result(); 
   //controllo se è presente almeno un vincitore 
   $dim = $stmt->num_rows; 
   if($dim > 0) { 
    $i = 1; 
    while($i <= $dim) {
     $stmt->bind_result($nomevincitore); 
     $stmt->fetch(); 
     $esito[$i] = $nomevincitore;
     $i++; 
    } 
   $stmt->close();                           
   } else 
    $esito[1] = false; 
 } else 
  $esito[0] = false; 
  $mysqli->close(); 
  return $esito; 
 } 
 public function termina($id, $orario) { 
   //metodo per terminare la partita 
   //restituirà un booleano contenente l'esito dell'esecuzione 
   //true se l'esito è positivo, false altrimenti  
   //per terminare un partita dobbiamo mettere a 1 il campo Finita della 
   //partita in corso nella tabella Partita 
   //e mettere a zero il campo InGioco di tutti gli utenti nella tabella 
   //salvadanaio 
   require("confDB.php");
   $ris = true; //viene cambiato solo se le query non vanno a buon fine 
   if($stmt = $mysqli->prepare("UPDATE `bingo`.`partita`
                                SET Finita  = 1 
                                WHERE Idpartita = ? 
                                AND  OrarioPartita = ?")) {
   $stmt->bind_param('is',$id , $orario);
   $stmt->execute();
   $stmt->close(); 
   } else  //erroe nell'esecuzione della query 
     $ris = false;
   if($stmt = $mysqli->prepare("UPDATE `bingo`.`salvadanaio`
                         SET InGioco = 0")) {  
    $stmt->execute(); 
    $stmt->close(); 
   } else  //erroe nell'esecuzione della query 
    $ris = false;
    $mysqli->close(); 
   return $ris; 
 }


}

?>

 