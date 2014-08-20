<?php

/**
 *
 *
 * @version $Id$
 * @copyright 2005
 **/

if (strlen(session_id()) < 5) {
	session_start();
}

include_once 'LIB_Session.inc';
include_once 'LIB_SharedFormModules.inc';
include_once 'LIB_Utilities.inc';
include_once 'LIB_DbUtilities.inc';
include_once 'LIB_DbTaskHandlers.inc';
include_once 'FCD_Registration.inc';

switch (getSession('ReportType', 0)) {
  case "by_class":
    AdminTemplate_Registration_ReportByClass(getSession('ClassNmbr', 0), getSession('SchoolYear', 0));
    break;
  case "all":
    AdminTemplate_Registration_ReportAll($_SESSION['SchoolYear']);
    break;
  default:
}


/**
 *
 * @name 		AdminTemplate_Registration_ReportByClass
 * @args 		0
 * @return	website template
 * @desc		
 *
 **/
function AdminTemplate_Registration_ReportByClass($pClassNmbr, $pSchoolYear) {
  $report_hdlr = new ReportHandler();
  $family_hdlr = new StudentAccountHandler();
  $student_by_class = $report_hdlr->GetStudentByClass($pClassNmbr, $pSchoolYear);
  $class_info = $report_hdlr->GetClassInfo($pClassNmbr, $pSchoolYear);
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
	<table border="0" width="600" align="center" cellspacing="0" cellpadding="0">
		<tr height="100"> 
			<td align="center" style="font-size: 20px;font-weight:bold;">
        芳草地中文学校
		  </td>
		</tr>
	</table>
	<table width="600" align="center" cellspacing="5" cellpadding="5" class="noborder" style="font-size: 13px">
		<tr>
			<td width="400">
				<?php
          if (isset($class_info[0])) {
            echo "课程: &nbsp;&nbsp;" . $class_info[0]['ClassName_C'] . '<br/>';
            echo "教室: &nbsp;&nbsp;" . $class_info[0]['Classroom'] . '<br/>';
            echo "时段: &nbsp;&nbsp;" . $class_info[0]['ClassTime'] . '<br/>';
            echo "学生人数: &nbsp;&nbsp;" . sizeof($student_by_class) . '<br/>';
          }
				?>
			</td>
			<td width="200" align="right" valign="bottom">
				<?php
          if (isset($class_info[0])) {
            echo "教师: &nbsp;&nbsp;" . $class_info[0]['LastName'] . " " . $class_info[0]['FirstName'] . " " . $class_info[0]['ChineseName'];
          }
				?>
      </td>
		</tr>
	</table>
	<table width="600" border="1" align="center" cellspacing="0" cellpadding="0" class="thinborder" style="font-size: 13px">
		<tr>
			<td width="90" align="center">学生姓名</td>
			<td width="50" align="center">性别</td>
			<td width="80" align="center">家庭代码</td>
			<td width="90" align="center">父亲</td>
			<td width="90" align="center">母亲</td>
			<td width="200" align="center">电话 / Email</td>
		</tr>
<?php
  for ($i = 0; $i < sizeof($student_by_class); $i++) {
    if (isset($student_by_class[0]['FamilyID']) && $student_by_class[0]['FamilyID'] != '') {
?>
		<tr>
			<td align="center">
        &nbsp;
        <?php echo $student_by_class[$i]['LastName'] . " " . $student_by_class[$i]['FirstName'] . "<br/>" . $student_by_class[$i]['ChineseName']; ?>
      </td>
			<td align="center">
        &nbsp;
        <?php 
        if ($student_by_class[$i]['Gender'] == 'Male') echo "男"; 
        if ($student_by_class[$i]['Gender'] == 'Female') echo "女"; 
        ?>
      </td>
			<td align="center">
        &nbsp;
        <?php echo $student_by_class[$i]['FamilyID']; ?>
      </td>
			<td align="center">
        &nbsp;
        <?php 
        $family_info = $family_hdlr->GetFamilyAndFamilyMemberInfo($student_by_class[$i]['FamilyNmbr'], 5);
        if (isset($family_info[0])) {
          echo $family_info[0]['LastName'] . " " . $family_info[0]['FirstName'] . "<br/>" . $family_info[0]['ChineseName']; 
        }
        ?>
      </td>
			<td align="center">
        &nbsp;
        <?php 
        $family_info = $family_hdlr->GetFamilyAndFamilyMemberInfo($student_by_class[$i]['FamilyNmbr'], 6);
        if (isset($family_info[0])) {
          echo $family_info[0]['LastName'] . " " . $family_info[0]['FirstName'] . "<br/>" . $family_info[0]['ChineseName']; 
        }
        ?>
      </td>
			<td align="center">
        &nbsp;
        <?php 
        $family_info = $family_hdlr->GetFamilyInfo($student_by_class[$i]['FamilyNmbr']);
        if (isset($family_info[0])) {
          echo $family_info[0]['HomeTelephone'] . '<br>' . $family_info[0]['Email']; 
        }
        ?>
      </td>
		</tr>
<?php
    }
  }
?>
	</table>
</body>
</html>
<?php
}

/**
 *
 * @name 		AdminTemplate_Registration_ReportAll
 * @args 		0
 * @return	website template
 * @desc		
 *
 **/
function AdminTemplate_Registration_ReportAll($pSchoolYears) {
  $ref_lib = new RefLibrary();
  $report_hdlr = new ReportHandler();
  $student_all = $report_hdlr->GetAllStudent($pSchoolYears, getSession('SortBy', 0));
  if (in_array('ClassTuitionFees', $_SESSION['DisplayOptions'])) {
	  $registrationfee_dues = $ref_lib->GetRefValues('SCHL_RegistrationFeeDue');
  }
	if (in_array('TuitionFeeStatus', $_SESSION['DisplayOptions'])) {
	  $tuition_status = $ref_lib->GetRefValues('SCHL_TuitionDue');
  }
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
	<table border="0" width="600" align="center" cellspacing="0" cellpadding="0">
		<tr height="100"> 
			<td align="center" style="font-size: 20px;font-weight:bold;">
        芳草地中文学校
		  </td>
		</tr>
	</table>
	<table border="1" align="center" cellspacing="0" cellpadding="0" class="thinborder" style="font-size: 13px">
		<tr>
<?php if (in_array('FamilyID', $_SESSION['DisplayOptions'])) { ?>
			<td width="80" align="center">家庭代码</td>
<?php } if (in_array('StudentName', $_SESSION['DisplayOptions'])) { ?>
			<td width="200" align="center">学生姓名</td>
<?php } if (in_array('StudentGender', $_SESSION['DisplayOptions'])) { ?>
			<td width="50" align="center">性别</td>
<?php } if (in_array('SchoolYear', $_SESSION['DisplayOptions'])) { ?>
			<td width="70" align="center">学期</td>
<?php } if (in_array('CourseName', $_SESSION['DisplayOptions'])) { ?>
			<td width="200" align="center">课程</td>
<?php } if (in_array('CourseLevel', $_SESSION['DisplayOptions'])) { ?>
			<td width="120" align="center">年级</td>
<?php } if (in_array('Teacher', $_SESSION['DisplayOptions'])) { ?>
			<td width="200" align="center">教师</td>
<?php } if (in_array('ContactInfo', $_SESSION['DisplayOptions'])) { ?>
				<td width="200" align="center">学生家庭住址</td>
			<td width="100" align="center">电话</td>
			<td width="100" align="center">EMAIL</td>
<?php } if (in_array('ClassTuitionFees', $_SESSION['DisplayOptions'])) { ?>
			<td width="30" align="center">学费</td>
			<td width="30" align="center">书费</td>
			<td width="30" align="center">注册费</td>
<?php } if (in_array('TuitionFeeStatus', $_SESSION['DisplayOptions'])) { ?>
			<td width="30" align="center">管理费</td>
			<td width="30" align="center">迟报名费</td>
			<td width="30" align="center">总计</td>
			<td width="30" align="center">已付</td>
			<td width="30" align="center">退款</td>
			<td width="30" align="center">备注</td>
<?php } ?>
		</tr>
<?php
  $current_familynmbr = '';
  $current_studentnmbr = '';
  for ($i = 0; $i < sizeof($student_all); $i++) {
?>
		<tr>
<?php if (in_array('FamilyID', $_SESSION['DisplayOptions'])) { ?>
			<td align="center">
        <?php echo $student_all[$i]['FamilyID']; ?>
      </td>
<?php } if (in_array('StudentName', $_SESSION['DisplayOptions'])) { ?>
			<td align="center">
        &nbsp;<?php echo $student_all[$i]['StudentLastName'] . ' ' . $student_all[$i]['StudentFirstName'] . ' ' . $student_all[$i]['StudentChineseName']; ?>
      </td>
<?php } if (in_array('StudentGender', $_SESSION['DisplayOptions'])) { ?>
			<td align="center">
        &nbsp;<?php echo $student_all[$i]['StudentGender']; ?>
      </td>
<?php } if (in_array('SchoolYear', $_SESSION['DisplayOptions'])) { ?>
			<td align="center">
        &nbsp;<?php echo $student_all[$i]['SchoolYear']; ?>
      </td>
<?php } if (in_array('CourseName', $_SESSION['DisplayOptions'])) { ?>
			<td align="center">
        &nbsp;<?php echo $student_all[$i]['CourseName_E'] . ' ' . $student_all[$i]['CourseName_C']; ?>
      </td>
<?php } if (in_array('CourseLevel', $_SESSION['DisplayOptions'])) { ?>
			<td align="center">
        &nbsp;<?php echo $student_all[$i]['CourseLevel_E'] . ' ' . $student_all[$i]['CourseLevel_C']; ?>
      </td>
<?php } if (in_array('Teacher', $_SESSION['DisplayOptions'])) { ?>
			<td align="center">
        &nbsp;<?php echo $student_all[$i]['TeacherLastName'] . ' ' . $student_all[$i]['TeacherFirstName'] . ' ' . $student_all[$i]['TeacherChineseName']; ?>
      </td>
<?php } if (in_array('ContactInfo', $_SESSION['DisplayOptions'])) { ?>
			<td align="center">
        &nbsp;<?php echo $student_all[$i]['Street'] . '<br/>' . $student_all[$i]['City'] . ' ' . $student_all[$i]['State'] . ' ' . $student_all[$i]['ZipCode']; ?>
      </td>
			<td align="center">
        &nbsp;<?php echo $student_all[$i]['HomeTelephone']; ?>
      </td>
			<td align="center">
        &nbsp;<?php echo $student_all[$i]['Email']; ?>
      </td>
<?php } 
      if (in_array('ClassTuitionFees', $_SESSION['DisplayOptions'])) {
        // one regfee for each registered student
        $registrationfee_due = "";
        for ($k = 0; $k < sizeof($registrationfee_dues); $k++) {
          if ($current_studentnmbr != $student_all[$i]['FamilyMemberNmbr'] && $student_all[$i]['FamilyMemberNmbr'] == $registrationfee_dues[$k]['FamilyMemberNmbr']) {
            $registrationfee_due = $student_all[$i]['RegistrationFee'];
            break;
          }
        }
?>
			<td align="center">
        &nbsp;<?php echo $student_all[$i]['Tuition']; ?>
      </td>
			<td align="center">
        &nbsp;<?php echo $student_all[$i]['BookFee']; ?>
      </td>
			<td align="center">
        &nbsp;<?php echo $registrationfee_due; ?>
      </td>
<?php } 
      if (in_array('TuitionFeeStatus', $_SESSION['DisplayOptions'])) {
        // one value per family
        $managementfee_due = "";
        $latefee_due = "";
        $tuition_due = "";
        $tuition_paid = "";
        $tuition_refund = "";
        for ($k = 0; $k < sizeof($tuition_status); $k++) {
          if ($current_familynmbr != $student_all[$i]['FamilyNmbr'] && $student_all[$i]['FamilyNmbr'] == $tuition_status[$k]['FamilyNmbr']) {
            $managementfee_due = $tuition_status[$k]['ManagementFeeDue'];
            $latefee_due = $tuition_status[$k]['LateFeeDue'];
            $tuition_due = $tuition_status[$k]['TotalFeeTuition'];
            $tuition_paid = $tuition_status[$k]['FeeTuitionPaid'];
            $tuition_refund = $tuition_status[$k]['Refund'];
            $note = $tuition_status[$k]['Note'];
            break;
          }
        }
?>
			<td align="center">
        &nbsp;<?php echo $managementfee_due; ?>
      </td>
			<td align="center">
        &nbsp;<?php echo $latefee_due; ?>
      </td>
			<td align="center">
        &nbsp;<?php echo $tuition_due; ?>
      </td>
			<td align="center">
        &nbsp;<?php echo $tuition_paid; ?>
      </td>
			<td align="center">
        &nbsp;<?php echo $tuition_refund; ?>
      </td>
			<td align="center">
        &nbsp;<?php echo $note; ?>
      </td>
		</tr>
<?php
      }
      $current_familynmbr = $student_all[$i]['FamilyNmbr'];
      $current_studentnmbr = $student_all[$i]['FamilyMemberNmbr'];
  }
?>
	</table>
	<table border="0" width="600" align="center" cellspacing="0" cellpadding="0">
		<tr height="100"> 
			<td>&nbsp;</td>
		</tr>
	</table>
</body>
</html>
<?php
}



?>


