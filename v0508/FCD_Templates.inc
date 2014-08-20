<?php

/**
 *
 *
 * @version $Id$
 * @copyright 2005
 **/

/**
 *
 * @name 		GetWebSite
 * @args 		2
 *					arg[0] = section_id
 *					arg[1] = language_nmbr
 * @return	website template
 * @desc		
 *
 **/
function GetWebSite($pSubjectID, $pLanguageNmbr, $pSectionNmbr, $pSubtask, $pHtmlUrl)
{
	$menuarray = GetSubMenu('ALBUM');
?>
	<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
	<html>
	<head>
	<title><?php if ($pLanguageNmbr == 1) echo '芳草地中文学校'; else echo 'FCD Chinese School'; ?></title>
	<meta http-equiv="Content-Type" content="text/html" charset="UTF-8">
	<link rel="stylesheet" type="text/css" href="stylesheet/fcd.css" />
	<script src="./javascript/FCD.js"></script>
	<script language="JavaScript" src="./javascript/mm_menu.js"></script>
	<script language="JavaScript" src="./javascript/hash.js"></script>

	<SCRIPT LANGUAGE="JavaScript">
	var n = 0;
	
	timedelay = 5;
	timedelay *= 1000;
	
	var imgs = new Array();
	imgs[0] = "./images/csl.jpg";
	imgs[1] = "./images/kingdergarten.jpg";
	imgs[2] = "./images/contest.jpg";
	imgs[3] = "./images/abacus.jpg";

	function newColor(id, color) { 
		document.getElementById(id).style.background=color;
	}
	
	function rotate() {
		if (document.picform) {
			document.picform.slideshow.src = imgs[n];
			(n == (imgs.length - 1)) ? n = 0 : n++;
			window.setTimeout("rotate()", timedelay);
		}
	}

	function LoadMenus() {
		window.chineseteachingmenu_C = new Menu("root",140,20,"Arial, Helvetica, sans-serif",12,"#FFFFFF","#005A00","#589201","#93C203","center","middle",3,1,100,-5,7,true,true,true,0,true,true);
		chineseteachingmenu_C.addMenuItem("学生作文","location='./fcdschool.php?subjectid=STUDENTWORK&languagenmbr=1'");
		chineseteachingmenu_C.addMenuItem("教学体会","location='./fcdschool.php?subjectid=TEACHING&languagenmbr=1'");
		chineseteachingmenu_C.addMenuItem("儿童教育论坛","location='./fcdschool.php?subjectid=FORUM&languagenmbr=1'");
		chineseteachingmenu_C.addMenuItem("家长信箱","location='./fcdschool.php?subjectid=PARENTMAILBOX&languagenmbr=1'");
		chineseteachingmenu_C.fontWeight="normal";
		chineseteachingmenu_C.hideOnMouseOut=true;
		chineseteachingmenu_C.bgColor='#ffffff';
		chineseteachingmenu_C.menuBorder=1;
		chineseteachingmenu_C.menuLiteBgColor='#ffffff';
		chineseteachingmenu_C.menuBorderBgColor='#ffffff';

		window.homeworkmenu_C = new Menu("root",140,20,"Arial, Helvetica, sans-serif",12,"#FFFFFF","#005A00","#589201","#93C203","center","middle",3,1,100,-5,7,true,true,true,0,true,true);
		homeworkmenu_C.addMenuItem("CSL","location='./fcdschool.php?subjectid=CSLHOMEWORK&languagenmbr=1'");
		homeworkmenu_C.addMenuItem("成绩单","location='./fcdschool.php?subjectid=GRADEREPORT&subtask=login&languagenmbr=1'");
		homeworkmenu_C.addMenuItem("","location=''");
		homeworkmenu_C.fontWeight="normal";
		homeworkmenu_C.hideOnMouseOut=true;
		homeworkmenu_C.bgColor='#ffffff';
		homeworkmenu_C.menuBorder=1;
		homeworkmenu_C.menuLiteBgColor='#ffffff';
		homeworkmenu_C.menuBorderBgColor='#ffffff';

		window.homeworkmenu_E = new Menu("root",140,20,"Arial, Helvetica, sans-serif",12,"#FFFFFF","#005A00","#589201","#93C203","center","middle",3,1,100,-5,7,true,true,true,0,true,true);
		homeworkmenu_E.addMenuItem("CSL","location='./fcdschool.php?subjectid=CSLHOMEWORK&languagenmbr=2'");
		homeworkmenu_E.addMenuItem("Grade Report","location='./fcdschool.php?subjectid=GRADEREPORT&subtask=login&languagenmbr=2'");
		homeworkmenu_E.addMenuItem("","location=''");
		homeworkmenu_E.fontWeight="normal";
		homeworkmenu_E.hideOnMouseOut=true;
		homeworkmenu_E.bgColor='#ffffff';
		homeworkmenu_E.menuBorder=1;
		homeworkmenu_E.menuLiteBgColor='#ffffff';
		homeworkmenu_E.menuBorderBgColor='#ffffff';


		window.photomenu_C = new Menu("root",140,20,"Arial, Helvetica, sans-serif",12,"#FFFFFF","#005A00","#589201","#93C203","center","middle",3,1,100,-5,7,true,true,true,0,true,true);
<?php
	for ($i = 0; $i < sizeof($menuarray); $i++) {
?>
		photomenu_C.addMenuItem("<?php echo $menuarray[$i]['Subject_C']; ?>","location='./fcdschool.php?subjectid=<?php echo $menuarray[$i]['SubjectID']; ?>&languagenmbr=1'");
<?php
	}
?>
		photomenu_C.fontWeight="normal";
		photomenu_C.hideOnMouseOut=true;
		photomenu_C.bgColor='#ffffff';
		photomenu_C.menuBorder=1;
		photomenu_C.menuLiteBgColor='#ffffff';
		photomenu_C.menuBorderBgColor='#ffffff';



		window.photomenu_E = new Menu("root",160,20,"Arial, Helvetica, sans-serif",12,"#FFFFFF","#005A00","#589201","#93C203","center","middle",3,1,100,-5,7,true,true,true,0,true,true);
<?php
	for ($i = 0; $i < sizeof($menuarray); $i++) {
?>
		photomenu_E.addMenuItem("<?php echo substr($menuarray[$i]['Subject_E'], 8); ?>","location='./fcdschool.php?subjectid=<?php echo $menuarray[$i]['SubjectID']; ?>&languagenmbr=2'");
<?php
	}
?>
		photomenu_E.fontWeight="normal";
		photomenu_E.hideOnMouseOut=true;
		photomenu_E.bgColor='#ffffff';
		photomenu_E.menuBorder=1;
		photomenu_E.menuLiteBgColor='#ffffff';
		photomenu_E.menuBorderBgColor='#ffffff';
	
		photomenu_E.writeMenus();
	}

	function findLeftOffset(obj) {
		var left_offset = 0;
		if (obj.offsetParent) {
			left_offset = obj.offsetLeft
			while (obj = obj.offsetParent) { left_offset += obj.offsetLeft }
		}
		return left_offset;
	}
	
	function findTopOffset(obj) {
		var top_offset = 0;
		if (obj.offsetParent) {
			top_offset = obj.offsetTop
			while (obj = obj.offsetParent) { top_offset += obj.offsetTop }
		}
		return top_offset;
	}
	</script>


	</head>
	<body topmargin="0"  leftmargin="0" marginwidth="0" marginheight="0" onLoad="rotate();">
	<script language="JavaScript1.2">LoadMenus();</script>
		<!-- div style="line-height:10px;">&nbsp;</div-->
		<!-- ***************************************** -->
		<!--							Content Box   							 -->
		<!-- ***************************************** -->
		<table border="0" width="750" align="left" cellspacing="0" cellpadding="0" bgcolor="#E9FFEB" class="lefttoprightborder">
			<tr>
				<td>
					<!-- ***************************************** -->
					<!--								Frame_1										 -->
					<!-- ***************************************** -->
					<table border="0" width="750" height="725" align="center" cellspacing="0" cellpadding="0" bgcolor="#E9FFEB" class="lefttoprightborder">
						<tr>
							<!-- ***************************************** -->
							<!--								Frame_2										 -->
							<!-- ***************************************** -->
<?php 
	if ($pSubjectID != "REGIST"
	|| ($pSubjectID == "REGIST" && ($pSubtask == 'main' || $pSubtask == 'login' || $pSubtask == 'cancel' || (getSession('FamilyNmbr', 0) == '' && $pSubtask == 'summary')))
	) {
?>
							<td width="150" align="center" valign="top">
								<img src="./images/FCD_Logo.jpg" border="0"/>
								<p/>
								<table border="0" width="140" cellspacing="0" cellpadding="0">
									<tr>
										<td align="center" class="labelfont">
										<?php 
										if ($pLanguageNmbr == 1) { 
										?>
											<a href="fcdschool.php?languagenmbr__=2">English</a>
											&nbsp;&nbsp;
											中文
										<?php 
										} else { 
										?>
											English
											&nbsp;&nbsp;
											<a href="fcdschool.php?languagenmbr__=1">中文</a>
										<?php 
										} 
										?>
										</td>
									</tr>
								</table>
								<table border="0" width="140" height="280" cellspacing="0" cellpadding="0" class="doubleborder">
									<tr align="center">
										<td width="140" align="center" border="1" valign="top" class="leftpanel">
											<br/><br/><br/>
											<?php 
											if ($pLanguageNmbr == 1) { 
												GetTemplate_ChineseLP1();
											}	else {
												GetTemplate_EnglishLP1();
											}
											?>
										</td>
									</tr>
								</table>
								<p/>
								<table border="0" width="140" height="90" cellspacing="0" cellpadding="0" class="doubleborder">
									<tr align="center">
										<td width="140" align="center" border="1" valign="top" class="leftpanel">
											<br/><br/><br/>
											<?php 
											if ($pLanguageNmbr == 1) { 
												GetTemplate_ChineseLP2();
											}	else {
												GetTemplate_EnglishLP2();
											}
											?>
										</td>
									</tr>
								</table>
								<p/>
<?php 
		if ($pLanguageNmbr == 1) {
?>
								<table border="0" width="140" height="140" cellspacing="0" cellpadding="0" class="singleborder">
									<tr height="35" align="center">
										<td align="center" class="smalltitlefont">
											<font size="2" color="#589201"><b>相关网站</b></font>
										</td>
									</tr>
									<tr>
										<td align="center">
											<a href="http://www.mychineseschool.com" target=_ class="linkfont">斯坦福中文学校</a><br/>
											<a href="http://www.newconcept.com" target=_ class="linkfont">新意中文学校</a><br/>
											<a href="http://www.yinghua.org" target=_ class="linkfont">英华语言学校</a><br/>
											<a href="http://www.chineseon.net" target=_ class="linkfont">中国上网</a><br/>
											<a href="http://www.shuku.net" target=_ class="linkfont">亦凡公益图书馆</a><br/>
											<a href="http://www.educasian.com" target=_ class="linkfont">东方教育</a><br/>
											<a href="http://www.pep.com.cn" target=_ class="linkfont">人民教育出版社</a><br/>
											<a href="http://www.nyconsulate.prchina.org" target=_ class="linkfont">中国驻纽约总领事馆</a><br/>
										</td>
									</tr>
									<tr>
										<td>&nbsp;</td>
									</tr>
								</table>
<?php 
		}
		else {
?>
								<table border="0" width="140" height="140" cellspacing="0" cellpadding="0" class="singleborder">
									<tr height="35" align="center">
										<td align="center" class="smalltitlefont">
											<font size="2" color="#589201"><b>Related Links</b></font>
										</td>
									</tr>
									<tr>
										<td align="center">
											<a href="http://www.mychineseschool.com" target=_ class="linkfont2">Stanford Chinese School</a><br/>
											<a href="http://www.newconcept.com" target=_ class="linkfont2">New Concept Chinese School</a><br/>
											<a href="http://www.yinghua.org" target=_ class="linkfont2">YingHua Language School</a><br/>
											<a href="http://www.chineseon.net" target=_ class="linkfont2">ChineseOn.net</a><br/>
											<a href="http://www.shuku.net" target=_ class="linkfont2">YiFan Public Library</a><br/>
											<a href="http://www.educasian.com" target=_ class="linkfont2">EducAsian</a><br/>
											<a href="http://www.pep.com.cn" target=_ class="linkfont2">People&acute;s Education Press</a><br/>
											<!-- http://www.nyconsulate.prchina.org -->
											<a href="./php_reader/phpExcelReader/example.php" target=_ class="linkfont2">Chinese Consulate (New York)</a><br/>
										</td>
									</tr>
									<tr>
										<td>&nbsp;</td>
									</tr>
								</table>
<?php 
		}
?>
							</td>
<?php 
	}
?>
							<!-- ***************************************** -->
							<!--								Frame_3										 -->
							<!-- ***************************************** -->
<?php 
	if ($pSubjectID == "REGIST"
			&& $pSubtask != 'main' 
			&& $pSubtask != 'login' 
			&& $pSubtask != 'cancel' 
			&& !(getSession('FamilyNmbr', 0) == '' && $pSubtask == 'summary')
		) { 
?>
							<td width="750" align="center" valign="top">
								<table width="750" align="center" border="0" cellspacing="0" cellpadding="0">
									<tr>
										<td width="180" height="80" align="center" class="adsfont">
											<img src="./images/FCD_Logo2.jpg"/>
										</td>
										<td width="470" height="80" align="center" class="adsfont">
											<table border="0" width="460" cellspacing="0" cellpadding="0">
												<tr>
													<td width="460" height="70" align="left" valign="bottom" class="adsfont">
														<img src="./images/ads3.jpg"/>
														<br/>
													</td>
												</tr>
											</table>
										</td>
									</tr>
								</table>
								<table border="0" cellspacing="0" cellpadding="0">
									<tr bgcolor="#009900">
										<td width="700" height="2" align="center" />
									</tr>
									<tr>
										<td width="700" height="1" align="center" />
									</tr>
									<tr bgcolor="#009900">
										<td width="700" height="1" align="center" />
									</tr>
								</table>
<?php 
	}
	else {
?>
							<td width="600" align="center" valign="top">
								<table border="0" width="460" cellspacing="0" cellpadding="0">
									<tr>
										<td width="460" height="70" align="left" valign="bottom" class="adsfont">
											<img src="./images/ads3.jpg"/>
											<br/>
										</td>
									</tr>
								</table>
								<table border="0" cellspacing="0" cellpadding="0">
									<tr bgcolor="#009900">
										<td width="500" height="2" align="center" />
									</tr>
									<?php
										GetTemplate(4, $pSubjectID, $pSectionNmbr, $pLanguageNmbr, "");
									?>
									<tr bgcolor="#009900">
										<td width="500" height="1" align="center" />
									</tr>
								</table>
<?php 
	}
?>
								<br/><br/>
								<table border="0" cellspacing="0" cellpadding="0">
									<tr>
										<td align="center" border="1" valign="top" class="leftpanel">
											<?php
											switch ($pSubjectID) {
												case "REGIST":
													GetTemplate_REG($pSubtask, $pLanguageNmbr);
													break;
												case "GRADEREPORT":
													GetTemplate_GRD($pSubtask, $pLanguageNmbr);
													break;
												case "HTML":
													GetTemplate_HTML($pHtmlUrl);
													break;
												case "HOME":
													GetTemplate(3, $pSubjectID, $pSectionNmbr, $pLanguageNmbr, "");
													_GetLeafImage();
													break;
												case "PERSONNEL":
													_GetHeading($pSubjectID, $pLanguageNmbr);
													GetTemplate(3, $pSubjectID, $pSectionNmbr, $pLanguageNmbr, "");
													break;
												default:
													GetTemplate(3, $pSubjectID, $pSectionNmbr, $pLanguageNmbr, $menuarray);
											}
											?>
										</td>
									</tr>
								</table>
							</td>
						</tr>
					</table>
<?php 
	if ($pSubjectID == 'HOME') { 
?>
					<table border="0" width="750" height="25" align="center" cellspacing="0" cellpadding="0" bgcolor="#E9FFEB" class="leftrightborder">
						<tr>
							<td align="center" valign="bottom" class="topaddressfont">
								<font color="#719601">
									<?php if ($pLanguageNmbr == 1) echo '学校地址:'; else echo 'School Address:'; ?>
									&nbsp;&nbsp;15 Cornell Street, Edison, NJ 08817
									<br/>
									<?php if ($pLanguageNmbr == 1) echo '邮寄地址:'; else echo 'Mailing Address:'; ?>
									&nbsp;&nbsp;P. O. Box 10453, New Brunswick, NJ 08906
								</font>
								<br/>
							</td>
						</tr>
					</table>
<?php 
	}
	else { 
?>
					<table border="0" width="750" height="25" align="center" cellspacing="0" cellpadding="0" bgcolor="#E9FFEB">
						<tr>
							<td>&nbsp;</td>
						</tr>
					</table>
<?php 
	}
?>
					<!-- ***************************************** -->
					<!--								Frame_5										 -->
					<!-- ***************************************** -->
					<table width="750" border="0" cellspacing="0" align="center" cellpadding="0" bgcolor="#E9FFEB" class="leftbottomrightborder">
<?php 
	if ($pSubjectID == 'HOME') { 
?>
						<tr>
							<td width="15">&nbsp;</td>
							<td width="720" class="fineprintfont">
								<hr/>
								FCD Chinese School admits students of any race, color, gender, national and ethnic origin to all the rights, 
								privileges, programs, and activities generally accorded or made available to students at the school. It does 
								not discriminate on the basis of race, color, national and ethnic origin in administration of its educational 
								policies, admissions policies, scholarship and loan programs, and athletic and other school-administered programs. 
							</td>
							<td width="15">&nbsp;</td>
						</tr>
<?php 
	}
?>
						<tr>
							<td width="15">&nbsp;</td>
<?php 
	if ($pSubjectID != 'HOME') { 
?>
							<td width="720" height="78" align="center" valign="bottom">
								<hr/>
<?php 
	}
	else {
?>
							<td width="720" align="center">
<?php 
	}
?>
								<?php if ($pLanguageNmbr == 1) { ?>
								<font size="2" color="#009900">&copy; 版权所有 芳草地中文学校</font>
								<?php } else { ?>
								<font size="2" color="#009900">&copy; All rights reserved. &nbsp; FCD Chinese School</font>
								<?php } ?>
							</td>
							<td width="15">&nbsp;</td>
						</tr>
						<tr>
							<td>&nbsp;</td>
							<td>&nbsp;</td>
							<td>&nbsp;</td>
						</tr>
					</table>
				</td>
			</tr>
		</table>
		<div>&nbsp;</div>
<div align="center" style="position:absolute;width:160px;height:auto;left:763px;top:6px;line-height:15px;padding:4;color:#606000;border:solid 1px #606000;background-color:E9FFEB;">
			
			<span style="font-size:14px;font-weight:bolder;"><?php if($pLanguageNmbr == 1) echo '布告栏' ; else echo 'Notice';?></span>
			<br>
			<br>
		<?php
									GetTemplate(5, $pSubjectID, $pSectionNmbr, $pLanguageNmbr, "");
									?>
		<div style="width:135px;height:10;">&nbsp;</div>
				 
</div>
<div id="LCS_C4CFC0DE_134F_4466_B2A2_FF7C59A8BFAD_communicationDiv" lcs_c4cfc0de_134f_4466_b2a2_ff7c59a8bfad_valuename="WSG_status" lcs_c4cfc0de_134f_4466_b2a2_ff7c59a8bfad_valueresult="active|||8641369747818005">
					</div>	
	</body>
	</html>
<?php
}

/**
 *
 * @name 		GetTemplate_EnglishLP1
 * @args 		2
 *					arg[0] = url
 *					arg[1] = url_text
 * @return	template
 * @desc		left panel links
 *
 **/
function GetTemplate_EnglishLP1()
{
?>
							<table border="0" width="110" height="21" <?php _GetButtonColor('HOME'); ?> cellspacing="0" cellpadding="0" class="thinborder">
								<tr>
									<td align="center"><a href="./fcdschool.php?subjectid=HOME&languagenmbr=2"><font color="white" size="2">Home</font></a></td>
								</tr>
							</table>
							<br/>
							<table border="0" width="110" height="21" <?php _GetButtonColor('NEWS'); ?> cellspacing="0" cellpadding="0" class="thinborder">
								<tr>
									<td align="center"><a href="./fcdschool.php?subjectid=NEWS&languagenmbr=2"><font color="white" size="2">News</font></a></td>
								</tr>
							</table>
							<br/>
							<table border="0" width="110" height="21" <?php _GetButtonColor('REGIST'); ?> cellspacing="0" cellpadding="0" class="thinborder">
								<tr>
									<td align="center"><a href="./fcdschool.php?subjectid=REGIST&subtask=main&languagenmbr=2"><font color="white" size="2">Registration</font></a></td>
								</tr>
							</table>
							<br/>
							<table border="0" width="110" height="21" <?php _GetButtonColor('CLASSINFO'); ?> cellspacing="0" cellpadding="0" class="thinborder">
								<tr>
									<td align="center"><a href="./fcdschool.php?subjectid=CLASSINFO&languagenmbr=2"><font color="white" size="2">Class Info</font></a></td>
								</tr>
							</table>
							<br/>
							<table border="0" width="110" height="21" <?php _GetButtonColor('School_calendar-2013-2014_E.html'); ?> cellspacing="0" cellpadding="0" class="thinborder">
								<tr>
									<td align="center"><a href="./fcdschool.php?subjectid=HTML&languagenmbr=2&htmlfile=School_calendar-2013-2014_E.html"><font color="white" size="2">School Calendar</font></a></td>
								</tr>
							</table>
							<br/>
							
							<table border="0" width="110" height="21" <?php _GetButtonColor('Donations_E.html'); ?> cellspacing="0" cellpadding="0" class="thinborder">
								<tr>
									<td align="center"><a href="./fcdschool.php?subjectid=HTML&languagenmbr=2&htmlfile=Donations_E.html"><font color="white" size="2">Donations</font></a></td>
								</tr>
							</table>
							<br/>
							<table border="0" width="110" height="21" <?php _GetButtonColor('Sponsors_E.html'); ?> cellspacing="0" cellpadding="0" class="thinborder">
								<tr>
									<td align="center"><a href="./fcdschool.php?subjectid=HTML&languagenmbr=2&htmlfile=Sponsors_E.html"><font color="white" size="2">Sponsors</font></a></td>
								</tr>
							</table>
							<br/>
							<table border="0" width="110" height="21" <?php _GetButtonColor('DrivingDirection.html'); ?> cellspacing="0" cellpadding="0" class="thinborder">
								<tr>
									<td align="center"><a href="./fcdschool.php?subjectid=HTML&languagenmbr=2&htmlfile=DrivingDirection.html"><font color="white" size="2">Directions</font></a></td>
								</tr>
							</table>
							<br/>
							<table border="0" width="110" height="21" <?php _GetButtonColor('Contact_E.html'); ?> cellspacing="0" cellpadding="0" class="thinborder">
								<tr>
									<td align="center"><a href="./fcdschool.php?subjectid=HTML&languagenmbr=2&htmlfile=Contact_E.html"><font color="white" size="2">Contact Us</font></a></td>
								</tr>
							</table>
							<br/>
<?php
}

/**
 *
 * @name 		GetTemplate_EnglishLP2
 * @args 		2
 *					arg[0] = url
 *					arg[1] = url_text
 * @return	template
 * @desc		left panel links
 *
 **/
function GetTemplate_EnglishLP2()
{
?>
							<br/>
							<table id="e_lp2-1" border="0" width="110" height="21" <?php _GetButtonColor('HOMEWORK'); ?> cellspacing="0" cellpadding="0" class="thinborder">
								<tr>
									<td align="center" id="y" onMouseOut="newColor('y', '#589201');MM_startTimeout();" 
									onMouseOver="
									var lp = findLeftOffset(document.getElementById('e_lp2-1')) + 110;
									var tp = findTopOffset(document.getElementById('e_lp2-1'));
									newColor('y', '#93C203');MM_showMenu(window.homeworkmenu_E,lp,tp,null,'');">
										<a href="<?php echo $_SERVER['REQUEST_URI']; ?>"><font color="white" size="2">Homework/Grade</font></a>
									</td>
								</tr>
							</table>
							<br/>
							<table id="e_lp2-2" border="0" width="110" height="21" <?php _GetButtonColor('ALBUM'); ?> cellspacing="0" cellpadding="0" class="thinborder">
								<tr>
									<td align="center" id="x" onMouseOut="newColor('x', '#589201');MM_startTimeout();" 
									onMouseOver="
									var lp = findLeftOffset(document.getElementById('e_lp2-2')) + 110;
									var tp = findTopOffset(document.getElementById('e_lp2-2'));
									newColor('x', '#93C203');MM_showMenu(window.photomenu_E,lp,tp,null,'');">
										<a href="<?php echo $_SERVER['REQUEST_URI']; ?>"><font color="white" size="2">Photo Album</font></a>
									</td>
								</tr>
							</table>
							<br/>
							<table border="0" width="110" height="21" <?php _GetButtonColor('PERSONNEL'); ?> cellspacing="0" cellpadding="0" class="thinborder">
								<tr>
									<td align="center"><a href="./fcdschool.php?subjectid=PERSONNEL&languagenmbr=2"><font color="white" size="2">Administration</font></a></td>
								</tr>
							</table>
							<br/>
<?php
}

/**
 *
 * @name 		GetTemplate_ChineseLP1
 * @args 		none
 * @return	template
 * @desc		left panel links
 *
 **/
function GetTemplate_ChineseLP1()
{
?>
							<table border="0" width="110" height="21" <?php _GetButtonColor('HOME'); ?> cellspacing="0" cellpadding="0" class="thinborder">
								<tr>
									<td align="center"><a href="./fcdschool.php?subjectid=HOME&languagenmbr=1"><font color="white" size="2">主页</font></a></td>
								</tr>
							</table>
							<br/>
							<table border="0" width="110" height="21" <?php _GetButtonColor('NEWS'); ?> cellspacing="0" cellpadding="0" class="thinborder">
								<tr>
									<td align="center"><a href="./fcdschool.php?subjectid=NEWS&languagenmbr=1"><font color="white" size="2">新闻报道</font></a></td>
								</tr>
							</table>
							<br/>
							<table border="0" width="110" height="21" <?php _GetButtonColor('CLASSINFO'); ?> cellspacing="0" cellpadding="0" class="thinborder">
								<tr>
									<td align="center"><a href="./fcdschool.php?subjectid=CLASSINFO&languagenmbr=1"><font color="white" size="2">课程简介</font></a></td>
								</tr>
							</table>
							<br/>
							<table border="0" width="110" height="21" <?php _GetButtonColor('School_calendar-2013-2014_C.html'); ?> cellspacing="0" cellpadding="0" class="thinborder">
								<tr>
									<td align="center"><a href="./fcdschool.php?subjectid=HTML&languagenmbr=1&htmlfile=School_calendar-2013-2014_C.html"><font color="white" size="2">校历</font></a></td>
								</tr>
							</table>
							<br/>
							<table border="0" width="110" height="21" <?php _GetButtonColor('REGIST'); ?> cellspacing="0" cellpadding="0" class="thinborder">
								<tr>
									<td align="center"><a href="./fcdschool.php?subjectid=REGIST&subtask=main&languagenmbr=1"><font color="white" size="2">报名注册</font></a></td>
								</tr>
							</table>
							<br/>
							<table border="0" width="110" height="21" <?php _GetButtonColor('SAT'); ?> cellspacing="0" cellpadding="0" class="thinborder">
								<tr>
									<td align="center"><a href="./fcdschool.php?subjectid=SAT&languagenmbr=1"><font color="white" size="2">SAT 课程</font></a></td>
								</tr>
							</table>
							<br/>
							
							<table border="0" width="110" height="21" <?php _GetButtonColor('DrivingDirection.html'); ?> cellspacing="0" cellpadding="0" class="thinborder">
								<tr>
									<td align="center"><a href="./fcdschool.php?subjectid=HTML&languagenmbr=1&htmlfile=DrivingDirection.html"><font color="white" size="2">学校地址</font></a></td>
								</tr>
							</table>
							<br/>
							<table border="0" width="110" height="21" <?php _GetButtonColor('PERSONNEL'); ?> cellspacing="0" cellpadding="0" class="thinborder">
								<tr>
									<td align="center"><a href="./fcdschool.php?subjectid=PERSONNEL&languagenmbr=1"><font color="white" size="2">校务人员</font></a></td>
								</tr>
							</table>
							<br/>
							<table border="0" width="110" height="21" <?php _GetButtonColor('Contact_C.html'); ?> cellspacing="0" cellpadding="0" class="thinborder">
								<tr>
									<td align="center"><a href="./fcdschool.php?subjectid=HTML&languagenmbr=1&htmlfile=Contact_C.html"><font color="white" size="2">与我们联系</font></a></td>
								</tr>
							</table>
							<br/>
							<table border="0" width="110" cellspacing="0" cellpadding="0" class="noborder">
								<tr>
									<td align="center">&nbsp;</td>
								</tr>
							</table>
							<br/>
<?php
}

/**
 *
 * @name 		GetTemplate_ChineseLP2
 * @args 		none
 * @return	template
 * @desc		left panel links
 *
 **/
function GetTemplate_ChineseLP2()
{
?>
							<br/>
							<table id="c_lp2-1" border="0" width="110" height="21" <?php _GetButtonColor('CHINESETEACHING'); ?> cellspacing="0" cellpadding="0" class="thinborder">
								<tr>
									<td align="center" id="x" onMouseOut="newColor('x', '#589201');MM_startTimeout();" 
									onMouseOver="
									var lp = findLeftOffset(document.getElementById('c_lp2-1')) + 110;
									var tp = findTopOffset(document.getElementById('c_lp2-1'));
									newColor('x', '#93C203');MM_showMenu(window.chineseteachingmenu_C,lp,tp,null,'');">
										<a href="<?php echo $_SERVER['REQUEST_URI']; ?>"><font color="white" size="2">中文教学园地</font></a>
									</td>
								</tr>
							</table>
							<br/>
							<table id="c_lp2-2" border="0" width="110" height="21" <?php _GetButtonColor('HOMEWORK'); ?> cellspacing="0" cellpadding="0" class="thinborder">
								<tr>
									<td align="center" id="y" onMouseOut="newColor('y', '#589201');MM_startTimeout();" 
									onMouseOver="
									var lp = findLeftOffset(document.getElementById('c_lp2-2')) + 110;
									var tp = findTopOffset(document.getElementById('c_lp2-2'));
									newColor('y', '#93C203');MM_showMenu(window.homeworkmenu_C,lp,tp,null,'');">
										<a href="<?php echo $_SERVER['REQUEST_URI']; ?>"><font color="white" size="2">家庭作业/成绩单</font></a>
									</td>
								</tr>
							</table>
							<br/>
							<table id="c_lp2-3" border="0" width="110" height="21" <?php _GetButtonColor('ALBUM'); ?> cellspacing="0" cellpadding="0" class="thinborder">
								<tr>
									<td align="center" id="z" onMouseOut="newColor('z', '#589201');MM_startTimeout();" 
									onMouseOver="
									var lp = findLeftOffset(document.getElementById('c_lp2-3')) + 110;
									var tp = findTopOffset(document.getElementById('c_lp2-3'));
									newColor('z', '#93C203');MM_showMenu(window.photomenu_C,lp,tp,null,'');">
										<a href="<?php echo $_SERVER['REQUEST_URI']; ?>"><font color="white" size="2">芳草地影集</font></a>
									</td>
								</tr>
							</table>
							<br/>
<?php
}

/**
 *
 * @name 		GetTemplate
 * @args 		2
 *					arg[0] = title
 *					arg[1] = text_content
 * @return	template
 * @desc		title + text
 *
 **/
function GetTemplate($pFrameNmbr, $pSubjectID, $pSectionNmbr, $pLanguageNmbr, $pSubmenuArray)
{
	switch ($pFrameNmbr) {
		case 3:
			$sectionset = GetSection($pFrameNmbr, $pSubjectID, $pSectionNmbr, $pLanguageNmbr);
			if (sizeof($sectionset) > 0) {
				if (_BelongToGroup($pSubjectID, 'ALBUM')) {
					GetTemplate_310($pSubjectID, $sectionset, $pLanguageNmbr, $pSubmenuArray);
				}
				elseif ($pSubjectID == 'STUDENTWORK') {
					GetTemplate_LIST($pSubjectID, $sectionset, $pLanguageNmbr);
				}
				elseif ($pSubjectID == 'FORUM') {
					GetTemplate_LIST($pSubjectID, $sectionset, $pLanguageNmbr);
				}
				elseif ($pSubjectID == 'TEACHING') {
					GetTemplate_LIST($pSubjectID, $sectionset, $pLanguageNmbr);
				}
				elseif ($pSubjectID == 'PARENTMAILBOX') {
					GetTemplate_LIST($pSubjectID, $sectionset, $pLanguageNmbr);
				}
				elseif ($pSubjectID == 'NEWS') {
					GetTemplate_LIST($pSubjectID, $sectionset, $pLanguageNmbr);
				}
				elseif ($pSubjectID == 'SAT') {
					GetTemplate_LIST($pSubjectID, $sectionset, $pLanguageNmbr);
				}
				elseif ($pSubjectID == 'CSLHOMEWORK') {
					GetTemplate_HOMEWORK($pSubjectID, $sectionset, $pLanguageNmbr);
				}
				else {
					// loop through all sections for this subject
					for ($i = 0; $i < sizeof($sectionset); $i++) {
						$sectionnmbr = $sectionset[$i]['SectionNmbr'];
						$sectiontypenmbr = $sectionset[$i]['SectionTypeNmbr'];
						$itemset = GetItem($sectionnmbr);
						if (sizeof($itemset) > 0) {
							for ($k = 0; $k < sizeof($itemset); $k++) {
								// populate all item content variables for this section
								${'item_' . $itemset[$k]['Type']} = stripslashes($itemset[$k]['Content']);
							}
							// call template for each section type
							switch ($sectiontypenmbr) {
								case 301:
									if (!isset($item_subtitle)) $item_subtitle = "";
									GetTemplate_301($pSubjectID, $item_title, $item_subtitle, $item_fullcontent, $pLanguageNmbr);
									break;
								case 302:
									if (!isset($item_subtitle)) $item_subtitle = "";
									GetTemplate_302($pSubjectID, $item_title, $item_subtitle, $item_abstract, $item_fullcontenturl, $pLanguageNmbr);
									break;
								case 303:
									if (!isset($item_subtitle)) $item_subtitle = "";
									GetTemplate_303($pSubjectID, $item_title, $item_subtitle, $item_image, $pLanguageNmbr);
									break;
								case 304:
									if (!isset($item_subtitle)) $item_subtitle = "";
									GetTemplate_304($pSubjectID, $item_title, $item_subtitle, $item_image, $item_fullcontent, $pLanguageNmbr);
									break;
								case 305:
									if (!isset($item_subtitle)) $item_subtitle = "";
									GetTemplate_305($pSubjectID, $item_title, $item_subtitle, $item_thumbnail, $item_fullimageurl, $item_fullcontent, $pLanguageNmbr);
									break;
								case 306:
									if (!isset($item_subtitle)) $item_subtitle = "";
									GetTemplate_306($pSubjectID, $item_title, $item_subtitle, $item_image, $item_abstract, $item_fullcontenturl, $pLanguageNmbr);
									break;
								case 307:
									if (!isset($item_subtitle)) $item_subtitle = "";
									GetTemplate_307($pSubjectID, $item_title, $item_subtitle, $item_thumbnail, $item_fullimageurl, $item_abstract, $item_fullcontenturl, $pLanguageNmbr);
									break;
								case 308:
									if (!isset($item_subtitle)) $item_subtitle = "";
									GetTemplate_308($pSubjectID, $item_title, $item_subtitle, $item_url, $item_urltext, $pLanguageNmbr);
									break;
								case 309:
									if (!isset($item_subtitle)) $item_subtitle = "";
									GetTemplate_309($pSubjectID, $item_url, $item_urltext, $pLanguageNmbr);
									break;
								case 901: // full content
									if (!isset($item_subtitle)) $item_subtitle = "";
									if (!isset($item_fullcontent)) $item_fullcontent = "";
									if (!isset($item_image)) $item_image = "";
									GetTemplate_901($item_title, $item_subtitle, $item_image, $item_fullcontent, $pLanguageNmbr);
									break;
								default:
							}
						}
						$item_subtitle = "";
					}
				}
			}
			break;
		case 4:
			// rolling text
			$rollingtext = "";
			if ($pSubjectID == "HOME") {
				$sectionset = GetSection($pFrameNmbr, 'ROLLINGTEXT', '', $pLanguageNmbr);
				if (sizeof($sectionset) > 0) {
					for ($i = 0; $i < sizeof($sectionset); $i++) {
						$sectionnmbr = $sectionset[$i]['SectionNmbr'];
						$itemset = GetItem($sectionnmbr);
						if (sizeof($itemset) > 0) {
							for ($k = 0; $k < sizeof($itemset); $k++) {
								$rollingtext = $rollingtext . "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;" . stripslashes($itemset[$k]['Content']);
							}
						}
					}
				}
			}
			GetTemplate_401($rollingtext, $pSubjectID, $pLanguageNmbr);
			break;
		  case 5:
				$sectionset = GetSection($pFrameNmbr, 'NOTICE', $pSectionNmbr, $pLanguageNmbr);
				if(sizeof($sectionset) > 0){
					for ($i = 0; $i < sizeof($sectionset); $i++) {
						$sectionnmbr = $sectionset[$i]['SectionNmbr'];
						$itemset = GetItem($sectionnmbr);
						if (sizeof($itemset) > 0) {
							for ($k = 0; $k < sizeof($itemset); $k++) {
								${'item_' . $itemset[$k]['Type']} = stripslashes($itemset[$k]['Content']);
							}
				if (!isset($item_subtitle)) $item_subtitle = "";
				if (!isset($item_fullcontent)) $item_fullcontent = "";
				GetTemplate_501($pSubjectID, $item_title, $item_subtitle, $item_fullcontent, $item_fullcontenturl, $item_fullimageurl, $pLanguageNmbr);
					}	
				     }	
				}
		
				
				break;
		default:
	}

}

/**
 *
 * @name 		GetTemplate_301
 * @args 		2
 *					arg[0] = title
 *					arg[1] = subtitle
 *					arg[2] = text_content
 * @return	template
 * @desc		title + text
 *
 **/
function GetTemplate_301($pSubjectID, $pTitle, $pSubtitle, $pTextContent, $pLanguageNmbr)
{
?>
				<table border="0" width="500" align="center" cellspacing="0" cellpadding="0">
					<?php _GetTitle($pSubjectID, $pTitle, $pSubtitle); ?>
<?php
	if ($pSubjectID == "HOME") {
?>
					<tr height="80">
						<td align="center" valign="center">
							<img src="./photos/all.jpg" border="0" width="500"/>
						</td>
					</tr>
<?php
	}
?>
					<tr valign="top">
						<td class="contentfont">
							<?php echo $pTextContent; ?>
						</td>
					</tr>
					<tr height="50">
						<td>&nbsp;</td>
					</tr>
				</table>
<?php
}

/**
 *
 * @name 		GetTemplate_302
 * @args 		3
 *					arg[0] = title
 *					arg[1] = subtitle
 *					arg[2] = abstract
 *					arg[3] = full_content_url
 * @return	template
 * @desc		title + abstract + full_content
 *
 **/
function GetTemplate_302($pSubjectID, $pTitle, $pSubtitle, $pAbstract, $pFullContentUrl, $pLanguageNmbr)
{
?>
				<table width="480" align="center" cellspacing="0" cellpadding="0">
					<?php _GetTitle($pSubjectID, $pTitle, $pSubtitle); ?>
					<tr>
						<td class="contentfont">
							<?php echo $pAbstract; ?>
						</td>
					</tr>
					<tr>
						<td align="right" class="labelfont">
<?php	
	switch ($pSubjectID) {
		case "CLASSINFO":
?>
							<a href="<?php echo $pFullContentUrl; ?>" class="urlfont">
								<?php 
									if ($pLanguageNmbr == 1) echo "详细介绍 ...";
									else echo "details ..."; 
								?>
							</a>
<?php
			break;
		default:
?>
							<a href="<?php echo $pFullContentUrl; ?>" class="urlfont">
								<?php 
									if ($pLanguageNmbr == 1) echo "详细内容 ...";
									else echo "more ..."; 
								?>
							</a>
<?php	
	}
?>
						</td>
					</tr>
					<tr height="50">
						<td>&nbsp;</td>
					</tr>
				</table>
<?php
}

/**
 *
 * @name 		GetTemplate_303
 * @args 		2
 *					arg[0] = title
 *					arg[1] = subtitle
 *					arg[2] = image_url
 * @return	template
 * @desc		title + image
 *
 **/
function GetTemplate_303($pSubjectID, $pTitle, $pSubtitle, $pImageUrl, $pLanguageNmbr)
{
?>
				<table width="480" align="center" cellspacing="0" cellpadding="0">
					<?php _GetTitle($pSubjectID, $pTitle, $pSubtitle); ?>
					<tr>
						<td>
							<img src="<?php echo $pImageUrl; ?>" class="url"/>
						</td>
					</tr>
					<tr height="50">
						<td>&nbsp;</td>
					</tr>
				</table>
<?php
}

/**
 *
 * @name 		GetTemplate_304
 * @args 		3
 *					arg[0] = title
 *					arg[1] = subtitle
 *					arg[2] = image_url
 *					arg[3] = text_content
 * @return	template
 * @desc		title + image + text
 *
 **/
function GetTemplate_304($pSubjectID, $pTitle, $pSubtitle, $pImageUrl, $pTextContent, $pLanguageNmbr)
{
	switch ($pSubjectID) {
		case "PERSONNEL":
?>
				<table width="480" align="center" cellspacing="0" cellpadding="0">
					<tr>
						<td width="70" class="contentfont">
							<img height="100" src="<?php echo $pImageUrl; ?>" class="url"/>
						</td>
						<td width="20">&nbsp;</td>
						<td width="390" class="contentfont">
							<?php _GetTitle($pSubjectID, $pTitle, $pSubtitle); ?>
							<?php echo $pTextContent; ?>
						</td>
					</tr>
					<tr>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
					</tr>
				</table>
<?php
			break;
		default:
?>
				<table width="480" align="center" cellspacing="0" cellpadding="0">
					<?php _GetTitle($pSubjectID, $pTitle, $pSubtitle); ?>
					<tr>
						<td class="contentfont">
							<img height="60" src="<?php echo $pImageUrl; ?>" class="url"/>
							<?php echo $pTextContent; ?>
						</td>
					</tr>
					<tr height="50">
						<td>&nbsp;</td>
					</tr>
				</table>
<?php
	}
}

/**
 *
 * @name 		GetTemplate_305
 * @args 		3
 *					arg[0] = title
 *					arg[1] = subtitle
 *					arg[2] = thumbnail_url
 *					arg[3] = fullimage_url
 *					arg[4] = text_content
 * @return	template
 * @desc		title + thumbnail + full image + text
 *
 **/
function GetTemplate_305($pSubjectID, $pTitle, $pSubtitle, $pThumbnailUrl, $pFullImageUrl, $pTextContent, $pLanguageNmbr)
{
?>
				<table width="480" align="center" cellspacing="0" cellpadding="0">
					<?php _GetTitle($pSubjectID, $pTitle, $pSubtitle); ?>
					<tr>
						<td class="contentfont">
							<a href="<?php echo $pFullImageUrl; ?>"><img height="60" src="<?php echo $pThumbnailUrl; ?>" class="url"/></a>
							<?php echo $pTextContent; ?>
						</td>
					</tr>
					<tr height="50">
						<td>&nbsp;</td>
					</tr>
				</table>
<?php
}

/**
 *
 * @name 		GetTemplate_306
 * @args 		3
 *					arg[0] = title
 *					arg[1] = subtitle
 *					arg[2] = image_url
 *					arg[3] = abstract
 *					arg[4] = full_content_url
 * @return	template
 * @desc		title + image + abstract + full_content
 *
 **/
function GetTemplate_306($pSubjectID, $pTitle, $pSubtitle, $pImageUrl, $pAbstract, $pFullContentUrl, $pLanguageNmbr)
{
?>
				<table width="480" align="center" cellspacing="0" cellpadding="0">
					<?php _GetTitle($pSubjectID, $pTitle, $pSubtitle); ?>
					<tr>
						<td class="contentfont">
							<img height="60" src="<?php echo $pImageUrl; ?>" class="url"/>
							<?php echo $pAbstract; ?>
						</td>
					</tr>
					<tr>
						<td align="right" class="urlfont">
<?php	if ($pLanguageNmbr == 1) {?>
							<a href="<?php echo $pFullContentUrl; ?>">详细内容 ...</a>
<?php	}else {?>
							<a href="<?php echo $pFullContentUrl; ?>">more ...</a>
<?php	}?>
						</td>
					</tr>
					<tr height="50">
						<td>&nbsp;</td>
					</tr>
				</table>
<?php
}

/**
 *
 * @name 		GetTemplate_307
 * @args 		3
 *					arg[0] = title
 *					arg[1] = subtitle
 *					arg[2] = image_url
 *					arg[3] = abstract
 *					arg[4] = full_content_url
 * @return	template
 * @desc		title + thumbnail + full_image + abstract + full_content
 *
 **/
function GetTemplate_307($pSubjectID, $pTitle, $pSubtitle, $pThumbnailUrl, $pFullImageUrl, $pAbstract, $pFullContentUrl, $pLanguageNmbr)
{
?>
				<table width="480" align="center" cellspacing="0" cellpadding="0">
					<?php _GetTitle($pSubjectID, $pTitle, $pSubtitle); ?>
					<tr>
						<td class="contentfont">
							<a href="<?php echo $pFullImageUrl; ?>"><img height="60" src="<?php echo $pThumbnailUrl; ?>" class="url"/></a>
							<?php echo $pAbstract; ?>
						</td>
					</tr>
					<tr>
						<td align="right" class="urlfont">
<?php	if ($pLanguageNmbr == 1) {?>
							<a href="<?php echo $pFullContentUrl; ?>">详细内容 ...</a>
<?php	}else {?>
							<a href="<?php echo $pFullContentUrl; ?>">more ...</a>
<?php	}?>
						</td>
					</tr>
					<tr height="50">
						<td>&nbsp;</td>
					</tr>
				</table>
<?php
}

/**
 *
 * @name 		GetTemplate_308
 * @args 		3
 *					arg[0] = title
 *					arg[1] = subtitle
 *					arg[2] = url
 *					arg[3] = url_text
 * @return	template
 * @desc		title + url
 *
 **/
function GetTemplate_308($pSubjectID, $pTitle, $pSubtitle, $pUrl, $pUrlText, $pLanguageNmbr)
{
?>
				<table width="480" align="center" cellspacing="0" cellpadding="0">
					<?php _GetTitle($pSubjectID, $pTitle, $pSubtitle); ?>
					<tr>
						<td>
							<a href="<?php echo $pUrl; ?>" class="url">____</a>
						</td>
					</tr>
					<tr height="50">
						<td>&nbsp;</td>
					</tr>
				</table>
<?php
}

/**
 *
 * @name 		GetTemplate_309
 * @args 		3
 *					arg[0] = url
 *					arg[1] = url_text
 * @return	template
 * @desc		url
 *
 **/
function GetTemplate_309($pSubjectID, $pUrl, $pUrlText, $pLanguageNmbr)
{
?>
				<table width="480" align="center" cellspacing="0" cellpadding="0">
					<tr>
						<td>
							<a href="<?php echo $pUrl; ?>">____</a>
						</td>
					</tr>
					<tr height="50">
						<td>&nbsp;</td>
					</tr>
				</table>
<?php
}

/**
 *
 * @name 		GetTemplate_310
 * @args 		3
 *					arg[0] = subject_id
 *					arg[1] = section_set
 *					arg[3] = language
 * @return	template
 * @desc		title + thumbnail + full image
 *
 **/
function GetTemplate_310($pSubjectID, $pSectionSet, $pLanguageNmbr, $pSubmenuArray)
{
?>
				<table width="480" align="center" cellspacing="0" cellpadding="0">
					<tr height="50">
						<td align="center" class="titlefont">
							<b>
							<?php 
								for ($i = 0; $i < sizeof($pSubmenuArray); $i++) {
									if ($pSubmenuArray[$i]['SubjectID'] == $pSubjectID) {
										if ($pLanguageNmbr == 1) echo $pSubmenuArray[$i]['Subject_C'];
										else echo $pSubmenuArray[$i]['Subject_E'];
									}
								}
							?>
							</b>
						</td>
					</tr>
				</table>
<?php
	// loop through all sections for this subject
	for ($i = 0; $i < sizeof($pSectionSet); $i++) {
		$sectionnmbr = $pSectionSet[$i]['SectionNmbr'];
		$sectiontypenmbr = $pSectionSet[$i]['SectionTypeNmbr'];
		$itemset = GetItem($sectionnmbr);
		if (sizeof($itemset) > 0) {
			for ($k = 0; $k < sizeof($itemset); $k++) {
				// populate all item content variables for this section
				${'item_' . $itemset[$k]['Type']} = stripslashes($itemset[$k]['Content']);
				/***
				$item_title
				$item_subtitle
				$item_thumbnail
				$item_fullimageurl
				***/
			}
			if (!isset($item_subtitle)) $item_subtitle = "";
			if (fmod(($i + 1), 4) == 0) {
?>
						<td width="97" align="center" valign="center">
							<a href="<?php echo $item_fullimageurl; ?>"><img border="0" height="63" src="<?php echo $item_thumbnail; ?>"/></a>
						</td>
					</tr>
				</table>
				<p/>
<?php
			}
			else {
				if (fmod(($i + 1), 4) == 1) {
?>
				<table width="390" align="center" cellspacing="0" cellpadding="0">
				<!--table width="390" align="center" cellspacing="0" cellpadding="0" background="./images/filmstrip.gif"-->
					<tr height="85">
						<td width="97" align="center" valign="center">
							<a href="<?php echo $item_fullimageurl; ?>"><img border="0" height="63" src="<?php echo $item_thumbnail; ?>"/></a>
						</td>
<?php
				}
				else {
?>
						<td width="97" align="center" valign="center">
							<a href="<?php echo $item_fullimageurl; ?>"><img border="0" height="63" src="<?php echo $item_thumbnail; ?>"/></a>
						</td>
<?php
				}
			}
		}
	}
	if (fmod($i, 4) != 0) {
		for ($k = 0; $k < (4 - fmod($i, 4)); $k++) {
?>
						<td width="97">&nbsp;</td>
<?php
		}
?>
					</tr>
				</table>
				<p/>
<?php
	}
?>
				<table width="400" align="center" cellspacing="0" cellpadding="0">
					<tr height="50">
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
					</tr>
				</table>
<?php
}

/**
 *
 * @name 		GetTemplate_401
 * @args 		3
 *					arg[0] = rolling_text
 *					arg[1] = subject_id
 *					arg[2] = language
 * @return	template
 * @desc		rolling ads
 *
 **/
function GetTemplate_401($pRollingText, $pSubjectID, $pLanguageNmbr)
{
	if ($pRollingText != "" && $pSubjectID == "HOME") {
?>
						<tr>
							<td width="500" height="10" align="center" bgcolor="#aaddbe">
								<marquee
								<?php
								/*
								WIDTH: how wide the marquee is
								HEIGHT: how tall the marquee is
								DIRECTION: which direction the marquee should scroll
								BEHAVIOR: what type of scrolling
								SCROLLDELAY: how long to delay between each jump
								SCROLLAMOUNT: how far to jump
								LOOP: how many times to loop
								BGCOLOR: background color
								HSPACE: horizontal space around the marquee
								VSPACE: vertical space around the marquee
								*/
								?>
								width="70%"
								scrollamount="1"
								scrolldelay="1"
								bgcolor="#aaddbe"
								onMouseOver="this.stop();" onMouseOut="this.start();">
									<font size="2" color="darkgreen">
										<?php 
											echo $pRollingText; 
										?>
									</font>
								</marquee>
							</td>
						</tr>
<?php
	}
	else {
?>
						<tr>
							<td width="500" height="1" align="center"/>
						</tr>

<?php
}
}

/**
 *
 * @name 		GetTemplate_501
 * @args 		5
 *					arg[0] = title
 *					arg[1] = subtitle
 *					arg[3] = text_content
 *					arg[4] = full_content_url
 *					arg[5] = fullimage_url
 * @return	template
 * @desc		title + subtitle + text_content + full_content_url + fullimage_url
 *
 **/
function GetTemplate_501($pSubjectID, $pTitle, $pSubtitle, $pTextContent, $pFullContentUrl, $pFullImageUrl, $pLanguageNmbr)
{
?>
	<div align="left" style="position:relative;width:145px;height:auto;font-size:13px;line-height:15px;">
		<b><?php _GetTitle($pSubjectID, $pTitle, $pSubtitle); ?></b>
		<br>
		<?php echo $pTextContent; ?>
		<?php if(pFullContentUrl != ""){?>
		<a href="<?php echo $pFullContentUrl; ?>" class="urlfont"></a>
		<?php }?>
		<br><br>
		
</div>
<?php 
 
}
/**
 *
 * @name 		GetTemplate_901
 * @args 		3
 *					arg[0] = title
 *					arg[1] = subtitle
 *					arg[2] = image_url
 *					arg[3] = text_content
 * @return	template
 * @desc		title + image + text
 *
 **/
function GetTemplate_901($pTitle, $pSubtitle, $pImageUrl, $pTextContent, $pLanguageNmbr)
{
?>
				<table width="500" align="center" cellspacing="0" cellpadding="0">
					<?php _GetTitle('FULL', $pTitle, $pSubtitle); ?>
					<tr>
						<td class="contentfont">
<?php if ($pImageUrl != "") { ?>
							<img width="450" src="<?php echo $pImageUrl; ?>" class="url"/>
<?php } ?>
							</br/>
							<?php echo $pTextContent; ?>
						</td>
					</tr>
					<tr height="50">
						<td>&nbsp;</td>
					</tr>
				</table>
<?php
}

/**
 *
 * @name 		GetTemplate_LIST
 * @args 		3
 *					arg[0] = subject_id
 *					arg[1] = section_set
 *					arg[3] = language
 * @return	template
 * @desc		list + full content
 *
 **/
function GetTemplate_LIST($pSubjectID, $pSectionSet, $pLanguageNmbr)
{
	switch ($pSubjectID) {
		case "STUDENTWORK":
			if ($pLanguageNmbr == 1) {
				$headingtext = "学生作文";
				$introtext = "";
				$titletext = "作文题目";
				$authortext = "作者";
			}
			else {
				$headingtext = "Student Work";
				$introtext = "";
				$titletext = "Title";
				$authortext = "Author";
			}
			break;
		case "FORUM":
			if ($pLanguageNmbr == 1) {
				$headingtext = "儿童教育论坛";
				$introtext = "";
				$titletext = "";
				$authortext = "";
			}
			else {
				$headingtext = "Teaching Forum";
				$introtext = "";
				$titletext = "";
				$authortext = "";
			}
			break;
		case "TEACHING":
			if ($pLanguageNmbr == 1) {
				$headingtext = "教学体会";
				$introtext = "";
				$titletext = "标题";
				$authortext = "作者";
			}
			else {
				$headingtext = "Chinese Teaching Experience";
				$introtext = "";
				$titletext = "Title";
				$authortext = "Author";
			}
			break;
		case "PARENTMAILBOX":
			if ($pLanguageNmbr == 1) {
				$headingtext = "家长来信";
				$introtext = "";
				$titletext = "来信标题";
				$authortext = "家长";
			}
			else {
				$headingtext = "Parent Letters";
				$introtext = "";
				$titletext = "Title";
				$authortext = "Parent";
			}
			break;
		case "NEWS":
			if ($pLanguageNmbr == 1) {
				$headingtext = "芳草地新闻报道";
				$introtext = "";
				$titletext = "";
				$authortext = "";
			}
			else {
				$headingtext = "FCD News";
				$introtext = "";
				$titletext = "";
				$authortext = "";
			}
			break;
		case "SAT":
			if ($pLanguageNmbr == 1) {
				$headingtext = "芳草地学生中心SAT辅导课程";
				$introtext = "";
				$titletext = "";
				$authortext = "";
			}
			else {
				$headingtext = "SAT Preparation Programs in FCD Student Center";
				$introtext = "By working with one of the leading institutes that provide professional test preparation services for a variety of exams since 1991, FCD Chinese School is offering the New SAT preparation full length course and also weekend course. The quality is comparable with Kaplan and Princeton Review and price is ~ 20% less.  In Houston Area, 4 students scored a perfect 2400 on the New SAT, three of them took the course from our incorporated Institute. ";
				$titletext = "";
				$authortext = "";
			}
			break;
		default:
	}
?>
				<table width="480" align="center" cellspacing="0" cellpadding="0">
					<tr height="50">
						<td align="center" class="titlefont"><b><?php echo $headingtext; ?></b></td>
					</tr>
					<tr>
						<td>&nbsp;</td>
					</tr>
<?php
	if ($introtext != "") {
?>
					<tr height="50">
						<td><?php echo $introtext; ?></td>
					</tr>
					<tr>
						<td>&nbsp;</td>
					</tr>
<?php
	}
?>
				</table>
<?php
	if ($pSubjectID == "NEWS" || $pSubjectID == "FORUM" || $pSubjectID == "SAT") {
?>
				<table border="0" width="450" align="center" cellspacing="0" cellpadding="0" class="urlfont">
					<tr>
						<td>
							<ul>
<?php
		// loop through all sections for this subject
		for ($i = 0; $i < sizeof($pSectionSet); $i++) {
			$section_authorname = $pSectionSet[$i]['AuthorName'];
			$sectionnmbr = $pSectionSet[$i]['SectionNmbr'];
			$sectiontypenmbr = $pSectionSet[$i]['SectionTypeNmbr'];
			$itemset = GetItem($sectionnmbr);
			if (sizeof($itemset) > 0) {
				for ($k = 0; $k < sizeof($itemset); $k++) {
					// populate all item content variables for this section
					${'item_' . $itemset[$k]['Type']} = stripslashes($itemset[$k]['Content']);
				}
				if (!isset($item_subtitle)) $item_subtitle = "";
				if (!isset($section_authorname)) $section_authorname = "&nbsp;";
?>
								<li>
									<a href="<?php echo $item_fullcontenturl; ?>">
										<?php echo $item_title; if ($item_subtitle != '') echo '-- <font size=1>' . $item_subtitle . '</font>'; ?>
									</a>
								</li><p/>
<?php
			}
			$item_subtitle = '';
		}
?>
							</ul>
						</td>
					</tr>
				</table>
<?php
	}
	else {
?>
				<table border="1" width="480" align="center" cellspacing="0" cellpadding="0">
					<tr>
						<td width="300" align="center" bgcolor="#a0c512" class="smalltitlefont">
							<?php echo $titletext; ?>
						</td>
						<td width="180" align="center" bgcolor="#a0c512" class="smalltitlefont">
							<?php echo $authortext; ?>
						</td>
					</tr>
<?php
		// loop through all sections for this subject
		for ($i = 0; $i < sizeof($pSectionSet); $i++) {
			$section_authorname = $pSectionSet[$i]['AuthorName'];
			$sectionnmbr = $pSectionSet[$i]['SectionNmbr'];
			$sectiontypenmbr = $pSectionSet[$i]['SectionTypeNmbr'];
			$itemset = GetItem($sectionnmbr);
			if (sizeof($itemset) > 0) {
				for ($k = 0; $k < sizeof($itemset); $k++) {
					// populate all item content variables for this section
					${'item_' . $itemset[$k]['Type']} = stripslashes($itemset[$k]['Content']);
				}
				if (!isset($item_subtitle)) $item_subtitle = "";
				if (!isset($section_authorname)) $section_authorname = "&nbsp;";
?>
					<tr>
						<td class="contentfont">
							&nbsp;
							<a href="<?php echo $item_fullcontenturl; ?>">
								<?php echo $item_title; if ($item_subtitle != '') echo ' - ' . $item_subtitle; ?>
							</a>
						</td>
						<td class="contentfont">&nbsp;<?php echo $section_authorname; ?></td>
					</tr>
<?php
			}
			$item_subtitle = "";
		}
?>
				</table>
<?php
	}
}

/**
 *
 * @name 		GetTemplate_HOMEWORK
 * @args 		3
 *					arg[0] = subject_id
 *					arg[1] = section_set
 *					arg[3] = language
 * @return	template
 * @desc		list + full content
 *
 **/
function GetTemplate_HOMEWORK($pSubjectID, $pSectionSet, $pLanguageNmbr)
{
	switch ($pSubjectID) {
		case "CSLHOMEWORK":
			if ($pLanguageNmbr == 1) {
				$headingtext = "CSL 家庭作业";
				$titletext = "作业";
				$authortext = "日期";
			}
			else {
				$headingtext = "CSL Homework";
				$titletext = "Assignment";
				$authortext = "Date";
			}
			break;
		default:
	}
?>
				<table width="480" align="center" cellspacing="0" cellpadding="0">
					<tr height="50">
						<td align="center" class="titlefont"><b><?php echo $headingtext; ?></b></td>
					</tr>
					<tr>
						<td>&nbsp;</td>
					</tr>
				</table>
				<table border="1" width="480" align="center" cellspacing="0" cellpadding="0">
					<tr>
						<td width="300" align="center" bgcolor="#a0c512" class="smalltitlefont">
							<?php echo $titletext; ?>
						</td>
						<td width="180" align="center" bgcolor="#a0c512" class="smalltitlefont">
							<?php echo $authortext; ?>
						</td>
					</tr>
<?php
		// loop through all sections for this subject
		for ($i = 0; $i < sizeof($pSectionSet); $i++) {
			$section_authorname = $pSectionSet[$i]['AuthorName'];
			$sectionnmbr = $pSectionSet[$i]['SectionNmbr'];
			$createddate = $pSectionSet[$i]['CreatedDate'];
			$sectiontypenmbr = $pSectionSet[$i]['SectionTypeNmbr'];
			$itemset = GetItem($sectionnmbr);
			if (sizeof($itemset) > 0) {
				for ($k = 0; $k < sizeof($itemset); $k++) {
					// populate all item content variables for this section
					${'item_' . $itemset[$k]['Type']} = stripslashes($itemset[$k]['Content']);
				}
				if (!isset($item_subtitle)) $item_subtitle = "";
				if (!isset($section_authorname)) $section_authorname = "&nbsp;";
?>
					<tr>
						<td class="contentfont">
							&nbsp;
							<a href="<?php echo $item_url; ?>" target=_>
								<?php echo $item_title; if ($item_subtitle != '') echo ' - ' . $item_subtitle; ?>
							</a>
						</td>
						<td class="contentfont">&nbsp;<?php echo strtok($createddate, " "); ?></td>
					</tr>
<?php
			}
			$item_subtitle = "";
		}
?>
				</table>
<?php
}

/**
 *
 * @name 		GetTemplate_HTML
 * @args 		1
 *					arg[0] = html_url
 * @return	template
 * @desc		display external html
 *
 **/
function GetTemplate_HTML($pHtmlUrl)
{
?>
				<table width="500" align="center" cellspacing="0" cellpadding="0">
					<tr>
						<td>
							<?php include_once $pHtmlUrl; ?>
						</td>
					</tr>
					<tr>
						<td>&nbsp;</td>
					</tr>
				</table>
<?php
}

/**
 *
 * @name 		_GetTitle
 * @args 		2
 * @return	title
 * @desc		
 *
 **/
function _GetTitle($pSubjectID, $pTitle, $pSubtitle)
{
	switch ($pSubjectID) {
		case "HOME":
?>
					<tr>
						<td align="center" class="hometitlefont">
							<?php echo $pTitle . '<br/>'; ?>
						</td>
					</tr>
<?php
			break;
		case "PERSONNEL":
			echo $pTitle . '<br/>';
			break;
		default:
?>
					<tr>
						<td align="center" class="titlefont">
							<?php echo $pTitle . '<br/>'; ?>
						</td>
					</tr>
<?php 
	}
	if ($pSubjectID != "PERSONNEL") {
		if ($pSubtitle != "") {
?>
					<tr>
						<td align="center" class="subtitlefont">
							<?php echo  '<br/>- ' . $pSubtitle; ?>
						</td>
					</tr>
<?php
		}
?>
					<tr>
						<td>&nbsp;</td>
					</tr>
<?php
	}
}

/**
 *
 * @name 		_GetLeafImage
 * @args 		2
 *					arg[0] = title
 *					arg[1] = subtitle
 *					arg[2] = text_content
 * @return	template
 * @desc		title + text
 *
 **/
function _GetLeafImage()
{
?>
				<table border="0" width="500" align="center" cellspacing="0" cellpadding="0">
					<tr>
						<td align="right" valign="bottom">
							<img src="./images/leaf.jpg" border="0"/>
							&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
						</td>
					</tr>
				</table>
				<br/><br/>
<?php
}

/**
 *
 * @name 		_GetHeading
 * @args 		2
 *					arg[0] = subject_id
 *					arg[1] = language
 * @return	template
 * @desc		heading for the page
 *
 **/
function _GetHeading($pSubjectID, $pLanguageNmbr)
{
	switch ($pSubjectID) {
		case "PERSONNEL":
?>
				<table width="480" align="center" cellspacing="0" cellpadding="0">
					<tr>
						<td align="center" class="titlefont">
							<?php
								if ($pLanguageNmbr == "1") {
									echo "校务人员简介<br/><br/>";
								}
								else {
									echo "School Administration<br/><br/>";
								}
							?>
						</td>
					</tr>
				</table>
<?php
			break;
		default:
	}

}

/**
 *
 * @name 		_GetButtonColor
 * @args 		1
 *					arg[0] = subject_id
 * @return	template
 * @desc		left panel button color
 *
 **/
function _GetButtonColor($pParam)
{
	$subjectid = GetSubjectID();
	if ($subjectid == $pParam) {
		echo " bgcolor=\"#93C203\"";
	}
	else {
		if (_BelongToGroup($subjectid, $pParam)) {
			echo " bgcolor=\"#93C203\"";
		}
		else {
			if (isset($_GET['htmlfile']) && $_GET['htmlfile'] == $pParam) {
				echo " bgcolor=\"#93C203\"";
			}
			else {
				echo " bgcolor=\"#589201\"";
			}
		}
	}
	
}

/**
 *
 * @name 		_BelongToGroup
 * @args 		2
 *					arg[0] = subject_id
 *					arg[1] = group_name
 * @return	template
 * @desc		check group (ALBUM, etc.)
 *
 **/
function _BelongToGroup($pSubjectID, $pGroupName)
{
	$belong = false;
	if (is_int(strpos($pSubjectID, '-'))) {
		if (strtok($pSubjectID, '-') == $pGroupName) {
			$belong = true;
		}
	}
	else {
		switch ($pGroupName) {
			case 'CHINESETEACHING':
				if ($pSubjectID == 'STUDENTWORK'
						|| $pSubjectID == 'TEACHING'
						|| $pSubjectID == 'FORUM'
						|| $pSubjectID == 'PARENTMAILBOX') {
					$belong = true;
				}
				break;
			case 'HOMEWORK':
				if ($pSubjectID == 'CSLHOMEWORK') {
					$belong = true;
				}
				break;
			default:
		}
	}
	return $belong;
	
}


?>










