DROP TABLE IF EXISTS `ligneCommandes`;
CREATE TABLE IF NOT EXISTS `ligneCommandes` (
  `commande` int(11) NOT NULL,
  `numeroLigne` int(11) NOT NULL,
  `article` varchar(20) NOT NULL COMMENT 'Article',
  `quantite` double(10,2) NOT NULL COMMENT 'Quantité',
  `prixUnitaireHT` double(10,2) NOT NULL COMMENT 'Prix unitaire hors taxe',
  `tauxTva` double(10,3) NOT NULL COMMENT 'Taux de tva',
  `td` date NOT NULL DEFAULT '0000-00-00',
  PRIMARY KEY (`commande`,`numeroLigne`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

INSERT INTO `ligneCommandes` (`commande`, `numeroLigne`, `article`, `quantite`, `prixUnitaireHT`, `tauxTva`, `td`) VALUES
(1, 1, 'PRGINF10', 0.50, 500.00, 0.196, '2012-11-02'),
(1, 2, 'PRGINF10', 1.00, 500.00, 0.196, '2012-11-02'),
(1, 3, 'PRGINF10', 1.50, 500.00, 0.196, '2012-11-02'),
(2, 1, 'PRGINF10', 1.50, 500.00, 0.196, '2012-11-04'),
(2, 2, 'PRGINF10', 2.50, 500.00, 0.196, '2012-11-04'),
(3, 1, 'PRGINF10', 1.00, 500.00, 0.196, '2012-11-10'),
(3, 2, 'PRGINF10', 2.00, 500.00, 0.196, '2012-11-10'),
(3, 3, 'FORMINF', 0.50, 0.00, 0.196, '2012-11-10'),
(3, 4, 'BULPAIE', 0.00, 12.00, 0.196, '2012-11-10'),
(3, 5, 'BULPAIE', 45.00, 12.00, 0.196, '2012-11-10');