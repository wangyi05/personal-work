<?php

/**
 *
 *
 * @version $Id$
 * @copyright 2005
 **/

/**
 *
 * @name 		GetTemplate_GRD
 * @args 		1
 * @return	template
 * @desc		registration
 *
 **/
function GetTemplate_GRD($pSubTask, $pLanguageNmbr)
{
	switch (strtok($pSubTask, '#')) {
		case "login":
			GetTemplate_Login('gradereport', $pLanguageNmbr);
			break;
		case "refresh":
			setSession();
			GetGRD_StudentGrade($pLanguageNmbr);
			break;
		case "gradeinfo":
			GetGRD_StudentGrade($pLanguageNmbr);
			break;
		default:
	}

}

/**
 *
 * @name 		GetGRD_StudentGrade
 * @args 		none
 * @return	template
 * @desc		
 *
 **/
function GetGRD_StudentGrade($pLanguageNmbr)
{
	$ref_lib = new RefLibrary();
	$school_years = $ref_lib->GetSchoolYear('all');
	$marking_periods = $ref_lib->GetRefValues('REF_MarkingPeriod');
	$familymember_hdlr = new StudentAccountHandler();
	$student_info = $familymember_hdlr->GetStudentInfo(getSession('FamilyNmbr', 0));
?>
	<form name="form1" action="fcdschool.php" method="POST">
	<table width="460" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td height="60" align="center" valign="top">
				<font size="3" color="darkred"><b>Student Grade Information</b></font><br/><br/>
			</td>
		</tr>
	</table>
	<table width="460" align="center" cellspacing="0" cellpadding="0" style="font-size: 13px;">
		<tr height="30">
			<td width="300" align="right"><b>School Year (学年）:</b></td>
			<td width="20">&nbsp;</td>
			<td width="140" align="left">
				<select name="SchoolYear__" size="1" style="width: 150px;"
				onChange="document.form1.subjectid__.value='GRADEREPORT';document.form1.subtask__.value='refresh';document.form1.submit();"
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
		<tr height="60" valign="top">
			<td align="right"><b>Marking Period （考核时段或学期）:</b></td>
			<td>&nbsp;</td>
			<td align="left">
				<select name="MarkingPeriod__" size="1" style="width: 150px;"
				onChange="document.form1.subjectid__.value='GRADEREPORT';document.form1.subtask__.value='refresh';document.form1.submit();"
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
	</table>
	<table width="500" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td>
				<table width="500" border="1" align="center" cellspacing="0" cellpadding="2" class="thinborder" style="font-size: 13px;">
					<tr>
						<td width="100" align="center" bgcolor="#BADBC6">Student<br/>(学生）</td>
						<td width="230" align="center" bgcolor="#BADBC6">Course<br/>（课程）</td>
						<td width="100" align="center" bgcolor="#BADBC6">Category<br/>（类别）</td>
						<td width="70" align="center" bgcolor="#BADBC6">Grade<br/>（成绩）</td>
					</tr>
<?php
	if (getSession('SchoolYear', 0) != ''
			&& getSession('MarkingPeriod', 0) != ''
			&& $student_info 
			&& sizeof($student_info) > 0) 
	{
		$grade_hdlr = new StudentGradeHandler();
		for ($i = 0; $i < sizeof($student_info); $i++) {
			$family_member_nmbr = $student_info[$i]['FamilyMemberNmbr'];
			$student_grades = $grade_hdlr->GetStudentGrade(getSession('SchoolYear', 0), getSession('MarkingPeriod', 0), '', $family_member_nmbr);
			for ($k = 0; $k < sizeof($student_grades); $k++) {
				if ($k == 0) {
?>
					<tr>
						<td><?php echo $student_info[$i]['LastName'] . ', ' . $student_info[$i]['FirstName'] . ' ' . $student_info[$i]['ChineseName'] . ''; ?></td>
						<td><?php echo $student_grades[$k]['ClassName_E'] . ' ' . $student_grades[$k]['ClassName_C'] . ''; ?>&nbsp;</td>
						<td align="center">&nbsp;</td>
						<td align="center">&nbsp;</td>
					</tr>
<?php
				}
				if (trim($student_grades[$k]['VocabDictation']) != '') {
?>
					<tr>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td align="center">生字听写</td>
						<td align="center">&nbsp;<?=$student_grades[$k]['VocabDictation']?></td>
					</tr>
<?php
				}
				if (trim($student_grades[$k]['VocabDictationExtraCredit']) != '') {
?>
					<tr>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td align="center">听写附加</td>
						<td align="center"><?=$student_grades[$k]['VocabDictationExtraCredit']?></td>
					</tr>
<?php
				}
				if (trim($student_grades[$k]['ParagraphDictation']) != '') {
?>
					<tr>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td align="center">段落听写</td>
						<td align="center"><?=$student_grades[$k]['ParagraphDictation']?></td>
					</tr>
<?php
				}
				if (trim($student_grades[$k]['SentenceMaking']) != '') {
?>
					<tr>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td align="center">造句</td>
						<td align="center"><?=$student_grades[$k]['SentenceMaking']?></td>
					</tr>
<?php
				}
				if (trim($student_grades[$k]['PassageUnderstanding']) != '') {
?>
					<tr>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td align="center">课文理解</td>
						<td align="center"><?=$student_grades[$k]['PassageUnderstanding']?></td>
					</tr>
<?php
				}
				if (trim($student_grades[$k]['ReadingComprehension']) != '') {
?>
					<tr>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td align="center">阅读理解</td>
						<td align="center"><?=$student_grades[$k]['ReadingComprehension']?></td>
					</tr>
<?php
				}
				if (trim($student_grades[$k]['WrittenExamTotal']) != '') {
?>
					<tr>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td align="center"><b>笔试总分</b></td>
						<td align="center"><b><?=$student_grades[$k]['WrittenExamTotal']?></b></td>
					</tr>
<?php
				}
				if (trim($student_grades[$k]['VocabRecognition']) != '') {
?>
					<tr>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td align="center">认读生字</td>
						<td align="center"><?=$student_grades[$k]['VocabRecognition']?></td>
					</tr>
<?php
				}
				if (trim($student_grades[$k]['PassageReading']) != '') {
?>
					<tr>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td align="center">朗读课文</td>
						<td align="center"><?=$student_grades[$k]['PassageReading']?></td>
					</tr>
<?php
				}
				if (trim($student_grades[$k]['PassageRecording']) != '') {
?>
					<tr>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td align="center">课文录音</td>
						<td align="center"><?=$student_grades[$k]['PassageRecording']?></td>
					</tr>
<?php
				}
				if (trim($student_grades[$k]['PassageReadingExtraCredit']) != '') {
?>
					<tr>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td align="center">阅读录音附加</td>
						<td align="center"><?=$student_grades[$k]['PassageReadingExtraCredit']?></td>
					</tr>
<?php
				}
				if (trim($student_grades[$k]['OralExamTotal']) != '') {
?>
					<tr>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td align="center"><b>口试总分</b></td>
						<td align="center"><b><?=$student_grades[$k]['OralExamTotal']?></b></td>
					</tr>
<?php
				}
				if (trim($student_grades[$k]['HomeworkCompletion']) != '') {
?>
					<tr>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td align="center">完成作业</td>
						<td align="center"><?=$student_grades[$k]['HomeworkCompletion']?></td>
					</tr>
<?php
				}
				if (trim($student_grades[$k]['Quiz']) != '') {
?>
					<tr>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td align="center">测验成绩</td>
						<td align="center"><?=$student_grades[$k]['Quiz']?></td>
					</tr>
<?php
				}
				if (trim($student_grades[$k]['Attendance']) != '') {
?>
					<tr>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td align="center">考勤</td>
						<td align="center"><?=$student_grades[$k]['Attendance']?></td>
					</tr>
<?php
				}
				if (trim($student_grades[$k]['Participation']) != '') {
?>
					<tr>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td align="center">课堂表现</td>
						<td align="center"><?=$student_grades[$k]['Participation']?></td>
					</tr>
<?php
				}
				if (trim($student_grades[$k]['ChineseSpeaking']) != '') {
?>
					<tr>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td align="center">说中文</td>
						<td align="center"><?=$student_grades[$k]['ChineseSpeaking']?></td>
					</tr>
<?php
				}
				if (trim($student_grades[$k]['Grade']) != '') {
?>
					<tr>
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<td align="center"><b>学期总评</b></td>
						<td align="center"><b><?=$student_grades[$k]['Grade']?></b></td>
					</tr>
<?php
				}
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
	<input type="hidden" name="subjectid__" value="" />
	<input type="hidden" name="subtask__" value="" />
	<input type="hidden" name="languagenmbr__" value="<?php echo $pLanguageNmbr; ?>" />
	</form>
<?php
}

?>
