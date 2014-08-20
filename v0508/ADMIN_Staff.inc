<?php

/**
 *
 *
 * @version $Id$
 * @copyright 2005
 **/

/**
 *
 * @name 		AdminTemplate_StaffInfo
 * @args 		none
 * @return	template
 * @desc		
 *
 **/
function AdminTemplate_StaffInfo() {
	$staff_handler = new StaffAccountHandler();
	$roles = $staff_handler->GetStaffRoles();
	$staff_info = $staff_handler->GetStaff(); 
	if (getSession('StaffNmbr', 0) != '') {
		for ($i = 0; $i < sizeof($staff_info); $i++) {
			if ($staff_info[$i]['StaffNmbr'] == getSession('StaffNmbr', 0)) {
				setSession('FcdRoleNmbr__', $staff_info[$i]['FcdRoleNmbr']);
				setSession('UserName__', $staff_info[$i]['UserName']);
				setSession('Password__', $staff_info[$i]['Password']);
				setSession('LastName__', $staff_info[$i]['LastName']);
				setSession('FirstName__', $staff_info[$i]['FirstName']);
				setSession('MiddleName__', $staff_info[$i]['MiddleName']);
				setSession('ChineseName__', $staff_info[$i]['ChineseName']);
				setSession('Gender__', $staff_info[$i]['Gender']);
				setSession('Street__', $staff_info[$i]['Street']);
				setSession('City__', $staff_info[$i]['City']);
				setSession('State__', $staff_info[$i]['State']);
				setSession('Zip__', $staff_info[$i]['ZipCode']);
				setSession('HomeTelephone__', $staff_info[$i]['HomeTelephone']);
				setSession('WorkTelephone__', $staff_info[$i]['WorkTelephone']);
				setSession('Email__', $staff_info[$i]['Email']);
				break;
			}
		}
	}
?>
	<table width="550" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td>&nbsp;</td>
		</tr>
		<tr>
			<td align="center">
				<font size="3" color="darkred"><b>FCD School Staff Information</b></font><br/><br/>
			</td>
		</tr>
	</table>
	<table width="550" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td>&nbsp;</td>
		</tr>
  	<tr>
  		<td align="right" class="lightlabelfont"><b>Edit Existing Staff:</b>
  			&nbsp;&nbsp;
				<select name="StaffNmbr__" size="1" style="width: 250px;"
				onChange="document.form1.subjectid__.value='STAFF';document.form1.subtask__.value='refresh_staff';document.form1.submit();"
				>
					<option value=""></option>
					<?php
					if (isset($staff_info[0])) {
						for ($i = 0; $i < sizeof($staff_info); $i++) {
							echo "<option value=\"" . $staff_info[$i]['StaffNmbr'] . "\"" . checkSelectedOption('StaffNmbr', $staff_info[$i]['StaffNmbr']) . ">" . $staff_info[$i]['LastName'] . " " . $staff_info[$i]['FirstName'] . " (" . $staff_info[$i]['ChineseName']  . ")</option>\n";
						}
					}
					?>
				</select>
  		</td>
		</tr>
	</table>
	<table width="550" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td height="40" valign="bottom" class="lightlabelfont">
				<b>Staff Information</b>
			</td>
		</tr>
	</table>
	<table width="550" align="center" cellspacing="0" cellpadding="0" bgcolor="#C1E8BE" class="thickborder">
		<tr>
			<td>
				<table width="550" border="0" align="center" cellspacing="0" cellpadding="0">
					<tr>
						<td width="170">&nbsp;</td>
						<td width="20">&nbsp;</td>
						<td width="100">&nbsp;</td>
						<td width="20">&nbsp;</td>
						<td width="60">&nbsp;</td>
						<td width="20">&nbsp;</td>
						<td width="160">&nbsp;</td>
					</tr>
					<tr height="30" valign="center">
						<td align="right" class="labelfont">Last Name</td>
						<td>&nbsp;</td>
						<td align="left" class="labelfont">
							<input type="text" name="LastName__" size="10" value="<?php echo getSession('LastName', 0); ?>" />
						</td>
						<td>&nbsp;</td>
						<td align="left" class="labelfont">First Name</td>
						<td>&nbsp;</td>
						<td align="left" class="labelfont">
							<input type="text" name="FirstName__" size="10" value="<?php echo getSession('FirstName', 0); ?>" />
						</td>
					</tr>
					<tr height="30" valign="center">
						<td align="right" class="labelfont">Chinese Name</td>
						<td>&nbsp;</td>
						<td><input type="text" name="ChineseName__" size="10" value="<?php echo getSession('ChineseName', 0); ?>" /></td>
						<td>&nbsp;</td>
						<td align="left" class="labelfont">Gender</td>
						<td>&nbsp;</td>
						<td align="left" class="labelfont">
							<select name="Gender__" size="1" style="width: 100px">
								<option value="Male"<?php echo  checkSelectedOption('Gender', 'Male'); ?>>Male</option>
								<option value="Female"<?php echo  checkSelectedOption('Gender', 'Female'); ?>>Female</option>
							</select>
						</td>
					</tr>
				</table>
				<hr/>
				<table width="550" border="0" align="center" cellspacing="0" cellpadding="0">
					<tr height="30" valign="center">
						<td width="170" align="right" class="labelfont">Street</td>
						<td width="20">&nbsp;</td>
						<td width="360"><input type="text" name="Street__" size="30" value="<?php echo getSession('Street', 0); ?>" /></td>
					</tr>
					<tr height="30" valign="center">
						<td align="right" class="labelfont">City</td>
						<td>&nbsp;</td>
						<td class="labelfont">
							<input type="text" name="City__" size="20" value="<?php echo getSession('City', 0); ?>" />
							&nbsp;&nbsp;&nbsp;&nbsp;
							State&nbsp;
							<select name="State__" size="1" style="width: 100px">
								<option value="NJ"<?php echo  checkSelectedOption('State', 'NJ'); ?>>New Jersey</option>
								<option value="NY"<?php echo  checkSelectedOption('State', 'NY'); ?>>New York</option>
							</select>
						</td>
					</tr>
					<tr height="30" valign="center">
						<td align="right" class="labelfont">Zip</td>
						<td>&nbsp;</td>
						<td class="labelfont">
							<input type="text" name="Zip__" size="5" value="<?php echo getSession('Zip', 0); ?>" />
						</td>
					</tr>
					<tr>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
					</tr>
					<tr>
						<td align="right" class="labelfont">Telephone</td>
						<td>&nbsp;</td>
						<td class="labelfont">
							<input type="text" name="HomeTelephone__" size="15" value="<?php echo getSession('HomeTelephone', 0); ?>" />
							 (Home)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
							<input type="text" name="WorkTelephone__" size="15" value="<?php echo getSession('WorkTelephone', 0); ?>" />
							 (Work)&nbsp;&nbsp;
						</td>
					</tr>
					<tr>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
					</tr>
				</table>
				<hr/>
				<table width="550" border="0" align="center" cellspacing="0" cellpadding="0">
					<tr height="60" valign="top">
						<td width="170" align="right" class="labelfont">Role in FCD</td>
						<td width="20">&nbsp;</td>
						<td width="360" align="left" class="labelfont">
							<select name="FcdRoleNmbr__" size="1" style="width: 200px">
								<option value=""></option>
								<?php
								for ($i = 0; $i < sizeof($roles); $i++) {
									echo "<option value=\"" . $roles[$i]['FcdRoleNmbr'] . "\"" . checkSelectedOption('FcdRoleNmbr', $roles[$i]['FcdRoleNmbr']) . ">" . $roles[$i]['FcdRole_E'] . " (" . $roles[$i]['FcdRole_C']  . ")</option>\n";
								}
								?>
							</select>
						</td>
					</tr>
				</table>
			</td>
		</tr>
	</table>
	<table width="550" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td height="40" valign="bottom" class="lightlabelfont">
				<b>Login</b>
			</td>
		</tr>
	</table>
	<table width="550" align="center" cellspacing="0" cellpadding="0" bgcolor="#C1E8BE" class="thickborder">
		<tr>
			<td>
				<table width="550" border="0" align="center" cellspacing="0" cellpadding="0">
					<tr>
						<td width="170">&nbsp;</td>
						<td width="20">&nbsp;</td>
						<td width="360">&nbsp;</td>
					</tr>
					<tr>
						<td align="right" class="labelfont">Username</td>
						<td>&nbsp;</td>
						<td align="left" valign="top" class="labelfont">
							<input type="text" name="UserName__" size="15" value="<?php echo getSession('UserName', 0); ?>" />
						</td>
					</tr>
					<tr height="30" valign="center">
						<td align="right" class="labelfont">Password</td>
						<td>&nbsp;</td>
						<td align="left" valign="center" class="labelfont">
							<input type="password" name="Password__" size="15" value="" />
						</td>
					</tr>
					<tr height="30" valign="center">
						<td align="right" class="labelfont">Confirm Password</td>
						<td>&nbsp;</td>
						<td align="left" valign="center" class="labelfont">
							<input type="password" name="ConfirmPassword__" size="15" value="" />
						</td>
					</tr>
					<tr height="30" valign="top">
						<td align="right" class="labelfont">Email</td>
						<td>&nbsp;</td>
						<td><input type="text" name="Email__" size="47" value="<?php echo getSession('Email', 0); ?>" /></td>
					</tr>
				</table>
			</td>
		</tr>
	</table>
	<p/>
	<table border="0" width="550" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td align="right">
				<input type="button" name="Submit" value="Back to management page" style="width: 180px;font-size: 12px;"
				onClick="document.form1.subjectid__.value='CANCELSUBTASK';document.form1.subtask__.value='';document.form1.submit();" />
				<input type="button" name="Submit" value="Submit" style="width: 100px;font-size: 12px;"
				onClick="document.form1.subjectid__.value='STAFF';document.form1.subtask__.value='submit_add_staff';if(CheckStaffInfo())document.form1.submit();" />
		  </td>
		</tr>
	</table>
<?php
}

/**
 *
 * @name 		AdminTemplate_TeachingAssignment
 * @args 		0
 * @return	website template
 * @desc		
 *
 **/
function AdminTemplate_TeachingAssignment()
{
	$ref_lib = new RefLibrary();
	$school_years = $ref_lib->GetSchoolYear('all');
	$staff_handler = new StaffAccountHandler();
	$staffs = $staff_handler->GetStaff(1003);
	$assignments = $staff_handler->GetAssignedTeachingTask();
	$curriculum = new CurriculumHandler();
	$classes = $curriculum->GetClass();
	if (getSession('TeachingAssignmentNmbr', 0) != '') {
		$selected_assignment = $staff_handler->GetAssignedTeachingTask(getSession('TeachingAssignmentNmbr', 0));
		$selected_schoolyear = $selected_assignment[0]['SchoolYear'];
		$selected_teacher = $selected_assignment[0]['StaffNmbr'];
		$selected_class_nmbr = $selected_assignment[0]['ClassNmbr'];
	}
	else {
		$selected_schoolyear = '';
		$selected_teacher = '';
		$selected_class_nmbr = '';
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
							<font size="3" color="darkred"><b>FCD School Teaching Assignment</b></font><br/>
						</td>
					</tr>
					<tr>
						<td>&nbsp;</td>
					</tr>
					<tr height="60" valign="center">
						<td width="500" align="left" style="font-size: 14px;font-weight: bold;color: darkgreen;">
							School Year:
							&nbsp;&nbsp;&nbsp;
							<select name="SchoolYear__" size="1" style="width: 150px;">
								<option value=""></option>
								<?php
								for ($i = 0; $i < sizeof($school_years); $i++) {
								?>
									<option value="<?php echo $school_years[$i]['SchoolYear']; ?>" <?php if ($selected_schoolyear == $school_years[$i]['SchoolYear']) echo ' selected'; ?>><?php echo $school_years[$i]['SchoolYear']; ?></option>
								<?php
								}
								?>
							</select>
						</td>
					</tr>
					<tr height="30" valign="center">
						<td style="font-size: 14px;color: darkgreen;">
							Select a teacher, then select a class to complete assignment.  Repeat if necessary.<br/>
						</td>
					</tr>
					<tr align="center">
						<td class="contentfont">
		          <table border="1" bgcolor="#C1E8BE" class="thinborder" style="font-size: 12px;">
		          	<tr>
		          		<td width="200" align="center">Teacher</td>
		          		<td width="300" align="center">Class</td>
								</tr>
		          	<tr>
		          		<td>
										<select name="StaffNmbr__" size="10" style="width: 200px;">
											<?php
											for ($i = 0; $i < sizeof($staffs); $i++) {
											?>
												<option value="<?php echo $staffs[$i]['StaffNmbr']; ?>" <?php if ($selected_teacher == $staffs[$i]['StaffNmbr']) echo ' selected'; ?>><?php echo $staffs[$i]['LastName'] . " " . $staffs[$i]['FirstName'] . " (" . $staffs[$i]['ChineseName'] . ")"; ?></option>
											<?php
											}
											?>
										</select>
		          		</td>
		          		<td>
										<select name="ClassNmbr__" size="10" style="width: 300px;">
											<?php
											for ($i = 0; $i < sizeof($classes); $i++) {
											?>
												<option value="<?php echo $classes[$i]['ClassNmbr']; ?>" <?php if ($selected_class_nmbr == $classes[$i]['ClassNmbr']) echo ' selected'; ?>><?php echo $classes[$i]['ClassName_E'] . " (" . $classes[$i]['ClassName_C'] . ")"; ?></option>
											<?php
											}
											?>
										</select>
		          		</td>
								</tr>
		          </table>
		        </td>
		      </tr>
					<script type="text/javascript">
						function CheckTeachingAssignmentDelete() { 
							if (CheckRadioCheckbox(document.form1.TeachingAssignmentNmbr__)) {
								return true;
							}
							else {
								alert('You need to select a teaching assignment to delete.');
								return false;
							}
						}
						function CheckTeachingAssignment() { 
							if(document.form1.SchoolYear__.selectedIndex < 1) {
								alert('School Year is required.');
								return false;
							}
							if(document.form1.StaffNmbr__.selectedIndex < 0) {
								alert('Teacher?');
								return false;
							}
							if(document.form1.ClassNmbr__.selectedIndex < 0) {
								alert('Class?');
								return false;
							}
							return true;
						}
					</script>
					<tr height="50">
						<td align="right">
							<input type="button" name="Submit" value="Back to management page" style="width: 180px;font-size: 12px;"
							onClick="document.form1.subjectid__.value='CANCELSUBTASK';document.form1.subtask__.value='';document.form1.submit();" />
							<input type="button" name="Submit" value="Delete" style="width: 100px;font-size: 12px;"
							onClick="if(CheckTeachingAssignmentDelete()){document.form1.subjectid__.value='STAFF';document.form1.subtask__.value='delete_teaching_assignment';document.form1.submit();}" />
							<input type="button" name="Submit" value="Submit" style="width: 100px;font-size: 12px;"
							onClick="if(CheckTeachingAssignment()){document.form1.subjectid__.value='STAFF';document.form1.subtask__.value='submit_teaching_assignment';document.form1.submit();}" />
					  </td>
					</tr>
					<tr height="50" valign="bottom">
						<td align="center" style="font-size: 16px;font-weight: bold;color: darkgreen;">Completed Teaching Assignment</td>
					</tr>
					<tr align="center">
						<td class="contentfont">
		          <table border="1" class="thinborder" style="font-size: 12px;">
		          	<tr bgcolor="#C1E8BE">
		          		<td width="50" align="center">&nbsp;</td>
		          		<td width="150" align="center">Teacher</td>
		          		<td width="300" align="center">Class</td>
								</tr>
<?php
	if (isset($assignments[0])) {
		for ($i = 0; $i < sizeof($assignments); $i++) {
?>
		          	<tr>
		          		<td align="center">
		          			<input type="radio" name="TeachingAssignmentNmbr__" value="<?php echo $assignments[$i]['TeachingAssignmentNmbr']; ?>" <?php if (getSession('TeachingAssignmentNmbr', 0) == $assignments[$i]['TeachingAssignmentNmbr']) echo 'checked'; ?>
										onClick="document.form1.subjectid__.value='STAFF';document.form1.subtask__.value='refresh_teaching_assignment';document.form1.submit();"
		          			/>
		          		</td>
		          		<td><?php echo $assignments[$i]['LastName'] . ' ' . $assignments[$i]['FirstName'] . ' (' . $assignments[$i]['ChineseName'] . ')'; ?></td>
		          		<td><?php echo $assignments[$i]['ClassName_E'] . ' (' . $assignments[$i]['ClassName_C'] . ')'; ?></td>
								</tr>
<?php
		}
	}
?>
		          	<tr>
		          		<td>&nbsp;</td>
		          		<td>&nbsp;</td>
		          		<td>&nbsp;</td>
								</tr>
		          </table>
		        </td>
		      </tr>
        	<tr height="50">
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
 * @name 		AdminTemplate_Staff_ViewReport
 * @args 		0
 * @return	website template
 * @desc		
 *
 **/
function AdminTemplate_Staff_ViewReport($pTarget) {
	switch ($pTarget) {
		case "regist":
			break;
		case "under_construction":
?>
	<table border="0" width="500" align="center" cellspacing="0" cellpadding="0">
		<tr height="300"> 
			<td align="center">
				<b>
Under Construction ...... </b>
		  </td>
		</tr>
	</table>
	<table border="0" width="500" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td align="right">
				<input type="button" name="Submit" value="Back to management page" style="width: 180px;font-size: 12px;"
				onClick="document.form1.subjectid__.value='CANCELSUBTASK';document.form1.subtask__.value='';document.form1.submit();" />
		  </td>
		</tr>
	</table>
<?php
			break;
		default:
	}
}


?>

