<?php

/**
 *
 *
 * @version $Id$
 * @copyright 2005
 **/

/**
 *
 * @name 		AdminTemplate_AddCourse
 * @args 		0
 * @return	website template
 * @desc		
 *
 **/
function AdminTemplate_AddCourse()
{
	$ref_lib = new RefLibrary();
	$curriculum_handler = new CurriculumHandler();
	$courses = $curriculum_handler->GetCourse();
	$course_categories = $ref_lib->GetRefValues('REF_CourseCategory');
	if (getSession('CourseNmbr', 0) != '') {
		$selected_course = $curriculum_handler->GetCourse(getSession('CourseNmbr', 0));
		$selected_course_e = $selected_course[0]['CourseName_E'];
		$selected_course_c = $selected_course[0]['CourseName_C'];
		$selected_course_catnmbr = $selected_course[0]['CourseCategoryNmbr'];
	}
	else {
		$selected_course_e = '';
		$selected_course_c = '';
		$selected_course_catnmbr = '';
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
							<font size="3" color="darkred"><b>FCD School Courses Offered</b></font><br/>
						</td>
					</tr>
					<tr>
						<td>&nbsp;</td>
					</tr>
					<tr align="center">
						<td class="contentfont">
		          <table border="1" bgcolor="#C1E8BE" class="thinborder" style="font-size: 12px;">
		          	<tr>
		          		<td width="150" align="center">Course Name</td>
		          		<td width="150" align="center">Course Name (Chinese)</td>
		          		<td width="200" align="center">Tuition Category</td>
								</tr>
		          	<tr>
		          		<td>
										<input type="text" name="CourseName_E__" value="<?php echo $selected_course_e; ?>" style="width: 150px;" />
		          		</td>
		          		<td>
										<input type="text" name="CourseName_C__" value="<?php echo $selected_course_c; ?>" style="width: 150px;" />
		          		</td>
		          		<td>
										<select name="CourseCategoryNmbr__" size="1" style="width: 200px;">
											<option value=""></option>
											<?php
											for ($i = 0; $i < sizeof($course_categories); $i++) {
											?>
												<option value="<?php echo $course_categories[$i]['CourseCategoryNmbr']; ?>" <?php if ($selected_course_catnmbr == $course_categories[$i]['CourseCategoryNmbr']) echo ' selected'; ?>><?php echo $course_categories[$i]['CourseCategory_E'] . " (" . $course_categories[$i]['CourseCategory_C']  . ")"; ?></option>
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
						function CheckCourseDelete() { 
							if (CheckRadioCheckbox(document.form1.CourseNmbr__)) {
								return true;
							}
							else {
								alert('You need to select a course to delete.');
								return false;
							}
						}
						function CheckCourseSubmit() { 
							if(document.form1.CourseName_E__.value == '') {
								alert('Course Name (English) is required.');
								return false;
							}
							if(document.form1.CourseName_C__.value == '') {
								alert('Course Name (Chinese) is required.');
								return false;
							}
							if(document.form1.CourseCategoryNmbr__.selectedIndex < 1) {
								alert('Course Category is required (for calculating tuition and fees).');
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
							onClick="if(CheckCourseDelete()){document.form1.subjectid__.value='CURRICULUM';document.form1.subtask__.value='delete_course';document.form1.submit();}" />
							<input type="button" name="Submit" value="Submit" style="width: 100px;font-size: 12px;"
							onClick="if(CheckCourseSubmit()){document.form1.subjectid__.value='CURRICULUM';document.form1.subtask__.value='submit_add_course';document.form1.submit();}" />
					  </td>
					</tr>
					<tr height="50" valign="bottom">
						<td align="center" style="font-size: 16px;font-weight: bold;color: darkgreen;">Current Courses Offered</td>
					</tr>
					<tr align="center">
						<td class="contentfont">
		          <table border="1" class="thinborder" style="font-size: 12px;">
		          	<tr bgcolor="#C1E8BE">
		          		<td width="50" align="center">&nbsp;</td>
		          		<td width="300" align="center">Course</td>
		          		<td width="150" align="center">Category</td>
								</tr>
<?php
	for ($i = 0; $i < sizeof($courses); $i++) {
?>
		          	<tr>
		          		<td align="center">
		          			<input type="radio" name="CourseNmbr__" value="<?php echo $courses[$i]['CourseNmbr']; ?>" <?php if (getSession('CourseNmbr', 0) == $courses[$i]['CourseNmbr']) echo 'checked'; ?>
										onClick="document.form1.subjectid__.value='CURRICULUM';document.form1.subtask__.value='refresh_course';document.form1.submit();"
		          			/>
		          		</td>
		          		<td><?php echo $courses[$i]['CourseName_E'] . ' (' . $courses[$i]['CourseName_C'] . ')'; ?></td>
		          		<td><?php echo $courses[$i]['CourseCategory_E'] . ' (' . $courses[$i]['CourseCategory_C'] . ')'; ?></td>
								</tr>
<?php
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
 * @name 		AdminTemplate_Classroom
 * @args 		0
 * @return	website template
 * @desc		
 *
 **/
function AdminTemplate_Classroom()
{
	$ref_lib = new RefLibrary();
	$classrooms = $ref_lib->GetRefValues('REF_Classroom');
	if (getSession('ClassroomNmbr', 0) != '') {
		$selected_classroom_info = $ref_lib->GetRefValues('REF_Classroom', 'ClassroomNmbr', getSession('ClassroomNmbr', 0));
		$selected_classroom = $selected_classroom_info[0]['Classroom'];
	}
	else {
		$selected_role_e = '';
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
							<font size="3" color="darkred"><b>FCD School Classrooms</b></font><br/>
						</td>
					</tr>
					<tr>
						<td>&nbsp;</td>
					</tr>
					<tr align="center">
						<td class="contentfont">
		          <table border="0" bgcolor="#C1E8BE" class="thinborder" style="font-size: 12px;">
		          	<tr>
		          		<td width="200" align="right">Classroom</td>
		          		<td width="20">&nbsp;</td>
		          		<td width="280" align="left">
										<input type="text" name="Classroom__" value="<?php echo $selected_classroom; ?>" style="width: 250px;" />
		          		</td>
								</tr>
		          </table>
		        </td>
		      </tr>
					<script type="text/javascript">
						function CheckClassroomDelete() { 
							if (CheckRadioCheckbox(document.form1.ClassroomNmbr__)) {
								return true;
							}
							else {
								alert('You need to select a classroom to delete.');
								return false;
							}
						}
						function CheckClassroomSubmit() { 
							if(document.form1.Classroom__.value == '') {
								alert('Classroom is required.');
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
							onClick="if (CheckClassroomDelete()){document.form1.subjectid__.value='CURRICULUM';document.form1.subtask__.value='delete_classroom';document.form1.submit();}" />
							<input type="button" name="Submit" value="Submit" style="width: 100px;font-size: 12px;"
							onClick="if (CheckClassroomSubmit()){document.form1.subjectid__.value='CURRICULUM';document.form1.subtask__.value='add_classroom';document.form1.submit();}" />
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
		          		<td width="550" align="center">Classroom</td>
								</tr>
<?php
	if (isset($classrooms[0])) {
		for ($i = 0; $i < sizeof($classrooms); $i++) {
?>
		          	<tr>
		          		<td align="center">
		          			<input type="radio" name="ClassroomNmbr__" value="<?php echo $classrooms[$i]['ClassroomNmbr']; ?>" <?php if (getSession('ClassroomNmbr', 0) == $classrooms[$i]['ClassroomNmbr']) echo 'checked'; ?>
										onClick="document.form1.subjectid__.value='CURRICULUM';document.form1.subtask__.value='refresh_classroom';document.form1.submit();"
		          			/>
		          		</td>
		          		<td align="center"><?php echo $classrooms[$i]['Classroom']; ?></td>
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
 * @name 		AdminTemplate_ClassBuilder
 * @args 		0
 * @return	website template
 * @desc		
 *
 **/
function AdminTemplate_ClassBuilder()
{
	$ref_lib = new RefLibrary();
	$courses = $ref_lib->GetRefValues('SCHL_Course');
	$course_levels = $ref_lib->GetRefValues('REF_CourseLevel');
	$classrooms = $ref_lib->GetRefValues('REF_Classroom');
	$class_periods = $ref_lib->GetRefValues('REF_ClassPeriod');
	
	$curriculum_handler = new CurriculumHandler();
	$classes = $curriculum_handler->GetClass();
	if (getSession('ClassNmbr', 0) != '') {
		$selected_class = $curriculum_handler->GetClass('', getSession('ClassNmbr', 0));
		$selected_course = $selected_class[0]['CourseNmbr'];
		$selected_class_e = $selected_class[0]['ClassName_E'];
		$selected_class_c = $selected_class[0]['ClassName_C'];
		$selected_course_level = $selected_class[0]['CourseLevelNmbr'];
		$selected_classroom = $selected_class[0]['ClassroomNmbr'];
		$selected_class_period = $selected_class[0]['ClassPeriodNmbr'];
	}
	else {
		$selected_class_e = '';
		$selected_class_c = '';
		$selected_course = '';
		$selected_course_catnmbr = '';
		$selected_course_level = '';
		$selected_classroom = '';
		$selected_class_period = '';
	}
?>
	<table border="0" width="600" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td>
				<table width="550" align="center" cellspacing="0" cellpadding="0">
					<tr>
						<td>&nbsp;</td>
					</tr>
					<tr>
						<td align="center">
							<font size="3" color="darkred"><b>FCD School Class Builder</b></font><br/>
						</td>
					</tr>
					<tr>
						<td>&nbsp;</td>
					</tr>
					<tr height="30" valign="center">
						<td style="font-size: 14px;color: darkgreen;">
							Give the class a name, then select a course, course level, classroom, and period to form a class.  
							Repeat if necessary.
						</td>
					</tr>
					<tr height="60" valign="center">
						<td width="550" align="left" style="font-size: 14px;font-weight: bold;color: darkgreen;">
							Class Name (English):
							&nbsp;&nbsp;&nbsp;&nbsp;
							<input type="text" name="ClassName_E__" value="<?php echo $selected_class_e; ?>" style="width: 300px;" /><br/>
							Class Name (Chinese):
							&nbsp;&nbsp;&nbsp;
							<input type="text" name="ClassName_C__" value="<?php echo $selected_class_c; ?>" style="width: 300px;" />
						</td>
					</tr>
					<tr align="center">
						<td class="contentfont">
		          <table border="1" bgcolor="#C1E8BE" class="thinborder" style="font-size: 12px;">
		          	<tr>
		          		<td width="220" align="center">Course</td>
		          		<td width="160" align="center">Course Level</td>
		          		<td width="100" align="center">Classroom</td>
		          		<td width="170" align="center">Period</td>
								</tr>
		          	<tr>
		          		<td>
										<select name="CourseNmbr__" size="10" style="width: 220px;">
											<?php
											for ($i = 0; $i < sizeof($courses); $i++) {
											?>
												<option value="<?php echo $courses[$i]['CourseNmbr']; ?>" <?php if ($selected_course == $courses[$i]['CourseNmbr']) echo ' selected'; ?>><?php echo $courses[$i]['CourseName_E'] . " (" . $courses[$i]['CourseName_C']  . ")"; ?></option>
											<?php
											}
											?>
										</select>
		          		</td>
		          		<td>
										<select name="CourseLevelNmbr__" size="10" style="width: 160px;">
											<?php
											for ($i = 0; $i < sizeof($course_levels); $i++) {
											?>
												<option value="<?php echo $course_levels[$i]['CourseLevelNmbr']; ?>" <?php if ($selected_course_level == $course_levels[$i]['CourseLevelNmbr']) echo ' selected'; ?>><?php echo $course_levels[$i]['CourseLevel_E'] . " (" . $course_levels[$i]['CourseLevel_C']  . ")"; ?></option>
											<?php
											}
											?>
										</select>
		          		</td>
		          		<td>
										<select name="ClassroomNmbr__" size="10" style="width: 100px;">
											<?php
											for ($i = 0; $i < sizeof($classrooms); $i++) {
											?>
												<option value="<?php echo $classrooms[$i]['ClassroomNmbr']; ?>" <?php if ($selected_classroom == $classrooms[$i]['ClassroomNmbr']) echo ' selected'; ?>><?php echo $classrooms[$i]['Classroom']; ?></option>
											<?php
											}
											?>
										</select>
		          		</td>
		          		<td>
										<select name="ClassPeriodNmbr__" size="10" style="width: 170px;">
											<?php
											for ($i = 0; $i < sizeof($class_periods); $i++) {
											?>
												<option value="<?php echo $class_periods[$i]['ClassPeriodNmbr']; ?>" <?php if ($selected_class_period == $class_periods[$i]['ClassPeriodNmbr']) echo ' selected'; ?>><?php echo $class_periods[$i]['ClassPeriod_E'] . " (" . $class_periods[$i]['ClassPeriod_C']  . ")"; ?></option>
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
						function CheckClassBuilderDelete() { 
							if (CheckRadioCheckbox(document.form1.ClassNmbr__)) {
								return true;
							}
							else {
								alert('You need to select a class to delete.');
								return false;
							}
						}
						function CheckClassBuilder() { 
							if(document.form1.ClassName_E__.value == '') {
								alert('Class Name (English) is required.');
								return false;
							}
							if(document.form1.ClassName_C__.value == '') {
								alert('Class Name (Chinese) is required.');
								return false;
							}
							if(document.form1.CourseNmbr__.selectedIndex < 0) {
								alert('Course is required.');
								return false;
							}
							if(document.form1.CourseLevelNmbr__.selectedIndex < 0) {
								alert('Course level is required.');
								return false;
							}
							if(document.form1.ClassroomNmbr__.selectedIndex < 0) {
								alert('If classroom cannot be decided at the moment, select Pending.');
								return false;
							}
							if(document.form1.ClassPeriodNmbr__.selectedIndex < 0) {
								alert('Class period is required.');
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
							onClick="if(CheckClassBuilderDelete()){document.form1.subjectid__.value='CURRICULUM';document.form1.subtask__.value='delete_class';document.form1.submit();}" />
							<input type="button" name="Submit" value="Submit" style="width: 100px;font-size: 12px;"
							onClick="if(CheckClassBuilder()){document.form1.subjectid__.value='CURRICULUM';document.form1.subtask__.value='submit_class';document.form1.submit();}" />
					  </td>
					</tr>
					<tr height="50" valign="bottom">
						<td align="center" style="font-size: 16px;font-weight: bold;color: darkgreen;">Current Classes</td>
					</tr>
					<tr align="center">
						<td class="contentfont">
		          <table width="600" border="1" class="thinborder" style="font-size: 12px;">
		          	<tr bgcolor="#C1E8BE">
		          		<td width="50" align="center">&nbsp;</td>
		          		<td width="550" align="center">Class</td>
								</tr>
<?php
	if (isset($classes[0])) {
		for ($i = 0; $i < sizeof($classes); $i++) {
?>
		          	<tr>
		          		<td align="center">
		          			<input type="radio" name="ClassNmbr__" value="<?php echo $classes[$i]['ClassNmbr']; ?>" <?php if (getSession('ClassNmbr', 0) == $classes[$i]['ClassNmbr']) echo 'checked'; ?>
										onClick="document.form1.subjectid__.value='CURRICULUM';document.form1.subtask__.value='refresh_class';document.form1.submit();"
		          			/>
		          		</td>
		          		<td><?php echo $classes[$i]['ClassName_E'] . ' (' . $classes[$i]['ClassName_C'] . ')'; ?></td>
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
 * @name 		AdminTemplate_Curriculum_ViewReport
 * @args 		0
 * @return	website template
 * @desc		
 *
 **/
function AdminTemplate_Curriculum_ViewReport($pTarget) {
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

