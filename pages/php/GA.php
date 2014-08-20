<!DOCTYPE html>
<html lang="zh-cn">
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta name="description" content="">
    <meta name="author" content="">
    <!--<link rel="shortcut icon" href="../../docs-assets/ico/favicon.png">-->

    <title>BIA660 Final Project</title>

	<!-- CSS stylesheet -->
    <link href="../dist/css/bootstrap.css" rel="stylesheet">
    <link href="../css/framework.css" rel="stylesheet">
	
  </head>

  <body>

    <div class="container">
      <div class="header">
        <ul class="nav nav-pills pull-right" id="headtitle">
          <li class="title_btn active"><a href="../">Back</a></li>
        </ul>
        <h3 class="text-muted">BIA660 Web Analysis</h3>
		<h4 class="text-muted">Final Project</h4>
      </div>

      <div class="jumbotron" id="intro" style="min-height:553px">
        <h2 style="font-weight:bold">COURSE COMBINATION RESULT</h2>
<?php
	$course=array();
	$no=array();
	$con = mysql_connect("127.0.0.1","root","Stevens05");
	if (!$con)
	  {
	  die('Could not connect: ' . mysql_error());
	  }

	mysql_select_db("mocc", $con);
	if(isset($_GET["tags"])){
		$gettags = $_GET["tags"];
		if(isset($_GET["time"])){
		$time = $_GET["time"];}
		$tags = explode(",",$gettags);
		$max = 0;
		$sum=0;
		$min=100;
		if($_GET["self"]==="self"){
			while(count($tags)!==0){
			$res=mysql_query("SELECT * from Mocc_Course where Whole_Cost ='Self Paced'");
			while ($row =mysql_fetch_row($res)){
				$tags1= explode(",",$row[3]);
				$temp = array_intersect($tags,$tags1);
				if($max <count($temp)){
				$max = count($temp);
			    $temp1 = $temp;
				$ctemp=$row[0];
			}
					
				}   if($max===0){break;}
					else{$max=0;}
					array_push($course,$ctemp);
					$tags=array_diff($tags,$temp1);
					
					
				}
					
			   
			}
		
			$max = 0;
				while(count($tags)!==0){
				$res=mysql_query("SELECT * from Mocc_Course where Whole_Cost!='Self Paced'");
				while ($row =mysql_fetch_row($res)){
					$cost=str_replace(" Weeks","",$row[1]);
					$tags1= explode(",",$row[3]);
					$temp = array_intersect($tags,$tags1);
					if($max <count($temp)){
					$max = count($temp);
					$costmax=$cost;
				    $temp1 = $temp;
					$ctemp=$row[0];
					$min = $cost;
				}
				if($max ===count($temp)&&$min>$cost){
				$max = count($temp);
	            $costmax=$cost;
			    $temp1 = $temp;
				$ctemp=$row[0];
				$min=$cost;
			}
					
					}   if($max===0){break;}
						else{$max=0;}
						array_push($course,$ctemp);
						$tags=array_diff($tags,$temp1);
						$sum=$costmax+$sum;
						
					
					}
					
					if(count($tags)!==0){
						echo 
							"<h2 style='font-weight:bold; margin-top:115px'>No match found!</h2>";
					}else if(isset($time)){
						if($sum<=$time){
							if(!empty($course)){
								foreach($course as $key1=>$value1) {
									$res=mysql_query("SELECT * from Mocc_Course where Course_Name = '$value1'");
									$row =mysql_fetch_row($res);
									$dis_tag= explode(",",$row[3]);
									echo 
									"<form class='form-horizontal' role='form' style='margin-top:50px;text-align:left;border:2px solid #ffffff' method='get' action='test.php'>
										<div class='form-group'>
											<label for='tags' class='col-sm-2 control-label' style='width:37%'>Course name:</label>
											<div class='col-sm-6'>
												<p style='margin-top:16px'><h3>".$row[0]."</h3></p>
											</div>
										</div>
										<div class='form-group'>
											<label for='tags' class='col-sm-2 control-label' style='width:37%'>Estimate time:</label>
											<div class='col-sm-6'>
												<p style='margin-top:16px'><h3>".$row[1]."</h3></p>
											</div>
										</div>
										<div class='form-group'>
											<label for='tags' class='col-sm-2 control-label' style='width:37%'>Estimate effort:</label>
											<div class='col-sm-6'>
												<p style='margin-top:16px'><h3>".$row[2]."</h3></p>
											</div>
										</div>
										<div class='form-group'>
											<label for='tags' class='col-sm-2 control-label' style='width:37%'>Cover tags:</label>
											<div class='col-sm-6'>";
												foreach($dis_tag as $k => $v) {
													if($k === 0) {
														echo "<h3 style='margin-top:19px'>".$v."<br/></h3>";
													} else {
														echo "<h3 style='margin-top:0px'>".$v."<br/></h3>";
													}
												}
												echo "</div>
										</div>
									</form>";
								}
							}
						} else {
							echo 
							"<h2 style='font-weight:bold; margin-top:115px'>No match found with this time limit!</h2>";
						}
					} else {
						if(!empty($course)){
							foreach($course as $key1=>$value1) {
								$res=mysql_query("SELECT * from Mocc_Course where Course_Name = '$value1'");
								$row =mysql_fetch_row($res);
								$dis_tag= explode(",",$row[3]);
								echo 
								"<form class='form-horizontal' role='form' style='margin-top:50px;text-align:left;border:2px solid #ffffff' method='get' action='test.php'>
										<div class='form-group'>
											<label for='tags' class='col-sm-2 control-label' style='width:37%'>Course name:</label>
											<div class='col-sm-6'>
												<p style='margin-top:16px'><h3>".$row[0]."</h3></p>
											</div>
										</div>
										<div class='form-group'>
											<label for='tags' class='col-sm-2 control-label' style='width:37%'>Estimate time:</label>
											<div class='col-sm-6'>
												<p style='margin-top:16px'><h3>".$row[1]."</h3></p>
											</div>
										</div>
										<div class='form-group'>
											<label for='tags' class='col-sm-2 control-label' style='width:37%'>Estimate effort:</label>
											<div class='col-sm-6'>
												<p style='margin-top:16px'><h3>".$row[2]."</h3></p>
											</div>
										</div>
										<div class='form-group'>
											<label for='tags' class='col-sm-2 control-label' style='width:37%'>Cover tags:</label>
											<div class='col-sm-6'>";
												foreach($dis_tag as $k => $v) {
													if($k === 0) {
														echo "<h3 style='margin-top:19px'>".$v."<br/></h3>";
													} else {
														echo "<h3 style='margin-top:0px'>".$v."<br/></h3>";
													}
												}
												echo "</div>
										</div>
								</form>";
							}
						}
					}
			  } 
?>
      </div>

      <div class="footer">
        <p>&copy; Team3</p>
		<p>Fei Feng, Yi Wang, Changshuo Gao, Xin Sun, Fangzhou Yan</p>
      </div>

    </div> <!-- /container -->
  </body>
</html>
