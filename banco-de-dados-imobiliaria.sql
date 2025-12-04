-- MySQL dump 10.13  Distrib 8.0.40, for Win64 (x86_64)
--
-- Host: localhost    Database: imobiliaria
-- ------------------------------------------------------
-- Server version	8.0.40

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `cliente`
--

DROP TABLE IF EXISTS `cliente`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `cliente` (
  `id_cliente` int NOT NULL AUTO_INCREMENT,
  `nome` varchar(200) NOT NULL,
  `cpf` char(11) NOT NULL,
  `telefone_um` varchar(20) NOT NULL,
  `telefone_dois` varchar(20) DEFAULT NULL,
  `estado_civil` enum('Solteiro','Casado','Divorciado','Viúvo') NOT NULL,
  `tipo_cliente` enum('Proprietario','Inquilino') NOT NULL,
  PRIMARY KEY (`id_cliente`),
  UNIQUE KEY `cpf` (`cpf`)
) ENGINE=InnoDB AUTO_INCREMENT=12 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `cliente`
--

LOCK TABLES `cliente` WRITE;
/*!40000 ALTER TABLE `cliente` DISABLE KEYS */;
INSERT INTO `cliente` VALUES (1,'Enzo Basaldella','9642517037','2196166370',NULL,'Divorciado','Proprietario'),(2,'Jurair Rosa','5650928088','2299509835','2493608190','Solteiro','Inquilino'),(3,'Laura Assis','6277128361','2399852540','2291235943','Solteiro','Proprietario'),(4,'Gustavo Kanji','5416297828','2297351912',NULL,'Casado','Inquilino'),(5,'Nicolas Nogueira','9330297894','2395972415','2297992826','Solteiro','Proprietario'),(6,'Luis Tarrataca','4783358772','2394054341','2194445825','Casado','Inquilino'),(7,'Ana Elisa','5516868187','2492056315','2194242659','Viúvo','Proprietario'),(8,'Carlos Eduardo','8833047391','2297462042',NULL,'Divorciado','Inquilino'),(9,'Fernanda Souza','2885707641','2394676221','2199110532','Solteiro','Proprietario'),(10,'Paulo Henrique','3978408758','2297410831','2198170387','Casado','Inquilino'),(11,'Rebeca Alves Peres','12125093740','2299998888','2499998888','Solteiro','Inquilino');
/*!40000 ALTER TABLE `cliente` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `contrato`
--

DROP TABLE IF EXISTS `contrato`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `contrato` (
  `id_contrato` int NOT NULL AUTO_INCREMENT,
  `id_proposta` int NOT NULL,
  `duracao` int NOT NULL,
  `valor_inicial` decimal(12,2) NOT NULL,
  PRIMARY KEY (`id_contrato`),
  UNIQUE KEY `id_proposta` (`id_proposta`),
  CONSTRAINT `contrato_ibfk_1` FOREIGN KEY (`id_proposta`) REFERENCES `proposta` (`id_proposta`) ON DELETE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `contrato`
--

LOCK TABLES `contrato` WRITE;
/*!40000 ALTER TABLE `contrato` DISABLE KEYS */;
INSERT INTO `contrato` VALUES (1,2,12,3600.00),(2,8,10,2500.00),(3,9,12,2500.00),(4,7,10,2800.00),(5,13,8,1500.00);
/*!40000 ALTER TABLE `contrato` ENABLE KEYS */;
UNLOCK TABLES;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = cp850 */ ;
/*!50003 SET character_set_results = cp850 */ ;
/*!50003 SET collation_connection  = cp850_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `atualizar_situacao_imovel` AFTER INSERT ON `contrato` FOR EACH ROW UPDATE Imovel
SET situacao = 'Indisponivel'
WHERE id_imovel = (SELECT id_imovel FROM Proposta WHERE id_proposta = NEW.id_proposta) */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = cp850 */ ;
/*!50003 SET character_set_results = cp850 */ ;
/*!50003 SET collation_connection  = cp850_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `restaurar_situacao_imovel` AFTER DELETE ON `contrato` FOR EACH ROW UPDATE Imovel
SET situacao = 'Disponivel'
WHERE id_imovel = (SELECT id_imovel FROM Proposta WHERE id_proposta = OLD.id_proposta) */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Table structure for table `corretor`
--

DROP TABLE IF EXISTS `corretor`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `corretor` (
  `id_corretor` int NOT NULL AUTO_INCREMENT,
  `nome` varchar(200) NOT NULL,
  `creci` varchar(50) NOT NULL,
  `telefone` varchar(20) NOT NULL,
  `data_prestacao` date NOT NULL,
  `comissao` decimal(5,2) NOT NULL,
  PRIMARY KEY (`id_corretor`),
  UNIQUE KEY `creci` (`creci`),
  UNIQUE KEY `telefone` (`telefone`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `corretor`
--

LOCK TABLES `corretor` WRITE;
/*!40000 ALTER TABLE `corretor` DISABLE KEYS */;
INSERT INTO `corretor` VALUES (1,'Rodrigo Lima','CRECI-RJ 2486 F','2196575901','2020-04-07',6.57),(2,'Carolina Braga','CRECI-SP 5891 J','2392706242','2020-08-15',5.15),(3,'Aline Silverio','CRECI-RJ 3742 F','2193890256','2017-01-15',4.07);
/*!40000 ALTER TABLE `corretor` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `fiador`
--

DROP TABLE IF EXISTS `fiador`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `fiador` (
  `id_fiador` int NOT NULL AUTO_INCREMENT,
  `id_inquilino` int NOT NULL,
  `nome` varchar(100) NOT NULL,
  `telefone` varchar(20) NOT NULL,
  `saldo_bancario` decimal(12,2) NOT NULL,
  PRIMARY KEY (`id_fiador`),
  KEY `id_inquilino` (`id_inquilino`),
  CONSTRAINT `fiador_ibfk_1` FOREIGN KEY (`id_inquilino`) REFERENCES `inquilino` (`id_inquilino`) ON DELETE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=14 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `fiador`
--

LOCK TABLES `fiador` WRITE;
/*!40000 ALTER TABLE `fiador` DISABLE KEYS */;
INSERT INTO `fiador` VALUES (1,2,'Adailson Cardoso','2497391686',420000.00),(2,2,'Camila Figo','2391436264',32000.00),(3,4,'Athos Fernandes','2397698934',15000.00),(4,4,'Renato Campos','2191494026',18000.00),(5,6,'Carla Albuquerque','2294747338',22000.00),(6,6,'Felipe Siqueira','2193591106',28000.00),(7,6,'Isabela Neves Peres','2495850755',150000.00),(8,8,'Pacha Basaldella','2294747338',35000.00),(9,8,'Andre Leo Soares','2193591106',40000.00),(10,10,'Joao Matheus Borges','2495850755',27000.00),(11,10,'Tatiane Silva Borges','2391436264',29000.00),(12,10,'Vinicius Dutra Borges','2191494026',450000.00),(13,11,'Enzo Alves','2499998887',2000.05);
/*!40000 ALTER TABLE `fiador` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `imovel`
--

DROP TABLE IF EXISTS `imovel`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `imovel` (
  `id_imovel` int NOT NULL AUTO_INCREMENT,
  `id_proprietario` int NOT NULL,
  `id_corretor` int DEFAULT NULL,
  `tipo` enum('Casa','Apartamento','Kitnet') NOT NULL,
  `num_comodos` int NOT NULL,
  `vagas_garagem` int NOT NULL,
  `area` decimal(8,2) NOT NULL,
  `cidade` varchar(50) NOT NULL,
  `bairro` varchar(50) NOT NULL,
  `rua` varchar(150) NOT NULL,
  `numero` varchar(10) NOT NULL,
  `valor_aluguel` decimal(12,2) NOT NULL,
  `data_oferta` date NOT NULL,
  `situacao` enum('Disponivel','Indisponivel') DEFAULT 'Disponivel',
  PRIMARY KEY (`id_imovel`),
  KEY `id_proprietario` (`id_proprietario`),
  KEY `id_corretor` (`id_corretor`),
  CONSTRAINT `imovel_ibfk_1` FOREIGN KEY (`id_proprietario`) REFERENCES `proprietario` (`id_proprietario`) ON DELETE CASCADE,
  CONSTRAINT `imovel_ibfk_2` FOREIGN KEY (`id_corretor`) REFERENCES `corretor` (`id_corretor`) ON DELETE SET NULL
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `imovel`
--

LOCK TABLES `imovel` WRITE;
/*!40000 ALTER TABLE `imovel` DISABLE KEYS */;
INSERT INTO `imovel` VALUES (1,1,3,'Casa',5,3,170.63,'Sao Pedro','Centro','Rua das Palmeiras','332',3300.00,'2017-08-05','Indisponivel'),(2,3,2,'Apartamento',5,2,31.69,'Petropolis','Centro','Rua do Imperador','593',1677.61,'2019-08-24','Indisponivel'),(3,1,3,'Casa',2,3,141.92,'Petropolis','Centro','13 de Marco','290',3674.87,'2016-01-04','Indisponivel'),(4,5,3,'Casa',3,3,190.89,'Sao Pedro','Centro','Rua das Palmeiras','383',2986.57,'2017-08-05','Indisponivel'),(5,9,3,'Kitnet',1,0,127.98,'Petropolis','Centro','Paulo Barbosa','464',4334.65,'2020-08-04','Disponivel'),(6,7,2,'Apartamento',2,2,173.32,'Cabo Frio','Passagem','Rua Maestro','561',2560.39,'2022-12-30','Disponivel'),(7,5,2,'Casa',3,2,149.71,'Cabo Frio','Centro','Jose Paes de Abreu','593',3951.68,'2015-08-15','Disponivel'),(8,3,1,'Casa',4,2,135.50,'Sao Pedro','Centro','Rua das Palmeiras','789',3500.00,'2023-07-15','Indisponivel'),(9,5,1,'Apartamento',2,1,78.30,'Petropolis','Centro','Rua do Imperador','125',2100.00,'2022-11-30','Disponivel'),(10,1,3,'Casa',3,2,120.00,'Petropolis','Centro','Rua do Imperador','10',4400.00,'2025-02-02','Disponivel');
/*!40000 ALTER TABLE `imovel` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `inquilino`
--

DROP TABLE IF EXISTS `inquilino`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `inquilino` (
  `id_inquilino` int NOT NULL,
  `profissao` varchar(50) NOT NULL,
  `renda_familiar` decimal(12,2) NOT NULL,
  PRIMARY KEY (`id_inquilino`),
  CONSTRAINT `inquilino_ibfk_1` FOREIGN KEY (`id_inquilino`) REFERENCES `cliente` (`id_cliente`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `inquilino`
--

LOCK TABLES `inquilino` WRITE;
/*!40000 ALTER TABLE `inquilino` DISABLE KEYS */;
INSERT INTO `inquilino` VALUES (2,'Médica',16800.00),(4,'Engenheiro',9500.75),(6,'Professor',4500.00),(8,'Advogado',10500.90),(10,'Designer',2900.00),(11,'Medica',5500.00);
/*!40000 ALTER TABLE `inquilino` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `proposta`
--

DROP TABLE IF EXISTS `proposta`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `proposta` (
  `id_proposta` int NOT NULL AUTO_INCREMENT,
  `id_inquilino` int DEFAULT NULL,
  `id_imovel` int DEFAULT NULL,
  `valor_proposta` decimal(12,2) NOT NULL,
  `data_proposta` date NOT NULL,
  `validade` date NOT NULL,
  PRIMARY KEY (`id_proposta`),
  KEY `id_inquilino` (`id_inquilino`),
  KEY `id_imovel` (`id_imovel`),
  CONSTRAINT `proposta_ibfk_1` FOREIGN KEY (`id_inquilino`) REFERENCES `inquilino` (`id_inquilino`) ON DELETE SET NULL,
  CONSTRAINT `proposta_ibfk_2` FOREIGN KEY (`id_imovel`) REFERENCES `imovel` (`id_imovel`) ON DELETE SET NULL
) ENGINE=InnoDB AUTO_INCREMENT=18 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `proposta`
--

LOCK TABLES `proposta` WRITE;
/*!40000 ALTER TABLE `proposta` DISABLE KEYS */;
INSERT INTO `proposta` VALUES (1,2,1,3500.00,'2024-02-10','2024-02-20'),(2,4,1,3600.00,'2024-02-12','2024-02-25'),(3,6,1,3400.00,'2024-02-15','2024-02-28'),(4,8,1,3300.00,'2024-02-18','2024-03-02'),(5,10,1,3200.00,'2024-02-20','2024-03-05'),(6,2,1,3700.00,'2024-02-22','2024-03-10'),(7,4,2,2800.00,'2024-03-01','2024-03-15'),(8,6,3,2000.00,'2024-03-05','2024-03-20'),(9,8,4,2500.00,'2024-03-10','2024-03-25'),(10,10,5,1800.00,'2024-03-15','2024-03-30'),(11,2,6,3000.00,'2024-03-20','2024-04-05'),(12,4,7,4000.00,'2024-03-25','2024-04-10'),(13,6,8,1500.00,'2024-04-01','2024-04-15'),(14,8,9,2700.00,'2024-04-05','2024-04-20'),(15,10,2,2900.00,'2024-04-10','2024-04-25'),(16,11,10,4000.00,'2025-02-02','2025-02-03'),(17,11,10,3400.00,'2025-02-02','2025-02-03');
/*!40000 ALTER TABLE `proposta` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `proprietario`
--

DROP TABLE IF EXISTS `proprietario`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `proprietario` (
  `id_proprietario` int NOT NULL,
  `certidao_registro` varchar(100) NOT NULL,
  `data_registro` date NOT NULL,
  PRIMARY KEY (`id_proprietario`),
  UNIQUE KEY `certidao_registro` (`certidao_registro`),
  CONSTRAINT `proprietario_ibfk_1` FOREIGN KEY (`id_proprietario`) REFERENCES `cliente` (`id_cliente`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `proprietario`
--

LOCK TABLES `proprietario` WRITE;
/*!40000 ALTER TABLE `proprietario` DISABLE KEYS */;
INSERT INTO `proprietario` VALUES (1,'343335-184','2018-05-14'),(3,'792283-444','2023-06-18'),(5,'155080-740','2016-03-05'),(7,'807035-913','2019-04-11'),(9,'455668-750','2023-12-27');
/*!40000 ALTER TABLE `proprietario` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `visita`
--

DROP TABLE IF EXISTS `visita`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `visita` (
  `id_visita` int NOT NULL AUTO_INCREMENT,
  `id_inquilino` int DEFAULT NULL,
  `id_imovel` int DEFAULT NULL,
  `id_corretor` int DEFAULT NULL,
  `data_visita` datetime NOT NULL,
  PRIMARY KEY (`id_visita`),
  KEY `id_inquilino` (`id_inquilino`),
  KEY `id_imovel` (`id_imovel`),
  KEY `id_corretor` (`id_corretor`),
  CONSTRAINT `visita_ibfk_1` FOREIGN KEY (`id_inquilino`) REFERENCES `inquilino` (`id_inquilino`) ON DELETE SET NULL,
  CONSTRAINT `visita_ibfk_2` FOREIGN KEY (`id_imovel`) REFERENCES `imovel` (`id_imovel`) ON DELETE SET NULL,
  CONSTRAINT `visita_ibfk_3` FOREIGN KEY (`id_corretor`) REFERENCES `corretor` (`id_corretor`) ON DELETE SET NULL
) ENGINE=InnoDB AUTO_INCREMENT=22 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `visita`
--

LOCK TABLES `visita` WRITE;
/*!40000 ALTER TABLE `visita` DISABLE KEYS */;
INSERT INTO `visita` VALUES (1,2,1,3,'2024-02-10 15:30:00'),(2,4,1,3,'2024-02-15 16:30:00'),(3,6,1,3,'2024-02-20 14:00:00'),(4,8,1,3,'2024-02-25 11:00:00'),(5,10,1,3,'2024-02-28 13:00:00'),(6,4,1,3,'2024-03-02 09:00:00'),(7,6,2,2,'2024-03-10 12:00:00'),(8,8,2,2,'2024-03-15 14:00:00'),(9,4,3,3,'2024-04-06 11:00:00'),(10,6,3,3,'2024-04-10 10:30:00'),(11,8,3,3,'2024-04-15 17:00:00'),(12,2,4,3,'2024-05-07 09:30:00'),(13,4,5,2,'2024-06-07 09:30:00'),(14,6,5,2,'2024-06-10 11:00:00'),(15,8,5,2,'2024-06-15 13:00:00'),(16,10,5,2,'2024-06-18 10:00:00'),(17,2,6,1,'2024-07-07 09:30:00'),(18,4,6,1,'2024-07-10 12:00:00'),(19,6,6,1,'2024-07-15 14:00:00'),(21,11,10,3,'2024-02-02 00:00:00');
/*!40000 ALTER TABLE `visita` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2025-02-02 17:57:52
