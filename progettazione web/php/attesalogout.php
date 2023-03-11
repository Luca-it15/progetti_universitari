<!DOCTYPE html>
 <head>logout</head> 
 <body> 
 <?php 
 echo '<script>'; 
 echo 'var x = confirm("Sei sicuro di Uscire?");'; 
 echo 'if(!x) location.href="../home.php";';
 echo 'else location.href="logout.php"' ;  
 echo '</script>'; 
?> 
</body> 
</html> 