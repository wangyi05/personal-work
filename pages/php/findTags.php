<?php
/*
 *  Ajax implementation to searching the tags in Database
 *	@Input string
 *	@Output string
 */
$str = $_POST["str"];
//$str = "";
$origin_str="";
if (isset($str)&&!empty($str)) {
	// Deal with the input
	$token = explode(',', $str);
	$size = count($token);
	
	for($i=0;$i<count($token)-1;$i++){
		$origin_str .= $token[$i].",";
	}
	
	if(!empty($token[$size-1])) {
		// Link the database without password
		$con =  mysql_connect("127.0.0.1","root","Stevens05");
		if(!$con) {
			die('Could not connect: ' . mysql_error());
		}
		mysql_select_db("mocc", $con);
		$query = "SELECT tag FROM tags WHERE tag LIKE '".$token[$size-1]."%' LIMIT 10";
		$res = mysql_query($query);
	}
}

$tmp = array();
$tmp["str"] = $origin_str;
$tmp["list"] = array();
if(isset($str)&&!empty($str)) {
	if(!empty($token[$size-1])) {
		while ($row =mysql_fetch_row($res)){
			array_push($tmp["list"],$row[0]);
		}
		mysql_close();
	}
}

echo json_encode($tmp);
?>