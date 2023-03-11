-- Progettazione Web 
DROP DATABASE if exists bingo; 
CREATE DATABASE bingo; 
USE bingo; 
-- MySQL dump 10.13  Distrib 5.6.20, for Win32 (x86)
--
-- Host: localhost    Database: bingo
-- ------------------------------------------------------
-- Server version	5.6.20

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
-- Table structure for table ` sessionlog`
--

DROP TABLE IF EXISTS ` sessionlog`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE ` sessionlog` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `NomeUtente` varchar(50) NOT NULL,
  `orarioinizio` datetime NOT NULL,
  `orariofine` datetime DEFAULT NULL,
  PRIMARY KEY (`ID`,`NomeUtente`)
) ENGINE=InnoDB DEFAULT CHARSET=ucs2;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table ` sessionlog`
--

LOCK TABLES ` sessionlog` WRITE;
/*!40000 ALTER TABLE ` sessionlog` DISABLE KEYS */;
/*!40000 ALTER TABLE ` sessionlog` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `cartellina`
--

DROP TABLE IF EXISTS `cartellina`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `cartellina` (
  `Idcartellina` int(11) NOT NULL,
  `NomeUtente` varchar(100) NOT NULL,
  `Numero` int(11) NOT NULL,
  `PosizioneNumero` int(11) NOT NULL,
  `Riga` varchar(45) NOT NULL,
  PRIMARY KEY (`Idcartellina`,`NomeUtente`,`Numero`,`PosizioneNumero`,`Riga`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `cartellina`
--

LOCK TABLES `cartellina` WRITE;
/*!40000 ALTER TABLE `cartellina` DISABLE KEYS */;
/*!40000 ALTER TABLE `cartellina` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `estratti`
--

DROP TABLE IF EXISTS `estratti`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `estratti` (
  `Idpartita` int(11) NOT NULL,
  `OrarioPartita` datetime NOT NULL,
  `Idnumero` int(11) NOT NULL AUTO_INCREMENT,
  `NumeroEstratto` int(11) NOT NULL,
  `Estratto` tinyint(4) DEFAULT '0',
  PRIMARY KEY (`Idnumero`,`Idpartita`,`OrarioPartita`,`NumeroEstratto`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `estratti`
--

LOCK TABLES `estratti` WRITE;
/*!40000 ALTER TABLE `estratti` DISABLE KEYS */;
/*!40000 ALTER TABLE `estratti` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `partita`
--

DROP TABLE IF EXISTS `partita`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `partita` (
  `Idpartita` int(11) NOT NULL AUTO_INCREMENT,
  `OrarioPartita` datetime NOT NULL,
  `Finita` tinyint(4) DEFAULT '0',
  PRIMARY KEY (`Idpartita`,`OrarioPartita`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `partita`
--

LOCK TABLES `partita` WRITE;
/*!40000 ALTER TABLE `partita` DISABLE KEYS */;
/*!40000 ALTER TABLE `partita` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `salvadanaio`
--

DROP TABLE IF EXISTS `salvadanaio`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `salvadanaio` (
  `NomeUtente` varchar(50) NOT NULL,
  `Saldo` double DEFAULT '0',
  `PremioGiornaliero` tinyint(4) NOT NULL,
  `InGioco` tinyint(4) NOT NULL,
  PRIMARY KEY (`NomeUtente`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `salvadanaio`
--

LOCK TABLES `salvadanaio` WRITE;
/*!40000 ALTER TABLE `salvadanaio` DISABLE KEYS */;
INSERT INTO `salvadanaio` VALUES ('Admin',15,0,0),('dino1',15,0,0),('frank',15,0,0),('Giacomo2',15,0,0),('Giulio11',15,0,0),('Giuseppe5',15,0,0),('Giuseppe7',15,0,0),('Luca15',15,0,0),('Marco1',15,0,0),('Marco12',15,0,0),('Marco22',15,0,0),('Mario15',15,0,0);
/*!40000 ALTER TABLE `salvadanaio` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `servizioclienti`
--

DROP TABLE IF EXISTS `servizioclienti`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `servizioclienti` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `Data` datetime NOT NULL,
  `NomeUtente` varchar(45) NOT NULL,
  `Email` varchar(100) NOT NULL,
  `Richiesta` varchar(100) NOT NULL,
  `Messaggio` varchar(200) DEFAULT NULL,
  PRIMARY KEY (`ID`,`Data`,`NomeUtente`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `servizioclienti`
--

LOCK TABLES `servizioclienti` WRITE;
/*!40000 ALTER TABLE `servizioclienti` DISABLE KEYS */;
/*!40000 ALTER TABLE `servizioclienti` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `utenti`
--

DROP TABLE IF EXISTS `utenti`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `utenti` (
  `NomeUtente` varchar(50) NOT NULL,
  `Nome` varchar(50) DEFAULT NULL,
  `Cognome` varchar(50) DEFAULT NULL,
  `DataNascita` varchar(50) NOT NULL,
  `Email` varchar(100) NOT NULL,
  `Password` varchar(150) NOT NULL,
  `UltimoAccesso` datetime NOT NULL,
  PRIMARY KEY (`NomeUtente`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `utenti`
--

LOCK TABLES `utenti` WRITE;
/*!40000 ALTER TABLE `utenti` DISABLE KEYS */;
INSERT INTO `utenti` VALUES ('Admin','','','1981-03-01','Admin@bingo.com','$2y$10$JEn23cMYmyBRmTCkcEmBzu/nJrzYAIbqOAgTiCyS0ZTBBjE.RMA6e','2021-06-13 16:51:18'),('frank','franco','blue','1957-05-12','frankblue@gmail.com','$2y$10$GWqB9/c.FwLSVpm2UeKwKuCMgcM7ME8pcJhob5EEQr8UJi2VskDvq','0000-00-00 00:00:00'),('Giacomo2','giacomo','arancioni','1987-12-30','giacomoarancioni@icloud.com','$2y$10$JpPCnnTJo4PIOz2IxWB/3eZvuR2Z2ShDw4S1B78kIsJcVKRQqI1ga','2021-04-06 14:05:23'),('Giulio11','giulio','bianchi','1999-08-06','giuliobianchi@gmail.com','$2y$10$0oVUANNBs6ChPiyO.yEBbehek/coxOAHRGPp5FSspKrh0SmjwEqOu','0000-00-00 00:00:00'),('Giuseppe5','giuseppe','viola','1989-02-16','violagiuseppe2@gmail.com','$2y$10$YioUDJtctTUcFPCjw1KGSecJh840lCbeeV2Lw25P5Ora/LEdD3Khy','2021-02-11 11:33:26'),('Giuseppe7','giuseppe','viola','1998-02-22','violagiuseppe@icloud.com','$2y$10$q2OCcMaZFRKH5bXdQyXZtuic9MTcGxIDmNJoZRbQi/5LkP3wx6yiS','2021-05-23 23:31:59'),('Luca15','luca','chiocchetti','1998-08-15','chiocchettiluca15@gmail.com','$2y$10$2iCQQLMBSOapCv5p4pXZRukopajoubPj0XWIUrTiXktxwtTW/c4hO','2021-06-13 16:51:14'),('Marco1','marco','bianchi','1997-02-13','bianchimarco@icloud.com','$2y$10$AFupAzc1GaRO5PRMf5QI0.H4V2My4fbNz0wy2VrncV1P73TGeJcPe','0000-00-00 00:00:00'),('Marco12','marco','verdi','1995-08-19','verdimarco.info@gmail.com','$2y$10$fgTd7cEsoVq3n1nuqAgYKuajIvXrP3NwAYgRLLw/tRa3JKGUi.Xi.','2021-02-10 12:30:40'),('Marco22','marco','bianchi','2000-01-19','bianchimarco@gmail.com','$2y$10$9tWXM2EdIj8YZEqzH8c6U.dyzmarzMaHKY21FiTkc/2vkW4bXYMVe','2021-05-24 23:35:30'),('Mario15','Mario','Rossi','2000-06-13','mario.rossi@gmail.com','$2y$10$tPH4HfMHaNuAnl7KfCqp5elcSoAayVq1dN1mzwdVTFqWHHA2Ky7xy','2021-06-13 16:51:20');
/*!40000 ALTER TABLE `utenti` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `vincita`
--

DROP TABLE IF EXISTS `vincita`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `vincita` (
  `Idpartita` int(11) NOT NULL,
  `OrarioPartita` varchar(50) NOT NULL,
  `NomeUtente` varchar(60) DEFAULT NULL,
  `TipoVincita` varchar(45) NOT NULL,
  `Importo` double DEFAULT NULL,
  PRIMARY KEY (`Idpartita`,`OrarioPartita`,`TipoVincita`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `vincita`
--

LOCK TABLES `vincita` WRITE;
/*!40000 ALTER TABLE `vincita` DISABLE KEYS */;
/*!40000 ALTER TABLE `vincita` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2021-06-13 16:55:37
