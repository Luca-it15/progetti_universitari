<?php
//parametri di configurazione per il database mysql
 ini_set('display_errors', 1);
 ini_set('display_startup_errors', 1);
 error_reporting(E_ALL | E_STRICT);
 
 $DATABASE_HOST = 'localhost';
 $DATABASE_USER = 'root';
 $DATABASE_PASS = '';
 $DATABASE_NAME = 'Bingo';
 
 $mysqli = mysqli_connect($DATABASE_HOST, $DATABASE_USER, $DATABASE_PASS, $DATABASE_NAME);
 if ( mysqli_connect_errno() ) {
	exit('Failed to connect to MySQL: ' . mysqli_connect_error());
 }

?>
