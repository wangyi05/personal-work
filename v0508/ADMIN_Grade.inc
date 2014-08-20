<?php

/**
 *
 *
 * @version $Id$
 * @copyright 2005
 **/

/**
 *
 * @name 		AdminTemplate_GradeTracking
 * @args 		0
 * @return	website template
 * @desc		
 *
 **/
function AdminTemplate_GradeTracking()
{
	$ref_lib = new RefLibrary();
	$school_years = $ref_lib->GetSchoolYear('all');
	$marking_periods = $ref_lib->GetRefValues('REF_MarkingPeriod');
	$curriculum = new CurriculumHandler();
	$classes = $curriculum->GetClass();
	if (getSession('SchoolYear', 0) != '' && getSession('MarkingPeriod', 0) != '' && getSession('ClassNmbr', 0) != '') {
		$reg_handler = new RegistrationHandler();
		$registrations = $reg_handler->GetRegistration(getSession('SchoolYear', 0), getSession('ClassNmbr', 0), '', '', '');
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
							<font size="3" color="darkred"><b>FCD School Student Grade</b></font><br/>
						</td>
					</tr>
					<tr height="40">
						<td>&nbsp;</td>
					</tr>
					<tr height="30" valign="center">
						<td width="500" align="left" style="font-size: 14px;font-weight: bold;color: darkgreen;">
							School Year:
							&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
							<select name="SchoolYear__" size="1" style="width: 150px;"
							onChange="document.form1.subjectid__.value='GRADE';document.form1.subtask__.value='refresh';document.form1.submit();"
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
					<tr height="30" valign="center">
						<td width="500" align="left" style="font-size: 14px;font-weight: bold;color: darkgreen;">
							Class:
							&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
							&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
							<select name="ClassNmbr__" size="1" style="width: 250px;"
							onChange="document.form1.subjectid__.value='GRADE';document.form1.subtask__.value='refresh';document.form1.submit();"
							>
								<option value=""></option>
								<?php
								for ($i = 0; $i < sizeof($classes); $i++) {
									echo "<option value=\"" . $classes[$i]['ClassNmbr'] . "\" " . checkSelectedOption("ClassNmbr", $classes[$i]['ClassNmbr']) . ">" . $classes[$i]['ClassName_E'] . " (" . $classes[$i]['ClassName_C'] . ")</option>\n";
								}
								?>
							</select>
						</td>
					</tr>
					<tr height="30" valign="center">
						<td width="500" align="left" style="font-size: 14px;font-weight: bold;color: darkgreen;">
							Marking Period:
							&nbsp;
							<select name="MarkingPeriod__" size="1" style="width: 150px;"
							onChange="document.form1.subjectid__.value='GRADE';document.form1.subtask__.value='refresh';document.form1.submit();"
							>
								<option value=""></option>
								<?php
								for ($i = 0; $i < sizeof($marking_periods); $i++) {
									echo "<option value=\"" . $marking_periods[$i]['MarkingPeriod'] . "\" " . checkSelectedOption("MarkingPeriod", $marking_periods[$i]['MarkingPeriod']) . ">" . $marking_periods[$i]['MarkingPeriod']  . "</option>\n";
								}
								?>
							</select>
						</td>
					</tr>
					<tr height="30" valign="center">
						<td width="500" align="left" style="font-size: 14px;font-weight: bold;color: darkgreen;">
							Student:
							&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
							&nbsp;&nbsp;&nbsp;&nbsp;
							<select name="StudentNmbr__" size="1" style="width: 250px;"
							onChange="document.form1.subjectid__.value='GRADE';document.form1.subtask__.value='refresh';document.form1.submit();"
							>
								<option value=""></option>
								<?php
								for ($i = 0; $i < sizeof($registrations); $i++) {
									echo "<option value=\"" . $registrations[$i]['FamilyMemberNmbr'] . "\" " . checkSelectedOption("StudentNmbr", $registrations[$i]['FamilyMemberNmbr']) . ">" . $registrations[$i]['LastName'] . ' ' . $registrations[$i]['FirstName'] . ' (' . $registrations[$i]['ChineseName'] . ")</option>\n";
								}
								?>
							</select>
						</td>
					</tr>
        	<tr>
        		<td>&nbsp;</td>
					</tr>
<?php
	if (getSession('StudentNmbr', 0) != '') {
		$reg_handler = new RegistrationHandler();
		$registrations = $reg_handler->GetRegistration(getSession('SchoolYear', 0), getSession('ClassNmbr', 0), getSession('StudentNmbr', 0), '', '');
		$grade_handler = new StudentGradeHandler();
		$grades = $grade_handler->GetStudentGrade(getSession('SchoolYear', 0), getSession('MarkingPeriod', 0), getSession('ClassNmbr', 0), getSession('StudentNmbr', 0));
?>		
					<tr align="center">
						<td class="contentfont">
		          <table width="350" border="1" bgcolor="#C1E8BE" class="thinborder" style="font-size: 12px;">
		          	<tr height="30" bgcolor="#A8CFA5">
		          		<td width="200" align="center">Test Category</td>
		          		<td width="150" align="center">Grade</td>
								</tr>
		          	<tr>
		          		<td align="center">
										生字听写
		          		</td>
		          		<td align="center">
										<input type="text" name="VocabDictation__" style="width: 100px" value="<?php echo $grades[0]['VocabDictation']; ?>" />
		          		</td>
								</tr>
		          	<tr>
		          		<td align="center">
										听写附加
		          		</td>
		          		<td align="center">
										<input type="text" name="VocabDictationExtraCredit__" style="width: 100px" value="<?php echo $grades[0]['VocabDictationExtraCredit']; ?>" />
		          		</td>
								</tr>
		          	<tr>
		          		<td align="center">
										段落听写
		          		</td>
		          		<td align="center">
										<input type="text" name="ParagraphDictation__" style="width: 100px" value="<?php echo $grades[0]['ParagraphDictation']; ?>" />
		          		</td>
								</tr>
		          	<tr>
		          		<td align="center">
										造句
		          		</td>
		          		<td align="center">
										<input type="text" name="SentenceMaking__" style="width: 100px" value="<?php echo $grades[0]['SentenceMaking']; ?>" />
		          		</td>
								</tr>
		          	<tr>
		          		<td align="center">
										课文理解
		          		</td>
		          		<td align="center">
										<input type="text" name="PassageUnderstanding__" style="width: 100px" value="<?php echo $grades[0]['PassageUnderstanding']; ?>" />
		          		</td>
								</tr>
		          	<tr>
		          		<td align="center">
										阅读理解
		          		</td>
		          		<td align="center">
										<input type="text" name="ReadingComprehension__" style="width: 100px" value="<?php echo $grades[0]['ReadingComprehension']; ?>" />
		          		</td>
								</tr>
		          	<tr>
		          		<td align="center">
										笔试总分
		          		</td>
		          		<td align="center">
										<input type="text" name="WrittenExamTotal__" style="width: 100px" value="<?php echo $grades[0]['WrittenExamTotal']; ?>" />
		          		</td>
								</tr>
			        	<tr>
			        		<td>&nbsp;</td>
			        		<td>&nbsp;</td>
								</tr>
		          	<tr>
		          		<td align="center">
										认读生字
		          		</td>
		          		<td align="center">
										<input type="text" name="VocabRecognition__" style="width: 100px" value="<?php echo $grades[0]['VocabRecognition']; ?>" />
		          		</td>
								</tr>
		          	<tr>
		          		<td align="center">
										朗读课文
		          		</td>
		          		<td align="center">
										<input type="text" name="PassageReading__" style="width: 100px" value="<?php echo $grades[0]['PassageReading']; ?>" />
		          		</td>
								</tr>
		          	<tr>
		          		<td align="center">
										课文录音
		          		</td>
		          		<td align="center">
										<input type="text" name="PassageRecording__" style="width: 100px" value="<?php echo $grades[0]['PassageRecording']; ?>" />
		          		</td>
								</tr>
		          	<tr>
		          		<td align="center">
										阅读录音附加
		          		</td>
		          		<td align="center">
										<input type="text" name="PassageReadingExtraCredit__" style="width: 100px" value="<?php echo $grades[0]['PassageReadingExtraCredit']; ?>" />
		          		</td>
								</tr>
		          	<tr>
		          		<td align="center">
										口试总分
		          		</td>
		          		<td align="center">
										<input type="text" name="OralExamTotal__" style="width: 100px" value="<?php echo $grades[0]['OralExamTotal']; ?>" />
		          		</td>
								</tr>
			        	<tr>
			        		<td>&nbsp;</td>
			        		<td>&nbsp;</td>
								</tr>
		          	<tr>
		          		<td align="center">
										完成作业
		          		</td>
		          		<td align="center">
										<input type="text" name="HomeworkCompletion__" style="width: 100px" value="<?php echo $grades[0]['HomeworkCompletion']; ?>" />
		          		</td>
								</tr>
		          	<tr>
		          		<td align="center">
										测验成绩
		          		</td>
		          		<td align="center">
										<input type="text" name="Quiz__" style="width: 100px" value="<?php echo $grades[0]['Quiz']; ?>" />
		          		</td>
								</tr>
		          	<tr>
		          		<td align="center">
										考勤
		          		</td>
		          		<td align="center">
										<input type="text" name="Attendance__" style="width: 100px" value="<?php echo $grades[0]['Attendance']; ?>" />
		          		</td>
								</tr>
		          	<tr>
		          		<td align="center">
										课堂表现
		          		</td>
		          		<td align="center">
										<input type="text" name="Participation__" style="width: 100px" value="<?php echo $grades[0]['Participation']; ?>" />
		          		</td>
								</tr>
		          	<tr>
		          		<td align="center">
										说中文
		          		</td>
		          		<td align="center">
										<input type="text" name="ChineseSpeaking__" style="width: 100px" value="<?php echo $grades[0]['ChineseSpeaking']; ?>" />
		          		</td>
								</tr>
			        	<tr>
			        		<td>&nbsp;</td>
			        		<td>&nbsp;</td>
								</tr>
		          	<tr>
		          		<td align="center">
										学期总评
		          		</td>
		          		<td align="center">
										<input type="text" name="Grade__" style="width: 100px" value="<?php echo $grades[0]['Grade']; ?>" />
		          		</td>
								</tr>
		          </table>
		        </td>
		      </tr>
<?php
	}
?>
        	<tr height="50">
        		<td>&nbsp;</td>
					</tr>
		    </table>
		  </td>
		</tr>
	</table>
	<script type="text/javascript">
		function CheckAssignGrade() { 
			var found = false;
			for (i = 0; i < document.form1.elements.length; i++) {
				if (document.form1.elements[i].name.substr(0, 6) == "Grade_") {
					found = true;
					break;
				}
			}
			if (!found) {
				alert('No student has been registered for selected class.');
				return false;
			}
			return true;
		}
	</script>
	<table border="0" width="500" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td align="right">
				<input type="button" name="Submit" value="Back to management page" style="width: 180px;font-size: 12px;"
				onClick="document.form1.subjectid__.value='CANCELSUBTASK';document.form1.subtask__.value='';document.form1.submit();" />
				<input type="button" name="Submit" value="Submit" style="width: 100px;font-size: 12px;"
				onClick="if (CheckAssignGrade()){document.form1.subjectid__.value='GRADE';document.form1.subtask__.value='submit_grade_tracking';document.form1.submit();}" />
		  </td>
		</tr>
	</table>
<?php
}

/**
 *
 * @name 		AdminTemplate_Grade_ViewReport
 * @args 		0
 * @return	website template
 * @desc		
 *
 **/
function AdminTemplate_Grade_ViewReport($pTarget) {
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

