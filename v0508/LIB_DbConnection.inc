<?php

/**
 *
 *
 * @version $Id$
 * @copyright 2005
 **/

/**
 *
 * @name 		GetConnection
 * @args 		none
 * @return	database connection
 * @desc		
 *
 **/
function GetConnection()
{
	$lUser = GetConfigurationParam("fcd_database_user");
	$lPassword = GetConfigurationParam("fcd_database_passwd");
	$lConn = mysql_connect("localhost", $lUser, $lPassword) or die("Connection to database failed : " . mysql_error());
	$db = GetConfigurationParam("fcd_database");
	mysql_select_db($db) or die("Error selecting database");
	return $lConn;

}


?>
