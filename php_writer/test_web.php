<meta http-equiv="Content-Type" content="text/html; charset=utf-8" /> 
<?php

require_once 'database_conn.php';



$db = GetConnection();

$db_selected = mysql_select_db('fcdschoo_fangcd0308', $db);

mysql_query("SET NAMES 'utf8'");

if(!$db_selected){
	die('Can\'t use fcdschoo_fangcd0308:' . mysql_error());
}
$tablename = "编码abc";  

$tablename = mb_convert_encoding($tablename, "utf-8", "GB2312" ); 


$query = "select * from registration_form where ClassName = 'CSL-Adult'";


$result = mysql_query($query) or die("Query failed : $query " . mysql_error());

echo "<table border=1>";
if (mysql_num_rows($result) > 0) {
		while ($row = mysql_fetch_array($result, MYSQL_ASSOC)) {
			$semester = $row['Semester'];
			echo "<tr>";
			echo "<td>$semester</td>";
			echo "<td>$tablename</td>";
			echo "</tr>";
		}
		mysql_free_result($result);
	}
echo"<table/>";

?>