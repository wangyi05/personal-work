<?php

/**
 *
 *
 * @version $Id$
 * @copyright 2005
 **/

/**
 *
 * @name 		AdminTemplate_SchoolYear
 * @args 		0
 * @return	website template
 * @desc		
 *
 **/
function AdminTemplate_SchoolYear() {
	$ref_lib = new RefLibrary();
	$school_years = $ref_lib->GetSchoolYear('all');
	if (getSession('SchoolYear', 0) != '') {
		$selected_schoolyear_info = $ref_lib->GetRefValues('REF_SchoolYear', 'SchoolYear', getSession('SchoolYear', 0));
		$selected_schoolyear = $selected_schoolyear_info[0]['SchoolYear'];
		$selected_semester = $selected_schoolyear_info[0]['Semester'];
		$selected_group = $selected_schoolyear_info[0]['SemesterGroup'];
		$selected_display_order = $selected_schoolyear_info[0]['DisplayOrder'];
	}
	else {
		$selected_schoolyear = '';
		$selected_semester = '';
		$selected_group = '';
		$selected_display_order = '';
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
							<font size="3" color="darkred"><b>FCD School Year</b></font><br/>
						</td>
					</tr>
					<tr height="50">
						<td>&nbsp;</td>
					</tr>
					<tr align="center">
						<td class="contentfont">
		          <table border="0" bgcolor="#C1E8BE" class="thinborder" style="font-size: 12px;">
		          	<tr>
		          		<td width="200" align="right">School Year</td>
		          		<td width="20">&nbsp;</td>
		          		<td width="280" align="left">
										<input type="text" name="NewSchoolYear__" value="<?php echo $selected_schoolyear; ?>" style="width: 250px;" />
		          		</td>
								</tr>
		          	<tr>
		          		<td width="200" align="right">Semester</td>
		          		<td width="20">&nbsp;</td>
		          		<td width="280" align="left">
										<input type="text" name="Semester__" value="<?php echo $selected_semester; ?>" style="width: 250px;" />
		          		</td>
								</tr>
		          	<tr>
		          		<td width="200" align="right">Group (e.g., 2006 Fall, 2007 Spring, 2006-2007 belong to the same group)</td>
		          		<td width="20">&nbsp;</td>
		          		<td width="280" align="left">
										<input type="text" name="SemesterGroup__" value="<?php echo $selected_group; ?>" style="width: 250px;" />
		          		</td>
								</tr>
		          	<tr>
		          		<td width="200" align="right">Display Order</td>
		          		<td width="20">&nbsp;</td>
		          		<td width="280" align="left">
										<input type="text" name="DisplayOrder__" value="<?php echo $selected_display_order; ?>" style="width: 250px;" />
		          		</td>
								</tr>
		          </table>
		        </td>
		      </tr>
					<tr height="50" valign="center">
						<td align="right">
							<input type="button" name="Submit" value="Back to management page" style="width: 180px;font-size: 12px;"
							onClick="document.form1.subjectid__.value='CANCELSUBTASK';document.form1.subtask__.value='';document.form1.submit();" />
							<input type="button" name="Submit" value="Delete" style="width: 100px;font-size: 12px;"
							onClick="document.form1.subjectid__.value='ADMINISTRATIVE';document.form1.subtask__.value='delete_schoolyear';document.form1.submit();" />
							<input type="button" name="Submit" value="Submit" style="width: 100px;font-size: 12px;"
							onClick="document.form1.subjectid__.value='ADMINISTRATIVE';document.form1.subtask__.value='add_schoolyear';document.form1.submit();" />
					  </td>
					</tr>
					<tr>
						<td>&nbsp;</td>
					</tr>
					<tr align="center">
						<td class="contentfont">
		          <table border="1" class="thinborder" style="font-size: 12px;">
		          	<tr bgcolor="#C1E8BE">
		          		<td width="50" align="center">&nbsp;</td>
		          		<td width="200" align="center">School Year</td>
		          		<td width="60" align="center">Semester</td>
		          		<td width="110" align="center">Group</td>
		          		<td width="80" align="center">Display Order</td>
								</tr>
<?php
	if (isset($school_years[0])) {
		for ($i = 0; $i < sizeof($school_years); $i++) {
?>
		          	<tr>
		          		<td align="center">
		          			<input type="radio" name="SchoolYear__" value="<?php echo $school_years[$i]['SchoolYear']; ?>" <?php if (getSession('SchoolYear', 0) == $school_years[$i]['SchoolYear']) echo 'checked'; ?>
										onClick="document.form1.subjectid__.value='ADMINISTRATIVE';document.form1.subtask__.value='refresh_schoolyear';document.form1.submit();"
		          			/>
		          		</td>
		          		<td align="center"><?php echo $school_years[$i]['SchoolYear']; ?></td>
		          		<td align="center"><?php echo $school_years[$i]['Semester']; ?></td>
		          		<td align="center"><?php echo $school_years[$i]['SemesterGroup']; ?></td>
		          		<td align="center"><?php echo $school_years[$i]['DisplayOrder']; ?></td>
								</tr>
<?php
		}
	}
?>
		          	<tr>
		          		<td>&nbsp;</td>
		          		<td>&nbsp;</td>
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
 * @name 		AdminTemplate_Role
 * @args 		0
 * @return	website template
 * @desc		
 *
 **/
function AdminTemplate_Role()
{
	$ref_lib = new RefLibrary();
	$roles = $ref_lib->GetRefValues('REF_FcdRole');
	if (getSession('FcdRoleNmbr', 0) != '') {
		$selected_role = $ref_lib->GetRefValues('REF_FcdRole', 'FcdRoleNmbr', getSession('FcdRoleNmbr', 0));
		$selected_role_e = $selected_role[0]['FcdRole_E'];
		$selected_role_c = $selected_role[0]['FcdRole_C'];
	}
	else {
		$selected_role_e = '';
		$selected_role_c = '';
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
							<font size="3" color="darkred"><b>FCD School Roles</b></font><br/>
						</td>
					</tr>
					<tr>
						<td>&nbsp;</td>
					</tr>
					<tr align="center">
						<td class="contentfont">
		          <table border="0" bgcolor="#C1E8BE" class="thinborder" style="font-size: 12px;">
		          	<tr>
		          		<td width="200" align="right">Role (English)</td>
		          		<td width="20">&nbsp;</td>
		          		<td width="280" align="left">
										<input type="text" name="FcdRole_E__" value="<?php echo $selected_role_e; ?>" style="width: 250px;" />
		          		</td>
								</tr>
		          	<tr>
		          		<td width="200" align="right">Role (Chinese)</td>
		          		<td width="20">&nbsp;</td>
		          		<td width="280" align="left">
										<input type="text" name="FcdRole_C__" value="<?php echo $selected_role_c; ?>" style="width: 250px;" />
		          		</td>
								</tr>
		          </table>
		        </td>
		      </tr>
					<tr height="50" valign="center">
						<td align="right">
							<input type="button" name="Submit" value="Back to management page" style="width: 180px;font-size: 12px;"
							onClick="document.form1.subjectid__.value='CANCELSUBTASK';document.form1.subtask__.value='';document.form1.submit();" />
							<input type="button" name="Submit" value="Delete" style="width: 100px;font-size: 12px;"
							onClick="document.form1.subjectid__.value='ADMINISTRATIVE';document.form1.subtask__.value='delete_role';document.form1.submit();" />
							<input type="button" name="Submit" value="Submit" style="width: 100px;font-size: 12px;"
							onClick="document.form1.subjectid__.value='ADMINISTRATIVE';document.form1.subtask__.value='add_role';document.form1.submit();" />
					  </td>
					</tr>
					<tr>
						<td>&nbsp;</td>
					</tr>
					<tr align="center">
						<td class="contentfont">
		          <table border="1" class="thinborder" style="font-size: 12px;">
		          	<tr bgcolor="#C1E8BE">
		          		<td width="50" align="center">&nbsp;</td>
		          		<td width="230" align="center">Role (English)</td>
		          		<td width="320" align="center">Role (Chinese)</td>
								</tr>
<?php
	if (isset($roles[0])) {
		for ($i = 0; $i < sizeof($roles); $i++) {
?>
		          	<tr>
		          		<td align="center">
		          			<input type="radio" name="FcdRoleNmbr__" value="<?php echo $roles[$i]['FcdRoleNmbr']; ?>" <?php if (getSession('FcdRoleNmbr', 0) == $roles[$i]['FcdRoleNmbr']) echo 'checked'; ?>
										onClick="document.form1.subjectid__.value='ADMINISTRATIVE';document.form1.subtask__.value='refresh_role';document.form1.submit();"
		          			/>
		          		</td>
		          		<td align="center"><?php echo $roles[$i]['FcdRole_E']; ?></td>
		          		<td align="center"><?php echo $roles[$i]['FcdRole_C']; ?></td>
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
        	<tr height="30">
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
 * @name 		AdminTemplate_CourseCategory
 * @args 		0
 * @return	website template
 * @desc		
 *
 **/
function AdminTemplate_CourseCategory()
{
	$ref_lib = new RefLibrary();
	$course_cats = $ref_lib->GetRefValues('REF_CourseCategory');
	if (getSession('CourseCategoryNmbr', 0) != '') {
		$selected_course_cat_info = $ref_lib->GetRefValues('REF_CourseCategory', 'CourseCategoryNmbr', getSession('CourseCategoryNmbr', 0));
		$selected_course_cat_e = $selected_course_cat_info[0]['CourseCategory_E'];
		$selected_course_cat_c = $selected_course_cat_info[0]['CourseCategory_C'];
		$selected_course_type = $selected_course_cat_info[0]['CourseType'];
	}
	else {
		$selected_course_cat_e = '';
		$selected_course_cat_c = '';
		$selected_course_type = '';
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
							<font size="3" color="darkred"><b>FCD School Course Category</b></font><br/>
						</td>
					</tr>
					<tr>
						<td>&nbsp;</td>
					</tr>
					<tr align="center">
						<td class="contentfont">
		          <table border="0" bgcolor="#C1E8BE" class="thinborder" style="font-size: 12px;">
		          	<tr>
		          		<td width="200" align="right">Course Category (English)</td>
		          		<td width="20">&nbsp;</td>
		          		<td width="280" align="left">
										<input type="text" name="CourseCategory_E__" value="<?php echo $selected_course_cat_e; ?>" style="width: 250px;" />
		          		</td>
								</tr>
		          	<tr>
		          		<td width="200" align="right">Course Category (Chinese)</td>
		          		<td width="20">&nbsp;</td>
		          		<td width="280" align="left">
										<input type="text" name="CourseCategory_C__" value="<?php echo $selected_course_cat_c; ?>" style="width: 250px;" />
		          		</td>
								</tr>
		          	<tr>
		          		<td width="200" align="right">Course Type</td>
		          		<td width="20">&nbsp;</td>
		          		<td width="280" align="left">
										<input type="text" name="CourseType__" value="<?php echo $selected_course_type; ?>" style="width: 250px;" />
		          		</td>
								</tr>
		          </table>
		        </td>
		      </tr>
					<tr height="50" valign="center">
						<td align="right">
							<input type="button" name="Submit" value="Back to management page" style="width: 180px;font-size: 12px;"
							onClick="document.form1.subjectid__.value='CANCELSUBTASK';document.form1.subtask__.value='';document.form1.submit();" />
							<input type="button" name="Submit" value="Delete" style="width: 100px;font-size: 12px;"
							onClick="document.form1.subjectid__.value='ADMINISTRATIVE';document.form1.subtask__.value='delete_course_category';document.form1.submit();" />
							<input type="button" name="Submit" value="Submit" style="width: 100px;font-size: 12px;"
							onClick="document.form1.subjectid__.value='ADMINISTRATIVE';document.form1.subtask__.value='add_course_category';document.form1.submit();" />
					  </td>
					</tr>
					<tr>
						<td>&nbsp;</td>
					</tr>
					<tr align="center">
						<td class="contentfont">
		          <table border="1" class="thinborder" style="font-size: 12px;">
		          	<tr bgcolor="#C1E8BE">
		          		<td width="50" align="center">&nbsp;</td>
		          		<td width="230" align="center">Course Category (English)</td>
		          		<td width="220" align="center">Course Category (Chinese)</td>
		          		<td width="100" align="center">Course Type</td>
								</tr>
<?php
	if (isset($course_cats[0])) {
		for ($i = 0; $i < sizeof($course_cats); $i++) {
?>
		          	<tr>
		          		<td align="center">
		          			<input type="radio" name="CourseCategoryNmbr__" value="<?php echo $course_cats[$i]['CourseCategoryNmbr']; ?>" <?php if (getSession('CourseCategoryNmbr', 0) == $course_cats[$i]['CourseCategoryNmbr']) echo 'checked'; ?>
										onClick="document.form1.subjectid__.value='ADMINISTRATIVE';document.form1.subtask__.value='refresh_course_category';document.form1.submit();"
		          			/>
		          		</td>
		          		<td align="center"><?php echo $course_cats[$i]['CourseCategory_E']; ?></td>
		          		<td align="center"><?php echo $course_cats[$i]['CourseCategory_C']; ?></td>
		          		<td align="center"><?php echo $course_cats[$i]['CourseType']; ?></td>
								</tr>
<?php
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
        	<tr height="30">
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
 * @name 		AdminTemplate_CourseLevel
 * @args 		0
 * @return	website template
 * @desc		
 *
 **/
function AdminTemplate_CourseLevel()
{
	$ref_lib = new RefLibrary();
	$course_levels = $ref_lib->GetRefValues('REF_CourseLevel');
	if (getSession('CourseLevelNmbr', 0) != '') {
		$selected_course_level_info = $ref_lib->GetRefValues('REF_CourseLevel', 'CourseLevelNmbr', getSession('CourseLevelNmbr', 0));
		$selected_course_level_e = $selected_course_level_info[0]['CourseLevel_E'];
		$selected_course_level_c = $selected_course_level_info[0]['CourseLevel_C'];
	}
	else {
		$selected_course_level_e = '';
		$selected_course_level_c = '';
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
							<font size="3" color="darkred"><b>FCD School Course Levels</b></font><br/>
						</td>
					</tr>
					<tr>
						<td>&nbsp;</td>
					</tr>
					<tr align="center">
						<td class="contentfont">
		          <table border="0" bgcolor="#C1E8BE" class="thinborder" style="font-size: 12px;">
		          	<tr>
		          		<td width="200" align="right">Course Level (English)</td>
		          		<td width="20">&nbsp;</td>
		          		<td width="280" align="left">
										<input type="text" name="CourseLevel_E__" value="<?php echo $selected_course_level_e; ?>" style="width: 250px;" />
		          		</td>
								</tr>
		          	<tr>
		          		<td width="200" align="right">Course Level (Chinese)</td>
		          		<td width="20">&nbsp;</td>
		          		<td width="280" align="left">
										<input type="text" name="CourseLevel_C__" value="<?php echo $selected_course_level_c; ?>" style="width: 250px;" />
		          		</td>
								</tr>
		          </table>
		        </td>
		      </tr>
					<script type="text/javascript">
						function CheckCourseLevelDelete() { 
							if (CheckRadioCheckbox(document.form1.CourseLevelNmbr__)) {
								return true;
							}
							else {
								alert('You need to select a course level to delete.');
								return false;
							}
						}
						function CheckCourseLevel() { 
							if(document.form1.CourseLevel_E__.value == '') {
								alert('Course level (English) is required.');
								return false;
							}
							if(document.form1.CourseLevel_C__.value == '') {
								alert('Course level (Chinese) is required.');
								return false;
							}
							return true;
						}
					</script>
					<tr height="50" valign="center">
						<td align="right">
							<input type="button" name="Submit" value="Back to management page" style="width: 180px;font-size: 12px;"
							onClick="document.form1.subjectid__.value='CANCELSUBTASK';document.form1.subtask__.value='';document.form1.submit();" />
							<input type="button" name="Submit" value="Delete" style="width: 100px;font-size: 12px;"
							onClick="if (CheckCourseLevelDelete()){document.form1.subjectid__.value='ADMINISTRATIVE';document.form1.subtask__.value='delete_course_level';document.form1.submit();}" />
							<input type="button" name="Submit" value="Submit" style="width: 100px;font-size: 12px;"
							onClick="if (CheckCourseLevel()){document.form1.subjectid__.value='ADMINISTRATIVE';document.form1.subtask__.value='add_course_level';document.form1.submit();}" />
					  </td>
					</tr>
					<tr>
						<td>&nbsp;</td>
					</tr>
					<tr align="center">
						<td class="contentfont">
		          <table border="1" class="thinborder" style="font-size: 12px;">
		          	<tr bgcolor="#C1E8BE">
		          		<td width="50" align="center">&nbsp;</td>
		          		<td width="230" align="center">Course Level (English)</td>
		          		<td width="320" align="center">Course Level (Chinese)</td>
								</tr>
<?php
	if (isset($course_levels[0])) {
		for ($i = 0; $i < sizeof($course_levels); $i++) {
?>
		          	<tr>
		          		<td align="center">
		          			<input type="radio" name="CourseLevelNmbr__" value="<?php echo $course_levels[$i]['CourseLevelNmbr']; ?>" <?php if (getSession('CourseLevelNmbr', 0) == $course_levels[$i]['CourseLevelNmbr']) echo 'checked'; ?>
										onClick="document.form1.subjectid__.value='ADMINISTRATIVE';document.form1.subtask__.value='refresh_course_level';document.form1.submit();"
		          			/>
		          		</td>
		          		<td align="center"><?php echo $course_levels[$i]['CourseLevel_E']; ?></td>
		          		<td align="center"><?php echo $course_levels[$i]['CourseLevel_C']; ?></td>
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
        	<tr height="30">
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
 * @name 		AdminTemplate_ClassPeriod
 * @args 		0
 * @return	website template
 * @desc		
 *
 **/
function AdminTemplate_ClassPeriod()
{
	$ref_lib = new RefLibrary();
	$class_periods = $ref_lib->GetRefValues('REF_ClassPeriod');
	if (getSession('ClassPeriodNmbr', 0) != '') {
		$selected_class_period_info = $ref_lib->GetRefValues('REF_ClassPeriod', 'ClassPeriodNmbr', getSession('ClassPeriodNmbr', 0));
		$selected_class_period_e = $selected_class_period_info[0]['ClassPeriod_E'];
		$selected_class_period_c = $selected_class_period_info[0]['ClassPeriod_C'];
		$selected_class_time = $selected_class_period_info[0]['ClassTime'];
	}
	else {
		$selected_class_period_e = '';
		$selected_class_period_c = '';
		$selected_class_time = '';
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
							<font size="3" color="darkred"><b>FCD School Class Period</b></font><br/>
						</td>
					</tr>
					<tr>
						<td>&nbsp;</td>
					</tr>
					<tr align="center">
						<td class="contentfont">
		          <table border="0" bgcolor="#C1E8BE" class="thinborder" style="font-size: 12px;">
		          	<tr>
		          		<td width="200" align="right">Class Period (English)</td>
		          		<td width="20">&nbsp;</td>
		          		<td width="280" align="left">
										<input type="text" name="ClassPeriod_E__" value="<?php echo $selected_class_period_e; ?>" style="width: 250px;" />
		          		</td>
								</tr>
		          	<tr>
		          		<td width="200" align="right">Class Period (Chinese)</td>
		          		<td width="20">&nbsp;</td>
		          		<td width="280" align="left">
										<input type="text" name="ClassPeriod_C__" value="<?php echo $selected_class_period_c; ?>" style="width: 250px;" />
		          		</td>
								</tr>
		          	<tr>
		          		<td width="200" align="right">Class Time</td>
		          		<td width="20">&nbsp;</td>
		          		<td width="280" align="left">
										<input type="text" name="ClassTime__" value="<?php echo $selected_class_time; ?>" style="width: 250px;" />
		          		</td>
								</tr>
		          </table>
		        </td>
		      </tr>
					<tr height="50" valign="center">
						<td align="right">
							<input type="button" name="Submit" value="Back to management page" style="width: 180px;font-size: 12px;"
							onClick="document.form1.subjectid__.value='CANCELSUBTASK';document.form1.subtask__.value='';document.form1.submit();" />
							<input type="button" name="Submit" value="Delete" style="width: 100px;font-size: 12px;"
							onClick="document.form1.subjectid__.value='ADMINISTRATIVE';document.form1.subtask__.value='delete_class_period';document.form1.submit();" />
							<input type="button" name="Submit" value="Submit" style="width: 100px;font-size: 12px;"
							onClick="document.form1.subjectid__.value='ADMINISTRATIVE';document.form1.subtask__.value='add_class_period';document.form1.submit();" />
					  </td>
					</tr>
					<tr>
						<td>&nbsp;</td>
					</tr>
					<tr align="center">
						<td class="contentfont">
		          <table border="1" class="thinborder" style="font-size: 12px;">
		          	<tr bgcolor="#C1E8BE">
		          		<td width="50" align="center">&nbsp;</td>
		          		<td width="200" align="center">Class Period (English)</td>
		          		<td width="200" align="center">Class Period (Chinese)</td>
		          		<td width="150" align="center">Class Time</td>
								</tr>
<?php
	if (isset($class_periods[0])) {
		for ($i = 0; $i < sizeof($class_periods); $i++) {
?>
		          	<tr>
		          		<td align="center">
		          			<input type="radio" name="ClassPeriodNmbr__" value="<?php echo $class_periods[$i]['ClassPeriodNmbr']; ?>" <?php if (getSession('ClassPeriodNmbr', 0) == $class_periods[$i]['ClassPeriodNmbr']) echo 'checked'; ?>
										onClick="document.form1.subjectid__.value='ADMINISTRATIVE';document.form1.subtask__.value='refresh_class_period';document.form1.submit();"
		          			/>
		          		</td>
		          		<td align="center">&nbsp;<?php echo $class_periods[$i]['ClassPeriod_E']; ?></td>
		          		<td align="center">&nbsp;<?php echo $class_periods[$i]['ClassPeriod_C']; ?></td>
		          		<td align="center">&nbsp;<?php echo $class_periods[$i]['ClassTime']; ?></td>
								</tr>
<?php
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
        	<tr height="30">
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
 * @name 		AdminTemplate_MarkingPeriod
 * @args 		0
 * @return	website template
 * @desc		
 *
 **/
function AdminTemplate_MarkingPeriod() {
	$ref_lib = new RefLibrary();
	$marking_periods = $ref_lib->GetRefValues('REF_MarkingPeriod');
	if (getSession('MarkingPeriod', 0) != '') {
		$selected_marking_period = getSession('MarkingPeriod', 0);
	}
	else {
		$selected_marking_period = '';
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
							<font size="3" color="darkred"><b>FCD School Marking Period</b></font><br/>
						</td>
					</tr>
					<tr height="50">
						<td>&nbsp;</td>
					</tr>
					<tr align="center">
						<td class="contentfont">
		          <table border="0" bgcolor="#C1E8BE" class="thinborder" style="font-size: 12px;">
		          	<tr>
		          		<td width="200" align="right">Marking Period</td>
		          		<td width="20">&nbsp;</td>
		          		<td width="280" align="left">
										<input type="text" name="NewMarkingPeriod__" value="<?php echo $selected_marking_period; ?>" style="width: 250px;" />
		          		</td>
								</tr>
		          </table>
		        </td>
		      </tr>
					<tr height="50" valign="center">
						<td align="right">
							<input type="button" name="Submit" value="Back to management page" style="width: 180px;font-size: 12px;"
							onClick="document.form1.subjectid__.value='CANCELSUBTASK';document.form1.subtask__.value='';document.form1.submit();" />
							<input type="button" name="Submit" value="Delete" style="width: 100px;font-size: 12px;"
							onClick="document.form1.subjectid__.value='ADMINISTRATIVE';document.form1.subtask__.value='delete_marking_period';document.form1.submit();" />
							<input type="button" name="Submit" value="Submit" style="width: 100px;font-size: 12px;"
							onClick="document.form1.subjectid__.value='ADMINISTRATIVE';document.form1.subtask__.value='add_marking_period';document.form1.submit();" />
					  </td>
					</tr>
					<tr>
						<td>&nbsp;</td>
					</tr>
					<tr align="center">
						<td class="contentfont">
		          <table border="1" class="thinborder" style="font-size: 12px;">
		          	<tr bgcolor="#C1E8BE">
		          		<td width="50" align="center">&nbsp;</td>
		          		<td width="550" align="center">Marking Period</td>
								</tr>
<?php
	if (isset($marking_periods[0])) {
		for ($i = 0; $i < sizeof($marking_periods); $i++) {
?>
		          	<tr>
		          		<td align="center">
		          			<input type="radio" name="MarkingPeriod__" value="<?php echo $marking_periods[$i]['MarkingPeriod']; ?>" <?php if (getSession('MarkingPeriod', 0) == $marking_periods[$i]['MarkingPeriod']) echo 'checked'; ?>
										onClick="document.form1.subjectid__.value='ADMINISTRATIVE';document.form1.subtask__.value='refresh_marking_period';document.form1.submit();"
		          			/>
		          		</td>
		          		<td align="center"><?php echo $marking_periods[$i]['MarkingPeriod']; ?></td>
								</tr>
<?php
		}
	}
?>
		          	<tr>
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
 * @name 		AdminTemplate_Sql
 * @args 		0
 * @return	website template
 * @desc		
 *
 **/
function AdminTemplate_Sql() {
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
							<font size="3" color="darkred"><b>SQL</b></font><br/>
						</td>
					</tr>
					<tr height="50">
						<td>&nbsp;</td>
					</tr>
					<tr align="center">
						<td class="contentfont">

							<?php 
							if (isset($_POST['Sql__']) && $_POST['Sql__'] != '') {
								include_once 'LIB_DbConnection.inc';
								$dbconn = GetConnection();
							
								$query = $_POST['Sql__'];
								$result = mysql_query($query) or die("Query failed : $query " . mysql_error());
								if (mysql_num_rows($result) > 0) {
									while ($row = mysql_fetch_array($result, MYSQL_ASSOC)) {
										echo '@@@@--';
										foreach ($row as $row_name => $val) {
											echo $val . '####';
										}
										echo '--@@@@<br/>';
									}
									mysql_free_result($result);
								}
							}
							?>
						

		          <table border="0" bgcolor="#C1E8BE" class="thinborder" style="font-size: 12px;">
		          	<tr>
		          		<td width="100" align="right" valign="top">SQL (end with ;)</td>
		          		<td width="20">&nbsp;</td>
		          		<td width="380" align="left">
										<textarea name="Sql__" style="width: 350px; height: 500px"></textarea>
		          		</td>
								</tr>
		          </table>
		        </td>
		      </tr>
					<tr height="50" valign="center">
						<td align="right">
							<input type="button" name="Submit" value="Back to management page" style="width: 180px;font-size: 12px;"
							onClick="document.form1.subjectid__.value='CANCELSUBTASK';document.form1.subtask__.value='';document.form1.submit();" />
							<input type="button" name="Submit" value="Submit" style="width: 100px;font-size: 12px;"
							onClick="document.form1.subjectid__.value='ADMINISTRATIVE';document.form1.subtask__.value='submit_sql';document.form1.submit();" />
					  </td>
					</tr>
					<tr>
						<td>&nbsp;</td>
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


?>

