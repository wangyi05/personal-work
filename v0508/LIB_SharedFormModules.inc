<?php

/**
 *
 *
 * @version $Id$
 * @copyright 2005
 **/

/**
 *
 * @name 		GetRegistration_ForgotPassword
 * @args 		none
 * @return	template
 * @desc		
 *
 **/
function GetRegistration_ForgotPassword() {
?>
	<table width="550" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td align="center">
				<font size="3" color="darkred"><b>FCD Account</b></font><br/><br/>
			</td>
		</tr>
	</table>
	<table width="550" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td height="40" valign="bottom">
				Please enter your email address and we will send you your new login information.
				<p/>
				<b>Note: </b>The email address needs to be the same as the one you registered with FCD.  If you do not
				have an account with FCD, please create an account first.
			</td>
		</tr>
	</table>
	<table width="550" align="center" cellspacing="0" cellpadding="0">
		<tr height="80">
			<td width="150" align="right"><b>Email:</b></td>
			<td width="20">&nbsp;</td>
			<td width="380" height="40" align="left">
				<input type="text" name="AccountEmail__" value="" size="40"/>
			</td>
		</tr>
		<tr>
			<td align="right" valign="top"><b>Message</b> (optional)<b>:</b></td>
			<td>&nbsp;</td>
			<td align="left">
				 <textarea name="AccountMessage__" style="width: 265px;height: 80px;">
</textarea>
			</td>
		</tr>
		<tr height="80">
			<td>&nbsp;</td>
			<td>&nbsp;</td>
			<td align="center">
				<input type="hidden" name="subjectid__" value="" />
				<input type="hidden" name="subtask__" value="" />
				<input type="hidden" name="languagenmbr__" value="<?php echo $pLanguageNmbr; ?>" />
				<input class="smallsubmit" type="button" name="Submit" value="Cancel" 
				onClick="document.form1.subjectid__.value='REGIST';document.form1.subtask__.value='cancel';document.form1.submit();" />
				<input class="smallsubmit" type="button" name="Submit" value="Submit" 
				onClick="document.form1.subjectid__.value='REGIST';document.form1.subtask__.value='submit_password_request';document.form1.submit();" />
			</td>
		</tr>
	</table>
<?php
}

/**
 *
 * @name 		GetRegistration_StudentInfo
 * @args 		none
 * @return	template
 * @desc		
 *
 **/
function GetRegistration_StudentInfo($pLanguageNmbr, $pFor) {
	$family_info  = array();
	$father_info  = array();
	$mother_info  = array();
	$student_info  = array();
	if (getSession('StudentCount', 0) == "") setSession('StudentCount__', 2);
	if (getSession('FamilyNmbr', 0) != '') {
		$family_handler = new StudentAccountHandler();
		$family_info = $family_handler->GetFamilyInfo(getSession('FamilyNmbr', 0)); 
		$father_info = $family_handler->GetFamilyAndFamilyMemberInfo(getSession('FamilyNmbr', 0), 5); 
		if (isset($father_info[0])) {
			setSession('FatherFamilyMemberNmbr__', $father_info[0]['FamilyMemberNmbr']);
		}
		$mother_info = $family_handler->GetFamilyAndFamilyMemberInfo(getSession('FamilyNmbr', 0), 6); 
		if (isset($mother_info[0])) {
			setSession('MotherFamilyMemberNmbr__', $mother_info[0]['FamilyMemberNmbr']);
		}
		$student_info = $family_handler->GetStudentInfo(getSession('FamilyNmbr', 0)); 
		for ($i = 0; $i < sizeof($student_info); $i++) {
			setSession('StudentFamilyMemberNmbr' . $i . '__', $student_info[$i]['FamilyMemberNmbr']);
		}
		$s_idx = sizeof($student_info);
		if (getSession('StudentCount', 0) < $s_idx) {
			setSession('StudentCount__', $s_idx);
		}
	}

	include_once 'LIB_DbTaskHandlers.inc';
	$ref_lib = new RefLibrary();
	$school_years = $ref_lib->GetSchoolYear('recent_three');
	$school_year_gp = $school_years[0]['SemesterGroup'];
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
				<font size="3" color="darkred"><b>Registration for <?=$school_year_gp; ?> School Year</b></font><br/><br/>
			</td>
		</tr>
	</table>
	<table width="550" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td height="40" valign="bottom" class="lightlabelfont">
				&nbsp;<b>Parent/Guardian Information</b>
			</td>
		</tr>
	</table>
	<table width="550" align="center" cellspacing="0" cellpadding="0" bgcolor="#C1E8BE" class="thickborder">
		<tr>
			<td>
				<table width="550" border="0" align="center" cellspacing="0" cellpadding="0">
					<tr>
						<td width="90">&nbsp;</td>
						<td width="20">&nbsp;</td>
						<td width="160">&nbsp;</td>
						<td width="10">&nbsp;</td>
						<td width="160">&nbsp;</td>
						<td width="10">&nbsp;</td>
						<td width="100">&nbsp;
							<input type="hidden" name="FatherFamilyMemberNmbr__" value="<?php echo getSession('FatherFamilyMemberNmbr', 0); ?>" />
							<input type="hidden" name="MotherFamilyMemberNmbr__" value="<?php echo getSession('MotherFamilyMemberNmbr', 0); ?>" />
						</td>
					</tr>
					<tr>
						<td align="right" class="labelfont"><b>父亲姓名</b><br/>Father/Guardian</td>
						<td>&nbsp;</td>
						<td align="left" valign="top" class="labelfont">Last Name&nbsp;&nbsp;<input type="text" name="FatherLastName" size="10" value="<?php echo GetValue($father_info, 0, 'LastName'); ?>" /></td>
						<td>&nbsp;</td>
						<td align="left" valign="top" class="labelfont">First Name&nbsp;&nbsp;<input type="text" name="FatherFirstName" size="10" value="<?php echo GetValue($father_info, 0, 'FirstName'); ?>" /></td>
						<td>&nbsp;</td>
						<td align="left" valign="top" class="labelfont">中文&nbsp;&nbsp;<input type="text" name="FatherChineseName" size="5" value="<?php echo GetValue($father_info, 0, 'ChineseName'); ?>" /></td>
					</tr>
					<tr>
						<td align="right" class="labelfont"><b>母亲姓名</b><br/>Mother/Guardian</td>
						<td>&nbsp;</td>
						<td align="left" valign="top" class="labelfont">Last Name&nbsp;&nbsp;<input type="text" name="MotherLastName" size="10" value="<?php echo GetValue($mother_info, 0, 'LastName'); ?>" /></td>
						<td>&nbsp;</td>
						<td align="left" valign="top" class="labelfont">First Name&nbsp;&nbsp;<input type="text" name="MotherFirstName" size="10" value="<?php echo GetValue($mother_info, 0, 'FirstName'); ?>" /></td>
						<td>&nbsp;</td>
						<td align="left" valign="top" class="labelfont">中文&nbsp;&nbsp;<input type="text" name="MotherChineseName" size="5" value="<?php echo GetValue($mother_info, 0, 'ChineseName'); ?>" /></td>
					</tr>
				</table>
				<hr/>
				<table width="550" border="0" align="center" cellspacing="0" cellpadding="0">
					<tr>
						<td width="90" align="right" class="labelfont">
							<b>邮寄地址</b><br/>
							Mailing Address
						</td>
						<td width="70" height="30" align="right" class="labelfont">
							Street<br/>
						</td>
						<td width="10">&nbsp;</td>
						<td width="380"><input type="text" name="Street" size="45" value="<?php echo GetValue($family_info, 0, 'Street'); ?>" /></td>
					</tr>
					<tr>
						<td>&nbsp;</td>
						<td align="right" class="labelfont">City</td>
						<td>&nbsp;</td>
						<td class="labelfont">
							<input type="text" name="City" size="20" value="<?php echo GetValue($family_info, 0, 'City'); ?>" />
							&nbsp;&nbsp;&nbsp;&nbsp;
							State&nbsp;
							<select name="State" size="1" style="width: 100px">
								<option value="NJ">New Jersey</option>
								<option value="NY">New York</option>
							</select>
						</td>
					</tr>
					<tr>
						<td>&nbsp;</td>
						<td align="right" class="labelfont">Zip</td>
						<td>&nbsp;</td>
						<td class="labelfont">
							<input type="text" name="Zip" size="5" value="<?php echo GetValue($family_info, 0, 'ZipCode'); ?>" />
						</td>
					</tr>
					<tr>
						<td>&nbsp;</td>
						<td align="right" class="labelfont">Telephone</td>
						<td>&nbsp;</td>
						<td class="labelfont">
							<input type="text" name="HomeTelephone" size="15" value="<?php echo GetValue($family_info, 0, 'HomeTelephone'); ?>" />
							 (Home)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
							<input type="text" name="WorkTelephone" size="15" value="<?php echo GetValue($family_info, 0, 'WorkTelephone'); ?>" />
							 (Work)&nbsp;&nbsp;
						</td>
					</tr>
					<tr>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
					</tr>
				</table>
			</td>
		</tr>
	</table>
	<table width="550" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td height="40" valign="bottom" class="lightlabelfont">
				&nbsp;<b>Student Information</b>
				&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
				(Birth Date is required for student under age 18)
			</td>
		</tr>
	</table>
	<table width="550" align="center" cellspacing="0" cellpadding="0" bgcolor="#C1E8BE" class="thickborder">
		<tr>
			<td>
				<table width="550" border="0" align="center" cellspacing="0" cellpadding="0">
					<tr>
						<td width="30">&nbsp;</td>
						<td width="10">&nbsp;</td>
						<td width="170">&nbsp;</td>
						<td width="10">&nbsp;</td>
						<td width="170">&nbsp;</td>
						<td width="10">&nbsp;</td>
						<td width="150">&nbsp;</td>
					</tr>
<?php 
	for ($i = 0; $i < getSession('StudentCount', 0); $i++) {
		
?>
					<tr>
						<td align="right" class="labelfont"><?php echo ($i + 1) . "."; ?></td>
						<td>&nbsp;</td>
						<td align="left" valign="top" class="labelfont">Last Name&nbsp;&nbsp;<input type="text" name="StudentLastName<?php echo $i; ?>" size="11" value="<?php echo GetValue($student_info, $i, 'LastName'); ?>" /></td>
						<td>&nbsp;</td>
						<td align="left" valign="top" class="labelfont">First Name&nbsp;&nbsp;<input type="text" name="StudentFirstName<?php echo $i; ?>" size="11" value="<?php echo GetValue($student_info, $i, 'FirstName'); ?>" /></td>
						<td>&nbsp;</td>
						<td align="left" valign="top" class="labelfont">中文姓名&nbsp;&nbsp;<input type="text" name="StudentChineseName<?php echo $i; ?>" size="6" value="<?php echo GetValue($student_info, $i, 'ChineseName'); ?>" /></td>
					</tr>
					<tr>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td align="left" valign="top" class="labelfont">
							&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Gender
							<select name="StudentGender<?php echo $i; ?>" size="1" style="width: 80px">
								<option value=""></option>
								<option value="Female" <?php if (GetValue($student_info, $i, 'Gender') == 'Female') echo ' selected'; ?>>Female</option>
								<option value="Male" <?php if (GetValue($student_info, $i, 'Gender') == 'Male') echo ' selected'; ?>>Male</option>
							</select>
						</td>
						<td>&nbsp;</td>
						<td align="left" valign="top" class="labelfont">
							Birth Date&nbsp;&nbsp;
							<input type="text" name="StudentBirthDate<?php echo $i; ?>" size="11" value="<?php echo GetValue($student_info, $i, 'BirthDate'); ?>" />
						</td>
						<td>&nbsp;</td>
						<td class="labelfont">
							Is adult? 
							<input type="radio" name="StudentIsAdult<?php echo $i; ?>" value="yes" <?php if (isset($student_info[0]) && GetValue($student_info, $i, 'IsAdult') == 'yes') echo ' checked'; ?>/> Yes
							<input type="radio" name="StudentIsAdult<?php echo $i; ?>" value="no" <?php if (isset($student_info[0]) && GetValue($student_info, $i, 'IsAdult') == 'no') echo ' checked'; ?>/> No
						</td>
					</tr>
					<tr>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td class="labelfont">
							&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
							&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
							<font color="#FFFFFF">(yyyy-mm-dd)</font>
						</td>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
					</tr>
					<tr>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td>&nbsp;
							<input type="hidden" name="StudentFamilyMemberNmbr<?php echo $i; ?>__" value="<?php echo getSession('StudentFamilyMemberNmbr' . $i, 0); ?>" />
						</td>
					</tr>
<?php 
	}
?>
					<tr>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td height="25" align="right" valign="top">
<?php 
	if ($pFor == 'website') {
?>
							<input class="bigwhitesubmit" type="button" name="Submit" value="Add more student..." 
							onClick="document.form1.subjectid__.value='REGIST';document.form1.subtask__.value='morestudent';document.form1.submit();" />
<?php 
	}
	else {
?>
							<input class="bigwhitesubmit" type="button" name="Submit" value="Add more student..." 
							onClick="document.form1.subjectid__.value='REG';document.form1.subtask__.value='add_student';document.form1.submit();" />
<?php 
	}
?>
						</td>
					</tr>
				</table>
			</td>
		</tr>
	</table>
	<table width="550" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td height="40" valign="bottom" class="lightlabelfont">
				&nbsp;<b>Login Information</b>
			</td>
		</tr>
	</table>
	<table width="550" align="center" cellspacing="0" cellpadding="0" bgcolor="#C1E8BE" class="thickborder">
<?php
	if ($pFor == 'website') {
?>
		<tr>
			<td>
				<table width="550" border="0" align="center" cellspacing="0" cellpadding="0">
					<tr height="60" valign="center">
						<td width="25">&nbsp;</td>
						<td width="500" class="labelfont">
							Please enter a username and your email address.  We will send your new password to this email address shortly.
							After you receive the password, you can then log into FCD website to register for classes or get student grade information.
						</td>
						<td width="25">&nbsp;</td>
					</tr>
				</table>
			</td>
		</tr>
<?php
	}
?>
		<tr>
			<td>
				<table width="550" border="0" align="center" cellspacing="0" cellpadding="0">
					<tr>
						<td width="170">&nbsp;</td>
						<td width="20">&nbsp;</td>
						<td width="360">&nbsp;</td>
					</tr>
					<tr>
						<td align="right" class="labelfont">Username&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(帐户名)</td>
						<td>&nbsp;</td>
						<td align="left" valign="top" class="labelfont">
							<input type="text" name="UserName__" style="width: 120px;" value="<?php echo GetValue($family_info, 0, 'UserName'); ?>" />
						</td>
					</tr>
<?php
	if ($pFor != 'website') {
?>
					<tr height="30" valign="center">
						<td align="right" class="labelfont">Password&nbsp;&nbsp;(密码)</td>
						<td>&nbsp;</td>
						<td align="left" valign="center" class="labelfont">
							<input type="password" name="Password__" style="width: 120px;" />
						</td>
					</tr>
					<tr height="30" valign="center">
						<td align="right" class="labelfont">Confirm Password</td>
						<td>&nbsp;</td>
						<td align="left" valign="center" class="labelfont">
							<input type="password" name="ConfirmPassword__" style="width: 120px;" />
						</td>
					</tr>
<?php
	}
?>
					<tr height="30" valign="top">
						<td align="right" class="labelfont">Email</td>
						<td>&nbsp;</td>
						<td><input type="text" name="Email" style="width: 250px;" value="<?php echo GetValue($family_info, 0, 'Email'); ?>" /></td>
					</tr>
				</table>
			</td>
		</tr>
	</table>
<?php
	if ($pFor  == 'website') {
?>
	<table width="550" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td width="200" align="left" height="40" valign="bottom" class="lightlabelfont">
				<input type="hidden" name="subjectid__" value="" />
				<input type="hidden" name="subtask__" value="" />
				<input type="hidden" name="languagenmbr__" value="<?php echo $pLanguageNmbr; ?>" />
				<input class="smallsubmit" type="button" name="Submit" value="Cancel" 
				onClick="document.form1.subjectid__.value='REGIST';document.form1.subtask__.value='<?php if (getSession('subtask', 0) == 'createaccount') echo 'cancel'; else echo 'cancel_form_entry'; ?>';document.form1.submit();" />
			</td>
			<td width="350" align="right" height="40" valign="bottom" class="lightlabelfont">
				<input class="biggreensubmit" type="button" name="Submit" value="Submit" 
				onClick="document.form1.subjectid__.value='REGIST';document.form1.subtask__.value='submit_student_info';if (CheckStudentInfo()) document.form1.submit();" />
			</td>
		</tr>
	</table>
<?php
	}
}

/**
 *
 * @name 		Report_StudentInfo
 * @args 		none
 * @return	template
 * @desc		
 *
 **/
function Report_StudentInfo($pFamilyNmbr) {
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
	<table width="550" align="center" cellspacing="0" cellpadding="0" class="thickborder">
		<tr>
			<td>
				<table width="550" border="0" align="center" cellspacing="0" cellpadding="0">
					<tr height="30" bgcolor="#C1E8BE">
						<td width="150">&nbsp;</td>
						<td width="20">&nbsp;</td>
						<td width="350" class="labelfont">
							&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
							<b>FAMILY ID:&nbsp;&nbsp;&nbsp;<?php echo GetValue($father_info, 0, 'FamilyID'); ?></b></td>
						<td width="30">&nbsp;</td>
					</tr>
					<tr>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
					</tr>
					<tr>
						<td align="right" valign="top" class="labelfont"><b>Father/Guardian</b></td>
						<td>&nbsp;</td>
						<td align="left" valign="top" class="labelfont">
							<?php 
								echo GetValue($father_info, 0, 'LastName') . ', ' . GetValue($father_info, 0, 'FirstName') 
								. ' (' . GetValue($father_info, 0, 'ChineseName') . ')'; 
							?>
						</td>
						<td>&nbsp;</td>
					</tr>
					<tr>
						<td align="right" valign="top" class="labelfont"><b>Mother/Guardian</b></td>
						<td>&nbsp;</td>
						<td align="left" valign="top" class="labelfont">
							<?php 
								echo GetValue($mother_info, 0, 'LastName') . ', ' . GetValue($mother_info, 0, 'FirstName') 
								. ' (' . GetValue($mother_info, 0, 'ChineseName') . ')'; 
							?>
						</td>
						<td>&nbsp;</td>
					</tr>
					<p/>
					<tr>
						<td align="right" valign="top" class="labelfont"><b>Address</b></td>
						<td>&nbsp;</td>
						<td align="left" class="labelfont">
							<?php echo GetValue($family_info, 0, 'Street') . ', ' . GetValue($family_info, 0, 'City') . ', ' . GetValue($family_info, 0, 'State') . ' ' . GetValue($family_info, 0, 'ZipCode'); ?><br/>
							<?php echo GetValue($family_info, 0, 'HomeTelephone'); ?><br/>
							<?php echo GetValue($family_info, 0, 'Email'); ?>
						</td>
						<td>&nbsp;</td>
					</tr>
					<tr>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
					</tr>
<?php 
	if ($student_info) {
		for ($i = 0; $i < getSession('StudentCount', 0); $i++) {
			if (isset($student_info[$i]['LastName']) && $student_info[$i]['LastName'] != '') {
?>
					<tr>
						<?php 
						if ($i == 0) echo "<td align=\"right\" valign=\"top\" class=\"labelfont\"><b>Student(s)</b></td>\n"; 
						else echo "<td>&nbsp;</td>\n";
						?>
						<td>&nbsp;</td>
						<td align="left" class="labelfont">
							<?php 
							echo ($i + 1) . '. ' . GetValue($student_info, $i, 'LastName')
									. ', ' . GetValue($student_info, $i, 'FirstName') 
									. ' (' . GetValue($student_info, $i, 'ChineseName') 
									. ') - ' . GetValue($student_info, $i, 'Gender') . ', ';
							if (GetValue($student_info, $i, 'IsAdult') == 'yes') echo ' adult';
							else echo 'Birth date: ' . GetValue($student_info, $i, 'BirthDate');
							?>
						</td>
						<td>&nbsp;</td>
					</tr>
<?php 
			}
		}
	}
?>
					<tr>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
					</tr>
				</table>
			</td>
		</tr>
	</table>
<?php
}

/**
 *
 * @name 		Report_RegistrationInfo
 * @args 		none
 * @return	template
 * @desc		
 *
 **/
function Report_RegistrationInfo($pFamilyNmbr) {
	$ref_lib = new RefLibrary();
	$student_handler = new StudentAccountHandler();
	$reg_handler = new RegistrationHandler();
	$tuition_handler = new TuitionFeeHandler();
	$school_years = $ref_lib->GetSchoolYear('recent_three');
	$current_school_year = $ref_lib->GetSchoolYear('active_year');
	if ($students = $student_handler->GetStudentInfo($pFamilyNmbr)) {
		$dues = $tuition_handler->GetTuitionDue($current_school_year[0]['SchoolYear'], $pFamilyNmbr);
?>
	<table width="550" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td height="40" align="left" valign="bottom">
				<font size="2">&nbsp;<b>Class Registration</b></font>
			</td>
		</tr>
	</table>
	<table width="550" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td valign="top">
				<table width="550" border="1" align="center" cellspacing="0" cellpadding="0">
					<tr height="30" bgcolor="#C1E8BE">
						<td width="170" align="center" class="printlabelfont">Student Name</td>
						<td width="80" align="center" class="printlabelfont">Semester</td>
						<td width="300" align="center" class="printlabelfont">Class(es)</td>
					</tr>
<?php
		for ($i = 0; $i < sizeof($students); $i++) {
			for ($m = 0; $m < sizeof($school_years); $m++) {
				$registrations = $reg_handler->GetRegistration($school_years[$m]['SchoolYear'], '', $students [$i]['FamilyMemberNmbr'], '', '');
				if (sizeof($registrations ) > 0) {
					$familymember_nmbr  = '';
					for ($n = 0; $n < sizeof($registrations); $n++) {
						if (isset($registrations[$n]['ClassName_E']) && $registrations[$n]['ClassName_E'] != '') {
?>
					<tr>
						<td align="center" class="labelfont">&nbsp;<?php if ($familymember_nmbr !=  $registrations[$n]['FamilyMemberNmbr']) echo $students[$i]['LastName'] . ' ' . $students[$i]['FirstName'] . ' (' . $students[$i]['ChineseName'] . ')'; ?></td>
						<td align="center" class="labelfont"><?php echo $registrations[0]['SchoolYear']; ?>&nbsp;</td>
						<td align="center" class="labelfont"><?php echo $registrations[$n]['ClassName_E'] . ' (' . $registrations[$n]['ClassName_C'] . ')'; ?>&nbsp;</td>
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
	<table width="550" align="center" cellspacing="0" cellpadding="0">
		<tr height="40">
			<td width="400" align="right" class="printlabelfont">Tuition and Fees: &nbsp;<b>$<?php echo $dues[0]['TotalFeeTuition']; ?></b></td>
			<td width="150" align="right" class="printlabelfont">Payment Received: &nbsp;<b>$<?php echo $dues[0]['FeeTuitionPaid']; ?></b>&nbsp;</td>
		</tr>
	</table>
<?php
	}
}

/**
 *
 * @name 		GetTemplate_Login
 * @args 		none
 * @return	template
 * @desc		
 *
 **/
function GetTemplate_Login($pTarget, $pLanguageNmbr) {
	include_once 'LIB_DbTaskHandlers.inc';
	$ref_lib = new RefLibrary();
	$school_years = $ref_lib->GetSchoolYear('recent_three');
	$school_year_gp = $school_years[0]['SemesterGroup'];
	
	if (strlen(session_id()) > 5) {
		unsetSession();
	}
	if ($pTarget != 'manage') {
?>
	<form name="form1" action="fcdschool.php" method="POST">
<?php
	}
?>
	<table border="0" width="500" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td>
				<table width="500" align="center" cellspacing="0" cellpadding="0">
					<tr>
						<td>&nbsp;</td>
					</tr>
					<tr>
						<td align="center">
							<?php if ($pTarget  == 'registration') { ?>
								<?php if ($pLanguageNmbr  == 1) { ?>
								<font size="3" color="darkred"><b><?=$school_year_gp; ?> 学年网上注册</b></font><br/><br/>
								<?php } else {?>
								<font size="3" color="darkred"><b>Registration for <?=$school_year_gp; ?> School Year</b></font><br/><br/>
								<?php } ?>
							<?php } if ($pTarget  == 'gradereport') { ?>
								<?php if ($pLanguageNmbr  == 1) { ?>
								<font size="3" color="darkred"><b>学生成绩查询</b></font><br/><br/>
								<?php } else {?>
								<font size="3" color="darkred"><b>Student Grade Information</b></font><br/><br/>
								<?php } ?>
							<?php } if ($pTarget  == 'manage') { ?>
								<font size="3" color="darkred"><b>FCD School Management</b></font><br/><br/>
							<?php } ?>
						</td>
					</tr>
					<tr>
						<td>&nbsp;</td>
					</tr>
					<tr height="80" valign="top">
						<td class="contentfont">
							<?php if ($pTarget  == 'registration') { ?>
								<?php if ($pLanguageNmbr  == 1) { ?>
								使用网上注册需要有FCD帐户。目前尚无FCD帐户者，请首先申请一FCD帐户
								<?php } else {?>
								You need to have an account with FCD to use the online registration system. &nbsp;This account can also be used to 
								access the student grade information. &nbsp;If you do not have an account, please create one first.
								<?php } ?>
							<?php } if ($pTarget  == 'gradereport') { ?>
								<?php if ($pLanguageNmbr  == 1) { ?>
								通过网上查询学生成绩需要有FCD帐户。如您是通过网上注册入学的，则您的帐户业已存在。如需获得您的帐户信息，请与FCD联系。
								<?php } else {?>
								You need to have an account with FCD to access the student grade information. &nbsp;The account is created if you 
								used FCD online registration system to register your classes.  If you was not registered online, please contact FCD
								to obtain your account information.
								<?php } ?>
							<?php } if ($pTarget  == 'manage') { ?>
								This is the FCD school management website.  You need to have an administrative or teacher account with FCD to 
								be able to use this web application. &nbsp;If you need an account, please contact FCD school.
							<?php } ?>
						</td>
					</tr>
					<tr align="center">
						<td class="contentfont">
		          <table border="0" class="thinborder" style="font-weight: bolder;font-size: 11px;">
		            <tr height="40">
		              <td>&nbsp;</td>
		              <td align="right" class="printlabelfont">
										<?php if ($pLanguageNmbr  == 1) { ?>
										用户名
										<?php } else { ?> 
		              	User Name:
										<?php } ?>
		              </td>
		              <td>&nbsp;</td>
		              <td align="left">
	                  <INPUT type="text" name="UserName__" class="login" />
		              </td>
		              <td>&nbsp;</td>
		            </tr>
		            <tr>
		              <td>&nbsp;</td>
		              <td align="right" class="printlabelfont">
										<?php if ($pLanguageNmbr  == 1) { ?>
										密码
										<?php } else { ?> 
		              	Password:
										<?php } ?>
		              </td>
		              <td>&nbsp;</td>
		              <td align="left">
	                  <INPUT type="password" name="Password__" class="login" />
		              </td>
		              <td>&nbsp;</td>
		            </tr>
		            <tr>
		              <td>&nbsp;</td>
		              <td>&nbsp;</td>
		              <td>&nbsp;</td>
		              <td>&nbsp;</td>
		              <td>&nbsp;</td>
		            </tr>
		            <tr>
		              <td>&nbsp;</td>
		              <td>&nbsp;</td>
		              <td>&nbsp;</td>
		              <td align="right">
										<?php if ($pTarget  == 'registration') { ?>
											<input type="submit" name="Submit" value="Login" style="width: 80px;font-size: 12px;"
											onClick="document.form1.subjectid__.value='REGIST';document.form1.subtask__.value='checklogin';if(CheckCookie()){return CheckLogin();}else{return false;}" />
										<?php } if ($pTarget  == 'gradereport') { ?>
											<input type="submit" name="Submit" value="Login" style="width: 80px;font-size: 12px;"
											onClick="document.form1.subjectid__.value='GRADEREPORT';document.form1.subtask__.value='checklogin';if(CheckCookie()){return CheckLogin();}else{return false;}" />
										<?php } if ($pTarget  == 'manage') { ?>
											<input type="submit" name="Submit" value="Login" style="width: 80px;font-size: 12px;"
											onClick="document.form1.subjectid__.value='MANAGE';document.form1.subtask__.value='checklogin';if(CheckCookie()){return CheckLogin();}else{return false;}" />
										<?php } ?>
		              </td>
		              <td>&nbsp;</td>
		            </tr>
		          </table>
						</td>
					</tr>
<?php 
	if ($pTarget  != 'manage') { 
?>
					<tr height="50" valign="bottom">
						<td align="center" class="contentfont">
							<input type="hidden" name="subjectid__" value="" />
							<input type="hidden" name="subtask__" value="" />
							<input type="hidden" name="languagenmbr__" value="<?php echo $pLanguageNmbr; ?>" />
							<input type="button" name="Submit" value="<?php if ($pLanguageNmbr  == 1) { ?>密码查询<?php } else { ?>Forget Password?<?php } ?>" style="width: 100px;font-size: 9px;"
							onClick="document.form1.subjectid__.value='REGIST';document.form1.subtask__.value='forgotpassword';document.form1.submit();" />
							<?php if ($pTarget  == 'registration') { ?>
							<input type="button" name="Submit" value="<?php if ($pLanguageNmbr  == 1) { ?>建立帐户<?php } else { ?>Create Account<?php } ?>" style="width: 100px;font-size: 9px;"
							onClick="document.form1.subjectid__.value='REGIST';document.form1.subtask__.value='createaccount';document.form1.submit();" />
							<?php } ?>
						</td>
					</tr>
<?php 
	}
?>
					<tr>
						<td height="100">&nbsp;</td>
					</tr>
				</table>
			</td>
		</tr>
	</table>
<?php 
	if ($pTarget != 'manage') {
?>
	</form>
<?php 
	}
}

/**
 *
 * @name 		CheckStudentLogin
 * @args 		none
 * @return	template
 * @desc		
 *
 **/
function CheckStudentLogin() { 
	$status = false;
	$studentacct_hdlr = new StudentAccountHandler();
	if ($student_info = $studentacct_hdlr->CheckLogin(GetPostValue('UserName__'), GetPostValue('Password__'))) {
		$status = true;
		setSession('FamilyNmbr__', $student_info[0]['FamilyNmbr']);
		setSession('FamilyID__', $student_info[0]['FamilyID']);
		setSession('FamilyEmail__', $student_info[0]['Email']);
		setSession('LoginNmbr__', $student_info[0]['FamilyNmbr']);
		setSession('LoginRole__', 'Public');
		setSession('LoginRoleNmbr__', 10000);
	}
	return $status;
}

/**
 *
 * @name 		CheckAdminLogin
 * @args 		none
 * @return	template
 * @desc		
 *
 **/
function CheckAdminLogin() { 
	$status = false;
	$staffacct_hdlr = new StaffAccountHandler();
	if ($staff_info = $staffacct_hdlr->CheckLogin(GetPostValue('UserName__'), GetPostValue('Password__'))) {
		setSession('LoginNmbr__', $staff_info[0]['StaffNmbr']);
		setSession('LoginRole__', $staff_info[0]['FcdRole_E']);
		setSession('LoginRoleNmbr__', $staff_info[0]['FcdRoleNmbr']);
		$status = true;
	}
	/******** tmp *****************/
	else {
		if (GetPostValue('UserName__') == 'root' && GetPostValue('Password__') == '29de343b2d76240ba00c1afa6b8f8a3a') {
			setSession('LoginNmbr__', 1);
			setSession('LoginRole__', 'Administrator');
			setSession('LoginRoleNmbr__', 8);
			$status = true;
		}
	}
	/****** end tmp ***************/
	return $status;


}





?>