<?php

/**
 *
 *
 * @version $Id$
 * @copyright 2005
 **/

include_once 'LIB_Session.inc';
include_once 'LIB_SharedFormModules.inc';
include_once 'LIB_Utilities.inc';
include_once 'LIB_DbUtilities.inc';
include_once 'LIB_DbTaskHandlers.inc';
include_once 'FCD_Registration.inc';

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
</head>
<body topmargin="0"  leftmargin="0" marginwidth="0" marginheight="0" onLoad="rotate()">
<?php
if (isset($_GET['fn'])) {
  $fn_array = explode('-', rtrim($_GET['fn'], '-'));
  for ($i = 0; $i < sizeof($fn_array); $i++) {
    AdminTemplate_Registration_PrintAdmission('print_admission_letter', $fn_array[$i]);
  }
}
?>
</body>
</html>

<?php
/**
 *
 * @name 		AdminTemplate_Registration_PrintAdmission
 * @args 		0
 * @return	website template
 * @desc		
 *
 **/
function AdminTemplate_Registration_PrintAdmission($pTarget, $pFamilyNmbr) {
	switch ($pTarget) {
		case "regist":
			break;
		case "print_admission_letter":
			if ($pFamilyNmbr != '') {
				$family_handler = new StudentAccountHandler();
				$family_info = $family_handler->GetFamilyInfo($pFamilyNmbr); 
				$father_info = $family_handler->GetFamilyAndFamilyMemberInfo($pFamilyNmbr, 5); 
				if (isset($father_info[0])) {
					setSession('FatherFamilyMemberNmbr__', $father_info[0]['FamilyMemberNmbr']);
				}
				$mother_info = $family_handler->GetFamilyAndFamilyMemberInfo($pFamilyNmbr, 6); 
				if (isset($mother_info[0])) {
					setSession('MotherFamilyMemberNmbr__', $mother_info[0]['FamilyMemberNmbr']);
				}
				$student_info = $family_handler->GetStudentInfo($pFamilyNmbr); 
				for ($i = 0; $i < sizeof($student_info); $i++) {
					setSession('StudentFamilyMemberNmbr' . $i . '__', $student_info[$i]['FamilyMemberNmbr']);
				}
				$s_idx = sizeof($student_info);
				if (getSession('StudentCount', 0) < $s_idx) {
					setSession('StudentCount__', $s_idx);
				}
			}
?>
	<table width="600" align="center" cellspacing="0" cellpadding="0" class="noborder" style="font-size: 13px">
		<tr height="40"> 
			<td align="left">
        FCD Chinese School<br/>
        P.O. BOX 10453<br/>
        NEW BRUNSWICK,NJ 08906<br/>
		  </td>
		</tr>
		<tr height="30"> 
			<td align="left">
        <?php echo date("F j, Y"); ?>
		  </td>
		</tr>
	</table>
	<table border="0" width="600" align="center" cellspacing="0" cellpadding="0">
		<tr height="100"> 
			<td align="center" style="font-size: 20px;font-weight:bold;">
        芳草地中文学校入学通知书
		  </td>
		</tr>
	</table>
	<table width="600" align="center" cellspacing="0" cellpadding="0" class="noborder" style="font-size: 13px">
		<tr>
			<td width="400">
				<?php 
          $l_name_display = "";
					if (GetValue($father_info, 0, 'ChineseName') != '') {
            $l_name_display = GetValue($father_info, 0, 'ChineseName');
          }
          else {
					  if (GetValue($father_info, 0, 'LastName') != '') $l_name_display = GetValue($father_info, 0, 'FirstName') . ' ' . GetValue($father_info, 0, 'LastName');
          }
					if (GetValue($mother_info, 0, 'ChineseName') != '') {
            if ($l_name_display != '') $l_name_display = $l_name_display . ", " . GetValue($mother_info, 0, 'ChineseName');
            else $l_name_display = GetValue($mother_info, 0, 'ChineseName');
          }
          else {
					  if (GetValue($mother_info, 0, 'LastName') != '') {
              if ($l_name_display != '') $l_name_display = $l_name_display . ", " . GetValue($mother_info, 0, 'FirstName') . ' ' . GetValue($mother_info, 0, 'LastName');
              else $l_name_display = GetValue($mother_info, 0, 'FirstName') . ' ' . GetValue($mother_info, 0, 'LastName');
            }
          }
          echo $l_name_display;
				?>
			</td>
			<td width="200" align="right" valign="top">
			  <b>FAMILY ID:&nbsp;&nbsp;<?php echo GetValue($father_info, 0, 'FamilyID'); ?></b>
      </td>
		</tr>
		<tr>
			<td>
				<?php echo GetValue($family_info, 0, 'Street'); ?><br/>
				<?php echo GetValue($family_info, 0, 'City') . ', ' . GetValue($family_info, 0, 'State') . ' ' . GetValue($family_info, 0, 'ZipCode'); ?><br/>
				<?php echo GetValue($family_info, 0, 'HomeTelephone'); ?><br/>
				<?php echo GetValue($family_info, 0, 'Email'); ?>
			</td>
			<td>&nbsp;</td>
		</tr>
	</table>
	<table width="600" align="center" cellspacing="0" cellpadding="0" class="noborder" style="font-size: 13px">
		<tr>
			<td>&nbsp;</td>
		</tr>
		<tr>
			<td>
        尊敬的 <?php echo $l_name_display; ?> 家长: &nbsp;您好!
			</td>
		</tr>
		<tr>
			<td>&nbsp;</td>
		</tr>
		<tr>
			<td>
        我们很荣幸地通知您，您的报名表已经收到。请仔细核对该通知书中的项目，如发现有误，请及时告知。 联系人：蔡菁 老师 Jean Cai (732) 937-9014 chan_je@yahoo.com
			</td>
		</tr>
		<tr>
			<td>&nbsp;</td>
		</tr>
		<tr>
			<td>
        芳草地中文学校是一所周末语言学校，要想教好我们的孩子，使孩子们学有所成，除了校方和老师们的努力之外，必然要靠所有家长们的积极配合和大力协助。
        为此，学校希望您能配合我们做到以下几点：<br/>
        <ol>
	 	        <li>找一切机会，尽量和您的孩子讲中文、讲普通话；</li>
	 	        <li>积极参加学校活动和公益服务工作，为办好学校及时提出您的宝贵建议和意见；</li>
	 	        <li>请积极配合学校，按时送孩子到校上课；如同学因故不能来校上课，请提前电话通知本班老师。</li>
        </ol>
			</td>
		</tr>
		<tr>
			<td>&nbsp;</td>
		</tr>
		<tr>
			<td>
        <b>
          *此通知书也作为交费收据，请妥善保存。
        </b>
			</td>
		</tr>
	</table>
	<table width="600" align="center" cellspacing="0" cellpadding="0" class="noborder" style="font-size: 13px">
		<tr>
			<td>&nbsp;</td>
		</tr>
<?php 
			/****
      if ($student_info) {
				for ($i = 0; $i < getSession('StudentCount', 0); $i++) {
?>
		<tr>
      <td>
<?php 
					if (isset($student_info[$i]['LastName']) && $student_info[$i]['LastName'] != '') {
						echo ($i + 1) . '. ' . GetValue($student_info, $i, 'LastName')
								. ', ' . GetValue($student_info, $i, 'FirstName') 
								. ' (' . GetValue($student_info, $i, 'ChineseName') 
								. ') - ' . GetValue($student_info, $i, 'Gender') . ', ';
						if (GetValue($student_info, $i, 'IsAdult') == 'yes') echo ' adult';
						else echo 'Birth date: ' . GetValue($student_info, $i, 'BirthDate');
					}
?>
			</td>
		</tr>
<?php 
				}
			}
      ****/
?>
	</table>
<?php
	    $ref_lib = new RefLibrary();
	    $student_handler = new StudentAccountHandler();
	    $reg_handler = new RegistrationHandler();
	    $tuition_handler = new TuitionFeeHandler();
	    $school_years = $ref_lib->GetSchoolYear('recent_three');
	    $current_school_year = $ref_lib->GetSchoolYear('active_year');
	    if ($students = $student_handler->GetStudentInfo($pFamilyNmbr)) {
		    $dues = $tuition_handler->GetTuitionDue($current_school_year[0]['SchoolYear'], $pFamilyNmbr);
        $curriculum_handler = new CurriculumHandler();
	      $classrooms = $ref_lib->GetRefValues('REF_Classroom');
	      $class_periods = $ref_lib->GetRefValues('REF_ClassPeriod');
?>
	<table width="600" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td valign="top">
				<table width="600" border="1" align="center" cellspacing="0" cellpadding="0">
					<tr height="30" bgcolor="#C1E8BE">
						<td width="140" align="center" class="printlabelfont">学生姓名</td>
						<td width="100" align="center" class="printlabelfont">学期</td>
						<td width="180" align="center" class="printlabelfont">注册课程</td>
						<td width="80" align="center" class="printlabelfont">教室</td>
						<td width="100" align="center" class="printlabelfont">上课时间</td>
					</tr>
<?php
		for ($i = 0; $i < sizeof($students); $i++) {
			for ($m = 0; $m < sizeof($school_years); $m++) {
				$registrations = $reg_handler->GetRegistration($school_years[$m]['SchoolYear'], '', $students [$i]['FamilyMemberNmbr'], '', '');



				if (sizeof($registrations ) > 0) {
					$familymember_nmbr  = '';
					for ($n = 0; $n < sizeof($registrations); $n++) {
						if (isset($registrations[$n]['ClassName_E']) && $registrations[$n]['ClassName_E'] != '') {
              $selected_class = $curriculum_handler->GetClass('', $registrations[$n]['ClassNmbr']);
              $l_classname = $registrations[$n]['ClassName_E'] . '<br/>(' . $registrations[$n]['ClassName_C'] . ')';
              for ($p = 0; $p < sizeof($classrooms); $p++) {if ($classrooms[$p]['ClassroomNmbr'] == $registrations[$n]['ClassroomNmbr']){$l_classroom = $classrooms[$p]['Classroom'];break;}}
              for ($q = 0; $q < sizeof($class_periods); $q++) {if ($class_periods[$q]['ClassPeriodNmbr'] == $registrations[$n]['ClassPeriodNmbr']){$l_classperiod = $class_periods[$q]['ClassPeriod_E'] . '<br/>' . $class_periods[$q]['ClassPeriod_C'];break;}}
?>
					<tr>
						<td align="center" class="labelfont">&nbsp;<?php if ($familymember_nmbr !=  $registrations[$n]['FamilyMemberNmbr']) echo $students[$i]['LastName'] . ' ' . $students[$i]['FirstName'] . ' (' . $students[$i]['ChineseName'] . ')'; ?></td>
						<td align="center" class="labelfont"><?php echo $registrations[0]['SchoolYear']; ?>&nbsp;</td>
						<td align="center" class="labelfont"><?php echo $l_classname; ?>&nbsp;</td>
						<td align="center" class="labelfont"><?php echo $l_classroom; ?>&nbsp;</td>
						<td align="center" class="labelfont"><?php echo $l_classperiod; ?>&nbsp;</td>
					</tr>
<?php
						}
						if ($familymember_nmbr !=  $registrations[$n]['FamilyMemberNmbr']) $familymember_nmbr =  $registrations[0]['FamilyMemberNmbr'];
					}
					break;
				}
			}
		}
?>
				</table>
			</td>
		</tr>
	</table>
	<table width="600" align="center" cellspacing="0" cellpadding="0">
		<tr height="40">
			<td align="left" class="printlabelfont">
        注: 2008年秋季开学日期为9月6日 &nbsp;&nbsp;&nbsp;上课时间: 第一节 9:30-10:20; 第二节 10:30-11:20; 第三节 11:30-12:20
      </td>
		</tr>
	</table>
	<table width="600" align="center" cellspacing="0" cellpadding="0">
		<tr height="40">
			<td align="left" class="printlabelfont">
        <?php /****
        学杂费总额: &nbsp;<b>$<?php echo $dues[0]['TotalFeeTuition'] . '.00'; ?></b><br/>
        ********/ ?>
			  已交纳: &nbsp;<b>$<?php echo $dues[0]['FeeTuitionPaid']; ?></b>
      </td>
		</tr>
	</table>
<?php
	}
?>
	<table width="600" align="center" cellspacing="0" cellpadding="0" class="noborder" style="font-size: 13px">
		<tr height="40" valign="bottom">
			<td width="400">&nbsp;</td>
			<td width="200">
        芳草地中文学校
			</td>
		</tr>
		<tr>
			<td>&nbsp;</td>
			<td>
        校长  &nbsp;&nbsp;肖毅<br/>
        教务长  &nbsp;&nbsp;姜若青<br/>
			</td>
		</tr>
	</table>
<p style="page-break-before: always">
<?php
			break;
		default:
	}
}


?>

