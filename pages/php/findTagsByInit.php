<?php
/*
 *  Ajax implementation to searching the tags in Database
 *	@Input string
 *	@Output string
 */
$str = $_POST["str"];

// Link the database without password
$con =  mysql_connect("127.0.0.1","root","Stevens05");
if(!$con) {
	die('Could not connect: ' . mysql_error());
}
mysql_select_db("mocc", $con);
if($str == "&amp;") {
	$query = "SELECT tag FROM tags WHERE tag REGEXP '^[^A-Z].+$'";
} else {
	$query = "SELECT tag FROM tags WHERE tag LIKE '".$str."%'";
}
mysql_query("set names 'utf8'");
$res = mysql_query($query);

$tmp = array();
while ($row =mysql_fetch_row($res)){
	array_push($tmp,$row[0]);
}
mysql_close();

echo json_encode($tmp);
?>