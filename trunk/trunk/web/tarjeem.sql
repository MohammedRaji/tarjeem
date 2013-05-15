-- phpMyAdmin SQL Dump
-- version 3.4.5
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: May 15, 2013 at 08:48 AM
-- Server version: 5.5.16
-- PHP Version: 5.3.8

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `tarjeem`
--

-- --------------------------------------------------------

--
-- Table structure for table `permissions`
--

CREATE TABLE IF NOT EXISTS `permissions` (
  `id` mediumint(8) NOT NULL AUTO_INCREMENT,
  `name` varchar(12) NOT NULL,
  `description` text NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=2 ;

--
-- Dumping data for table `permissions`
--

INSERT INTO `permissions` (`id`, `name`, `description`) VALUES
(1, 'admin', 'System administrators.');

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

CREATE TABLE IF NOT EXISTS `users` (
  `id` mediumint(8) NOT NULL AUTO_INCREMENT,
  `name` varchar(80) NOT NULL,
  `email` varchar(30) DEFAULT NULL,
  `login` varchar(18) NOT NULL,
  `password` varchar(60) NOT NULL,
  `last_login` date DEFAULT NULL,
  `active` tinyint(1) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=3 ;

--
-- Dumping data for table `users`
--

INSERT INTO `users` (`id`, `name`, `email`, `login`, `password`, `last_login`, `active`) VALUES
(1, 'Administrator', 'admin@localhost', 'admin', '$2a$12$SR04o2/JNV5ZoVGZNgPiiezqM2f5D0eVDXsSDoWcfQqg/mST6O6Ye', '2013-04-19', 1),
(2, 'Nurul Maulidiah', 'lia.sf07@gmail.com', 'lia', '$2a$12$SR04o2/JNV5ZoVGZNgPiiezqM2f5D0eVDXsSDoWcfQqg/mST6O6Ye', '2013-04-19', 1);

-- --------------------------------------------------------

--
-- Table structure for table `users_permissions`
--

CREATE TABLE IF NOT EXISTS `users_permissions` (
  `user_id` mediumint(8) NOT NULL,
  `permission_id` mediumint(8) NOT NULL,
  KEY `user_id` (`user_id`),
  KEY `permission_id` (`permission_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `users_permissions`
--

INSERT INTO `users_permissions` (`user_id`, `permission_id`) VALUES
(1, 1);

--
-- Constraints for dumped tables
--

--
-- Constraints for table `users_permissions`
--
ALTER TABLE `users_permissions`
  ADD CONSTRAINT `users_permissions_ibfk_1` FOREIGN KEY (`user_id`) REFERENCES `users` (`id`) ON DELETE CASCADE,
  ADD CONSTRAINT `users_permissions_ibfk_2` FOREIGN KEY (`permission_id`) REFERENCES `permissions` (`id`) ON DELETE CASCADE;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
