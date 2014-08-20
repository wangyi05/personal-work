<?php
require_once 'Excel/reader.php';
require_once 'database_conn.php';


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

$data->setOutputEncoding('utf-8');

$data->read('Registration Form_Format.xls');

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

?>

<!DOCTYPE html>
<html>

<head>
	<meta charset='UTF-8'>
	
	<title>Responsive Table</title>
	
	<meta name="viewport" content="width=device-width, initial-scale=1.0">

	<link rel="stylesheet" href="css/style.css">
	
	<script type="text/javascript" src="js/note.js"></script>
	<!--[if !IE]><!-->
	<style>
	/* 
	Max width before this PARTICULAR table gets nasty
	This query will take effect for any screen smaller than 760px
	and also iPads specifically.
	*/
	@media 
	only screen and (max-width: 760px),
	(min-device-width: 768px) and (max-device-width: 1024px)  {
	
		/* Force table to not be like tables anymore */
		table, thead, tbody, th, td, tr { 
			display: block; 
		}
		
		html {
  			font-size: 18px;
		}
		/* Hide table headers (but not display: none;, for accessibility) */
		thead tr { 
			position: absolute;
			top: -9999px;
			left: -9999px;
		}
		
		tr { border: 1px solid #ccc; }
		
		td { 
			/* Behave  like a "row" */
			border: none;
			border-bottom: 1px solid #eee; 
			position: relative;
			padding-left: 50%; 
		}
		
		td:before { 
			/* Now like a table header */
			position: absolute;
			/* Top/left values mimic padding */
			top: 6px;
			left: 6px;
			width: 45%; 
			padding-right: 10px; 
			white-space: nowrap;
		}
		
		/*
		Label the data
		*/
		td:nth-of-type(1):before { content: "StudentId"; }
		td:nth-of-type(2):before { content: "Last Name"; }
		td:nth-of-type(3):before { content: "Job Title"; }
		td:nth-of-type(4):before { content: "Favorite Color"; }
		td:nth-of-type(5):before { content: "Wars of Trek?"; }
		td:nth-of-type(6):before { content: "Porn Name"; }
		td:nth-of-type(7):before { content: "Date of Birth"; }
		td:nth-of-type(8):before { content: "Dream Vacation City"; }
		td:nth-of-type(9):before { content: "GPA"; }
		td:nth-of-type(10):before { content: "Arbitrary Data"; }
	}
	
	/* Smartphones (portrait and landscape) ----------- */
	@media only screen
	and (min-device-width : 320px)
	and (max-device-width : 480px) {
		body { 
			padding: 0; 
			margin: 0; 
			width: 320px; }
		}
	
	/* iPads (portrait and landscape) ----------- */
	@media only screen and (min-device-width: 768px) and (max-device-width: 1024px) {
		body { 
			width: 495px; 
		}
	}
	
	</style>
	<!--<![endif]-->

</head>

<body>

	<header>
  <input id="f-size" type="number" min="12" max="36" value="18"/>
  --- Change root font size
	</header>

	<div id="page-wrap">

	<h1>Responsive Table</h1>
  
	<p>Go to <a href="index.html">Non-Responsive Table</a></p>
    
	<p>This is the exact same table, only has @media queries applied to is so that when the screen is too narrow, it reformats (via only CSS) to make each row a bit like it's own table. This makes for much more repetition and vertical space needed, but it fits within the horizontal space, so only natural vertical scrolling is needed to explore the data.</p>
    
	<table>
		<thead>
		<tr>
			<th>StudentId</th>
			<th>Name</th>
			<th>Gender</th>
			<th>Semester</th>
			<th>ClassName</th>
			<th>CultureId</th>
			<th>TeacherId</th>
			<th>Telephone</th>
			<th>Email</th>
		</tr>
		</thead>
		<tbody>5431·
		<?php
		for($rows = 0; $rows < $n; $rows++){?>
		<tr>
			<td><?php echo"$StudentId[$rows]"?></td>
			<td><?php echo"$Name[$rows]"?></td>
			<td><?php echo"$Gender[$rows]"?></td>
			<td><?php echo"$Semester[$rows]"?></td>
			<td><?php echo"$ClassName[$rows]"?></td>
			<td><?php echo"$TeacherId[$rows]"?></td>
			<td><?php echo"$Email[$rows]"?></td>
		</tr>
		<?php } ?>	
		</tbody>
	</table>
	
	</div>
		
</body>

</html>