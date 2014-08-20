<?php
// Test CVS

include_once '../LIB_DbConnection.inc';
include_once '/Excel/reader.php';
echo getcwd().'/Excel/reader.php';
?>



<?php
$cust = array();
$prod = array();
$day = array();
$month = array();
$year = array();
$state = array();
$quant = array();
$lconn = mysql_connect("localhost","fcdschoo","Wenxinw$1996") or die("Connect to database failed: ". mysql_error());
mysql_select_db("fcdschoo_fangcd0308") or die("Error selecting database");

// ExcelFile($filename, $encoding);
$data = new Spreadsheet_Excel_Reader();

echo "dasdasd";

// Set output Encoding.
$data->setOutputEncoding('CP1251');

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

$data->read('test.xls');

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
$j = 2;
for ($i = 2; $i <= $data->sheets[0]['numRows']; $i++) {
	$cust[$n] = $data->sheets[0]['cells'][$i][$j];
	$prod[$n] = $data->sheets[0]['cells'][$i][++$j];
	$day[$n] = $data->sheets[0]['cells'][$i][++$j];
	$month[$n] = $data->sheets[0]['cells'][$i][++$j];
	$year[$n] = $data->sheets[0]['cells'][$i][++$j];
	$state[$n] = $data->sheets[0]['cells'][$i][++$j];
	$quant[$n] = $data->sheets[0]['cells'][$i][++$j];
	$n++;
	$j = 2;
	echo "\n";

}
echo "$n";
for($rows = 0; $rows < $n; $rows++){
$query = "insert into sales values("
		." '".$cust[$rows]. "', "
		." '".$prod[$rows]. "', "
		." '".$day[$rows]. "', "
		." '".$month[$rows]."',"
		." '".$year[$rows]. "',"
		." '".$state[$rows]. "',"
		." '".$quant[$rows]. "'"
		.")";
mysql_query($query) or die("Query failed: $query " . mysql_error());
}

print_r($state);

//print_r($data);
//print_r($data->formatRecords);
?>
