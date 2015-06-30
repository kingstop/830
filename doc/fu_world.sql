/*
Navicat MySQL Data Transfer

Source Server         : localhost
Source Server Version : 50613
Source Host           : localhost:3306
Source Database       : fu_world

Target Server Type    : MYSQL
Target Server Version : 50613
File Encoding         : 65001

Date: 2013-10-08 15:30:03
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `city_config`
-- ----------------------------
DROP TABLE IF EXISTS `city_config`;
CREATE TABLE `city_config` (
  `mapId` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `city` int(10) unsigned zerofill NOT NULL,
  `scene` int(10) unsigned zerofill NOT NULL,
  PRIMARY KEY (`mapId`)
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

-- ----------------------------
-- Records of city_config
-- ----------------------------
INSERT INTO `city_config` VALUES ('1', '0000000001', '0000000001');
INSERT INTO `city_config` VALUES ('2', '0000000001', '0000000002');
INSERT INTO `city_config` VALUES ('3', '0000000001', '0000000003');
INSERT INTO `city_config` VALUES ('4', '0000000002', '0000000001');
INSERT INTO `city_config` VALUES ('5', '0000000002', '0000000002');
INSERT INTO `city_config` VALUES ('6', '0000000002', '0000000003');
INSERT INTO `city_config` VALUES ('7', '0000000003', '0000000001');
INSERT INTO `city_config` VALUES ('8', '0000000003', '0000000002');
INSERT INTO `city_config` VALUES ('9', '0000000003', '0000000003');

-- ----------------------------
-- Table structure for `map_config`
-- ----------------------------
DROP TABLE IF EXISTS `map_config`;
CREATE TABLE `map_config` (
  `sceneid` int(10) unsigned zerofill NOT NULL,
  `top` int(11) NOT NULL,
  `bottom` int(11) NOT NULL,
  `left` int(11) NOT NULL,
  `right` int(11) NOT NULL,
  `center_x` float NOT NULL,
  `center_y` float NOT NULL,
  `view` float NOT NULL,
  PRIMARY KEY (`sceneid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

-- ----------------------------
-- Records of map_config
-- ----------------------------
INSERT INTO `map_config` VALUES ('0000000001', '300', '-300', '350', '350', '0', '0', '40');
INSERT INTO `map_config` VALUES ('0000000002', '300', '-300', '350', '350', '0', '0', '40');
INSERT INTO `map_config` VALUES ('0000000003', '300', '-300', '350', '350', '0', '0', '40');
