<?php

/**
 *
 * FCD school management package
 * @author YUY
 * @version $Id$
 * @package FCDadmin
 * 
 **/

if (strlen(session_id()) < 5) {
	session_start();
}
// 0 = no, 1 = yes
$debug = 0;
if ($debug) {
	//error_reporting(E_ALL);
	ini_set("display_errors","1");
}
include_once 'LIB_Session.inc';
include_once 'LIB_SharedFormModules.inc';
include_once 'LIB_Utilities.inc';
include_once 'LIB_DbUtilities.inc';
include_once 'LIB_DbTaskHandlers.inc';
include_once 'FCD_Registration.inc';


//setSession();
if (isset($_POST['subjectid__'])) setSession('subjectid__');
if (isset($_POST['subtask__'])) setSession('subtask__');
GetManagerWebSite();

/***********
$l_to = "yuy_yhmail@yahoo.com";
$l_cc = "yuy_yhmail@yahoo.com";
$l_from = "test";
$l_subject = 'FCD Class Registration Test';
$l_msg = "New registration for FCD class(es):\n\n "
			 . "FamilyID: xxxx\n";
SendEmail($l_to, $l_cc, $l_from, $l_subject, $l_msg);
***********/


/**
 * 
 * FCD management web interface
 * @param
 * @desc		
 *
 */
function GetManagerWebSite() {
?>
	<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
	<html>
	<head>
	<title>FCD Management</title>
	<meta http-equiv="Content-Type" content="text/html"; charset="UTF-8">
	<link rel="stylesheet" type="text/css" href="stylesheet/fcd.css" />
	<script src="./javascript/FCD.js"></script>
	<script language="JavaScript" src="./javascript/mm_menu.js"></script>
	<script language="JavaScript" src="./javascript/hash.js"></script>
	</head>

	<body topmargin="0"  leftmargin="0" marginwidth="0" marginheight="0">
	<form name="form1" enctype="multipart/form-data" action="fcdschool_management.php" method="POST">
	<!-- ***************************************** -->
	<!--								Frame_1										 -->
	<!-- ***************************************** -->
		<table border="0" width="750" height="725" border="0" cellspacing="0" cellpadding="0" bgcolor="#E9FFEB" class="lefttoprightborder">
			<tr>
	<!-- ***************************************** -->
	<!--								Frame_3										 -->
	<!-- ***************************************** -->
				<td width="750" align="center" valign="top">
					<table width="750" align="center" border="0" cellspacing="0" cellpadding="0">
						<tr>
							<td width="180" height="80" align="center" class="adsfont">
								<a href="fcdschool_management.php"><img src="./images/FCD_Logo2.jpg"/></a>
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
	switch (getSession('subjectid', 0)) {
		case "MANAGE":
			if (getSession('subtask', 0) == 'checklogin') {
				if (CheckAdminLogin()) {
					AdminTaskHandler();
				}
				else {
					unsetSession();
					GetTemplate_Login('manage', 1);
				}
			}
			break;
		case "WEBSITE":
			include_once 'ADMIN_Website.inc';
			switch (getSession('subtask', 0)) {
				case "update_website":
					GetManageWebsite();
					break;
				case "refresh_website":
					setSession();
					GetManageWebsite();
					break;
				case "cancel_website":
					unsetSessionForNextTask('admin');
					AdminTaskHandler();
					break;
				case "submit_update_website":
					setSession();
					switch (getSession('WebsiteTask', 0)) {
						case "UpdateWebsite":
							AdmUpdateWebsite(getSession('LanguageNmbr', 0));
							break;
						case "DeleteSection":
							for ($i = 0; $i < sizeof($_SESSION['SectionToDelete']); $i++) {
								AdmDeleteSection(getSession('SectionToDelete', $i));
							}
							break;
						case "UpdatePhotogroup":
							AdmUpdatePhotogroup(getSession('PhotogroupEnglishLabel', 0), getSession('PhotogroupChineseLabel', 0));
							break;
						case "DeletePhotogroup":
							for ($i = 0; $i < sizeof($_SESSION['PhotogroupToDelete']); $i++) {
								AdmDeletePhotogroup(getSession('PhotogroupToDelete', $i));
							}
							break;
						default:
					}
					GetManageWebsite();
					break;
				case "view_report":
					break;
				default:
			}
			break;
		case "REG":
			include_once 'ADMIN_Registration.inc';
			switch (getSession('subtask', 0)) {
				case "list_family":
	        if (isset($_POST['SearchType__'])) setSession('SearchType__');
					AdminTemplate_StudentInfo('familylist');
					break;
				case "add_family":
					AdminTemplate_StudentInfo('familyinfo');
					break;
				case "edit_family":
					setSession('FamilyNmbr__');
					AdminTemplate_StudentInfo('familyinfo');
					break;
				case "add_student":
				  setSession('StudentCount__', (getSession('StudentCount', 0) + 1));
					AdminTemplate_StudentInfo('familyinfo');
					break;
				case "cancel_add_family":
					unsetSessionForNextTask('admin');
					AdminTemplate_StudentInfo('familylist');
					break;
				case "submit_add_family":
					$handler = new StudentAccountHandler();
					if (getSession('FamilyNmbr', 0) == '') { // create
						$family_nmbr = $handler->CreateFamily('', GetPostValue('UserName__'), GetPostValue('Password__'), GetPostValue('Street'), GetPostValue('City'), GetPostValue('State'), GetPostValue('Zip'), GetPostValue('HomeTelephone'), GetPostValue('Email'));
						if (GetPostValue('FatherLastName') != '' || GetPostValue('FatherChineseName') != '') {
							$handler->CreateFamilyMember($family_nmbr, 5, GetPostValue('FatherLastName'), GetPostValue('FatherFirstName'), GetPostValue('FatherMiddleName'), GetPostValue('FatherChineseName'), GetPostValue('FatherGender'), GetPostValue('FatherBirthDate'), GetPostValue('WorkTelephone'), GetPostValue('FatherEmail'), 'yes');
						}
						if (GetPostValue('MotherLastName') != '' || GetPostValue('MotherChineseName') != '') {
							$handler->CreateFamilyMember($family_nmbr, 6, GetPostValue('MotherLastName'), GetPostValue('MotherFirstName'), GetPostValue('MotherMiddleName'), GetPostValue('MotherChineseName'), GetPostValue('MotherGender'), GetPostValue('MotherBirthDate'), GetPostValue('WorkTelephone'), GetPostValue('MotherEmail'), 'yes');
						}
						for ($i = 0; $i < getSession('StudentCount', 0); $i++) {
							if (GetPostValue('StudentLastName' . $i) != '' || GetPostValue('StudentChineseName' . $i) != '') {
								$handler->CreateFamilyMember($family_nmbr, 7, GetPostValue('StudentLastName' . $i), GetPostValue('StudentFirstName' . $i), GetPostValue('StudentMiddleName' . $i), GetPostValue('StudentChineseName' . $i), GetPostValue('StudentGender' . $i), GetPostValue('StudentBirthDate' . $i), GetPostValue('WorkTelephone' . $i), GetPostValue('StudentEmail' . $i), GetPostValue('StudentIsAdult' . $i));
							}
						}
					}
					else { // edit
						if ($handler->UpdateFamily(getSession('FamilyNmbr', 0), GetPostValue('UserName__'), GetPostValue('Password__'), GetPostValue('Street'), GetPostValue('City'), GetPostValue('State'), GetPostValue('Zip'), GetPostValue('HomeTelephone'), GetPostValue('Email'))) {
							if (GetPostValue('FatherLastName') != '' || GetPostValue('FatherChineseName') != '') {
								if (getSession('FatherFamilyMemberNmbr', 0) != '') {
									$handler->UpdateFamilyMember(getSession('FatherFamilyMemberNmbr', 0), 5, GetPostValue('FatherLastName'), GetPostValue('FatherFirstName'), GetPostValue('FatherMiddleName'), GetPostValue('FatherChineseName'), GetPostValue('FatherGender'), GetPostValue('FatherBirthDate'), GetPostValue('FatherWorkTelephone'), GetPostValue('FatherEmail'), 'yes');
								}
								else {
									$handler->CreateFamilyMember(getSession('FamilyNmbr', 0), 5, GetPostValue('FatherLastName'), GetPostValue('FatherFirstName'), GetPostValue('FatherMiddleName'), GetPostValue('FatherChineseName'), GetPostValue('FatherGender'), GetPostValue('FatherBirthDate'), GetPostValue('FatherWorkTelephone'), GetPostValue('FatherEmail'), 'yes');
								}
							}
							if (GetPostValue('MotherLastName') != '' || GetPostValue('MotherChineseName') != '') {
								if (getSession('MotherFamilyMemberNmbr', 0) != '') {
									$handler->UpdateFamilyMember(getSession('MotherFamilyMemberNmbr', 0), 6, GetPostValue('MotherLastName'), GetPostValue('MotherFirstName'), GetPostValue('MotherMiddleName'), GetPostValue('MotherChineseName'), GetPostValue('MotherGender'), GetPostValue('MotherBirthDate'), GetPostValue('MotherWorkTelephone'), GetPostValue('MotherEmail'), 'yes');
								}
								else {
									$handler->CreateFamilyMember(getSession('FamilyNmbr', 0), 6, GetPostValue('MotherLastName'), GetPostValue('MotherFirstName'), GetPostValue('MotherMiddleName'), GetPostValue('MotherChineseName'), GetPostValue('MotherGender'), GetPostValue('MotherBirthDate'), GetPostValue('MotherWorkTelephone'), GetPostValue('MotherEmail'), 'yes');
								}
							}
							for ($i = 0; $i < getSession('StudentCount', 0); $i++) {
								if (getSession('StudentFamilyMemberNmbr' . $i, 0) != '') {
									if (GetPostValue('StudentLastName' . $i) != '' || GetPostValue('StudentChineseName' . $i) != '') {
										$handler->UpdateFamilyMember(getSession('StudentFamilyMemberNmbr' . $i, 0), 7, GetPostValue('StudentLastName' . $i), GetPostValue('StudentFirstName' . $i), GetPostValue('StudentMiddleName' . $i), GetPostValue('StudentChineseName' . $i), GetPostValue('StudentGender' . $i), GetPostValue('StudentBirthDate' . $i), GetPostValue('StudentWorkTelephone' . $i), GetPostValue('StudentEmail' . $i), GetPostValue('StudentIsAdult' . $i));
									}
									else {
										$handler->DeleteFamilyMember(getSession('StudentFamilyMemberNmbr' . $i, 0));
									}
								}
								else {
									if (GetPostValue('StudentLastName' . $i) != '' || GetPostValue('StudentChineseName' . $i) != '') {
                  	$handler->CreateFamilyMember(getSession('FamilyNmbr', 0), 7, GetPostValue('StudentLastName' . $i), GetPostValue('StudentFirstName' . $i), GetPostValue('StudentMiddleName' . $i), GetPostValue('StudentChineseName' . $i), GetPostValue('StudentGender' . $i), GetPostValue('StudentBirthDate' . $i), GetPostValue('WorkTelephone' . $i), GetPostValue('StudentEmail' . $i), GetPostValue('StudentIsAdult' . $i));
                  }
								}
							}
						}
					}
					unsetSessionForNextTask('admin');
					AdminTemplate_StudentInfo('familylist');
					break;
				case "course_registration":
					AdminTemplate_Registration('familylist');
					break;
				case "goto_registration":
					setSession();
					AdminTemplate_Registration('regist');
					break;
				case "cancel_registration":
					unsetSessionForNextTask('admin');
					AdminTemplate_Registration('familylist');
					break;
				case "refresh_reg":
					setSession();
					AdminTemplate_Registration('regist');
					break;
				case "add_registration":
					setSession();
					$family_nmbr = getSession('FamilyNmbr', 0);
					$handler = new RegistrationHandler();
					if (getSession('RegistrationNmbr', 0) == '') { // create
						$handler->CreateNewRegistration(getSession('FamilyMemberNmbr', 0), getSession('ClassNmbr', 0), getSession('SchoolYear', 0));
					}
					else { // update
						$handler->UpdateRegistration(getSession('RegistrationNmbr', 0), getSession('ClassNmbr', 0), getSession('SchoolYear', 0));
					}
					$ref_lib = new RefLibrary();
					$tuition_handler = new TuitionFeeHandler();
					// update registration due
          $registrationfee_due = $tuition_handler->GetRegistrationFee(getSession('SchoolYear', 0), 'no_check', date("Y-m-d"));
					if (isset($registrationfee_due[0]['RegistrationFeeNmbr']) && $registrationfee_due[0]['RegistrationFeeNmbr'] != '') {
            $regfee_nmbr = $registrationfee_due[0]['RegistrationFeeNmbr'];
            $tuition_handler->UpdateRegistrationFeeDue(getSession('FamilyMemberNmbr', 0), $regfee_nmbr, getSession('SchoolYear', 0));
          }
					// update tuition due
					$tuition_info = $tuition_handler->CalculateTuitionFromDb(getSession('FamilyNmbr', 0), getSession('RegMethod', 0), getSession('RegDate', 0));
					$managementfee_due = $tuition_info['ManagementFeeDue'];
					$latefee_due = $tuition_info['LateFeeDue'];
					$tuition_due = $tuition_info['TuitionDue'];
          $school_year = $ref_lib->GetSchoolYear('active_year');
					$tuition_handler->UpdateTuitionDue(getSession('FamilyNmbr', 0), $school_year[0]['SchoolYear'], 0, $managementfee_due, $latefee_due, $tuition_due, '', '', '', '', getSession('RegDate', 0), getSession('RegMethod', 0), '', 'OPEN');
					unsetSessionForNextTask('admin');
					setSession('FamilyNmbr__', $family_nmbr);
					setSession('SchoolYear__', $school_year[0]['SchoolYear']);
					AdminTemplate_Registration('regist');
					break;
				case "delete_registration":
					setSession();
					$family_nmbr = getSession('FamilyNmbr', 0);
					$handler = new RegistrationHandler();
					$handler->DeleteRegistration(getSession('RegistrationNmbr', 0));
					$tuition_handler = new TuitionFeeHandler();
					// update registration due
          $registrationfee_due = $tuition_handler->GetRegistrationFee(getSession('SchoolYear', 0), 'no_check', date("Y-m-d"));
					if (isset($registrationfee_due[0]['RegistrationFeeNmbr']) && $registrationfee_due[0]['RegistrationFeeNmbr'] != '') {
            $regfee_nmbr = $registrationfee_due[0]['RegistrationFeeNmbr'];
            $tuition_handler->UpdateRegistrationFeeDue(getSession('FamilyMemberNmbr', 0), $regfee_nmbr, getSession('SchoolYear', 0));
          }
					// update tuition due
					$tuition_info = $tuition_handler->CalculateTuitionFromDb(getSession('FamilyNmbr', 0), getSession('RegMethod', 0), getSession('RegDate', 0));
					$managementfee_due = $tuition_info['ManagementFeeDue'];
					$latefee_due = $tuition_info['LateFeeDue'];
					$tuition_due = $tuition_info['TuitionDue'];
					$tuition_handler->UpdateTuitionDue(getSession('FamilyNmbr', 0), getSession('SchoolYear', 0), 0, $managementfee_due, $latefee_due, $tuition_due, '', '', '', '', getSession('RegDate', 0), getSession('RegMethod', 0), '', 'OPEN');
					unsetSessionForNextTask('admin');
					setSession('FamilyNmbr__', $family_nmbr);
					AdminTemplate_Registration('regist');
					break;
				case "view_report":
					AdminTemplate_Registration_ViewReport('by_class');
					break;
				case "refresh_report":
					setSession();
					AdminTemplate_Registration_ViewReport('by_class');
					break;
				case "list_family_for_admission_letter":
					AdminTemplate_Registration_PrintAdmission('familylist', '');
					break;
				case "refresh_print_admission":
					setSession();
          if (!isset($_POST['FamilyNmbr'])) unsetSession('FamilyNmbr');
					AdminTemplate_Registration_PrintAdmission('familylist', '');
					break;
				default:
			}
			break;
		case "CURRICULUM":
			include_once 'ADMIN_Curriculum.inc';
			switch (getSession('subtask', 0)) {
				case "add_course":
					AdminTemplate_AddCourse();
					break;
				case "refresh_course":
					unsetSessionForNextTask('admin');
					setSession('CourseNmbr__');
					AdminTemplate_AddCourse();
					break;
				case "submit_add_course":
					setSession();
					$handler = new CurriculumHandler();
					if (getSession('CourseNmbr', 0) == '') { // add
						$handler->AddCourse(getSession('CourseCategoryNmbr', 0), getSession('CourseName_E', 0), getSession('CourseName_C', 0));
					}
					else { // edit
						$handler->UpdateCourse(getSession('CourseNmbr', 0), getSession('CourseCategoryNmbr', 0), getSession('CourseName_E', 0), getSession('CourseName_C', 0));
					}
					unsetSessionForNextTask('admin');
					AdminTemplate_AddCourse();
					break;
				case "delete_course":
					if (getSession('CourseNmbr', 0) != '') {
						$handler = new CurriculumHandler();
						$handler->DeleteCourse(getSession('CourseNmbr', 0));
					}
					unsetSessionForNextTask('admin');
					AdminTemplate_AddCourse();
					break;
				// --- classroom
				case "classroom":
					AdminTemplate_Classroom();
					break;
				case "refresh_classroom":
					setSession('ClassroomNmbr__');
					AdminTemplate_Classroom();
					break;
				case "add_classroom":
					setSession();
					$handler = new AdministrativeTaskHandler();
					if (getSession('ClassroomNmbr', 0) == '') { // add
						$handler->AddClassroom(getSession('Classroom', 0));
					}
					else {
						$handler->UpdateClassroom(getSession('ClassroomNmbr', 0), getSession('Classroom', 0));
					}
					unsetSessionForNextTask('admin');
					AdminTemplate_Classroom();
					break;
				case "delete_classroom":
					setSession();
					$handler = new AdministrativeTaskHandler();
					$handler->DeleteClassroom(getSession('ClassroomNmbr', 0));
					unsetSessionForNextTask('admin');
					AdminTemplate_Classroom();
					break;
				// --- class builder
				case "class_builder":
					AdminTemplate_ClassBuilder();
					break;
				case "refresh_class":
					unsetSessionForNextTask('admin');
					setSession('ClassNmbr__');
					AdminTemplate_ClassBuilder();
					break;
				case "submit_class":
					setSession();
					$handler = new CurriculumHandler();
					if (getSession('ClassNmbr', 0) == '') { // add
						$handler->BuildClass(getSession('CourseNmbr', 0), getSession('CourseLevelNmbr', 0), getSession('ClassroomNmbr', 0), getSession('ClassPeriodNmbr', 0), getSession('ClassName_E', 0), getSession('ClassName_C', 0));
					}
					else { // edit
						$handler->UpdateClass(getSession('ClassNmbr', 0), getSession('CourseNmbr', 0), getSession('CourseLevelNmbr', 0), getSession('ClassroomNmbr', 0), getSession('ClassPeriodNmbr', 0), getSession('ClassName_E', 0), getSession('ClassName_C', 0));
					}
					unsetSessionForNextTask('admin');
					AdminTemplate_ClassBuilder();
					break;
				case "delete_class":
					setSession();
					$handler = new CurriculumHandler();
					$handler->DeleteClass(getSession('ClassNmbr', 0));
					unsetSessionForNextTask('admin');
					AdminTemplate_ClassBuilder();
					break;
				case "view_report":
					AdminTemplate_Curriculum_ViewReport('under_construction');
					break;
				default:
			}
			break;
		case "STAFF":
			include_once 'ADMIN_Staff.inc';
			switch (getSession('subtask', 0)) {
				case "add":
					AdminTemplate_StaffInfo();
					break;
				case "refresh_staff":
					unsetSessionForNextTask('admin');
					setSession('StaffNmbr__');
					AdminTemplate_StaffInfo();
					break;
				case "submit_add_staff":
					setSession();
					$handler = new StaffAccountHandler();
					if (getSession('StaffNmbr', 0) == '') {
						$handler->CreateStaff(getSession('FcdRoleNmbr', 0), getSession('UserName', 0), getSession('Password', 0), getSession('LastName', 0), getSession('FirstName', 0), getSession('MiddleName', 0), getSession('ChineseName', 0), getSession('Gender', 0), getSession('Street', 0), getSession('City', 0), getSession('State', 0), getSession('Zip', 0), getSession('HomeTelephone', 0), getSession('WorkTelephone', 0), getSession('Email', 0));
					}
					else {
						$handler->UpdateStaff(getSession('StaffNmbr', 0), getSession('FcdRoleNmbr', 0), getSession('UserName', 0), getSession('Password', 0), getSession('LastName', 0), getSession('FirstName', 0), getSession('MiddleName', 0), getSession('ChineseName', 0), getSession('Gender', 0), getSession('Street', 0), getSession('City', 0), getSession('State', 0), getSession('Zip', 0), getSession('HomeTelephone', 0), getSession('WorkTelephone', 0), getSession('Email', 0));
					}
					unsetSessionForNextTask('admin');
					AdminTemplate_StaffInfo();
					break;
				case "assign_teaching_job":
					AdminTemplate_TeachingAssignment();
					break;
				case "refresh_teaching_assignment":
					unsetSessionForNextTask('admin');
					setSession('TeachingAssignmentNmbr__');
					AdminTemplate_TeachingAssignment();
					break;
				case "submit_teaching_assignment":
					setSession();
					$handler = new StaffAccountHandler();
					if (getSession('TeachingAssignmentNmbr', 0) == '') {
						$handler->AssignTeachingTask(getSession('StaffNmbr', 0), getSession('ClassNmbr', 0), getSession('SchoolYear', 0));
					}
					else {
						$handler->UpdateTeachingTask(getSession('TeachingAssignmentNmbr', 0), getSession('StaffNmbr', 0), getSession('ClassNmbr', 0), getSession('SchoolYear', 0));
					}
					unsetSessionForNextTask('admin');
					AdminTemplate_TeachingAssignment();
					break;
				case "delete_teaching_assignment":
					setSession();
					$handler = new StaffAccountHandler();
					$handler->DeleteTeachingAssignment(getSession('TeachingAssignmentNmbr', 0));
					unsetSessionForNextTask('admin');
					AdminTemplate_TeachingAssignment();
					break;
				case "view_report":
					AdminTemplate_Staff_ViewReport('under_construction');
					break;
				default:
			}
			break;
		case "GRADE":
			include_once 'ADMIN_Grade.inc';
			switch (getSession('subtask', 0)) {
				case "refresh":
					setSession();
					AdminTemplate_GradeTracking();
					break;
				case "add_grade":
					AdminTemplate_GradeTracking();
					break;
				case "submit_grade_tracking":
					setSession();
					$handler = new StudentGradeHandler();
					$handler->UpdateStudentGrade(
						getSession('StudentNmbr', 0), 
						getSession('SchoolYear', 0), 
						getSession('ClassNmbr', 0), 
						getSession('MarkingPeriod', 0), 
						getSession('VocabDictation', 0),
						getSession('VocabDictationExtraCredit', 0),
						getSession('ParagraphDictation', 0),
						getSession('SentenceMaking', 0),
						getSession('PassageUnderstanding', 0),
						getSession('ReadingComprehension', 0),
						getSession('WrittenExamTotal', 0),
						getSession('VocabRecognition', 0),
						getSession('PassageReading', 0),
						getSession('PassageRecording', 0),
						getSession('PassageReadingExtraCredit', 0),
						getSession('OralExamTotal', 0),
						getSession('HomeworkCompletion', 0),
						getSession('Quiz', 0),
						getSession('Attendance', 0),
						getSession('Participation', 0),
						getSession('ChineseSpeaking', 0),
						getSession('Grade', 0)
					);
					//unsetSessionForNextTask('admin');
					AdminTemplate_GradeTracking();
					break;
				case "view_report":
					AdminTemplate_Grade_ViewReport('under_construction');
					break;
				default:
			}
			break;
		case "ACCOUNTING":
			include_once 'ADMIN_Accounting.inc';
			switch (getSession('subtask', 0)) {
				case "school_fees":
					AdminTemplate_SchoolFees();
					break;
				case "refresh_school_fee":
					unsetSessionForNextTask('admin');
					setSession('SchoolFeesNmbr__');
					AdminTemplate_SchoolFees();
					break;
				case "registration_fee":
					AdminTemplate_RegistrationFee();
					break;
				case "refresh_reg_fee":
					unsetSessionForNextTask('admin');
					setSession('RegistrationFeeNmbr__');
					AdminTemplate_RegistrationFee();
					break;
				case "add_reg_fee":
					setSession();
					$handler = new TuitionFeeHandler();
					if (getSession('RegistrationFeeNmbr', 0) == '') { // add
						$handler->AddRegistrationFee(getSession('SchoolYear', 0), getSession('RegistrationFee', 0), getSession('StartDate', 0), getSession('EndDate', 0));
					}
					else { // edit
						$handler->UpdateRegistrationFee(getSession('RegistrationFeeNmbr', 0), getSession('SchoolYear', 0), getSession('RegistrationFee', 0), getSession('StartDate', 0), getSession('EndDate', 0));
					}
					unsetSessionForNextTask('admin');
					AdminTemplate_RegistrationFee();
					break;
				case "delete_reg_fee":
					setSession();
					$handler = new TuitionFeeHandler();
					$handler->DeleteRegistrationFee(getSession('RegistrationFeeNmbr', 0));
					unsetSessionForNextTask('admin');
					AdminTemplate_RegistrationFee();
					break;
				case "add_school_fee":
					setSession();
					$handler = new TuitionFeeHandler();
					if (getSession('SchoolFeesNmbr', 0) == '') { // add
						$handler->AddSchoolFees(getSession('SchoolYear', 0), getSession('SchoolFee', 0), getSession('SchoolFeeName_E', 0), getSession('SchoolFeeName_C', 0), getSession('EffectiveDate', 0));
					}
					else { // edit
						$handler->UpdateSchoolFees(getSession('SchoolFeesNmbr', 0), getSession('SchoolYear', 0), getSession('SchoolFee', 0), getSession('SchoolFeeName_E', 0), getSession('SchoolFeeName_C', 0), getSession('EffectiveDate', 0));
					}
					unsetSessionForNextTask('admin');
					AdminTemplate_SchoolFees();
					break;
				case "delete_school_fee":
					setSession();
					$handler = new TuitionFeeHandler();
					$handler->DeleteSchoolFees(getSession('SchoolFeesNmbr', 0));
					unsetSessionForNextTask('admin');
					AdminTemplate_SchoolFees();
					break;
				case "tuition":
					AdminTemplate_Tuition();
					break;
				case "refresh_tuition":
					unsetSessionForNextTask('admin');
					setSession();
					AdminTemplate_Tuition();
					break;
				case "add_tuition":
					setSession();
					$handler = new TuitionFeeHandler();
					if (getSession('TuitionNmbr', 0) == '') { // add
						$handler->AddTuition(getSession('CourseCategoryNmbr', 0), getSession('SchoolYear', 0), getSession('Tuition', 0), getSession('BookFee', 0), getSession('LabFee', 0), getSession('OtherFee', 0), '');
					}
					else {
						$handler->UpdateTuition(getSession('TuitionNmbr', 0), getSession('CourseCategoryNmbr', 0), getSession('SchoolYear', 0), getSession('Tuition', 0), getSession('BookFee', 0), getSession('LabFee', 0), getSession('OtherFee', 0), '');
					}
					unsetSessionForNextTask('admin');
					AdminTemplate_Tuition();
					break;
				case "delete_tuition":
					setSession();
					$handler = new TuitionFeeHandler();
					if (getSession('TuitionNmbr', 0) != '') $handler->DeleteTuition(getSession('TuitionNmbr', 0));
					unsetSessionForNextTask('admin');
					AdminTemplate_Tuition();
					break;
				case "refresh_tuitiondue":
					unsetSessionForNextTask('admin');
					setSession();
					AdminTemplate_PaymentStatus();
					break;
				case "edit_payment_status":
					AdminTemplate_PaymentStatus();
					break;
				case "edit_payment_status_next":
          setSession('FamilyNmbr__');
					AdminTemplate_PaymentStatus();
					break;
				case "back_to_payment_status_list":
					unsetSession('FamilyNmbr');
          AdminTemplate_PaymentStatus();
					break;
				case "submit_payment_status":
					setSession();
					$handler = new TuitionFeeHandler();
					$payment_status = $handler->GetTuitionDue(getSession('SchoolYear', 0), getSession('FamilyNmbr', 0));

						if (getSession('TuitionPaid', 0) == '') $l_tuitionpaid = '';
						else $l_tuitionpaid = getSession('TuitionPaid', 0);
						if (getSession('CheckNmbr', 0) == '') $l_checknmbr = '';
						else $l_checknmbr = getSession('CheckNmbr', 0);
						$handler->UpdateTuitionDue($payment_status[0]['FamilyNmbr'], getSession('SchoolYear', 0), $payment_status[0]['RegistrationFeeDue'], $payment_status[0]['ManagementFeeDue'], $payment_status[0]['LateFeeDue'], $payment_status[0]['TotalFeeTuition'], $l_tuitionpaid, $l_checknmbr, getSession('Refund', 0), getSession('RefundCheckNmbr', 0), '', '', getSession('RegNote', 0), getSession('RegStatus', 0));

					$school_year = getSession('SchoolYear', 0);
					unsetSessionForNextTask('admin');
					setSession('SchoolYear__', $school_year);
					AdminTemplate_PaymentStatus();
					break;
				case "view_report":
					AdminTemplate_Accounting_ViewReport('under_construction');
					break;
				default:
			}
			break;
		case "ADMINISTRATIVE":
			include_once 'ADMIN_Administrative.inc';
			switch (getSession('subtask', 0)) {
				// --- school year
				case "school_year":
					AdminTemplate_SchoolYear();
					break;
				case "refresh_schoolyear":
					setSession('SchoolYear__');
					AdminTemplate_SchoolYear();
					break;
				case "add_schoolyear":
					setSession();
					$handler = new AdministrativeTaskHandler();
					if (getSession('SchoolYear', 0) == '') { // add
						$handler->AddSchoolYear(getSession('NewSchoolYear', 0), getSession('Semester', 0), getSession('SemesterGroup', 0), getSession('DisplayOrder', 0));
					}
					else {
						$handler->UpdateSchoolYear(getSession('SchoolYear', 0), getSession('NewSchoolYear', 0), getSession('Semester', 0), getSession('SemesterGroup', 0), getSession('DisplayOrder', 0));
					}
					unsetSessionForNextTask('admin');
					AdminTemplate_SchoolYear();
					break;
				case "delete_schoolyear":
					setSession();
					$handler = new AdministrativeTaskHandler();
					$handler->DeleteSchoolYear(getSession('SchoolYear', 0));
					unsetSessionForNextTask('admin');
					AdminTemplate_SchoolYear();
					break;
				// --- course category
				case "course_category":
					AdminTemplate_CourseCategory();
					break;
				case "refresh_course_category":
					setSession('CourseCategoryNmbr__');
					AdminTemplate_CourseCategory();
					break;
				case "add_course_category":
					setSession();
					$handler = new AdministrativeTaskHandler();
					if (getSession('CourseCategoryNmbr', 0) == '') { // add
						$handler->AddCourseCategory(getSession('CourseCategory_E', 0), getSession('CourseCategory_C', 0), getSession('CourseType', 0));
					}
					else {
						$handler->UpdateCourseCategory(getSession('CourseCategoryNmbr', 0), getSession('CourseCategory_E', 0), getSession('CourseCategory_C', 0), getSession('CourseType', 0));
					}
					unsetSessionForNextTask('admin');
					AdminTemplate_CourseCategory();
					break;
				case "delete_course_category":
					setSession();
					$handler = new AdministrativeTaskHandler();
					$handler->DeleteCourseCategory(getSession('CourseCategoryNmbr', 0));
					unsetSessionForNextTask('admin');
					AdminTemplate_CourseCategory();
					break;
				// --- course level
				case "course_level":
					AdminTemplate_CourseLevel();
					break;
				case "refresh_course_level":
					setSession('CourseLevelNmbr__');
					AdminTemplate_CourseLevel();
					break;
				case "add_course_level":
					setSession();
					$handler = new AdministrativeTaskHandler();
					if (getSession('CourseLevelNmbr', 0) == '') { // add
						$handler->AddCourseLevel(getSession('CourseLevel_E', 0), getSession('CourseLevel_C', 0));
					}
					else {
						$handler->UpdateCourseLevel(getSession('CourseLevelNmbr', 0), getSession('CourseLevel_E', 0), getSession('CourseLevel_C', 0));
					}
					unsetSessionForNextTask('admin');
					AdminTemplate_CourseLevel();
					break;
				case "delete_course_level":
					setSession();
					$handler = new AdministrativeTaskHandler();
					$handler->DeleteCourseLevel(getSession('CourseLevelNmbr', 0));
					unsetSessionForNextTask('admin');
					AdminTemplate_CourseLevel();
					break;
				// --- class period
				case "class_period":
					AdminTemplate_ClassPeriod();
					break;
				case "refresh_class_period":
					setSession('ClassPeriodNmbr__');
					AdminTemplate_ClassPeriod();
					break;
				case "add_class_period":
					setSession();
					$handler = new AdministrativeTaskHandler();
					if (getSession('ClassPeriodNmbr', 0) == '') { // add
						$handler->AddClassPeriod(getSession('ClassPeriod_E', 0), getSession('ClassPeriod_C', 0), getSession('ClassTime', 0));
					}
					else {
						$handler->UpdateClassPeriod(getSession('ClassPeriodNmbr', 0), getSession('ClassPeriod_E', 0), getSession('ClassPeriod_C', 0), getSession('ClassTime', 0));
					}
					unsetSessionForNextTask('admin');
					AdminTemplate_ClassPeriod();
					break;
				case "delete_class_period":
					setSession();
					$handler = new AdministrativeTaskHandler();
					$handler->DeleteClassPeriod(getSession('ClassPeriodNmbr', 0));
					unsetSessionForNextTask('admin');
					AdminTemplate_ClassPeriod();
					break;
				// --- marking period
				case "marking_period":
					AdminTemplate_MarkingPeriod();
					break;
				case "refresh_marking_period":
					setSession('MarkingPeriod__');
					AdminTemplate_MarkingPeriod();
					break;
				case "add_marking_period":
					setSession();
					$handler = new AdministrativeTaskHandler();
					if (getSession('MarkingPeriod', 0) == '') { // add
						$handler->AddMarkingPeriod(getSession('NewMarkingPeriod', 0));
					}
					else {
						$handler->UpdateMarkingPeriod(getSession('MarkingPeriod', 0), getSession('NewMarkingPeriod', 0));
					}
					unsetSessionForNextTask('admin');
					AdminTemplate_MarkingPeriod();
					break;
				case "delete_marking_period":
					setSession();
					$handler = new AdministrativeTaskHandler();
					$handler->DeleteMarkingPeriod(getSession('MarkingPeriod', 0));
					unsetSessionForNextTask('admin');
					AdminTemplate_MarkingPeriod();
					break;
				// --- role
				case "role":
					AdminTemplate_Role();
					break;
				case "refresh_role":
					setSession('FcdRoleNmbr__');
					AdminTemplate_Role();
					break;
				case "add_role":
					setSession();
					$handler = new AdministrativeTaskHandler();
					if (getSession('FcdRoleNmbr', 0) == '') { // add
						$handler->AddFcdRole(getSession('FcdRole_E', 0), getSession('FcdRole_C', 0));
					}
					else {
						$handler->UpdateFcdRole(getSession('FcdRoleNmbr', 0), getSession('FcdRole_E', 0), getSession('FcdRole_C', 0));
					}
					unsetSessionForNextTask('admin');
					AdminTemplate_Role();
					break;
				case "delete_role":
					setSession();
					$handler = new AdministrativeTaskHandler();
					$handler->DeleteFcdRole(getSession('FcdRoleNmbr', 0));
					unsetSessionForNextTask('admin');
					AdminTemplate_Role();
					break;
				// --- sql
				case "sql":
					AdminTemplate_Sql();
					break;
				case "submit_sql":
					setSession();
					$handler = new AdministrativeTaskHandler();
					$handler->RunSQL();
					unsetSessionForNextTask('admin');
					AdminTemplate_Sql();
					break;
				default:
			}
			break;
		case "CANCELSUBTASK":
			unsetSessionForNextTask('admin');
			AdminTaskHandler();
			break;
		case "CANCEL":
			unsetSession();
			GetTemplate_Login('manage', 1);
			break;
		default:
			unsetSession();
			GetTemplate_Login('manage', 1);
	}
?>
				</td>
			</tr>
			<tr>
				<td align="right">
					&nbsp;
					<input type="hidden" name="subjectid__" value="" />
					<input type="hidden" name="subtask__" value="" />
				</td>
			</tr>
			<tr>
				<td width="750" height="80" align="center" valign="bottom">
					<hr/>
					<font size="2" color="#009900">&copy; All rights reserved. &nbsp; FCD Chinese School</font>
				</td>
				<td width="15">&nbsp;</td>
			</tr>
		</table>
	</form>	
	</body>
<?php
}

/**
 *
 * @name 		AdminTaskHandler
 * @args 		0
 * @return	website template
 * @desc		
 *
 */
function AdminTaskHandler() {
?>
	<table border="0" width="500" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td>
				<table width="650" align="center" cellspacing="0" cellpadding="0">
					<tr>
						<td>&nbsp;</td>
					</tr>
					<tr>
						<td align="right">
							<input class="smallwhitesubmit" type="button" name="Submit" value="Log out" 
							onClick="document.form1.subjectid__.value='CANCEL';document.form1.subtask__.value='cancel';document.form1.submit();" />
						</td>
					</tr>
				</table>
				<table width="500" align="center" cellspacing="0" cellpadding="0">
					<tr>
						<td>&nbsp;</td>
					</tr>
					<tr>
						<td align="center">
							<font size="3" color="darkred"><b>FCD School Management</b></font><br/>
						</td>
					</tr>
					<tr>
						<td>&nbsp;</td>
					</tr>
					<tr height="80" valign="top">
						<td class="contentfont">
							Use following options to manage FCD school related matters.  Please note that certain information need to be in
							the system to allow others to function.  Example: curriculum and teacher information need to be in the system 
							before student registration can be worked on.
						</td>
					</tr>
					<?php 
					if (getSession('LoginRole', 0) == 'Principal' 
					|| getSession('LoginRole', 0) == 'Webmaster'
					|| getSession('LoginRole', 0) == 'Administrator'
					) {
					/****************************************************************
					*                           Website                             *
					*****************************************************************/
					?>
					<tr align="center">
						<td class="contentfont">
		          <table border="0" bgcolor="#C1E8BE" class="thinborder" style="font-size: 12px;">
		          	<tr>
		          		<td width="200">&nbsp;</td>
		          		<td width="300">&nbsp;</td>
								</tr>
		          	<tr>
		          		<td>
		          			&nbsp;&nbsp;&nbsp;&nbsp;
		          			FCD Website
		          		</td>
		          		<td>
										<input type="button" name="Submit" value="Update FCD Website" style="width: 200px;font-size: 12px;"
										onClick="document.form1.subjectid__.value='WEBSITE';document.form1.subtask__.value='update_website';document.form1.submit();" />
									</td>
								</tr>
		          	<tr>
		          		<td>&nbsp;</td>
		          		<td>
										<input type="button" name="Submit" value="Visit Count" style="width: 200px;font-size: 12px;"
										onClick="document.form1.subjectid__.value='WEBSITE';document.form1.subtask__.value='view_report';document.form1.submit();" />
									</td>
								</tr>
		          	<tr>
		          		<td>&nbsp;</td>
		          		<td>&nbsp;</td>
								</tr>
		          </table>
		        </td>
		      </tr>
        	<tr height="50" valign="center">
        		<td><hr/></td>
					</tr>
					<?php 
					}
					if (getSession('LoginRole', 0) == 'Principal'
					|| getSession('LoginRole', 0) == 'Administrator'
					) {
					/****************************************************************
					*                     Staff and Teacher                         *
					*****************************************************************/
					?>
					<tr align="center">
						<td class="contentfont">
		          <table border="0" bgcolor="#C1E8BE" class="thinborder" style="font-size: 12px;">
		          	<tr>
		          		<td width="200">&nbsp;</td>
		          		<td width="300">&nbsp;</td>
								</tr>
		          	<tr>
		          		<td>
		          			&nbsp;&nbsp;&nbsp;&nbsp;
		          			Staff and Teacher
		          		</td>
		          		<td>
										<input type="button" name="Submit" value="Staff / Teacher Information" style="width: 200px;font-size: 12px;"
										onClick="document.form1.subjectid__.value='STAFF';document.form1.subtask__.value='add';document.form1.submit();" />
									</td>
								</tr>
		          	<tr>
		          		<td>&nbsp;</td>
		          		<td>
										<input type="button" name="Submit" value="Assign Teaching Task" style="width: 200px;font-size: 12px;"
										onClick="document.form1.subjectid__.value='STAFF';document.form1.subtask__.value='assign_teaching_job';document.form1.submit();" />
									</td>
								</tr>
		          	<tr>
		          		<td>&nbsp;</td>
		          		<td>
										<input type="button" name="Submit" value="View Report" style="width: 200px;font-size: 12px;"
										onClick="document.form1.subjectid__.value='STAFF';document.form1.subtask__.value='view_report';document.form1.submit();" />
									</td>
								</tr>
		          	<tr>
		          		<td>&nbsp;</td>
		          		<td>&nbsp;</td>
								</tr>
		          </table>
		        </td>
		      </tr>
        	<tr>
        		<td>&nbsp;</td>
					</tr>
					<?php 
					}
					if (getSession('LoginRole', 0) == 'Principal' 
					|| getSession('LoginRole', 0) == 'Administrator'
					|| getSession('LoginRole', 0) == 'Accountant'
					|| getSession('LoginRole', 0) == 'Staff'
					) {
					/****************************************************************
					*                         Curriculum                            *
					*****************************************************************/
					?>
					<tr align="center">
						<td class="contentfont">
		          <table border="0" bgcolor="#C1E8BE" class="thinborder" style="font-size: 12px;">
		          	<tr>
		          		<td width="200">&nbsp;</td>
		          		<td width="300">&nbsp;</td>
								</tr>
		          	<tr>
		          		<td>
		          			&nbsp;&nbsp;&nbsp;&nbsp;
		          			Curriculum
		          		</td>
		          		<td>
										<input type="button" name="Submit" value="Add / Edit Courses" style="width: 200px;font-size: 12px;"
										onClick="document.form1.subjectid__.value='CURRICULUM';document.form1.subtask__.value='add_course';document.form1.submit();" />
									</td>
								</tr>
		          	<tr>
		          		<td>&nbsp;</td>
		          		<td>
										<input type="button" name="Submit" value="Classroom" style="width: 200px;font-size: 12px;"
										onClick="document.form1.subjectid__.value='CURRICULUM';document.form1.subtask__.value='classroom';document.form1.submit();" />
									</td>
								</tr>
		          	<tr>
		          		<td>&nbsp;</td>
		          		<td>
										<input type="button" name="Submit" value="Class Builder" style="width: 200px;font-size: 12px;"
										onClick="document.form1.subjectid__.value='CURRICULUM';document.form1.subtask__.value='class_builder';document.form1.submit();" />
									</td>
								</tr>
		          	<tr>
		          		<td>&nbsp;</td>
		          		<td>
										<input type="button" name="Submit" value="View Report" style="width: 200px;font-size: 12px;"
										onClick="document.form1.subjectid__.value='CURRICULUM';document.form1.subtask__.value='view_report';document.form1.submit();" />
									</td>
								</tr>
		          	<tr>
		          		<td>&nbsp;</td>
		          		<td>&nbsp;</td>
								</tr>
		          </table>
		        </td>
		      </tr>
        	<tr>
        		<td>&nbsp;</td>
					</tr>
					<?php
					}
					if (getSession('LoginRole', 0) == 'Principal' 
					|| getSession('LoginRole', 0) == 'Administrator'
					|| getSession('LoginRole', 0) == 'Accountant'
					) {
					/****************************************************************
					*                        Accounting                             *
					*****************************************************************/
					?>
					<tr align="center">
						<td class="contentfont">
		          <table border="0" bgcolor="#C1E8BE" class="thinborder" style="font-size: 12px;">
		          	<tr>
		          		<td width="200">&nbsp;</td>
		          		<td width="300">&nbsp;</td>
								</tr>
		          	<tr>
		          		<td>
		          			&nbsp;&nbsp;&nbsp;&nbsp;
		          			Accounting
		          		</td>
		          		<td>
										<input type="button" name="Submit" value="School Fees" style="width: 200px;font-size: 12px;"
										onClick="document.form1.subjectid__.value='ACCOUNTING';document.form1.subtask__.value='school_fees';document.form1.submit();" />
									</td>
								</tr>
		          	<tr>
		          		<td>&nbsp;</td>
		          		<td>
										<input type="button" name="Submit" value="Registration Fee" style="width: 200px;font-size: 12px;"
										onClick="document.form1.subjectid__.value='ACCOUNTING';document.form1.subtask__.value='registration_fee';document.form1.submit();" />
									</td>
								</tr>
		          	<tr>
		          		<td>&nbsp;</td>
		          		<td>
										<input type="button" name="Submit" value="Tuition and Class Fees" style="width: 200px;font-size: 12px;"
										onClick="document.form1.subjectid__.value='ACCOUNTING';document.form1.subtask__.value='tuition';document.form1.submit();" />
									</td>
								</tr>
		          	<tr>
		          		<td>&nbsp;</td>
		          		<td>
										<input type="button" name="Submit" value="Student Tuition Payment Status" style="width: 200px;font-size: 12px;"
										onClick="document.form1.subjectid__.value='ACCOUNTING';document.form1.subtask__.value='edit_payment_status';document.form1.submit();" />
									</td>
								</tr>
		          	<tr>
		          		<td>&nbsp;</td>
		          		<td>
										<input type="button" name="Submit" value="View Report" style="width: 200px;font-size: 12px;"
										onClick="document.form1.subjectid__.value='ACCOUNTING';document.form1.subtask__.value='view_report';document.form1.submit();" />
									</td>
								</tr>
		          	<tr>
		          		<td>&nbsp;</td>
		          		<td>&nbsp;</td>
								</tr>
		          </table>
		        </td>
		      </tr>
        	<tr>
        		<td>&nbsp;</td>
					</tr>
					<?php 
					}
					if (getSession('LoginRole', 0) == 'Principal' 
					|| getSession('LoginRole', 0) == 'Administrator'
					|| getSession('LoginRole', 0) == 'Accountant'
					|| getSession('LoginRole', 0) == 'Staff'
					) {
					/****************************************************************
					*                       Registration                            *
					*****************************************************************/
					?>
					<tr align="center">
						<td class="contentfont">
		          <table border="0" bgcolor="#C1E8BE" class="thinborder" style="font-size: 12px;">
		          	<tr>
		          		<td width="200">&nbsp;</td>
		          		<td width="300">&nbsp;</td>
								</tr>
		          	<tr>
		          		<td>
		          			&nbsp;&nbsp;&nbsp;&nbsp;
		          			Registration
		          		</td>
		          		<td>
										<input type="button" name="Submit" value="Family / Student Information" style="width: 200px;font-size: 12px;"
										onClick="document.form1.subjectid__.value='REG';document.form1.subtask__.value='list_family';document.form1.submit();" />
									</td>
								</tr>
		          	<tr>
		          		<td>&nbsp;</td>
		          		<td>
										<input type="button" name="Submit" value="Class Registration" style="width: 200px;font-size: 12px;"
										onClick="document.form1.subjectid__.value='REG';document.form1.subtask__.value='course_registration';document.form1.submit();" />
									</td>
								</tr>
		          	<tr>
		          		<td>&nbsp;</td>
		          		<td>
										<input type="button" name="Submit" value="View Report" style="width: 200px;font-size: 12px;"
										onClick="document.form1.subjectid__.value='REG';document.form1.subtask__.value='view_report';document.form1.submit();" />
									</td>
								</tr>
		          	<tr>
		          		<td>&nbsp;</td>
		          		<td>
										<input type="button" name="Submit" value="Print Admission Letter" style="width: 200px;font-size: 12px;"
										onClick="document.form1.subjectid__.value='REG';document.form1.subtask__.value='list_family_for_admission_letter';document.form1.submit();" />
									</td>
								</tr>
		          	<tr>
		          		<td>&nbsp;</td>
		          		<td>&nbsp;</td>
								</tr>
		          </table>
		        </td>
		      </tr>
        	<tr>
        		<td>&nbsp;</td>
					</tr>
					<?php 
					}
					if (getSession('LoginRole', 0) == 'Teacher') {
					/****************************************************************
					*                       Registration (teacher)                  *
					*****************************************************************/
					?>
					<tr align="center">
						<td class="contentfont">
		          <table border="0" bgcolor="#C1E8BE" class="thinborder" style="font-size: 12px;">
		          	<tr>
		          		<td width="200">&nbsp;</td>
		          		<td width="300">&nbsp;</td>
								</tr>
		          	<tr>
		          		<td>
		          			&nbsp;&nbsp;&nbsp;&nbsp;
		          			Registration
		          		</td>
		          	<tr>
		          		<td>&nbsp;</td>
		          		<td>
										<input type="button" name="Submit" value="View Report" style="width: 200px;font-size: 12px;"
										onClick="document.form1.subjectid__.value='REG';document.form1.subtask__.value='view_report';document.form1.submit();" />
									</td>
								</tr>
		          	<tr>
		          		<td>&nbsp;</td>
		          		<td>&nbsp;</td>
								</tr>
		          </table>
		        </td>
		      </tr>
        	<tr>
        		<td>&nbsp;</td>
					</tr>
					<?php 
					}
					if (getSession('LoginRole', 0) == 'Principal' 
					|| getSession('LoginRole', 0) == 'Administrator'
					|| getSession('LoginRole', 0) == 'Accountant'
					|| getSession('LoginRole', 0) == 'Staff'
					|| getSession('LoginRole', 0) == 'Teacher'
					) {
					/****************************************************************
					*                            Grade                              *
					*****************************************************************/
					?>
					<tr align="center">
						<td class="contentfont">
		          <table border="0" bgcolor="#C1E8BE" class="thinborder" style="font-size: 12px;">
		          	<tr>
		          		<td width="200">&nbsp;</td>
		          		<td width="300">&nbsp;</td>
								</tr>
		          	<tr>
		          		<td>
		          			&nbsp;&nbsp;&nbsp;&nbsp;
		          			Student Grade
		          		</td>
		          		<td>
										<input type="button" name="Submit" value="Add / Edit Student Grade" style="width: 200px;font-size: 12px;"
										onClick="document.form1.subjectid__.value='GRADE';document.form1.subtask__.value='add_grade';document.form1.submit();" />
									</td>
								</tr>
		          	<tr>
		          		<td>&nbsp;</td>
		          		<td>
										<input type="button" name="Submit" value="View Report" style="width: 200px;font-size: 12px;"
										onClick="document.form1.subjectid__.value='GRADE';document.form1.subtask__.value='view_report';document.form1.submit();" />
									</td>
								</tr>
		          	<tr>
		          		<td>&nbsp;</td>
		          		<td>&nbsp;</td>
								</tr>
		          </table>
		        </td>
		      </tr>
        	<tr>
        		<td>&nbsp;</td>
					</tr>
					<?php 
					}
					if (getSession('LoginRole', 0) == 'Root' 
					|| getSession('LoginRole', 0) == 'Administrator'
					|| getSession('LoginRole', 0) == 'Principal'
					) {
					/****************************************************************
					*                        Administrative                         *
					*****************************************************************/
					?>
        	<tr height="40" valign="center">
        		<td><hr/></td>
					</tr>
					<tr align="center">
						<td class="contentfont">
		          <table border="0" bgcolor="#C1E8BE" class="thinborder" style="font-size: 12px;">
		          	<tr>
		          		<td width="200">&nbsp;</td>
		          		<td width="300">&nbsp;</td>
								</tr>
		          	<tr>
		          		<td>
		          			&nbsp;&nbsp;&nbsp;&nbsp;
		          			Administrative
		          		</td>
		          		<td>
										<input type="button" name="Submit" value="School Year" style="width: 200px;font-size: 12px;"
										onClick="document.form1.subjectid__.value='ADMINISTRATIVE';document.form1.subtask__.value='school_year';document.form1.submit();" />
									</td>
								</tr>
		          	<tr>
		          		<td>&nbsp;</td>
		          		<td>
										<input type="button" name="Submit" value="Course Category" style="width: 200px;font-size: 12px;"
										onClick="document.form1.subjectid__.value='ADMINISTRATIVE';document.form1.subtask__.value='course_category';document.form1.submit();" />
									</td>
								</tr>
		          	<tr>
		          		<td>&nbsp;</td>
		          		<td>
										<input type="button" name="Submit" value="Course Level" style="width: 200px;font-size: 12px;"
										onClick="document.form1.subjectid__.value='ADMINISTRATIVE';document.form1.subtask__.value='course_level';document.form1.submit();" />
									</td>
								</tr>
		          	<tr>
		          		<td>&nbsp;</td>
		          		<td>
										<input type="button" name="Submit" value="Class Period" style="width: 200px;font-size: 12px;"
										onClick="document.form1.subjectid__.value='ADMINISTRATIVE';document.form1.subtask__.value='class_period';document.form1.submit();" />
									</td>
								</tr>
		          	<tr>
		          		<td>&nbsp;</td>
		          		<td>
										<input type="button" name="Submit" value="Marking Period" style="width: 200px;font-size: 12px;"
										onClick="document.form1.subjectid__.value='ADMINISTRATIVE';document.form1.subtask__.value='marking_period';document.form1.submit();" />
									</td>
								</tr>
		          	<tr>
		          		<td>&nbsp;</td>
		          		<td>
										<input type="button" name="Submit" value="Role" style="width: 200px;font-size: 12px;"
										onClick="document.form1.subjectid__.value='ADMINISTRATIVE';document.form1.subtask__.value='role';document.form1.submit();" />
									</td>
								</tr>
		          	<tr>
		          		<td>&nbsp;</td>
		          		<td>
										<input type="button" name="Submit" value="SQL" style="width: 200px;font-size: 12px;"
										onClick="document.form1.subjectid__.value='ADMINISTRATIVE';document.form1.subtask__.value='sql';document.form1.submit();" />
									</td>
								</tr>
		          	<tr>
		          		<td>&nbsp;</td>
		          		<td>&nbsp;</td>
								</tr>
		          </table>
		        </td>
		      </tr>
					<?php 
					}
					?>
        	<tr height="60" valign="center">
        		<td>&nbsp;</td>
					</tr>
		    </table>
		  </td>
		</tr>
	</table>
<?php
}


if ($debug && function_exists('printSession')) {
	printSession();
}



?>