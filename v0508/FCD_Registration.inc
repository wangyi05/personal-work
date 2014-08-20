<?php

/**
 *
 *
 * @version $Id$
 * @copyright 2005
 **/


/**
 *
 * @name 		GetTemplate_REG
 * @args 		1
 * @return	template
 * @desc		registration
 *
 **/
function GetTemplate_REG($pSubTask, $pLanguageNmbr)
{
?>
	<form name="form1" action="fcdschool.php" method="POST">
<?php
	if (getSession('FamilyNmbr', 0) != '') {
		switch (strtok($pSubTask, '#')) {
			case "accountreport":
				Display_StudentInfo(getSession('FamilyNmbr', 0), $pLanguageNmbr);
				break;
			case "studentinfo":
				GetRegistration_StudentInfo($pLanguageNmbr, 'website');
				break;
			case "refresh_reg":
				Display_StudentInfo(getSession('FamilyNmbr', 0), $pLanguageNmbr);
				break;
			case "morestudent":
				setSession('StudentCount__', (getSession('StudentCount', 0) + 1));
				GetRegistration_StudentInfo($pLanguageNmbr, 'website');
				break;
			case "submit_student_info":
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
				unsetSessionForNextTask('website');
				Display_StudentInfo(getSession('FamilyNmbr', 0), $pLanguageNmbr);
				break;
			case "cancel_form_entry":
				unsetSessionForNextTask('website');
				Display_StudentInfo(getSession('FamilyNmbr', 0), $pLanguageNmbr);
				break;
			case "regist":
				GetRegistration_Regist($pLanguageNmbr);
				break;
			case "back_to_regist":
				GetRegistration_Regist($pLanguageNmbr);
				break;
			case "refresh_website_reg":
				setSession();
				GetRegistration_Regist($pLanguageNmbr);
				break;
			case "submit_registration":
				$handler = new RegistrationHandler();
				$tuition_handler = new TuitionFeeHandler();
				$ref_lib = new RefLibrary();
				$school_year = $ref_lib->GetSchoolYear('active_year');
				for ($i = 0; $i < getSession('StudentCount', 0); $i++) {
					$familymember_nmbr = getSession('StudentFamilyMemberNmbr' . $i, 0);
					// delete
					$registrations = $handler->GetRegistration(getSession('SchoolYear' . $familymember_nmbr, 0), '', $familymember_nmbr, '', '');
					for ($k = 0; $k < sizeof($registrations); $k++) {
						if (isset($registrations[$k]) && $registrations[$k]['RegistrationNmbr'] != '') {
							$handler->DeleteRegistration($registrations[$k]['RegistrationNmbr']);
						}
					}
					// insert
					if (getSession('Tuition' . $familymember_nmbr, 0) != '') {
						if (getSession('ChineseClass' . $familymember_nmbr, 0) != '') {
							$handler->CreateNewRegistration($familymember_nmbr, getSession('ChineseClass' . $familymember_nmbr, 0), getSession('SchoolYear' . $familymember_nmbr, 0));
						}
						if (getSession('CultureClass' . $familymember_nmbr, 0) != '') {
							$handler->CreateNewRegistration($familymember_nmbr, getSession('CultureClass' . $familymember_nmbr, 0), getSession('SchoolYear' . $familymember_nmbr, 0));
						}
						if (getSession('OtherClass' . $familymember_nmbr, 0) != '') {
							$handler->CreateNewRegistration($familymember_nmbr, getSession('OtherClass' . $familymember_nmbr, 0), getSession('SchoolYear' . $familymember_nmbr, 0));
						}
					}
					// update registration fee due
          $tuition_handler->UpdateRegistrationFeeDue($familymember_nmbr, getSession('RegistrationFeeNmbr', 0), $school_year);
				}
				// update tuition due
				$today = date("Y-m-d");
				if ($tuition_handler->UpdateTuitionDue(getSession('FamilyNmbr', 0), $school_year[0]['SchoolYear'], 0, getSession('ManagementFee', 0), getSession('LateFee', 0), getSession('Total', 0), '', '', '', '', $today, 'WEB', '', 'OPEN')) {
					GetRegistration_Print();
					// send email
					$l_family_info = $handler->GetFamilyInfo($family_nmbr);
					$l_to = "chan_je@yahoo.com";
					$l_from = getSession('FamilyEmail', 0);
					$l_subject = 'FCD Class Registration Alert';
					$l_msg = "New registration for FCD class(es):\n\n "
								 . "FamilyID: " . $l_family_info[0]['FamilyID'] . "\n";
					SendEmail($l_to, $l_cc, $l_from, $l_subject, $l_msg);
					$l_to = "principal@fcdschool.org";
					SendEmail($l_to, $l_cc, $l_from, $l_subject, $l_msg);
					$l_to = "yuy_yhmail@yahoo.com";
					SendEmail($l_to, $l_cc, $l_from, $l_subject, $l_msg);
					unsetSession();
				}
				else {
					echo "Error submit registration data.";
					unsetSession();
				}
				break;
			case "removereg":
				unsetSessionForReg();
				GetRegistration_Regist($pLanguageNmbr);
				break;
			case "summary":
				GetRegistration_Summary($pLanguageNmbr);
				break;
			case "back":
				GetRegistration_StudentInfo($pLanguageNmbr, 'website');
				break;
			case "cancel":
				unsetSessionForCancel();
				if ($pLanguageNmbr == 1) GetRegistration_Chinese();
				else GetRegistration_English();
				break;
			default:
				if ($pLanguageNmbr == 1) GetRegistration_Chinese();
				else GetRegistration_English();
		}
	}
	else { // need login or create new account
		switch (strtok($pSubTask, '#')) {
			case "login":
				GetTemplate_Login('registration', $pLanguageNmbr);
				break;
			case "checklogin":
				ProcessRegistrationLogin($pLanguageNmbr);
				break;
			case "createaccount":
				GetRegistration_StudentInfo($pLanguageNmbr, 'website');
				break;
			case "forgotpassword":
				GetRegistration_ForgotPassword();
				break;
			case "morestudent":
				setSession('StudentCount__', (getSession('StudentCount', 0) + 1));
				GetRegistration_StudentInfo($pLanguageNmbr, 'website');
				break;
			case "submit_password_request":
				// send email
				$l_family_info = $handler->GetFamilyInfo($family_nmbr);
				$l_to = "chan_je@yahoo.com";
				$l_from = GetPostValue('AccountEmail__');
				$l_subject = 'FCD account - forgot password';
				$l_msg = "Please check to make sure this user exists in FCD database.  Then reset the password and send the new "
							 . "password to the following email address: \n\n"
							 . "Email: " . GetPostValue('AccountEmail__') . "\n";
				SendEmail($l_to, $l_cc, $l_from, $l_subject, $l_msg);
				$l_to = "principal@fcdschool.org";
				SendEmail($l_to, $l_cc, $l_from, $l_subject, $l_msg);
				$l_to = "yuy_yhmail@yahoo.com";
				SendEmail($l_to, $l_cc, $l_from, $l_subject, $l_msg);
				unsetSession();
				GetTemplate_Login('registration', $pLanguageNmbr);
				break;
			case "submit_student_info":
				$handler = new StudentAccountHandler();
				$family_nmbr = $handler->CreateFamily('', GetPostValue('UserName__'), GetPostValue('Password__'), GetPostValue('Street'), GetPostValue('City'), GetPostValue('State'), GetPostValue('Zip'), GetPostValue('HomeTelephone'), GetPostValue('Email'));
				if (GetPostValue('FatherLastName') != '') {
					$handler->CreateFamilyMember($family_nmbr, 5, GetPostValue('FatherLastName'), GetPostValue('FatherFirstName'), GetPostValue('FatherMiddleName'), GetPostValue('FatherChineseName'), GetPostValue('FatherGender'), GetPostValue('FatherBirthDate'), GetPostValue('WorkTelephone'), GetPostValue('FatherEmail'), 'yes');
				}
				if (GetPostValue('MotherLastName') != '') {
					$handler->CreateFamilyMember($family_nmbr, 6, GetPostValue('MotherLastName'), GetPostValue('MotherFirstName'), GetPostValue('MotherMiddleName'), GetPostValue('MotherChineseName'), GetPostValue('MotherGender'), GetPostValue('MotherBirthDate'), GetPostValue('WorkTelephone'), GetPostValue('MotherEmail'), 'yes');
				}
				for ($i = 0; $i < getSession('StudentCount', 0); $i++) {
					if (GetPostValue('StudentLastName' . $i) != '') {
						$handler->CreateFamilyMember($family_nmbr, 7, GetPostValue('StudentLastName' . $i), GetPostValue('StudentFirstName' . $i), GetPostValue('StudentMiddleName' . $i), GetPostValue('StudentChineseName' . $i), GetPostValue('StudentGender' . $i), GetPostValue('StudentBirthDate' . $i), GetPostValue('WorkTelephone' . $i), GetPostValue('StudentEmail' . $i), GetPostValue('StudentIsAdult' . $i));
					}
				}
				// send email
				$l_family_info = $handler->GetFamilyInfo($family_nmbr);
				$l_to = "chan_je@yahoo.com";
				$l_from = GetPostValue('Email');
				$l_subject = 'FCD account password request';
				$l_msg = "A new family has been registered in FCD database.  Please check the registered information, "
							 . "set the password for this family, and send the new password to the following email address:\n\n"
							 . "FamilyID: " . $l_family_info[0]['FamilyID'] . "\n"
							 . "Email: " . GetPostValue('Email') . "\n";
				SendEmail($l_to, $l_cc, $l_from, $l_subject, $l_msg);
				$l_to = "principal@fcdschool.org";
				SendEmail($l_to, $l_cc, $l_from, $l_subject, $l_msg);
				$l_to = "yuy_yhmail@yahoo.com";
				SendEmail($l_to, $l_cc, $l_from, $l_subject, $l_msg);
				unsetSession();
				GetTemplate_Login('registration', $pLanguageNmbr);
				break;
			default:
				if ($pLanguageNmbr == 1) GetRegistration_Chinese();
				else GetRegistration_English();
		}
	}
?>
	</form>
<?php
}

/**
 *
 * @name 		GetRegistration_English
 * @args 		none
 * @return	template
 * @desc		
 *
 **/
function GetRegistration_English()
{
	include_once 'LIB_DbTaskHandlers.inc';
	$ref_lib = new RefLibrary();
	$school_years = $ref_lib->GetSchoolYear('recent_three');
	$school_year_gp = $school_years[0]['SemesterGroup'];
?>
	<table width="500" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td>
				<table width="500" align="center" cellspacing="0" cellpadding="0">
					<tr>
						<td>&nbsp;</td>
					</tr>
					<tr>
						<td align="center">
							<font size="3" color="darkred"><b>Registration for <?=$school_year_gp; ?> School Year</b></font><br/><br/>
						</td>
					</tr>
					<tr>
						<td>&nbsp;</td>
					</tr>
					<tr>
						<td class="contentfont">You can select one of the following two options to register for the classes in <?=$school_year_gp; ?> school year:<br/><br/></td>
					</tr>
					<tr>
						<td class="contentfont">
							<ul>
								<li style="disc">
									<a href="./fcdschool.php?subjectid=REGIST&subtask=login&languagenmbr=2">Register online</a> 
									Currently online credit card payment for
									tuition is not available.  After you fill out the online forms, you need to mail the payment of tuition and fees to the FCD mailing 
									address.
								</li>
								<br/><br/>
								<li style="disc">
									Download the registration form following the link below, fill out the form and mail the form with the payment to the FCD mailing address:</li>
								<br/>
							</ul>
						</td>
					</tr>
					<tr>
						<td class="contentfont">
							&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
							<a href="./download/2014-2015 Application Form.pdf" target=_>Application form</a>
						</td>
					</tr>
					<tr>
						<td class="contentfont">
							&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
							<a href="./download/Registration Policy for 2014-2015.pdf" target=_>2014-2015 Registration Policy</a>
						</td>
					</tr>
					<tr>
						<td height="100">&nbsp;</td>
					</tr>
					<tr>
						<td width="400" align="left" valign="top" class="labelfont">
							<br/>
							&nbsp;&nbsp;<font size="2">Tuitions and fee schedules can be found </font><a href="./html/TuitionFee_2014-2015_E.html" target=_><font size="2"><b>HERE</b></font></a>.
						</td>
					</tr>
				</table>
			</td>
		</tr>
	</table>
	<br/><br/>
<?php
}


/**
 * 
 * @name 	GetRegistration_Chinese
 * @args	none
 * @return	template
 * @desc
 * 
 */
function GetRegistration_Chinese()
{
	include_once 'LIB_DbTaskHandlers.inc';
	$ref_lib = new RefLibrary();
	$school_years = $ref_lib->GetSchoolYear('recent_three');
	$school_year_gp = $school_years[0]['SemesterGroup'];
?>
	<table width="500" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td>
				<table width="500" align="center" cellspacing="0" cellpadding="0">
					<tr>
						<td>&nbsp;</td>
					</tr>
					<tr>
						<td align="center">
							<font size="3" color="darkred"><b><?=$school_year_gp; ?> 学年学生注册</b></font><br/><br/>
						</td>
					</tr>
					<tr>
						<td>&nbsp;</td>
					</tr>
					<tr>
						<td class="contentfont">
							您可以选择以下任意一种方法注册<?=$school_year_gp; ?>学年课程. 为提高学校的管理效率,减少人为错误,我们鼓励选择在线注册:<br/><br/>
						</td>
					</tr>
					<tr>
						<td class="contentfont">
							<ul>
								<li style="disc">
									<a href="./fcdschool.php?subjectid=REGIST&subtask=login&languagenmbr=1">在线注册</a>
									目前我们尚无法接受信用卡作为支付学费的手段. 当您填写好在线报名表之后,请将支票连同打印出来的报名表一同寄往FCD邮寄地址.
								</li>
								<br/><br/>
								<li style="disc">
									通过以下链接下载报名表,填好后,连同支票一同寄往FCD邮寄地址.</li>
								<br/><br/>
							</ul>
						</td>
					</tr>
					<tr>
						<td class="contentfont">
							&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
							<a href="./download/2014-2015 Application Form.pdf" target=_>下载报名表</a>
						</td>
					</tr>
					<tr>
						<td class="contentfont">
							&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
							<a href="./download/Registration Policy for 2014-2015.pdf" target=_>2014-2015学年注册须知</a>
						</td>
					</tr>
					<tr>
						<td height="100">&nbsp;</td>
					</tr>
					<tr>
						<td width="400" align="left" valign="top" class="labelfont">
							<br/>
							&nbsp;&nbsp;<font size="2">附: </font><a href="./html/TuitionFee_2014-2015_C.html" target=_><font size="2">学杂费一览表.</font></a>.
						</td>
					</tr>
				</table>
			</td>
		</tr>
	</table>
	<br/><br/>
<?php
}

/**
 *
 * @name 		ProcessRegistrationLogin
 * @args 		none
 * @return	template
 * @desc		
 *
 **/
function ProcessRegistrationLogin($pLanguageNmbr)
{ 
	if (CheckStudentLogin()) { 
		GetRegistration_StudentInfo($pLanguageNmbr, 'website');
	}
	else {
		GetTemplate_Login('registration', $pLanguageNmbr);
	}
}

/**
 *
 * @name 		Display_StudentInfo
 * @args 		none
 * @return	template
 * @desc		
 *
 **/
function Display_StudentInfo($pFamilyNmbr, $pLanguageNmbr)
{
	$tuition_hdlr = new TuitionFeeHandler();
	$reg_status = $tuition_hdlr->GetStatus($pFamilyNmbr);
?>
	<table width="650" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td align="right">
				<input class="smallwhitesubmit" type="button" name="Submit" value="Log out" 
				onClick="document.form1.subjectid__.value='REGIST';document.form1.subtask__.value='cancel';document.form1.submit();" />
			</td>
		</tr>
		<tr>
			<td align="center">
				<font size="3" color="darkred"><b>Parent and Student Information</b></font><br/><br/>
			</td>
		</tr>
	</table>
<?php
	Report_StudentInfo($pFamilyNmbr);
	Report_RegistrationInfo($pFamilyNmbr);
?>
	<table width="550" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td width="100" align="left" height="40" valign="bottom" class="lightlabelfont">
				<input type="hidden" name="subjectid__" value="" />
				<input type="hidden" name="subtask__" value="" />
				<input type="hidden" name="languagenmbr__" value="<?php echo $pLanguageNmbr; ?>" />
			</td>
			<td width="450" align="right" height="40" valign="bottom" class="lightlabelfont">
				<input class="biggreensubmit" type="button" name="EditFamilyInfo" value="Edit Account" 
				onClick="document.form1.subjectid__.value='REGIST';document.form1.subtask__.value='studentinfo';document.form1.submit();" />
<?php
	if ($reg_status[0]['Status'] != 'CLOSED' && $reg_status[0]['RegistrationMethod'] != 'PAPER') {
?>
				<input class="biggreensubmit" type="button" name="RegistClass" value="Regist Class" 
				onClick="document.form1.subjectid__.value='REGIST';document.form1.subtask__.value='regist';document.form1.submit();" />
<?php
	}
?>
			</td>
		</tr>
	</table>
<?php
}

/**
 *
 * @name 		GetRegistration_Regist
 * @args 		none
 * @return	template
 * @desc		
 *
 **/
function GetRegistration_Regist($pLanguageNmbr)
{ 
	$ref_lib = new RefLibrary();
	$school_years = $ref_lib->GetSchoolYear('recent_three');
	$this_year = $ref_lib->GetSchoolYear('active_year');

	$curriculum_hdlr = new CurriculumHandler() ;
	$chinesecoursearray = $curriculum_hdlr->GetClass(1); //GetCourse('CHINESE', '');
	$culturecoursearray = $curriculum_hdlr->GetClass(2); //GetCourse('OTHER', '');
	$othercoursearray = $curriculum_hdlr->GetClass(3); //GetCourse('OTHER', '');
	$student_handler = new StudentAccountHandler();
	$students = $student_handler->GetStudentInfo(getSession('FamilyNmbr', 0));
	$reg_handler = new RegistrationHandler();
?>
	<script type="text/javascript">
		function CheckRegistration()
		{
<?php 
	for ($i = 0; $i < getSessionCount('StudentLastName', '*'); $i++) {
?>
			if (document.form1.ChineseClass<?php echo $i; ?>__.value == '' && document.form1.CultureClass<?php echo $i; ?>__.value == '') {
				alert ("You need to select at least one class for each student to continue.");
				return false;
			}
<?php
	}
?>
			return true;
			
		}
	</script>
	<table width="650" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td align="right">
				<input class="smallwhitesubmit" type="button" name="Submit" value="Log out" 
				onClick="document.form1.subjectid__.value='REGIST';document.form1.subtask__.value='cancel';document.form1.submit();" />
			</td>
		</tr>
		<tr>
			<td align="center">
				<font size="3" color="darkred"><b>Registration for <?php echo $school_years[0]['SchoolYear']; ?> School Year</b></font><br/><br/>
			</td>
		</tr>
	</table>
	<table width="750" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td height="40" align="center" valign="bottom" class="lightlabelfont"><b>Class Registration</b><br/><br/></td>
		</tr>
	</table>
	<table width="650" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td align="right" valign="top">
				<table width="650" border="1" align="center" cellspacing="0" cellpadding="0">
					<tr>
						<td width="90" align="center" class="labelfont">Student Name</td>
						<td width="70" align="center" class="labelfont">Semester</td>
						<td width="240" align="center" class="labelfont">Class (课程)</td>
						<td width="50" align="center" class="labelfont">Tuition</td>
						<td width="50" align="center" class="labelfont">Text Book</td>
						<td width="50" align="center" class="labelfont">Extra Fee</td>
						<td width="50" align="center" class="labelfont">Reg. Fee</td>
						<td width="50" align="center" class="labelfont">Sub-total</td>
					</tr>
<?php 
	for ($i = 0; $i < sizeof($students); $i++) {
		if (isset($students[$i]['LastName']) && $students[$i]['LastName'] != '') {
?>
					<tr>
						<td align="center" class="labelfont">&nbsp;<?php echo $students[$i]['LastName'] . ' ' . $students[$i]['FirstName'] . '<br/>' . $students[$i]['ChineseName']; ?></td>
						<td align="left" class="labelfont">
<?php
			for ($m = 0; $m < sizeof($school_years); $m++) {
				$registrations = $reg_handler->GetRegistration($school_years[$m]['SchoolYear'], '', $students [$i]['FamilyMemberNmbr'], '', '');
				for ($j = 0; $j < sizeof($registrations); $j++) {
					if (getSession('subtask', 0) == 'regist' && getSession('SchoolYear' . $students[$i]['FamilyMemberNmbr'], 0) == '') setSession('SchoolYear' . $students[$i]['FamilyMemberNmbr'] . '__', $school_years[$m]['SchoolYear']);
					if (getSession('subtask', 0) == 'regist' && $registrations[$j]['CourseCategoryNmbr'] == 1 && getSession('ChineseClass' . $students[$i]['FamilyMemberNmbr'], 0) == '') setSession('ChineseClass' . $students[$i]['FamilyMemberNmbr'] . '__', $registrations[$j]['ClassNmbr']);
					if (getSession('subtask', 0) == 'regist' && $registrations[$j]['CourseCategoryNmbr'] == 2 && getSession('CultureClass' . $students[$i]['FamilyMemberNmbr'], 0) == '') setSession('CultureClass' . $students[$i]['FamilyMemberNmbr'] . '__', $registrations[$j]['ClassNmbr']);
					if (getSession('subtask', 0) == 'regist' && $registrations[$j]['CourseCategoryNmbr'] == 3 && getSession('OtherClass' . $students[$i]['FamilyMemberNmbr'], 0) == '') setSession('OtherClass' . $students[$i]['FamilyMemberNmbr'] . '__', $registrations[$j]['ClassNmbr']);
				}
				CalculateAllFees($students[$i]['FamilyMemberNmbr'], getSession('SchoolYear' . $students[$i]['FamilyMemberNmbr'], 0), 'WEB');
?>
							<input type="radio" name="SchoolYear<?php echo $students[$i]['FamilyMemberNmbr']; ?>__" value="<?php echo $school_years[$m]['SchoolYear']; ?>" <?php if (getSession('SchoolYear' . $students[$i]['FamilyMemberNmbr'], 0) == $school_years[$m]['SchoolYear']) echo ' checked'; ?>
							onClick="document.form1.subjectid__.value='REGIST';document.form1.subtask__.value='refresh_website_reg';document.form1.submit();"
							>
							<?php echo $school_years[$m]['Semester']; ?><br/>
<?php
			}
?>
						</td>
						<td class="labelfont">
							&nbsp;Chinese Class (中文课)<br/>
							<select name="ChineseClass<?php echo $students[$i]['FamilyMemberNmbr']; ?>__" size="1" style="width: 240px"
							onChange="document.form1.subjectid__.value='REGIST';document.form1.subtask__.value='refresh_website_reg';
							if (CheckRegPeriod(document.form1.SchoolYear<?php echo $students[$i]['FamilyMemberNmbr']; ?>__)) document.form1.submit();">
								<option value=""<?php if (getSession('ChineseClass' . $students[$i]['FamilyMemberNmbr'], 0) == '') echo ' selected'; ?>>None</option>
<?php
			for ($k = 0; $k < sizeof($chinesecoursearray); $k++) {
				if (isset($chinesecoursearray[$k]['ClassNmbr']) && $chinesecoursearray[$k]['ClassNmbr'] != '') {
?>
								<option value="<?php echo $chinesecoursearray[$k]['ClassNmbr']; ?>"<?php if (getSession('ChineseClass' . $students[$i]['FamilyMemberNmbr'], 0) == $chinesecoursearray[$k]['ClassNmbr']) echo ' selected'; ?>><?php echo $chinesecoursearray[$k]['ClassName_E'] . ' (' . $chinesecoursearray[$k]['ClassName_C'] . ')'; ?></option>
<?php
				}
			}
?>
							</select>
							&nbsp;Culture Class (文体课)<br/>
							<select name="CultureClass<?php echo $students[$i]['FamilyMemberNmbr']; ?>__" size="1" style="width: 240px" 
							onChange="document.form1.subjectid__.value='REGIST';document.form1.subtask__.value='refresh_website_reg';
							if (CheckRegPeriod(document.form1.SchoolYear<?php echo $students[$i]['FamilyMemberNmbr']; ?>__)) document.form1.submit();">
								<option value=""<?php if (getSession('CultureClass' . $students[$i]['FamilyMemberNmbr'], 0) == '') echo ' selected'; ?>>None</option>
<?php
			for ($k = 0; $k < sizeof($culturecoursearray); $k++) {
				if (isset($culturecoursearray[$k]['ClassNmbr']) && $culturecoursearray[$k]['ClassNmbr'] != '') {
?>
								<option value="<?php echo $culturecoursearray[$k]['ClassNmbr']; ?>"<?php if (getSession('CultureClass' . $students[$i]['FamilyMemberNmbr'], 0) == $culturecoursearray[$k]['ClassNmbr']) echo ' selected'; ?>><?php echo $culturecoursearray[$k]['ClassName_E'] . ' (' . $culturecoursearray[$k]['ClassName_C'] . ')'; ?></option>
<?php
				}
			}
?>
							</select>
							&nbsp;Other Class (其它)<br/>
							<select name="OtherClass<?php echo $students[$i]['FamilyMemberNmbr']; ?>__" size="1" style="width: 240px" 
							onChange="document.form1.subjectid__.value='REGIST';document.form1.subtask__.value='refresh_website_reg';
							if (CheckRegPeriod(document.form1.SchoolYear<?php echo $students[$i]['FamilyMemberNmbr']; ?>__)) document.form1.submit();">
								<option value=""<?php if (getSession('OtherClass' . $students[$i]['FamilyMemberNmbr'], 0) == '') echo ' selected'; ?>>None</option>
<?php
			for ($k = 0; $k < sizeof($othercoursearray); $k++) {
				if (isset($othercoursearray[$k]['ClassNmbr']) && $othercoursearray[$k]['ClassNmbr'] != '') {
?>
								<option value="<?php echo $othercoursearray[$k]['ClassNmbr']; ?>"<?php if (getSession('OtherClass' . $students[$i]['FamilyMemberNmbr'], 0) == $othercoursearray[$k]['ClassNmbr']) echo ' selected'; ?>><?php echo $othercoursearray[$k]['ClassName_E'] . ' (' . $othercoursearray[$k]['ClassName_C'] . ')'; ?></option>
<?php
				}
			}
?>
							</select>
						</td>
						<td align="right" class="labelfont"><?php echo getSession('Tuition' . $students[$i]['FamilyMemberNmbr'], 0); ?>&nbsp;&nbsp;&nbsp;&nbsp;</td>
						<td align="right" class="labelfont"><?php echo getSession('BookFee' . $students[$i]['FamilyMemberNmbr'], 0); ?>&nbsp;&nbsp;&nbsp;&nbsp;</td>
						<td align="right" class="labelfont"><?php echo getSession('OtherFee' . $students[$i]['FamilyMemberNmbr'], 0); ?>&nbsp;&nbsp;&nbsp;&nbsp;</td>
						<td align="right" class="labelfont"><?php echo getSession('RegistrationFee' . $students[$i]['FamilyMemberNmbr'], 0); ?>&nbsp;&nbsp;&nbsp;&nbsp;</td>
						<td align="right" class="labelfont"><?php echo getSession('Subtotal' . $students[$i]['FamilyMemberNmbr'], 0); ?>&nbsp;&nbsp;&nbsp;&nbsp;</td>
					</tr>
<?php 
		}
	}
?>
				</table>
			</td>
		</tr>
		<tr>
			<td align="right" valign="top">
				<table cellspacing="0" cellpadding="0">
					<tr>
						<td width="400" align="left" valign="top" class="labelfont">
							<br/>
							&nbsp;&nbsp;<a href="./html/TuitionFee_2012-2013_E.html" target=_><font size="2">Tuitions and fee schedules</font></a>.
						</td>
						<td width="380" align="right">
							<table width="153" border="1" cellspacing="0" cellpadding="0">
<?php
	$schoolfee_handler = new TuitionFeeHandler();
	$all_school_fees = $schoolfee_handler->GetSchoolFees($this_year[0]['SchoolYear']);
	for ($m = 0; $m < sizeof($all_school_fees); $m++) {
		$schoolfee_sessionvar = str_replace(' ', '', $all_school_fees[$m]['FeeName_E']);
		if (getSessionCount($schoolfee_sessionvar, '') > 0) {
?>
								<tr>
									<td width="100" align="center" class="labelfont"><?php echo $all_school_fees[$m]['FeeName_E'] . '<br/>(' . $all_school_fees[$m]['FeeName_C'] . ')'; ?>:</td>
									<td width="53" align="center" class="labelfont"><?php echo getSession($schoolfee_sessionvar, 0); ?></td>
								</tr>
<?php 
		}
	}
?>
								<tr>
									<td align="center" class="labelfont"><b>Total:</b>&nbsp;&nbsp;</td>
									<td align="center" class="labelfont"><?php echo getSession('Total', 0); ?></td>
								</tr>
							</table>
						</td>
					</tr>
				</table>
			</td>
		</tr>
	</table>
	<br/><br/>
	<table width="700" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td>&nbsp;</td>
		</tr>
		<tr>
			<td class="labelfont">
				Tuition Refund:  100% tuition refund before or on the school opening day, 70% before or on the second school day, 50% before or 
				on the third school day, and no refund after third school day. Registration fee and text book fee are not refundable.  
			</td>
		</tr>
	</table>
	<br/><br/><br/>
	<table width="650"
	 align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td width="300" align="left" height="40" valign="bottom" class="lightlabelfont">
				<input type="hidden" name="subjectid__" value="" />
				<input type="hidden" name="subtask__" value="" />
				<input type="hidden" name="languagenmbr__" value="<?php echo $pLanguageNmbr; ?>" />
			</td>
			<td width="350" align="right" height="40" valign="bottom" class="lightlabelfont">
				<input class="smallsubmit" type="button" name="Submit" value="Back" 
				onClick="document.form1.subjectid__.value='REGIST';document.form1.subtask__.value='cancel_form_entry';document.form1.submit();" />
				<input class="biggreensubmit" type="button" name="Submit" value="Continue >>" 
				onClick="document.form1.subjectid__.value='REGIST';document.form1.subtask__.value='summary';
				if (CheckRegistration()) document.form1.submit();" />
			</td>
		</tr>
	</table>
<?php
}

/**
 *
 * @name 		GetRegistration_Summary
 * @args 		none
 * @return	template
 * @desc		
 *
 **/
function GetRegistration_Summary($pLanguageNmbr)
{
	GetRegistration_Session();
?>
	<p/>
	<table width="650" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td height="60" style="font-size: 15px"><b>Before you submit, please check the above information to make sure entries are correct, and read following statement carefully.</b></td>
		</tr>
		<tr>
			<td class="labelfont">
				<b>Release of Liability:</b> In consideration of the activities at John Marshall School Edison, NJ, sponsored by fcd School, a nonprofit 
				organization, I, the undersigned, understand and agree that the said fcd Chinese School, its officials, teachers, or volunteers, 
				will not be held responsible for any injury or accident sustained by any member of our party, or, for the loss of any property 
				belonging to any member of our party or anyone else.<br/><br/>

				<b>Parent&acute;s Agreement:</b> I understand that John Marshall School forbids the use of the School&acute;s athletic and other facilities or areas 
				not designated for fcd&acute;s instructional activities.  I further understand that any violations could (a) threaten the relationship 
				between fcd and John Marshall School, and (b) be punished under local laws. I agree to indemnify the fcd for any fines, remedies, 
				and punishments rendered or ordered as the result of any such violations.<br/><br/>
				 
				<b>Tuition Refund:</b>  100% tuition refund before or on the school opening day, 70% before or on the second school day, 50% before or 
				on the third school day, and no refund after third school day. Registration fee and text book fee are not refundable.  
			</td>
		</tr>
		<tr>
			<td height="80" valign="bottom" style="font-size: 15px">
				<b>After the form is submitted, you will be presented with a registration summary and signature page.  You need to 
				print that page, sign at the bottom, and mail it together with the check to FCD School to complete the registration process.</b>
			</td>
		</tr>
	</table>


	<table width="650" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td align="center">
				&nbsp;
			</td>
		</tr>
	</table>
	<table width="650" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td width="300" align="left" height="40" valign="bottom" class="lightlabelfont">
				<input type="hidden" name="subjectid__" value="" />
				<input type="hidden" name="subtask__" value="" />
				<input type="hidden" name="languagenmbr__" value="<?php echo $pLanguageNmbr; ?>" />
				<input class="smallsubmit" type="button" name="Submit" value="Back" 
				onClick="document.form1.subjectid__.value='REGIST';document.form1.subtask__.value='back_to_regist';document.form1.submit();" />
			</td>
			<td width="350" align="right" height="40" valign="bottom" class="lightlabelfont">
				<input class="bigredsubmit" type="submit" name="Submit" value="Submit" 
				onClick="document.form1.subjectid__.value='REGIST';document.form1.subtask__.value='submit_registration';" />
			</td>
		</tr>
	</table>
<?php
}

/**
 *
 * @name 		GetRegistration_Session
 * @args 		none
 * @return	template
 * @desc		
 *
 **/
function GetRegistration_Session()
{
	$student_handler = new StudentAccountHandler();
	$students = $student_handler->GetStudentInfo(getSession('FamilyNmbr', 0));

	include_once 'LIB_DbTaskHandlers.inc';
	$ref_lib = new RefLibrary();
	$school_years = $ref_lib->GetSchoolYear('recent_three');
	$school_year_gp = $school_years[0]['SemesterGroup'];
?>
	<table width="650" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td height="30" align="center" valign="bottom">
				<font size="3"><b>Registration for <?=$school_year_gp; ?> School Year</b></font><br/><br/>
			</td>
		</tr>
	</table>
	<table width="650" align="center" cellspacing="0" cellpadding="0" class="noborder">
		<tr>
			<td>
				<table width="650" border="0" align="center" cellspacing="0" cellpadding="0">
					<tr>
						<td width="160">&nbsp;</td>
						<td width="10">&nbsp;</td>
						<td width="480">&nbsp;</td>
					</tr>
<?php 
	$parents = $student_handler->GetFamilyAndFamilyMemberInfo(getSession('FamilyNmbr', 0), 5, 6);
	for ($i = 0; $i < sizeof($parents); $i++) {
?>
					<tr>
						<td align="right" valign="top" class="labelfont">
							<?php echo $parents[$i]['FcdRole_E'] . ' (' . $parents[$i]['FcdRole_C'] . '):'; ?>
						</td>
						<td>&nbsp;</td>
						<td align="left" valign="top" class="labelfont">
							<?php echo $parents[$i]['LastName'] . $parents[$i]['FirstName'] . ' (' . $parents[$i]['ChineseName'] . '):'; ?>
						</td>
					</tr>
<?php
	}
?>
					<tr>
						<td align="right" valign="top" class="labelfont">Mailing Address (邮寄地址):</td>
						<td>&nbsp;</td>
						<td align="left" valign="top" class="labelfont">
							<?php echo $parents[0]['Street']; ?><br/>
							<?php echo $parents[0]['City'] . ", " . $parents[0]['State'] . " " . $parents[0]['ZipCode']; ?>
							<br/>
						</td>
					</tr>
					<tr>
						<td align="right" valign="top" class="labelfont">
							Telephone:<br/>
							Email:
						</td>
						<td>&nbsp;</td>
						<td align="left" valign="top" class="labelfont">
							<?php echo $parents[0]['HomeTelephone']; ?><br/>
							<?php echo $parents[0]['Email']; ?>
						</td>
					</tr>
				</table>
			</td>
		</tr>
	</table>
	<p/>
	<table width="750" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td valign="top">
				<table width="650" border="1" align="center" cellspacing="0" cellpadding="0">
					<tr>
						<td width="140" align="center" class="labelfont">Student Name</td>
						<td width="50" align="center" class="labelfont">Semester</td>
						<td width="220" align="center" class="labelfont">Class(es)</td>
						<td width="40" align="center" class="labelfont">Tuition</td>
						<td width="50" align="center" class="labelfont">Book Fee</td>
						<td width="50" align="center" class="labelfont">Extra Fee</td>
						<td width="50" align="center" class="labelfont">Reg. Fee</td>
						<td width="50" align="center" class="labelfont">Sub-total</td>
					</tr>
<?php 
	$curriculum_hdlr = new CurriculumHandler();
	for ($i = 0; $i < getSession('StudentCount', 0); $i++) {
		if (getSession('Tuition' . $students[$i]['FamilyMemberNmbr'], 0) != '') {
			$classes = $curriculum_hdlr->GetClass();
			$chinese_class = '';
			$culture_class = '';
			$other_class = '';
			for ($k = 0; $k < sizeof($classes); $k++) {
				if (getSession('ChineseClass' . $students[$i]['FamilyMemberNmbr'], 0) != '' && $classes[$k]['ClassNmbr'] == getSession('ChineseClass' . $students[$i]['FamilyMemberNmbr'], 0)) {
					$chinese_class = $classes[$k]['ClassName_E'] . ' (' . $classes[$k]['ClassName_C'] . ')<br>';
				}
				if (getSession('CultureClass' . $students[$i]['FamilyMemberNmbr'], 0) != '' && $classes[$k]['ClassNmbr'] == getSession('CultureClass' . $students[$i]['FamilyMemberNmbr'], 0)) {
					$culture_class = $classes[$k]['ClassName_E'] . ' (' . $classes[$k]['ClassName_C'] . ')<br>';
				}
				if (getSession('OtherClass' . $students[$i]['FamilyMemberNmbr'], 0) != '' && $classes[$k]['ClassNmbr'] == getSession('OtherClass' . $students[$i]['FamilyMemberNmbr'], 0)) {
					$other_class = $classes[$k]['ClassName_E'] . ' (' . $classes[$k]['ClassName_C'] . ')';
				}
			}
?>
					<tr>
						<td class="labelfont">&nbsp;
							<?php echo $students[$i]['LastName'] . ', ' . $students[$i]['FirstName'] . ' (' . $students[$i]['ChineseName'] . ')'; ?>
						</td>
						<td align="left" class="labelfont">&nbsp;
							<?php echo getSession('SchoolYear' . $students[$i]['FamilyMemberNmbr'], 0); ?>
						</td>
						<td class="labelfont" align="center">
							<?php echo $chinese_class . $culture_class . $other_class; ?>
						</td>
						<td align="right" class="labelfont"><?php echo getSession('Tuition' . $students[$i]['FamilyMemberNmbr'], 0); ?>&nbsp;&nbsp;&nbsp;&nbsp;</td>
						<td align="right" class="labelfont"><?php echo getSession('BookFee' . $students[$i]['FamilyMemberNmbr'], 0); ?>&nbsp;&nbsp;&nbsp;&nbsp;</td>
						<td align="right" class="labelfont"><?php echo getSession('OtherFee' . $students[$i]['FamilyMemberNmbr'], 0); ?>&nbsp;&nbsp;&nbsp;&nbsp;</td>
						<td align="right" class="labelfont"><?php echo getSession('RegistrationFee' . $students[$i]['FamilyMemberNmbr'], 0); ?>&nbsp;&nbsp;&nbsp;&nbsp;</td>
						<td align="right" class="labelfont"><?php echo getSession('Subtotal' . $students[$i]['FamilyMemberNmbr'], 0); ?>&nbsp;&nbsp;&nbsp;&nbsp;</td>
					</tr>
<?php 
		}
	}
?>
				</table>
			</td>
		</tr>
		<tr>
			<td align="right" valign="top">
				<table width="650" border="0" align="center" cellspacing="0" cellpadding="0">
					<tr>
						<td width="496">&nbsp;</td>
						<td width="154">
							<table width="153" border="1" cellspacing="0" cellpadding="0">
								<tr>
									<td width="100" align="right" class="labelfont">Management Fee:&nbsp;&nbsp;</td>
									<td width="53" align="right" class="labelfont"><?php echo getSession('ManagementFee', 0); ?>&nbsp;&nbsp;&nbsp;&nbsp;</td>
								</tr>
								<tr>
									<td width="100" align="right" class="labelfont">Late Fee:&nbsp;&nbsp;</td>
									<td width="53" align="right" class="labelfont"><?php echo getSession('LateFee', 0); ?>&nbsp;&nbsp;&nbsp;&nbsp;</td>
								</tr>
								<tr>
									<td align="right" class="labelfont"><b>Total:</b>&nbsp;&nbsp;</td>
									<td align="right" class="labelfont"><?php echo getSession('Total', 0); ?>&nbsp;&nbsp;&nbsp;&nbsp;</td>
								</tr>
							</table>
						</td>
					</tr>
				</table>
			</td>
		</tr>
	</table>
<?php
}

/**
 *
 * @name 		GetRegistration_Print
 * @args 		none
 * @return	template
 * @desc		
 *
 **/
function GetRegistration_Print()
{
?>
	<html>
	<head>
	<title>www.fcdschool.org</title>
	<meta http-equiv="Content-Type" content="text/html"; charset="UTF-8">
	<link rel="stylesheet" type="text/css" href="stylesheet/fcd.css" />
	<script language="JavaScript"></script>
	</head>
	
	<body leftmargin="0" topmargin="0">
	<table width="650" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td align="center">
				<font size="4"><b>FCD Chinese School (èŠ³è�‰åœ°ä¸­æ–‡å­¦æ ¡)</b></font><br/>
			</td>
		</tr>
	</table>
<?php
	GetRegistration_Session();
?>
	<p/>
	<table width="650" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td>&nbsp;</td>
		</tr>
		<tr>
			<td height="50" class="printlabelfont">
				To complete registration, <b>ALL</b> students and parents/guardians must <b>READ</b> and <b>SIGN</b> the following. For 
				students age 18 or under, their parents/guardians must sign.
			</td>
		</tr>
		<tr>
			<td class="printlabelfont">
				<b>Release of Liability:</b> In consideration of the activities at John Marshall School Edison, NJ, sponsored by fcd School, a nonprofit 
				organization, I, the undersigned, understand and agree that the said fcd Chinese School, its officials, teachers, or volunteers, 
				will not be held responsible for any injury or accident sustained by any member of our party, or, for the loss of any property 
				belonging to any member of our party or anyone else.<br/><br/>

				<b>Parent&acute;s Agreement:</b> I understand that John Marshall School forbids the use of the School&acute;s athletic and other facilities or areas 
				not designated for fcd&acute;s instructional activities.  I further understand that any violations could (a) threaten the relationship 
				between fcd and John Marshall School, and (b) be punished under local laws. I agree to indemnify the fcd for any fines, remedies, 
				and punishments rendered or ordered as the result of any such violations.<br/><br/>
				 
				<b>Tuition Refund:</b>  100% tuition refund before or on the school opening day, 70% before or on the second school day, 50% before or 
				on the third school day, and no refund after third school day. Registration fee and text book fee are not refundable.  
			</td>
		</tr>
		<tr>
			<td height="40">&nbsp;</td>
		</tr>
		<tr>
			<td class="printlabelfont">
				<b>Parent/Guardian Signature ____________________________________________ Date _________________</b>
			</td>
		</tr>
	</table>
	<p/>
	<table>
		<tr>
			<td>&nbsp;</td>
		</tr>
	</table>
	<table width="650" align="center" cellspacing="0" cellpadding="0" class="thinborder">
		<tr>
			<td width="400" class="printlabelfont">
				&nbsp;<b>Make check payable to:</b>&nbsp;&nbsp; FCD School<br/>
				&nbsp;<b>Mailing Address:</b>&nbsp;&nbsp; P. O. Box 10453, New Brunswick, NJ 08906
			</td>
			<td width="250" class="printlabelfont">
				&nbsp;è�”ç³»äººç”µè¯�:&nbsp;&nbsp;&nbsp;&nbsp; è”¡ç®� è€�å¸ˆ &nbsp;&nbsp;&nbsp;732-937-9014<br/>
				&nbsp;Contact:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ä¸�è™¹ è€�å¸ˆ &nbsp;&nbsp;&nbsp;732-828-0885
			</td>
		</tr>
	</table>
	<table width="650" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td valign="bottom" height="40"><b>OFFICE USE ONLY:</b></td>
		</tr>
		<tr>
			<td>&nbsp;</td>
		</tr>
		<tr>
			<td class="printlabelfont">
				<b>Received by ______________________ Date ______________ Payment: $_________ Check No. ___________ </b><br/><br/><br/>
				<b>Note ____________________________________________________________________________________________</b>
			</td>
		</tr>
	</table>
	</body>
	</html>
<?php
}

/**
 *
 * @name 		GetRegistration_FinePrint
 * @args 		none
 * @return	template
 * @desc		
 *
 **/
function GetRegistration_FinePrint()
{
?>
				<table width="550" align="center" cellspacing="0" cellpadding="0">
					<tr>
						<td>&nbsp;</td>
					</tr>
					<tr>
						<td class="fineprintfont">
							Release of Liability: In consideration of the activities at John Marshall School Edison, NJ, sponsored by fcd School, a nonprofit 
							organization, I, the undersigned, understand and agree that the said fcd Chinese School, its officials, teachers, or volunteers, 
							will not be held responsible for any injury or accident sustained by any member of our party, or, for the loss of any property 
							belonging to any member of our party or anyone else.<br/><br/>

							Parent&acute;s Agreement: I understand that John Marshall School forbids the use of the School&acute;s athletic and other facilities or areas 
							not designated for fcd&acute;s instructional activities.  I further understand that any violations could (a) threaten the relationship 
							between fcd and John Marshall School, and (b) be punished under local laws. I agree to indemnify the fcd for any fines, remedies, 
							and punishments rendered or ordered as the result of any such violations.<br/><br/>
							 
							Tuition Refund:  100% tuition refund before or on the school opening day, 70% before or on the second school day, 50% before or 
							on the third school day, and no refund after third school day. Registration fee and text book fee are not refundable.  

						</td>
					</tr>
				</table>
<?php
}

/**
 *
 * @name 		CalculateAllFees
 * @args 		none
 * @return	tuition
 * @desc		
 *
 **/
function CalculateAllFees($pFamilyMemberNmbr, $pSchoolYear, $pRegMethod)
{
	$tuition_hdlr = new TuitionFeeHandler();
	$ref_lib = new RefLibrary();
	$this_year = $ref_lib->GetSchoolYear('active_year');
	$tuition = 0;
	$bookfee = 0;
	$labfee = 0;
	$otherfee = 0;
	// calculate fees
	if (getSession('ChineseClass' . $pFamilyMemberNmbr, 0) != '') {
		$chinese_class_nmbr = getSession('ChineseClass' . $pFamilyMemberNmbr, 0);
		$tuition_info = $tuition_hdlr->CalculateTuitionForClass($chinese_class_nmbr, $pSchoolYear);
		if (isset($tuition_info[0]) && isset($tuition_info[0]['Tuition'])) $tuition = $tuition + $tuition_info[0]['Tuition'];
		if (isset($tuition_info[0]) && isset($tuition_info[0]['BookFee'])) $bookfee = $bookfee + $tuition_info[0]['BookFee'];
		if (isset($tuition_info[0]) && isset($tuition_info[0]['LabFee'])) $labfee = $labfee + $tuition_info[0]['LabFee'];
		if (isset($tuition_info[0]) && isset($tuition_info[0]['OtherFee'])) $otherfee = $otherfee + $tuition_info[0]['OtherFee'];
	}
	if (getSession('CultureClass' . $pFamilyMemberNmbr, 0) != '') {
		$culture_class_nmbr = getSession('CultureClass' . $pFamilyMemberNmbr, 0);
		$tuition_info = $tuition_hdlr->CalculateTuitionForClass($culture_class_nmbr, $pSchoolYear);
		if (isset($tuition_info[0]) && isset($tuition_info[0]['Tuition'])) $tuition = $tuition + $tuition_info[0]['Tuition'];
		if (isset($tuition_info[0]) && isset($tuition_info[0]['BookFee'])) $bookfee = $bookfee + $tuition_info[0]['BookFee'];
		if (isset($tuition_info[0]) && isset($tuition_info[0]['LabFee'])) $labfee = $labfee + $tuition_info[0]['LabFee'];
		if (isset($tuition_info[0]) && isset($tuition_info[0]['OtherFee'])) $otherfee = $otherfee + $tuition_info[0]['OtherFee'];
	}
	if (getSession('OtherClass' . $pFamilyMemberNmbr, 0) != '') {
		$other_class_nmbr = getSession('OtherClass' . $pFamilyMemberNmbr, 0);
		$tuition_info = $tuition_hdlr->CalculateTuitionForClass($other_class_nmbr, $pSchoolYear);
		if (isset($tuition_info[0]) && isset($tuition_info[0]['Tuition'])) $tuition = $tuition + $tuition_info[0]['Tuition'];
		if (isset($tuition_info[0]) && isset($tuition_info[0]['BookFee'])) $bookfee = $bookfee + $tuition_info[0]['BookFee'];
		if (isset($tuition_info[0]) && isset($tuition_info[0]['LabFee'])) $labfee = $labfee + $tuition_info[0]['LabFee'];
		if (isset($tuition_info[0]) && isset($tuition_info[0]['OtherFee'])) $otherfee = $otherfee + $tuition_info[0]['OtherFee'];
	}
	// set session
	if ($tuition != 0) setSession('Tuition' . $pFamilyMemberNmbr . '__', $tuition);
	else unsetSession('Tuition' . $pFamilyMemberNmbr);
	if ($bookfee != 0) setSession('BookFee' . $pFamilyMemberNmbr . '__', $bookfee);
	else unsetSession('BookFee' . $pFamilyMemberNmbr);
	if ($labfee != 0) setSession('LabFee' . $pFamilyMemberNmbr . '__', $labfee);
	else unsetSession('LabFee' . $pFamilyMemberNmbr);
	if ($otherfee != 0) setSession('OtherFee' . $pFamilyMemberNmbr . '__', $otherfee);
	else unsetSession('OtherFee' . $pFamilyMemberNmbr);

	// registration fee
	if (getSession('Tuition' . $pFamilyMemberNmbr, 0) != '') { // class registered, set reg fee
    if ($registrationfee = $tuition_hdlr->GetRegistrationFee($this_year[0]['SchoolYear'], 'no_check', date("Y-m-d"))) {
		  setSession('RegistrationFee' . $pFamilyMemberNmbr . '__', $registrationfee[0]['RegistrationFee']);
		  setSession('RegistrationFeeNmbr__', $registrationfee[0]['RegistrationFeeNmbr']);
	  }
	  else {
		  $registrationfee = 0;
		  unsetSession('RegistrationFee' . $pFamilyMemberNmbr);
		  unsetSession('RegistrationFeeNmbr');
	  }
	}
	else {
		$registrationfee = 0;
		unsetSession('RegistrationFee' . $pFamilyMemberNmbr);
	  unsetSession('RegistrationFeeNmbr');
	}
	$subtotal = $tuition + $bookfee + $labfee + $otherfee + $registrationfee[0]['RegistrationFee'];
	if ($subtotal != 0) setSession('Subtotal' . $pFamilyMemberNmbr . '__', $subtotal);
	else unsetSession('Subtotal' . $pFamilyMemberNmbr);

	// management fee and late fee
	if (getSessionCount('Tuition', '*') > 0) {
		$school_fees = $tuition_hdlr->GetSchoolFees($this_year[0]['SchoolYear'], '', date("Y-m-d"));
		for ($i = 0; $i < sizeof($school_fees); $i++) {
			$session_var = str_replace(' ', '', $school_fees[$i]['FeeName_E']) . '__';
			if ($session_var == 'ManagementFee__') {
				if ($pRegMethod == 'WEB') $schoolfee = $school_fees[$i]['Fee'] - 10;
				else $schoolfee = $school_fees[$i]['Fee'];
			}
			else {
				$schoolfee = $school_fees[$i]['Fee'];
			}
			setSession($session_var, $schoolfee);
		}
		
		// total
		$total = 0;
		foreach ($_SESSION as $name => $value) {
			if (is_int(strpos($name, "Subtotal"))) {
				$total = $total + $value[0];
			}
		}
		if ($total != 0) {
			$total = $total + getSession('ManagementFee', 0) + getSession('LateFee', 0);
			setSession('Total__', $total);
		}
	}
	else {
		unsetSession('ManagementFee');
		unsetSession('LateFee');
		unsetSession('Total');
	}

}



?>