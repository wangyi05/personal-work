<!-- mysql_query("set character set 'utf8'");//读库  -->
<!-- mysql_query("set names 'utf8'");//写库  -->

<!-- create table registration_form(
    StudentId int(11),
    Name varchar(50),
    Gender varchar(50),
    Semester varchar(50),
    ClassName Varchar(50),
    CultureId varchar(50),
    TeacherId varchar(50),
    telephone varchar(50),
    Email varchar(50)
    
    ); -->


<?php
// Test CVS

require_once 'Excel/reader.php';
require_once 'database_conn.php';

// $cust = array();
// $prod = array();
// $day = array();
// $month = array();
// $year = array();
// $state = array();
// $quant = array();

 $StudentId = array();
 $Name = array();
 $Gender = array();
 $Semester = array();
 $ClassName = array();
 $CultureId = array();
 $TeacherId = array();
 $Telephone = array();
 $Email = array();

$db = GetConnection();
$db_selected = mysql_select_db('fcdschoo_fangcd0308', $db);
if(!$db_selected){
	die('Can\'t use fcdschoo_fangcd0308:' . mysql_error());
}
mysql_query("set names 'utf8'");

// ExcelFile($filename, $encoding);
$data = new Spreadsheet_Excel_Reader();

// Set output Encoding.
 $data->setOutputEncoding('utf-8');

/***
* if you want you can change 'iconv' to mb_convert_encoding:
* $data->setUTFEncoder('mb');
*
**/

/***
* By default rows & cols indeces start with 1
* For change initial index use:
* $data->setRowColOffset(0);
*
**/



/***
*  Some function for formatting output.
* $data->setDefaultFormat('%.2f');
* setDefaultFormat - set format for columns with unknown formatting
*
* $data->setColumnFormat(4, '%.3f');
* setColumnFormat - set format for column (apply only to number fields)
*
**/

 $data->read('Registration Form_Format.xls');

/*


 $data->sheets[0]['numRows'] - count rows
 $data->sheets[0]['numCols'] - count columns
 $data->sheets[0]['cells'][$i][$j] - data from $i-row $j-column

 $data->sheets[0]['cellsInfo'][$i][$j] - extended info about cell
    
    $data->sheets[0]['cellsInfo'][$i][$j]['type'] = "date" | "number" | "unknown"
        if 'type' == "unknown" - use 'raw' value, because  cell contain value with format '0.00';
    $data->sheets[0]['cellsInfo'][$i][$j]['raw'] = value if cell without format 
    $data->sheets[0]['cellsInfo'][$i][$j]['colspan'] 
    $data->sheets[0]['cellsInfo'][$i][$j]['rowspan'] 
*/



error_reporting(E_ALL ^ E_NOTICE);
$n = 0;
$j = 1;
for ($i = 2; $i <= $data->sheets[0]['numRows']; $i++) {
	$StudentId[$n] = $data->sheets[0]['cells'][$i][$j];
	$Name[$n] = $data->sheets[0]['cells'][$i][++$j];
	$Gender[$n] = $data->sheets[0]['cells'][$i][++$j];
	$Semester[$n] = $data->sheets[0]['cells'][$i][++$j];
	$j++;
	$ClassName[$n] = $data->sheets[0]['cells'][$i][++$j];
	$CultureId[$n] = $data->sheets[0]['cells'][$i][++$j];
	$TeacherId[$n] = $data->sheets[0]['cells'][$i][++$j];
	$Telephone[$n] = $data->sheets[0]['cells'][$i][++$j];
	$Email[$n] = $data->sheets[0]['cells'][$i][++$j];
	$n++;
	$j = 1;
	echo "\n";

}
echo "$n";
for($rows = 0; $rows < $n; $rows++){
$query = "insert into registration_form values("
		." '".$StudentId[$rows]. "', "
		." '".$Name[$rows]. "', "
		." '".$Gender[$rows]. "', "
		." '".$Semester[$rows]."',"
		." '".$ClassName[$rows]. "',"
		." '".$CultureId[$rows]. "',"
		." '".$TeacherId[$rows]. "',"
		." '".$Telephone[$rows]. "',"
		." '".$Email[$rows]. "'"
		.")";
mysql_query($query) or die("Query failed: $query " . mysql_error());
}


//print_r($data);
//print_r($data->formatRecords);
?>
