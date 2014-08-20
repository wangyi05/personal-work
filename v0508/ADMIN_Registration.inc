<?php

/**
 *
 *
 * @version $Id$
 * @copyright 2005
 **/

/**
 *
 * @name 		AdminTemplate_StudentInfo
 * @args 		none
 * @return	template
 * @desc		
 *
 **/
function AdminTemplate_StudentInfo($pTarget)
{
	switch ($pTarget) {
		case "familyinfo":
			GetRegistration_StudentInfo(1, 'management');
?>
	<p/>
	<table border="0" width="550" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td align="right">
				<input type="button" name="Submit" value="Back to management page" style="width: 180px;font-size: 12px;"
				onClick="document.form1.subjectid__.value='REG';document.form1.subtask__.value='cancel_add_family';document.form1.submit();" />
				<input type="button" name="Submit" value="Submit" style="width: 100px;font-size: 12px;"
				onClick="document.form1.subjectid__.value='REG';document.form1.subtask__.value='submit_add_family';if (CheckStudentInfo()){document.form1.submit();}" />
		  </td>
		</tr>
	</table>
<?php
			break;
		case "familylist":
			AdminTemplate_FamilyList('student_info');
?>
	<table border="0" width="500" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td align="right">
				<input type="button" name="Submit" value="Back to management page" style="width: 180px;font-size: 12px;"
				onClick="document.form1.subjectid__.value='CANCELSUBTASK';document.form1.subtask__.value='';document.form1.submit();" />
				<input type="button" name="Submit" value="Edit" style="width: 100px;font-size: 12px;"
				onClick="document.form1.subjectid__.value='REG';document.form1.subtask__.value='edit_family';document.form1.submit();" />
				<input type="button" name="Submit" value="Create New" style="width: 100px;font-size: 12px;"
				onClick="document.form1.subjectid__.value='REG';document.form1.subtask__.value='add_family';document.form1.submit();" />
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
 * @name 		AdminTemplate_FamilyList
 * @args 		none
 * @return	template
 * @desc		
 *
 **/
function AdminTemplate_FamilyList($pTarget) {
	$ref_lib = new RefLibrary();
  $families = $ref_lib->GetRefValues('SCHL_Family');
	$account_handler = new StudentAccountHandler();
	if (isset($_POST['SearchType__'])) {
    switch ($_POST['SearchType__']) {
      case "Telephone":
        $telephonenmbr = '';
        if (isset($_POST['SearchTerm__'])) $telephonenmbr = trim($_POST['SearchTerm__']);
        $selectedfamilies = $ref_lib->GetRefValues('SCHL_Family', 'HomeTelephone', $telephonenmbr);
        $family_nmbrs = array();
        for ($i = 0; $i < sizeof($selectedfamilies); $i++) array_push($family_nmbrs, $selectedfamilies[$i]['FamilyNmbr']);
        $family_filter = array_unique($family_nmbrs);
        break;
      case "PersonName":
        $telephonenmbr = '';
        if (isset($_POST['SearchTerm__'])) {
          $nameparts = explode(',', $_POST['SearchTerm__']);
          $lastname = trim($nameparts[0]);
          $firstname = '';
          if (isset($nameparts[1]) && trim($nameparts[1]) != '') $firstname = trim($nameparts[1]);
        }
        if ($firstname != '') {
          $familymembers = $ref_lib->GetRefValues('SCHL_FamilyMember', 'LastName', $lastname, 'FirstName', $firstname);
        }
        else {
          $familymembers = $ref_lib->GetRefValues('SCHL_FamilyMember', 'LastName', $lastname);
        }
        $familymember_nmbrs = array();
        for ($i = 0; $i < sizeof($familymembers); $i++) array_push($familymember_nmbrs, $familymembers[$i]['FamilyNmbr']);
        $family_filter = array_unique($familymember_nmbrs);
        break;
      default:
        $family_nmbrs = array();
        $selectedfamilies = $ref_lib->GetRefValues('SCHL_Family');
        for ($i = 0; $i < sizeof($selectedfamilies); $i++) array_push($family_nmbrs, $selectedfamilies[$i]['FamilyNmbr']);
        $family_filter = array_unique($family_nmbrs);
    }
  }
  else {
    $family_nmbrs = array();
    $selectedfamilies = $ref_lib->GetRefValues('SCHL_Family');
    for ($i = 0; $i < sizeof($selectedfamilies); $i++) array_push($family_nmbrs, $selectedfamilies[$i]['FamilyNmbr']);
    $family_filter = array_unique($family_nmbrs);
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
							<font size="3" color="darkred"><b>FCD School Class Registration</b></font><br/>
						</td>
					</tr>
					<tr>
						<td>&nbsp;</td>
					</tr>
					<tr height="50" valign="center">
						<td align="center" style="font-size: 16px;font-weight: bold;color: darkgreen;">
              Registered Families
              <?php if ($pTarget == 'print_admission') echo "<br/><div style=\"font-size: 10px;\">(Only families with CLOSED registration status are displayed here)<br/>"; ?>
            </td>
					</tr>
<?php 
  if ($pTarget != 'print_admission') {
?>
					<tr>
						<td height="60" valign="bottom">
              Search Criteria:
							<select name="SearchType__" size="1" style="width: 150px;">
								<option value="All" <?php if (getSession('SearchType', 0) == 'All') echo 'selected'; ?>>Display All</option>
								<option value="PersonName" <?php if (getSession('SearchType', 0) == 'PersonName') echo 'selected'; ?>>Person Name</option>
								<option value="Telephone" <?php if (getSession('SearchType', 0) == 'Telephone') echo 'selected'; ?>>Telephone Number</option>
							</select>
              <br/>
              Search Term:  &nbsp;&nbsp;
              <input type="text" name="SearchTerm__" value="" style="width: 270px;" />
              &nbsp;
							<input type="button" name="Submit" value="Search" style="width: 100px;font-size: 12px;"
							onClick="if(document.form1.SearchType__.value!='All'&&document.form1.SearchTerm__.value==''){alert('search term?');return false;}else{document.form1.subjectid__.value='REG';document.form1.subtask__.value='list_family';document.form1.submit();}" />
              <br/>
              (for name search, enter last name OR last name, first name)
            </td>
					</tr>
<?php 
  }
?>
					<tr align="center">
						<td class="contentfont">
		          <table border="1" class="thinborder" style="font-size: 12px;">
		          	<tr bgcolor="#C1E8BE">
		          		<td width="60">&nbsp;</td>
		          		<td width="120" align="center">Family ID</td>
		          		<td width="320" align="center">Parent</td>
								</tr>
<?php
  if ($pTarget == 'print_admission') $tuition_hdlr = new TuitionFeeHandler();
	if (isset($families[0])) {
    for ($i = 0; $i < sizeof($families); $i++) {
		  $display = false;
			$parent = $account_handler->GetParentInfo($families[$i]['FamilyNmbr']);
      if ($pTarget == 'print_admission') {
        $reg_status = $tuition_hdlr->GetStatus($families[$i]['FamilyNmbr']);
        if ($reg_status[0]['Status'] == 'CLOSED') $display = true;
      }
      else {
        $display = true;
      }
      if ($display) {
        if (in_array($families[$i]['FamilyNmbr'], $family_filter)) {
          if ($pTarget == 'print_admission') {
?>
		          	<tr>
		          		<td align="center">
		          			<input type="checkbox" name="FamilyNmbr[]" value="<?php echo $families[$i]['FamilyNmbr']; ?>"
                    onClick="document.form1.subjectid__.value='REG';document.form1.subtask__.value='refresh_print_admission';document.form1.submit();"
                    <?php if (isset($_SESSION['FamilyNmbr'][0]) && in_array($families[$i]['FamilyNmbr'], $_SESSION['FamilyNmbr'])) echo " checked"; ?>
                    />
		          		</td>
		          		<td align="center"><?php echo $families[$i]['FamilyID']; ?></td>
		          		<td>&nbsp;<?php echo $parent; ?></td>
								</tr>
<?php
          }
          else {
?>
		          	<tr>
		          		<td align="center">
		          			<input type="radio" name="FamilyNmbr__" value="<?php echo $families[$i]['FamilyNmbr']; ?>" />
		          		</td>
		          		<td align="center"><?php echo $families[$i]['FamilyID']; ?></td>
		          		<td>&nbsp;<?php echo $parent; ?></td>
								</tr>
<?php
          }
        }
      }
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
	<script type="text/javascript">
<?php 
  if ($pTarget == 'print_admission') {
?>
		function CheckFamilyList() { 
			if (CheckCheckboxArray('FamilyNmbr[]')) {
				return true;
			}
			else {
				alert('You need to select a family.');
				return false;
			}
		}
<?php 
  }
  else {
?>
		function CheckFamilyList() { 
			if (CheckRadioCheckbox(document.form1.FamilyNmbr__)) {
				return true;
			}
			else {
				alert('You need to select a family.');
				return false;
			}
		}
<?php 
  }
?>
	</script>
<?php
}

/**
 *
 * @name 		AdminTemplate_Registration
 * @args 		0
 * @return	website template
 * @desc		
 *
 **/
function AdminTemplate_Registration($pTarget) {
	switch ($pTarget) {
		case "regist":
			$ref_lib = new RefLibrary();
			$school_years = $ref_lib->GetSchoolYear('all');
			$classes = $ref_lib->GetRefValues('SCHL_Class');
			$student_handler = new StudentAccountHandler();
			$students = $student_handler->GetStudentInfo(getSession('FamilyNmbr', 0));
			$reg_handler = new RegistrationHandler();
			if (getSession('SchoolYear', 0) != '') {
				$registrations = $reg_handler->GetRegistration(getSession('SchoolYear', 0), '', '', getSession('FamilyNmbr', 0), '');
			}
			if (sizeof($students) > 0 && isset($students[0]['FamilyMemberNmbr'])) {
				if (getSession('RegistrationNmbr', 0) != '') {
					$selected_reg = $reg_handler->GetRegistration('', '', '', '', getSession('RegistrationNmbr', 0));
					setSession('SchoolYear__', $selected_reg[0]['SchoolYear']);
					$selected_family_member = $selected_reg[0]['FamilyMemberNmbr'];
					$selected_class = $selected_reg[0]['ClassNmbr'];
					// reg_date and reg_method
					$tuition_handler = new TuitionFeeHandler();
					$dues = $tuition_handler->GetTuitionDue(getSession('SchoolYear', 0), getSession('FamilyNmbr', 0));
					$selected_reg_date = $dues[0]['RegistrationDate'];
					$selected_reg_method = $dues[0]['RegistrationMethod'];
				}
				else {
					$selected_family_member = '';
					$selected_class = '';
					$selected_reg_date = '';
					$selected_reg_method = '';
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
							<font size="3" color="darkred"><b>FCD School Class Registration</b></font><br/>
						</td>
					</tr>
					<tr>
						<td>&nbsp;</td>
					</tr>
					<tr height="60" valign="center">
						<td width="500" align="left" style="font-size: 14px;font-weight: bold;color: darkgreen;">
		          <table border="0" style="font-size: 12px;">
		          	<tr>
		          		<td width="160" align="right">School Year:</td>
		          		<td width="20" align="center">&nbsp;</td>
		          		<td width="320" align="left">
										<select name="SchoolYear__" size="1" style="width: 100px;"
										onChange="document.form1.subjectid__.value='REG';document.form1.subtask__.value='refresh_reg';document.form1.submit();"
										>
											<option value=""></option>
											<?php
											for ($i = 0; $i < sizeof($school_years); $i++) {
												echo "<option value=\"" . $school_years[$i]['SchoolYear'] . "\" " . checkSelectedOption("SchoolYear", $school_years[$i]['SchoolYear']) . ">" . $school_years[$i]['SchoolYear']  . "</option>\n";
											}
											?>
										</select>
		          		</td>
								</tr>
		          	<tr>
		          		<td align="right">Registration Date:</td>
		          		<td align="center">&nbsp;</td>
		          		<td align="left">
										<input type="text" name="RegDate__" value="<?php echo $selected_reg_date; ?>" style="width: 100px;" />  (yyyy-mm-dd)
		          		</td>
								</tr>
		          	<tr>
		          		<td align="right">Student Registration Method:</td>
		          		<td align="center">&nbsp;</td>
		          		<td align="left">
										<select name="RegMethod__" size="1" style="width: 100px;">
											<option value=""></option>
											<option value="PAPER" <?php if ($selected_reg_method == 'PAPER') echo 'selected'; ?>>Paper</option>
											<option value="WEB" <?php if ($selected_reg_method == 'WEB') echo 'selected'; ?>>Web</option>
										</select>
		          		</td>
								</tr>
							</table>
						</td>
					</tr>
					<tr height="40" valign="bottom">
						<td style="font-size: 14px;color: darkgreen;">
							Select a student, then select a course to complete registration.  Repeat if necessary.<br/>
						</td>
					</tr>
					<tr align="center">
						<td class="contentfont">
		          <table border="1" bgcolor="#C1E8BE" class="thinborder" style="font-size: 12px;">
		          	<tr>
		          		<td width="200" align="center">Student</td>
		          		<td width="300" align="center">Class</td>
								</tr>
		          	<tr>
		          		<td>
										<select name="FamilyMemberNmbr__" size="10" style="width: 200px;">
											<?php
											for ($i = 0; $i < sizeof($students); $i++) {
												if ((isset($students[$i]['LastName']) && trim($students[$i]['LastName']) != '')
                        || (isset($students[$i]['ChineseName']) && trim($students[$i]['ChineseName']) != '')
                        ) {
											?>
												<option value="<?php echo $students[$i]['FamilyMemberNmbr']; ?>" <?php if ($selected_family_member == $students[$i]['FamilyMemberNmbr']) echo ' selected'; ?>><?php echo $students[$i]['LastName'] . " " . $students[$i]['FirstName'] . " (" . $students[$i]['ChineseName'] . ")"; ?></option>
											<?php
												}
											}
											?>
										</select>
		          		</td>
		          		<td>
										<select name="ClassNmbr__" size="10" style="width: 300px;">
											<?php
											for ($i = 0; $i < sizeof($classes); $i++) {
											?>
												<option value="<?php echo $classes[$i]['ClassNmbr']; ?>" <?php if ($selected_class == $classes[$i]['ClassNmbr']) echo ' selected'; ?>><?php echo $classes[$i]['ClassName_E'] . " (" . $classes[$i]['ClassName_C'] . ")"; ?></option>
											<?php
											}
											?>
										</select>
		          		</td>
								</tr>
		          </table>
		        </td>
		      </tr>
					<tr height="50" valign="center">
						<td align="right">
							<input type="button" name="Submit" value="Cancel" style="width: 100px;font-size: 12px;"
							onClick="document.form1.subjectid__.value='REG';document.form1.subtask__.value='cancel_registration';document.form1.submit();" />
							<input type="button" name="Submit" value="Delete" style="width: 100px;font-size: 12px;"
							onClick="if(CheckRegistrationAdminDelete()){document.form1.subjectid__.value='REG';document.form1.subtask__.value='delete_registration';document.form1.submit();}" />
							<input type="button" name="Submit" value="Submit" style="width: 100px;font-size: 12px;"
							onClick="if(CheckRegistrationAdmin()){document.form1.subjectid__.value='REG';document.form1.subtask__.value='add_registration';document.form1.submit();}" />
					  </td>
					</tr>
					<tr height="50" valign="bottom">
						<td align="center" style="font-size: 16px;font-weight: bold;color: darkgreen;">Current Class Registration</td>
					</tr>
					<tr align="center">
						<td class="contentfont">
		          <table border="1" class="thinborder" style="font-size: 12px;">
		          	<tr bgcolor="#C1E8BE">
		          		<td width="50" align="center">&nbsp;</td>
		          		<td width="150" align="center">Student</td>
		          		<td width="300" align="center">Class</td>
								</tr>
<?php
			if (isset($registrations[0])) {
				for ($i = 0; $i < sizeof($registrations); $i++) {
					if (isset($registrations[$i]['LastName'])
          || isset($registrations[$i]['ChineseName'])
          ) {
?>
		          	<tr>
		          		<td>
		          			<input type="radio" name="RegistrationNmbr__" value="<?php echo $registrations[$i]['RegistrationNmbr']; ?>" <?php if (getSession('RegistrationNmbr', 0) == $registrations[$i]['RegistrationNmbr']) echo 'checked'; ?> 
										onClick="document.form1.subjectid__.value='REG';document.form1.subtask__.value='refresh_reg';document.form1.submit();"
		          			/>
		          		</td>
		          		<td><?php echo $registrations[$i]['LastName'] . " " . $registrations[$i]['FirstName'] . " (" . $registrations[$i]['ChineseName'] . ")"; ?></td>
		          		<td><?php echo $registrations[$i]['ClassName_E'] . " (" . $registrations[$i]['ClassName_C'] . ")"; ?></td>
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
 
			else {
?>
	<table border="0" width="500" align="center" cellspacing="0" cellpadding="0">
		<tr height="100"> 
			<td align="center">
				<b>No student has been entered for this family.</b>
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
			}
			break;
		case "familylist":
			AdminTemplate_FamilyList('regist');
?>
	<table border="0" width="500" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td align="right">
				<input type="button" name="Submit" value="Back to management page" style="width: 180px;font-size: 12px;"
				onClick="document.form1.subjectid__.value='CANCELSUBTASK';document.form1.subtask__.value='';document.form1.submit();" />
				<input type="button" name="Submit" value="Next" style="width: 100px;font-size: 12px;"
				onClick="if (CheckFamilyList()){document.form1.subjectid__.value='REG';document.form1.subtask__.value='goto_registration';document.form1.submit();}" />
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
 * @name 		AdminTemplate_Registration_ViewReport
 * @args 		0
 * @return	website template
 * @desc		
 *
 **/
function AdminTemplate_Registration_ViewReport($pTarget) {
	switch ($pTarget) {
		case "regist":
			break;
		case "by_class":
			$ref_lib = new RefLibrary();
			$school_years = $ref_lib->GetSchoolYear('all');
	    $curriculum_handler = new CurriculumHandler();
	    $classes = $curriculum_handler->GetClass();
?>
	<table border="0" width="500" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td>&nbsp;</td>
		</tr>
		<tr>
			<td align="center">
				<font size="3" color="darkred"><b>FCD School Class Registration</b></font><br/>
			</td>
		</tr>
		<tr>
			<td>&nbsp;</td>
		</tr>
<?php 
      if (getSession('LoginRole', 0) == 'Teacher') {
        setSession('ReportType__', 'by_class');
      }
      else {
?>
		<tr height="60" valign="center">
			<td align="left" style="font-size: 14px;font-weight: bold;color: darkgreen;">
		    <table border="0" width="400" style="font-size: 12px;">
		      <tr height="50">
		        <td width="400" align="left" valign="top">
							<input type="radio" name="ReportType__" value="by_class" <?php if (getSession('ReportType', 0) == 'by_class') echo 'checked'; ?>
							onClick="document.form1.subjectid__.value='REG';document.form1.subtask__.value='refresh_report';document.form1.submit();"
              >
              &nbsp;&nbsp;
              Display report by class
              <br/>
              <input type="radio" name="ReportType__" value="all" <?php if (getSession('ReportType', 0) == 'all') echo 'checked'; ?>
							onClick="document.form1.subjectid__.value='REG';document.form1.subtask__.value='refresh_report';document.form1.submit();"
							>
              &nbsp;&nbsp;
              Display report of all students
		        </td>
					</tr>
        </table>
		  </td>
		</tr>
		<tr>
			<td><hr/></td>
		</tr>
<?php 
      }
      if (getSession('ReportType', 0) != '') {
?>
		<tr height="60" valign="center">
			<td align="left" style="font-size: 14px;font-weight: bold;color: darkgreen;">
		    <table border="0" width="400" style="font-size: 12px;">
		      <tr height="100">
		        <td width="80" align="left" valign="top">School Year:</td>
		        <td width="320" align="left" valign="top">
							<select name="SchoolYear[]" size="4" multiple style="width: 150px;"
							onChange="document.form1.subjectid__.value='REG';document.form1.subtask__.value='refresh_report';document.form1.submit();"
							>
								<?php
								for ($i = 0; $i < sizeof($school_years); $i++) {
									echo "<option value=\"" . $school_years[$i]['SchoolYear'] . "\" " . checkSelectedOption("SchoolYear", $school_years[$i]['SchoolYear']) . ">" . $school_years[$i]['SchoolYear']  . "</option>\n";
								}
								?>
							</select>
		        </td>
					</tr>
        </table>
		  </td>
		</tr>
		<tr height="60" valign="center">
			<td align="left" style="font-size: 14px;font-weight: bold;color: darkgreen;">
<?php
        if (getSession('ReportType', 0) == 'by_class') {
          for ($j = 0; $j < sizeof($classes); $j++) {
?>
		    <table border="1" width="400" style="font-size: 12px;">
		      <tr>
		        <td width="50" align="center">
		          <input type="radio" name="ClassNmbr__" value="<?php echo $classes[$j]['ClassNmbr']; ?>" <?php if (getSession('ClassNmbr', 0) == $classes[$j]['ClassNmbr']) echo 'checked'; ?> 
							onClick="document.form1.subjectid__.value='REG';document.form1.subtask__.value='refresh_report';document.form1.submit();"
		          />
		        </td>
		        <td width="350">&nbsp;<?php echo $classes[$j]['ClassName_E'] . " (" . $classes[$j]['ClassName_C'] . ")"; ?></td>
					</tr>
        </table>
<?php
          }
        }
        else {
          setSession('DisplayOptions', 'FamilyID');
?>
		    Select display options:
				<input type="button" name="Submit" value="Select all" style="width: 100px;font-size: 11px;"
				onClick="
			    for (i = 0; i < document.form1['DisplayOptions[]'].length; i++) {
				    document.form1['DisplayOptions[]'][i].checked = true;
			    }
          "
        />
        <br/>
        <table border="1" width="400" style="font-size: 12px;">
		      <tr>
			      <td width="330" align="center">Display Options</td>
			      <td width="70" align="center">Sort List By</td>
					</tr>
		      <tr>
			      <td>
	            <input type="checkbox" name="DisplayOptions[]" value="FamilyID" <?php if (in_array('FamilyID', $_SESSION['DisplayOptions'])) echo 'checked'; ?>
							onClick="document.form1.subjectid__.value='REG';document.form1.subtask__.value='refresh_report';document.form1.submit();" 
              />
              &nbsp;&nbsp;
              Family ID (家庭代码)<br/>
		        </td>
			      <td align="center">
	            <input type="radio" name="SortBy__" value="FamilyID" <?php if (getSession('SortBy', 0) == 'FamilyID') echo 'checked'; ?>
              onClick="document.form1.subjectid__.value='REG';document.form1.subtask__.value='refresh_report';document.form1.submit();"
		          />
		        </td>
					</tr>
		      <tr>
			      <td>
	            <input type="checkbox" name="DisplayOptions[]" value="StudentName" <?php if (in_array('StudentName', $_SESSION['DisplayOptions'])) echo 'checked'; ?>
							onClick="document.form1.subjectid__.value='REG';document.form1.subtask__.value='refresh_report';document.form1.submit();"
		          />
              &nbsp;&nbsp;
              Student Name (学生姓名)<br/>
		        </td>
			      <td align="center">&nbsp;</td>
					</tr>
		      <tr>
			      <td>
	            <input type="checkbox" name="DisplayOptions[]" value="StudentGender" <?php if (in_array('StudentGender', $_SESSION['DisplayOptions'])) echo 'checked'; ?>
							onClick="document.form1.subjectid__.value='REG';document.form1.subtask__.value='refresh_report';document.form1.submit();"
		          />
              &nbsp;&nbsp;
              Gender (学生性别)<br/>
		        </td>
			      <td align="center">
	            <input type="radio" name="SortBy__" value="StudentGender" <?php if (getSession('SortBy', 0) == 'StudentGender') echo 'checked'; ?>
							onClick="document.form1.subjectid__.value='REG';document.form1.subtask__.value='refresh_report';document.form1.submit();"
		          />
		        </td>
					</tr>
		      <tr>
			      <td>
	            <input type="checkbox" name="DisplayOptions[]" value="SchoolYear" <?php if (in_array('SchoolYear', $_SESSION['DisplayOptions'])) echo 'checked'; ?>
							onClick="document.form1.subjectid__.value='REG';document.form1.subtask__.value='refresh_report';document.form1.submit();"
		          />
              &nbsp;&nbsp;
              Semester (学期)<br/>
		        </td>
			      <td align="center">&nbsp;</td>
					</tr>
		      <tr>
			      <td>
	            <input type="checkbox" name="DisplayOptions[]" value="CourseName" <?php if (in_array('CourseName', $_SESSION['DisplayOptions'])) echo 'checked'; ?>
							onClick="document.form1.subjectid__.value='REG';document.form1.subtask__.value='refresh_report';document.form1.submit();"
		          />
              &nbsp;&nbsp;
              Registered Class (注册课程)<br/>
		        </td>
			      <td align="center">
	            <input type="radio" name="SortBy__" value="CourseName" <?php if (getSession('SortBy', 0) == 'CourseName') echo 'checked'; ?>
							onClick="document.form1.subjectid__.value='REG';document.form1.subtask__.value='refresh_report';document.form1.submit();"
		          />
		        </td>
					</tr>
		      <tr>
			      <td>
	            <input type="checkbox" name="DisplayOptions[]" value="CourseLevel" <?php if (in_array('CourseLevel', $_SESSION['DisplayOptions'])) echo 'checked'; ?>
							onClick="document.form1.subjectid__.value='REG';document.form1.subtask__.value='refresh_report';document.form1.submit();"
		          />
              &nbsp;&nbsp;
              Course Level (年级)<br/>
		        </td>
			      <td align="center">
	            <input type="radio" name="SortBy__" value="CourseLevel" <?php if (getSession('SortBy', 0) == 'CourseLevel') echo 'checked'; ?>
							onClick="document.form1.subjectid__.value='REG';document.form1.subtask__.value='refresh_report';document.form1.submit();"
		          />
		        </td>
					</tr>
		      <tr>
			      <td>
	            <input type="checkbox" name="DisplayOptions[]" value="Teacher" <?php if (in_array('Teacher', $_SESSION['DisplayOptions'])) echo 'checked'; ?>
							onClick="document.form1.subjectid__.value='REG';document.form1.subtask__.value='refresh_report';document.form1.submit();"
		          />
              &nbsp;&nbsp;
              Teacher (任课教师)<br/>
		        </td>
			      <td align="center">
	            <input type="radio" name="SortBy__" value="Teacher" <?php if (getSession('SortBy', 0) == 'Teacher') echo 'checked'; ?>
							onClick="document.form1.subjectid__.value='REG';document.form1.subtask__.value='refresh_report';document.form1.submit();"
		          />
		        </td>
					</tr>
		      <tr>
			      <td>
	            <input type="checkbox" name="DisplayOptions[]" value="ContactInfo" <?php if (in_array('ContactInfo', $_SESSION['DisplayOptions'])) echo 'checked'; ?>
							onClick="document.form1.subjectid__.value='REG';document.form1.subtask__.value='refresh_report';document.form1.submit();"
		          />
              &nbsp;&nbsp;
              Student Contact Info (学生联系地址, 含电话, EMAIL)<br/>
		        </td>
			      <td align="center">&nbsp;</td>
					</tr>
		      <tr>
			      <td>
	            <input type="checkbox" name="DisplayOptions[]" value="ClassTuitionFees" <?php if (in_array('ClassTuitionFees', $_SESSION['DisplayOptions'])) echo 'checked'; ?>
							onClick="document.form1.subjectid__.value='REG';document.form1.subtask__.value='refresh_report';document.form1.submit();"
		          />
              &nbsp;&nbsp;
              Class Tuition and Fees (课程学杂费)<br/>
		        </td>
			      <td align="center">&nbsp;</td>
					</tr>
		      <tr>
			      <td>
	            <input type="checkbox" name="DisplayOptions[]" value="TuitionFeeStatus" <?php if (in_array('TuitionFeeStatus', $_SESSION['DisplayOptions'])) echo 'checked'; ?>
							onClick="document.form1.subjectid__.value='REG';document.form1.subtask__.value='refresh_report';document.form1.submit();"
		          />
              &nbsp;&nbsp;
              Tuition and Fees Status (学杂费总计与交纳状况)<br/>
		        </td>
			      <td align="center">&nbsp;</td>
					</tr>
        </table>
<?php
        }
?>
		  </td>
		</tr>
	</table>
	<table border="0" width="500" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td height="60" align="right" valign="bottom">
				<input type="button" name="Submit" value="Back to management page" style="width: 180px;font-size: 12px;"
				onClick="document.form1.subjectid__.value='CANCELSUBTASK';document.form1.subtask__.value='';document.form1.submit();" />
				<input type="button" name="Submit" value="Display Report" style="width: 100px;font-size: 12px;"
				onClick="
        if (document.form1['SchoolYear[]'].selectedIndex < 0) {
          alert('School Year is missing'); return false;
        }
        if (document.form1.SortBy__) {
          if (GetCheckRadioCheckboxValue(document.form1.SortBy__) != 'FamilyID') {
			      for (i = 0; i < document.form1['DisplayOptions[]'].length; i++) {
				      if (document.form1['DisplayOptions[]'][i].checked) {
                if (document.form1['DisplayOptions[]'][i].value == 'ClassTuitionFees' || document.form1['DisplayOptions[]'][i].value == 'TuitionFeeStatus') {
                    alert('To display tuition, fees, or payment status, the list can only be sorted by FamilyID');
                    return false;
                }
              }
			      }
          }
        }
        else {
          if (!CheckRadioCheckbox(document.form1.ClassNmbr__)) {
            alert('You need to select a class.'); return false;
          }
        }
        window.open('ADMIN_Report.php', 'fcd', 'width=700,height=800,left=0,top=0,scrollbars=1,resizable=1,status=1,toolbar=1,location=0,menubar=1;directories=0');
        "
        />
		  </td>
		</tr>
	</table>
<?php
      }
      else {
?>
	<table border="0" width="500" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td height="60" align="right" valign="bottom">
				<input type="button" name="Submit" value="Back to management page" style="width: 180px;font-size: 12px;"
				onClick="document.form1.subjectid__.value='CANCELSUBTASK';document.form1.subtask__.value='';document.form1.submit();" />
		  </td>
		</tr>
	</table>
<?php
      }
			break;
		default:
	}
}

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
		case "familylist":
			AdminTemplate_FamilyList('print_admission');
?>
	<table border="0" width="500" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td align="right">
				<input type="button" name="Submit" value="Back to management page" style="width: 180px;font-size: 12px;"
				onClick="document.form1.subjectid__.value='CANCELSUBTASK';document.form1.subtask__.value='';document.form1.submit();" />
				<input type="button" name="Submit" value="Display Letter" style="width: 100px;font-size: 12px;"
				onClick="if (CheckFamilyList()){window.open('FCD_Print.php?fn=<?php foreach($_SESSION['FamilyNmbr'] as $v) echo $v . '-'; ?>', 'fcd', 'width=700,height=800,left=0,top=0,scrollbars=1,resizable=1,status=1,toolbar=1,location=0,menubar=1;directories=0');}"
        />
		  </td>
		</tr>
	</table>
<?php
			break;
		default:
	}
}


?>