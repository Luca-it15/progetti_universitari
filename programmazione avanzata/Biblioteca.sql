CREATE DATABASE  IF NOT EXISTS `biblioteca` /*!40100 DEFAULT CHARACTER SET latin1 */;
USE `biblioteca`;
-- MySQL dump 10.13  Distrib 5.6.17, for Win32 (x86)
--
-- Host: 127.0.0.1    Database: biblioteca
-- ------------------------------------------------------
-- Server version	5.6.21

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `prenotazioni`
--

DROP TABLE IF EXISTS `prenotazioni`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `prenotazioni` (
  `nomeUtente` varchar(50) NOT NULL,
  `dataPrenotazione` date NOT NULL,
  `turno` varchar(45) NOT NULL,
  `idtavolo` int(11) DEFAULT NULL,
  `tipo` varchar(100) DEFAULT NULL,
  `libro` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`nomeUtente`,`dataPrenotazione`,`turno`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `prenotazioni`
--

LOCK TABLES `prenotazioni` WRITE;
/*!40000 ALTER TABLE `prenotazioni` DISABLE KEYS */;
INSERT INTO `prenotazioni` VALUES ('Federico Bianchi','2021-02-15','Intero',4,'Standard','Grammtica inglese'),('Federico Bossi','2022-02-11','Intero',8,'Lettura con luce','Vincere a fantacalcio'),('Federico Bossi','2022-02-12','Intero',1,'Postazione pc','Guerra in crimea'),('Filippo Bianchi','2021-02-19','Intero',3,'Standard','Orgoglio e pregiudizio'),('Filippo Bianchi','2022-02-11','Intero',1,'Postazione pc','Orgoglio e pregiudizio'),('Filippo rossi ','2021-02-17','Intero',9,'Standard','Avere o essere'),('Filippo Verdi','2021-02-10','Mattina',6,'Lettura con luce','La fattoria degli animali'),('Filippo Verdi','2021-02-11','Mattina',2,'Lettura con luce','La fattoria degli animali'),('Filippo Verdi','2021-02-12','Mattina',3,'Standard','La fattoria degli animali '),('Filippo Verdi','2021-02-13','Mattina',3,'Standard','Lezoni di cucina'),('Filippo Verdi','2021-02-14','Mattina',3,'Standard','Lezioni di scienza'),('Filippo Verdi','2021-02-16','Mattina',7,'Postazione pc','porte logiche'),('Filippo Verdi','2021-02-17','Mattina',3,'Standard','Lezioni di scienza'),('Giacomo rossi','2021-02-15','Intero',3,'Standard','Medicina Generale'),('Giacomo rossi','2022-02-16','Intero',3,'Standard','cesare e roma'),('Giada Nivea','2021-02-17','Intero',12,'Lettura con luce','La lanterna sul lago'),('Giada Nivea','2021-02-18','Intero',11,'Postazione pc','La ricerca della felicita'),('Giovanni Verdi','2022-02-16','Pomeriggio',9,'Standard',NULL),('Giulio fiondini','2022-02-17','Intero',7,'Postazione pc','La battaglia di waterloo'),('Giuseppe Verdi','2022-02-12','Intero',5,'Postazione pc','Introduzione alla musica classica'),('Luca Boschi','2021-02-18','Intero',6,'Lettura con luce','Grammatica spagnola'),('Luca Boschi','2021-02-19','Intero',8,'Lettura con luce','I tre moschettieri'),('Luca Chiocchetti','2021-02-15','Mattina',3,'Standard','Modernità liquida'),('Luca Chiocchetti','2022-02-15','Mattina',3,'Standard','Maus'),('Luca Chiocchetti','2022-02-17','Mattina',2,'Lettura con luce','Le cronache di narnia'),('Luca Chiocchetti','2022-02-18','Pomeriggio',3,'Standard','Lezioni di musica'),('Maria Gialli','2022-02-12','Intero',9,'Standard','Diritto privato'),('maria Rossi','2022-02-17','Intero',5,'Postazione pc','Diritto Privato'),('Mario Draghi','2022-02-11','Intero',4,'Standard','Come diventare premier'),('Mario rossi','2021-02-15','Pomeriggio',4,'Standard','La vita di provincia'),('Mario Rossi','2021-02-16','Mattina',4,'Standard','Scooby doo'),('Orlando blu','2022-02-12','Intero',3,'Standard','Come diventare un attore'),('Sara Marrone','2022-02-12','Intero',10,'Standard','Diritto civile'),('Sara Marrone','2022-02-17','Intero',3,'Standard','Diritto Civile'),('Tommaso verdi','2021-02-17','Mattina',5,'Postazione pc','Lezioni di matematica'),('Tommaso verdi','2021-02-18','Mattina',4,'Standard','Lezioni di Matematica'),('Vincenzo Gialli','2022-02-16','Intero',5,'Postazione pc','nerone e roma'),('Viola Fucsia','2021-02-16','Intero',2,'Lettura con luce','Harry potter'),('Viola Fucsia','2022-02-18','Intero',7,'Postazione pc','Le scienze di tutti i giorni'),('Vittorio Blue','2022-02-17','Intero',9,'Standard','La carica dei 101'),('Vittorio Blue','2022-02-19','Intero',1,'Postazione pc','La carica dei 101');
/*!40000 ALTER TABLE `prenotazioni` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tavoli`
--

DROP TABLE IF EXISTS `tavoli`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tavoli` (
  `idtavolo` int(11) NOT NULL,
  `tipo` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`idtavolo`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tavoli`
--

LOCK TABLES `tavoli` WRITE;
/*!40000 ALTER TABLE `tavoli` DISABLE KEYS */;
INSERT INTO `tavoli` VALUES (1,'Postazione pc'),(2,'Lettura con luce'),(3,'Standard'),(4,'Standard'),(5,'Postazione pc'),(6,'Lettura con luce'),(7,'Postazione pc'),(8,'Lettura con luce'),(9,'Standard'),(10,'Standard'),(11,'Postazione pc'),(12,'Lettura con luce'),(13,'Postazione pc'),(14,'Standard'),(15,'Lettura con luce'),(16,'Postazione pc');
/*!40000 ALTER TABLE `tavoli` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2022-02-17 23:35:04
