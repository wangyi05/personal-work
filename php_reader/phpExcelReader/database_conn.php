<?php

function GetConnection(){
	$lUser ="root";
	$lPassword = "root";
	$ldatabase_name = "sales";
	$lConn = mysql_connect("localhost", $lUser, $lPassword, $ldatabase_name) or die("Connection to database failed : ". mysql_error());
	return $lConn;

}


?>