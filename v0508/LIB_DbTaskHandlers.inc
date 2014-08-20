<?php

/**
 *
 * @version $Id$
 * @copyright 2005
 * 
 * class StudentAccountHandler
 * class RegistrationHandler
 * class StudentGradeHandler
 * class CurriculumHandler
 * class StaffAccountHandler
 * class TuitionFeeHandler
 * class RefLibrary
 *
 **/

/**
 * Handle student account related tasks
 *
 **/
class StudentAccountHandler {
	var $cDbUtil;

	/**
	 * Constructor
	 * @param 
	 */
	function StudentAccountHandler() {
		$this->cDbUtil = new DbUtil();
	}
	
	/**
	 * Check login
	 * @param string $pUserName MD5 encrypted
	 * @param string $pPassword MD5 encrypted
	 * @return bool $status
	 */ 
	function CheckLogin($pUserName, $pPassword) {
		$status = $this->cDbUtil->SelectTable("SCHL_Family", "*", "UserName", "'" . $pUserName . "'", 'Password', "'" . $pPassword . "'");
		return $status;
	}

	/**
	 * Get family information
	 * @param zero or one param.  If one, family_nmbr 
	 * @return mixed (result set or bool)
	 */
	function GetFamilyInfo() {
		$argnum = func_num_args();
		$arglist = func_get_args();
		
		$l_sql = "select * from SCHL_Family";
		if ($argnum == 1) $l_sql = $l_sql . " where FamilyNmbr = " . $arglist[0];
		if ($l_rst = $this->cDbUtil->SelectTable($l_sql)) {
			return $l_rst;
		}
		else {
			return false;
		}
	}

	/**
	 * Get student information
	 * @param zero or one param.  If one, family_nmbr 
	 * @return mixed (result set or bool)
	 */
		function GetStudentInfo() {
		/*************
		usage:
		GetStudentInfo();  <- all students
		GetStudentInfo(family_nmbr);
		*************/
		$argnum = func_num_args();
		$arglist = func_get_args();
		
		$l_sql = "select * from SCHL_FamilyMember where FcdRoleNmbr = 7";
		if ($argnum == 1) $l_sql = $l_sql . " and FamilyNmbr = " . $arglist[0];
		if ($l_rst = $this->cDbUtil->SelectTable($l_sql)) {
			return $l_rst;
		}
		else {
			return false;
		}
	}

	/**
	 * Get family and family member information
	 * @param integer $pFamilyNmbr
	 * @param integer $pRoleNmbr1, ... one or more role numbers 
	 * @return mixed (result set or bool)
	 */
		function GetFamilyAndFamilyMemberInfo() {
		/*************
		usage:
		GetFamilyAndFamilyMemberInfo(family_nmbr);  <- all family members
		GetFamilyAndFamilyMemberInfo(family_nmbr, role_nmbr1, role_nmbr2, ...);
		*************/
		$argnum = func_num_args();
		$arglist = func_get_args();
		
		$l_sql = "select a.*, b.*, c.FcdRole_E, c.FcdRole_C "
           . "from "
           . "SCHL_Family a, "
           . "SCHL_FamilyMember b, "
           . "REF_FcdRole c "
					 . "where a.FamilyNmbr = " . $arglist[0] . " and b.FamilyNmbr = a.FamilyNmbr and c.FcdRoleNmbr = b.FcdRoleNmbr ";
		if ($argnum > 1) {
			for ($i = 1; $i < $argnum; $i++) {
				if ($i == 1) $l_sql = $l_sql . " and (b.FcdRoleNmbr = " . $arglist[$i];
				else $l_sql = $l_sql . " or b.FcdRoleNmbr = " . $arglist[$i];
			}
			$l_sql = $l_sql . ")";
		}
		if ($l_rst = $this->cDbUtil->SelectTable($l_sql)) {
			return $l_rst;
		}
		else {
			return false;
		}
	}

	/**
	 * Get parent information
	 * @param integer @pFamilyNmbr 
	 * @return mixed (result set or bool)
	 */
		function GetParentInfo($pFamilyNmbr) {
		$l_info = "";
		$l_sql = "select a.*, b.FcdRole_E, b.FcdRole_C from SCHL_FamilyMember a, REF_FcdRole b "
					 . "where (a.FcdRoleNmbr = 5 or a.FcdRoleNmbr = 6) and b.FcdRoleNmbr = a.FcdRoleNmbr and a.FamilyNmbr = " . $pFamilyNmbr;
		if ($l_rst = $this->cDbUtil->SelectTable($l_sql)) {
			for ($i = 0; $i < sizeof($l_rst); $i++) {
				$l_info = $l_info . $l_rst[$i]['LastName'] . " " . $l_rst[$i]['FirstName'] . " (" . $l_rst[$i]['ChineseName'] . ") ";
			}
			return trim($l_info);
		}
		else {
			return false;
		}
	}

	/**
	 * Create family
	 * @param string $pFamilyID
	 * @param string $pUserName
	 * @param string $pPassword
	 * @param string $pStreet
	 * @param string $pCity
	 * @param string $pSate
	 * @param $pZip
	 * @param $pHomeTelephone
	 * @param $pEmail
	 * @return integer $l_familynmbr
	 */
		function CreateFamily($pFamilyID, $pUserName, $pPassword, $pStreet, $pCity, $pState, $pZip, $pHomeTelephone, $pEmail) {
		$l_familynmbr = $this->cDbUtil->InsertTable(
				"SCHL_Family",
				"FamilyNmbr",
				"'" . $pFamilyID . "'",
				"'" . $pUserName . "'",
				"'" . $pPassword . "'",
				"'" . $pStreet . "'",
				"'" . $pCity . "'",
				"'" . $pState . "'",
				"'" . $pZip . "'",
				"'" . $pHomeTelephone . "'",
				"'" . $pEmail . "'",
				"CURRENT_TIMESTAMP",
				"''"
			);
		if ($pFamilyID == '') {
			$l_family_id = "FCDID" . str_pad($l_familynmbr, 4, "0", STR_PAD_LEFT);
			$l_updatesql = "Update SCHL_Family set FamilyID = '" . $l_family_id . "' where FamilyNmbr = " . $l_familynmbr;
			$this->cDbUtil->RunSQL($l_updatesql);
		}
		return $l_familynmbr;
	}
	
	/**
	 * Create password using random numbers
	 * @param string $pUserName 
	 * @return string $l_passwd
	 */
		function CreatePassword($pUserName) {
		$l_passwd = substr($pUserName, 0, 1) . substr($pUserName, -1, 1) . rand(1000, 10000);
		return $l_passwd;
	}
	
	/**
	 * Update family information
	 * @param integer $pFamilyNmbr
	 * @param string $pUserName
	 * @param string $pPassword
	 * @param string $pStreet
	 * @param string $pCity
	 * @param string $pSate
	 * @param $pZip
	 * @param $pHomeTelephone
	 * @param $pEmail
	 * @return bool $l_status
	 */
		function UpdateFamily($pFamilyNmbr, $pUserName, $pPassword, $pStreet, $pCity, $pState, $pZip, $pHomeTelephone, $pEmail) {
		$l_updatesql = "Update SCHL_Family set " .
				"UserName = '" . $pUserName . "', ";
		if (trim($pPassword) != '') $l_updatesql = $l_updatesql . "Password = '" . $pPassword . "', ";
		$l_updatesql = $l_updatesql .
				"Street = '" . $pStreet . "', " .
				"City = '" . $pCity . "', " .
				"State = '" . $pState . "', " .
				"ZipCode = '" . $pZip . "', " .
				"HomeTelephone = '" . $pHomeTelephone . "', " .
				"Email = '" . $pEmail . "', " .
				"UpdatedDate = CURRENT_TIMESTAMP " .
				"where FamilyNmbr = " . $pFamilyNmbr;
		$l_status = $this->cDbUtil->RunSQL($l_updatesql);
		return $l_status;
	}
	
	/**
	 * Update family login username and password
	 * @param integer $pFamilyNmbr
	 * @param string $pUserName
	 * @param string $pPassword
	 * @return bool $l_status
	 */
		function UpdateFamilyLogin($pFamilyNmbr, $pUserName, $pPassword) {
		$l_updatesql = "Update SCHL_Family set " .
				"UserName = '" . $pUserName . "', " .
				"Password = '" . $pPassword . "' " .
				"where FamilyNmbr = " . $pFamilyNmbr;
		$l_status = $this->cDbUtil->RunSQL($l_updatesql);
		return $l_status;
	}
	
	/**
	 * Create family member
	 * @param integer $pFamilyNmbr
	 * @param string $pFamilyRole
	 * @param string $pLastName
	 * @param string $pFirstName
	 * @param string $pMiddleName
	 * @param string $pChineseName
	 * @param $pGender
	 * @param $pBirthDate
	 * @param $pWorkTelephone
	 * @param $pEmail
	 * @param $pIsAdult
	 * @return integer $l_familymembernmbr
	 */
		function CreateFamilyMember($pFamilyNmbr, $pFamilyRole, $pLastName, $pFirstName, $pMiddleName, $pChineseName, $pGender, $pBirthDate, $pWorkTelephone, $pEmail, $pIsAdult) {
		$l_familymembernmbr = $this->cDbUtil->InsertTable(
				"SCHL_FamilyMember",
				"FamilyMemberNmbr",
				$pFamilyNmbr,
				"'" . $pFamilyRole . "'",
				"'" . $pLastName . "'",
				"'" . $pFirstName . "'",
				"'" . $pMiddleName . "'",
				"'" . $pChineseName . "'",
				"'" . $pGender . "'",
				"'" . $pBirthDate . "'",
				"'" . $pWorkTelephone . "'",
				"'" . $pEmail . "'",
				"'" . $pIsAdult . "'"
			);
		return $l_familymembernmbr;
	}
	
	/**
	 * Update family member
	 * @param integer $pFamilyMemberNmbr
	 * @param integer $pFcdRoleNmbr
	 * @param string $pLastName
	 * @param string $pFirstName
	 * @param string $pMiddleName
	 * @param string $pChineseName
	 * @param $pGender
	 * @param $pBirthDate
	 * @param $pWorkTelephone
	 * @param $pEmail
	 * @param $pIsAdult
	 * @return bool $l_status
	 */
		function UpdateFamilyMember($pFamilyMemberNmbr, $pFcdRoleNmbr, $pLastName, $pFirstName, $pMiddleName, $pChineseName, $pGender, $pBirthDate, $pWorkTelephone, $pEmail, $pIsAdult) {
		$l_updatesql = "Update SCHL_FamilyMember set " .
				"FcdRoleNmbr = " . $pFcdRoleNmbr . ", " .
				"LastName = '" . $pLastName . "', " .
				"FirstName = '" . $pFirstName . "', " .
				"MiddleName = '" . $pMiddleName . "', " .
				"ChineseName = '" . $pChineseName . "', " .
				"Gender = '" . $pGender . "', " .
				"BirthDate = '" . $pBirthDate . "', " .
				"WorkTelephone = '" . $pWorkTelephone . "', " .
				"Email = '" . $pEmail . "', " .
				"IsAdult = '" . $pIsAdult . "' " .
				"where FamilyMemberNmbr = " . $pFamilyMemberNmbr;
		$l_status = $this->cDbUtil->RunSQL($l_updatesql);
		return $l_status;
	}

	/**
	 * Delete family member
	 * @param integer $pFamilyMemberNmbr
	 * @return bool $l_status
	 */
		function DeleteFamilyMember($pFamilyMemberNmbr) {
		$l_updatesql = "Delete from SCHL_FamilyMember where FamilyMemberNmbr = " . $pFamilyMemberNmbr;
		$l_status = $this->cDbUtil->RunSQL($l_updatesql);
		return $l_status;
	}
	
}

/**
 *
 * @name 			RegistrationHandler
 * @type 			Class
 * @desc			
 * @function 	RegistrationHandler()
 *
 **/
class RegistrationHandler {
	var $cDbUtil;

	////// constructor
	function RegistrationHandler() {
		$this->cDbUtil = new DbUtil();
	}
	
	////// GetRegistration
	function GetRegistration($pSchoolYear, $pClassNmbr, $pFamilyMemberNmbr, $pFamilyNmbr, $pRegistrationNmbr) {
		
		$l_sql = "select a.*, b.LastName, b.FirstName, b.ChineseName, c.ClassNmbr, c.ClassroomNmbr, c.ClassPeriodNmbr, c.ClassName_E, c.ClassName_C, d.CourseCategoryNmbr "
					 . "from SCHL_CourseRegistration a, SCHL_FamilyMember b, SCHL_Class c, SCHL_Course d "
					 . "where b.FamilyMemberNmbr = a.FamilyMemberNmbr and c.ClassNmbr = a.ClassNmbr and d.CourseNmbr = c.CourseNmbr ";
		if ($pSchoolYear != '') {
			$l_sql = $l_sql . " and a.SchoolYear = '" . $pSchoolYear . "' ";
		}
		if ($pClassNmbr != '') {
			$l_sql = $l_sql . " and a.ClassNmbr = " . $pClassNmbr;
		}
		if ($pFamilyMemberNmbr != '') {
			$l_sql = $l_sql . " and b.FamilyMemberNmbr = " . $pFamilyMemberNmbr;
		}
		if ($pFamilyNmbr != '') {
			$l_sql = $l_sql . " and b.FamilyNmbr = " . $pFamilyNmbr;
		}
		if ($pRegistrationNmbr != '') {
			$l_sql = $l_sql . " and a.RegistrationNmbr = " . $pRegistrationNmbr;
		}
		$l_sql = $l_sql . " order by a.FamilyMemberNmbr";
		if ($l_rst = $this->cDbUtil->SelectTable($l_sql)) {
			return $l_rst;
		}
		else {
			return false;
		}
	}

	////// CreateNewRegistration
	function CreateNewRegistration($pFamilyMemberNmbr, $pClassNmbr, $pSchoolYear) {
		if ($l_coursetuitionnmbr = $this->_GetTuitionNmbr($pClassNmbr, $pSchoolYear)) {
			$l_regnmbr = $this->cDbUtil->InsertTable(
					"SCHL_CourseRegistration",
					"RegistrationNmbr",
					$pFamilyMemberNmbr,
					$pClassNmbr,
					"'" . $pSchoolYear . "'",
					$l_coursetuitionnmbr
				);
			return $l_regnmbr;
		}
		else {
			return false;
		}
	}
	
	////// UpdateRegistration
	function UpdateRegistration($pRegistrationNmbr, $pClassNmbr, $pSchoolYear) {
		if ($l_coursetuitionnmbr = $this->_GetTuitionNmbr($pClassNmbr, $pSchoolYear)) {
			$l_updatesql = "Update SCHL_CourseRegistration set " .
					"ClassNmbr = " . $pClassNmbr . ", " .
					"SchoolYear = '" . $pSchoolYear . "', " .
					"TuitionNmbr = " . $l_coursetuitionnmbr . " " .
					"where RegistrationNmbr = " . $pRegistrationNmbr;
			$l_status = $this->cDbUtil->RunSQL($l_updatesql);
			return $l_status;
		}
		else {
			return false;
		}
	}

	////// _GetTuitionNmbr
	function _GetTuitionNmbr($pClassNmbr, $pSchoolYear) {
		$l_sql = "select c.TuitionNmbr " .
						 "from SCHL_Class a, " .
						 "SCHL_Course b, " .
						 "SCHL_Tuition c " .
						 "where a.ClassNmbr = " . $pClassNmbr . " " .
						 "and b.CourseNmbr = a.CourseNmbr " .
						 "and c.CourseCategoryNmbr = b.CourseCategoryNmbr " .
						 "and c.SchoolYear = '" . $pSchoolYear . "' ";
		if ($l_rst = $this->cDbUtil->SelectTable($l_sql)) {
			return $l_rst[0]['TuitionNmbr'];
		}
		else {
			return false;
		}
	}

	////// DeleteRegistration
	function DeleteRegistration($pRegistrationNmbr) {
		$l_updatesql = "Delete from SCHL_CourseRegistration where RegistrationNmbr = " . $pRegistrationNmbr;
		$l_status = $this->cDbUtil->RunSQL($l_updatesql);
		return $l_status;
	}
	
}

/**
 *
 * @name 			StudentGradeHandler
 * @type 			Class
 * @desc			
 * @function 	StudentGradeHandler()
 *
 **/
class StudentGradeHandler {
	var $cDbUtil;

	////// constructor
	function StudentGradeHandler() {
		$this->cDbUtil = new DbUtil();
	}
	
	////// GetStudentGrade
	function GetStudentGrade() {
		/*************
		usage:
		GetStudentGrade(school_year, marking_period, class_nmbr);  <- all student
		GetStudentGrade(school_year, marking_period, '', family_member_nmbr);  <- all class for a student
		GetStudentGrade(school_year, marking_period, class_nmbr, family_member_nmbr);
		*************/
		$argnum = func_num_args();
		$arglist = func_get_args();
		
		$l_sql = "select a.*, b.ClassName_E, b.ClassName_C from SCHL_StudentGrade a, SCHL_Class b "
					 . "where a.SchoolYear = '" . $arglist[0] . "' and a.MarkingPeriod = '" . $arglist[1] . "' "
					 . "and b.ClassNmbr = a.ClassNmbr ";
		if ($arglist[2] != '') {
			$l_sql = $l_sql . "and a.ClassNmbr = " . $arglist[2] . " ";
		}
		if ($argnum > 3) {
			$l_sql = $l_sql . "and a.FamilyMemberNmbr = " . $arglist[3];
		}
		if ($l_rst = $this->cDbUtil->SelectTable($l_sql)) {
			return $l_rst;
		}
		else {
			return false;
		}
	}

	////// UpdateStudentGrade
	function UpdateStudentGrade(
		$pFamilyMemberNmbr, 
		$pSchoolYear, 
		$pClassNmbr, 
		$pMarkingPeriod, 
		$pVocabDictation,
		$pVocabDictationExtraCredit,
		$pParagraphDictation,
		$pSentenceMaking,
		$pPassageUnderstanding,
		$pReadingComprehension,
		$pWrittenExamTotal,
		$pVocabRecognition,
		$pPassageReading,
		$pPassageRecording,
		$pPassageReadingExtraCredit,
		$pOralExamTotal,
		$pHomeworkCompletion,
		$pQuiz,
		$pAttendance,
		$pParticipation,
		$pChineseSpeaking,
		$pGrade
	) {
		if ($l_grade_info = $this->GetStudentGrade($pSchoolYear, $pMarkingPeriod, $pClassNmbr, $pFamilyMemberNmbr)) {
			// update 
			$l_gradenmbr  = $l_grade_info[0]['StudentGradeNmbr'];
			$l_updatesql = "Update SCHL_StudentGrade set " .
					"VocabDictation = '" . $pVocabDictation . "', " .
					"VocabDictationExtraCredit = '" . $pVocabDictationExtraCredit . "', " .
					"ParagraphDictation = '" . $pParagraphDictation . "', " .
					"SentenceMaking = '" . $pSentenceMaking . "', " .
					"PassageUnderstanding = '" . $pPassageUnderstanding . "', " .
					"ReadingComprehension = '" . $pReadingComprehension . "', " .
					"WrittenExamTotal = '" . $pWrittenExamTotal . "', " .
					"VocabRecognition = '" . $pVocabRecognition . "', " .
					"PassageReading = '" . $pPassageReading . "', " .
					"PassageRecording = '" . $pPassageRecording . "', " .
					"PassageReadingExtraCredit = '" . $pPassageReadingExtraCredit . "', " .
					"OralExamTotal = '" . $pOralExamTotal . "', " .
					"HomeworkCompletion = '" . $pHomeworkCompletion . "', " .
					"Quiz = '" . $pQuiz . "', " .
					"Attendance = '" . $pAttendance . "', " .
					"Participation = '" . $pParticipation . "', " .
					"ChineseSpeaking = '" . $pChineseSpeaking . "', " .
					"Grade = '" . $pGrade . "' " .
					"where StudentGradeNmbr = " . $l_gradenmbr;
			if (!$this->cDbUtil->RunSQL($l_updatesql)) {
				return false;
			}		
		}
		else {
			// insert
			$l_gradenmbr = $this->cDbUtil->InsertTable(
					"SCHL_StudentGrade",
					"StudentGradeNmbr",
					$pFamilyMemberNmbr,
					$pClassNmbr,
					"'" . $pSchoolYear . "'",
					"'" . $pMarkingPeriod . "'",
					"'" . $pVocabDictation . "'",
					"'" . $pVocabDictationExtraCredit . "'",
					"'" . $pParagraphDictation . "'",
					"'" . $pSentenceMaking . "'",
					"'" . $pPassageUnderstanding . "'",
					"'" . $pReadingComprehension . "'",
					"'" . $pWrittenExamTotal . "'",
					"'" . $pVocabRecognition . "'",
					"'" . $pPassageReading . "'",
					"'" . $pPassageRecording . "'",
					"'" . $pPassageReadingExtraCredit . "'",
					"'" . $pOralExamTotal . "'",
					"'" . $pHomeworkCompletion . "'",
					"'" . $pQuiz . "'",
					"'" . $pAttendance . "'",
					"'" . $pParticipation . "'",
					"'" . $pChineseSpeaking . "'",
					"'" . $pGrade . "'"
			);
		}
		return $l_gradenmbr;
	}
	
	////// DeleteStudentGrade
	function DeleteStudentGrade($pSchoolYear, $pClassNmbr, $pMarkingPeriod) {
		$l_updatesql = "Delete from SCHL_StudentGrade where SchoolYear = '" . $pSchoolYear . "' "
								 . "and ClassNmbr = " . $pClassNmbr . " "
								 . "and MarkingPeriod = '" . $pMarkingPeriod . "'";
		$l_status = $this->cDbUtil->RunSQL($l_updatesql);
		return $l_status;
	}
	
}

/**
 *
 * @name 			CurriculumHandler
 * @type 			Class
 * @desc			
 * @function 	CurriculumHandler()
 *
 **/
class CurriculumHandler {
	var $cDbUtil;

	////// constructor
	function CurriculumHandler() {
		$this->cDbUtil = new DbUtil();
	}
	
	////// GetCourse
	function GetCourse() {
		/*************
		usage:
		GetCourse();  <- all courses
		GetCourse(course_nmbr);
		*************/
		$argnum = func_num_args();
		$arglist = func_get_args();

		$l_sql = "select a.*, b.CourseCategory_E, b.CourseCategory_C from SCHL_Course a, REF_CourseCategory b "
					 . "where b.CourseCategoryNmbr = a.CourseCategoryNmbr";
		if ($argnum == 1) $l_sql = $l_sql . " and a.CourseNmbr = " . $arglist[0];
		if ($l_rst = $this->cDbUtil->SelectTable($l_sql)) {
			return $l_rst;
		}
		else {
			return false;
		}
	}

	////// GetClass
	function GetClass() {
		/*************
		usage:
		GetClass();  <- all classes
		GetClass(course_category_nmbr);
		GetClass('', class_nmbr);
		*************/
		$argnum = func_num_args();
		$arglist = func_get_args();
		
    if (getSession('LoginRole', 0) == 'Teacher') {
		  $l_sql = "select a.*, b.CourseName_E, b.CourseName_C from SCHL_Class a, SCHL_Course b, SCHL_TeachingAssignment c "
             . "where c.StaffNmbr = " . getSession('LoginNmbr', 0) . " and a.ClassNmbr = c.ClassNmbr and b.CourseNmbr = a.CourseNmbr";
    }
    else {
		  $l_sql = "select a.*, b.CourseName_E, b.CourseName_C from SCHL_Class a, SCHL_Course b where b.CourseNmbr = a.CourseNmbr";
    }
		if ($argnum == 1) $l_sql = $l_sql . " and b.CourseCategoryNmbr = " . $arglist[0];
		if ($argnum == 2) $l_sql = $l_sql . " and a.ClassNmbr = " . $arglist[1];
		if ($l_rst = $this->cDbUtil->SelectTable($l_sql)) {
			return $l_rst;
		}
		else {
			return false;
		}
	}

	////// BuildClass
	function BuildClass($pCourseNmbr, $pCourseLevelNmbr, $pClassroomNmbr, $pClassPeriodNmbr, $pClassName_E, $pClassName_C) {
		$l_classnmbr = $this->cDbUtil->InsertTable(
				"SCHL_Class",
				"ClassNmbr",
				$pCourseNmbr,
				$pCourseLevelNmbr,
				$pClassroomNmbr,
				$pClassPeriodNmbr,
				"'" . $pClassName_E . "'",
				"'" . $pClassName_C . "'"
			);
		return $l_classnmbr;
	}
	
	////// UpdateClass
	function UpdateClass($pClassNmbr, $pCourseNmbr, $pCourseLevelNmbr, $pClassroomNmbr, $pClassPeriodNmbr, $pClassName_E, $pClassName_C) {
		$l_updatesql = "Update SCHL_Class set " .
				"CourseNmbr = " . $pCourseNmbr . ", " .
				"CourseLevelNmbr = " . $pCourseLevelNmbr . ", " .
				"ClassroomNmbr = " . $pClassroomNmbr . ", " .
				"ClassPeriodNmbr = " . $pClassPeriodNmbr . ", " .
				"ClassName_E = " . "'" . $pClassName_E . "', " .
				"ClassName_C = " . "'" . $pClassName_C . "' " .
				"where ClassNmbr = " . $pClassNmbr;
		$l_status = $this->cDbUtil->RunSQL($l_updatesql);
		return $l_status;
	}
	
	////// DeleteClass
	function DeleteClass($pClassNmbr) {
		$l_updatesql = "Delete from SCHL_Class where ClassNmbr = " . $pClassNmbr;
		$l_status = $this->cDbUtil->RunSQL($l_updatesql);
		return $l_status;
	}
	
	////// DeleteRoomClassAssignment
	function DeleteRoomClassAssignment($pClassNmbr) {
		$l_updatesql = "Delete from SCHL_Class where ClassNmbr = " . $pClassNmbr;
		$l_status = $this->cDbUtil->RunSQL($l_updatesql);
		return $l_status;
	}
	
	////// AddCourse
	function AddCourse($pCourseCategoryNmbr, $pCourseName_E, $pCourseName_C) {
		$l_coursenmbr = $this->cDbUtil->InsertTable(
				"SCHL_Course",
				"CourseNmbr",
				$pCourseCategoryNmbr,
				"'" . $pCourseName_E . "'",
				"'" . $pCourseName_C . "'"
			);
		return $l_coursenmbr;
	}
	
	////// UpdateCourse
	function UpdateCourse($pCourseNmbr, $pCourseCategoryNmbr, $pCourseName_E, $pCourseName_C) {
		$l_updatesql = "Update SCHL_Class set " .
				"CourseCategoryNmbr = " . $pCourseCategoryNmbr . ", " .
				"CourseName_E = " . "'" . $pCourseName_E . "', " .
				"CourseName_C = " . "'" . $pCourseName_C . "' " .
				"where CourseNmbr = " . $pCourseNmbr;
		$l_status = $this->cDbUtil->RunSQL($l_updatesql);
		return $l_status;
	}
	
	////// DeleteCourse
	function DeleteCourse($pCourseNmbr) {
		$l_updatesql = "Delete from SCHL_Course where CourseNmbr = " . $pCourseNmbr;
		$l_status = $this->cDbUtil->RunSQL($l_updatesql);
		return $l_status;
	}
	
}

/**
 *
 * @name 			StaffAccountHandler
 * @type 			Class
 * @desc			
 * @function 	StaffAccountHandler()
 *
 **/
class StaffAccountHandler {
	var $cDbUtil;

	////// constructor
	function StaffAccountHandler() {
		$this->cDbUtil = new DbUtil();
	}
	
	////// CheckLogin
	function CheckLogin($pUserName, $pPassword) {
		$l_sql = "select a.*, b.FcdRole_E from SCHL_Staff a, REF_FcdRole b where b.FcdRoleNmbr = a.FcdRoleNmbr and a.UserName = '" . $pUserName . "' and a.Password = '" . $pPassword . "'";		
		return $this->cDbUtil->SelectTable($l_sql);
	}

	////// GetStaffRoles
	function GetStaffRoles() {
		$l_sql = "select * from REF_FcdRole where FcdRoleNmbr >= 1000";
		if ($l_rst = $this->cDbUtil->SelectTable($l_sql)) {
			return $l_rst;
		}
		else {
			return false;
		}
	}

	////// GetStaff
	function GetStaff() {
		/*************
		usage:
		GetStaff();  <- all staffs
		GetStaff(role_nmbr);
		*************/
		$argnum = func_num_args();
		$arglist = func_get_args();
		
		if ($argnum == 0) $l_sql = "select * from SCHL_Staff";
		if ($argnum == 1) $l_sql = "select a.*, b.FcdRole_E, b.FcdRole_C from SCHL_Staff a, REF_FcdRole b where b.FcdRoleNmbr = a.FcdRoleNmbr and b.FcdRoleNmbr = " . $arglist[0];
		if ($l_rst = $this->cDbUtil->SelectTable($l_sql)) {
			return $l_rst;
		}
		else {
			return false;
		}
	}

	////// CreateStaff
	function CreateStaff($pRoleNmbr, $pUserName, $pPassword, $pLastName, $pFirstName, $pMiddleName, $pChineseName, $pGender, $pStreet, $pCity, $pState, $pZip, $pHomeTelephone, $pWorkTelephone, $pEmail) {
		$l_familynmbr = $this->cDbUtil->InsertTable(
				"SCHL_Staff",
				"StaffNmbr",
				$pRoleNmbr,
				"'" . $pUserName . "'",
				"'" . $pPassword . "'",
				"'" . $pLastName . "'",
				"'" . $pFirstName . "'",
				"'" . $pMiddleName . "'",
				"'" . $pChineseName . "'",
				"'" . $pGender . "'",
				"'" . $pStreet . "'",
				"'" . $pCity . "'",
				"'" . $pState . "'",
				"'" . $pZip . "'",
				"'" . $pHomeTelephone . "'",
				"'" . $pWorkTelephone . "'",
				"'" . $pEmail . "'"
			);
		return $l_familynmbr;
	}
	
	////// UpdateStaff
	function UpdateStaff($pStaffNmbr, $pRoleNmbr, $pUserName, $pPassword, $pLastName, $pFirstName, $pMiddleName, $pChineseName, $pGender, $pStreet, $pCity, $pState, $pZip, $pHomeTelephone, $pWorkTelephone, $pEmail) {
		$l_updatesql = "Update SCHL_Staff set " .
				"FcdRoleNmbr = " . $pRoleNmbr . ", " .
				"LastName = '" . $pLastName . "', " .
				"FirstName = '" . $pFirstName . "', " .
				"MiddleName = '" . $pMiddleName . "', " .
				"ChineseName = '" . $pChineseName . "', " .
				"Gender = '" . $pGender . "', " .
				"Street = '" . $pStreet . "', " .
				"City = '" . $pCity . "', " .
				"State = '" . $pState . "', " .
				"ZipCode = '" . $pZip . "', " .
				"HomeTelephone = '" . $pHomeTelephone . "', " .
				"WorkTelephone = '" . $pWorkTelephone . "', " .
				"Email = '" . $pEmail . "' ";
    if ($pUserName != '' && $pPassword != '') {
      $l_updatesql = $l_updatesql . ", " .
				"UserName = '" . $pUserName . "', " .
				"Password = '" . $pPassword . "' ";
    }
    $l_updatesql = $l_updatesql .
				"where StaffNmbr = " . $pStaffNmbr;
		$l_status = $this->cDbUtil->RunSQL($l_updatesql);
		return $l_status;
	}
	
	////// UpdateStaffLogin
	function UpdateStaffLogin($pStaffNmbr, $pUserName, $pPassword) {
		$l_updatesql = "Update SCHL_Staff set " .
				"UserName = '" . $pUserName . "', " .
				"Password = '" . $pPassword . "' " .
				"where StaffNmbr = " . $pStaffNmbr;
		$l_status = $this->cDbUtil->RunSQL($l_updatesql);
		return $l_status;
	}
	
	////// GetAssignedTeachingTask
	function GetAssignedTeachingTask() {
		/*************
		usage:
		GetAssignedTeachingTask();  <- all assignment
		GetAssignedTeachingTask(assignment_nmbr);
		*************/
		$argnum = func_num_args();
		$arglist = func_get_args();

		$l_sql = "select a.*, b.LastName, b.FirstName, b.ChineseName, c.ClassName_E, c.ClassName_C "
					 . "from SCHL_TeachingAssignment a, SCHL_Staff b, SCHL_Class c "
					 . "where b.StaffNmbr = a.StaffNmbr and c.ClassNmbr = a.ClassNmbr";
		if ($argnum == 1) $l_sql = $l_sql . " and a.TeachingAssignmentNmbr = " . $arglist[0];
		if ($l_rst = $this->cDbUtil->SelectTable($l_sql)) {
			return $l_rst;
		}
		else {
			return false;
		}
	}

	////// AssignTeachingTask
	function AssignTeachingTask($pStaffNmbr, $pClassNmbr, $pSchoolYear) {
		$l_assignmentnmbr = $this->cDbUtil->InsertTable(
				"SCHL_TeachingAssignment",
				"TeachingAssignmentNmbr",
				$pStaffNmbr,
				$pClassNmbr,
				"'" . $pSchoolYear . "'"
			);
		return $l_assignmentnmbr;
	}
	
	////// UpdateTeachingTask
	function UpdateTeachingTask($pTeachingAssignmentNmbr, $pStaffNmbr, $pClassNmbr, $pSchoolYear) {
		$l_updatesql = "Update SCHL_TeachingAssignment set " .
				"StaffNmbr = " . $pStaffNmbr . ", " .
				"ClassNmbr = " . $pClassNmbr . ", " .
				"SchoolYear = '" . $pSchoolYear . "' " .
				"where TeachingAssignmentNmbr = " . $pTeachingAssignmentNmbr;
		$l_status = $this->cDbUtil->RunSQL($l_updatesql);
		return $l_status;
	}
	
	////// DeleteTeachingAssignment
	function DeleteTeachingAssignment($pTeachingAssignmentNmbr) {
		$l_updatesql = "Delete from SCHL_TeachingAssignment where TeachingAssignmentNmbr = " . $pTeachingAssignmentNmbr;
		$l_status = $this->cDbUtil->RunSQL($l_updatesql);
		return $l_status;
	}
	
}

/**
 *
 * @name 			TuitionFeeHandler
 * @type 			Class
 * @desc			
 * @function 	TuitionFeeHandler()
 *
 **/
class TuitionFeeHandler {
	var $cDbUtil;

	////// constructor
	function TuitionFeeHandler() {
		$this->cDbUtil = new DbUtil();
	}

	////// GetStatus
	function GetStatus($pFamilyNmbr) {
		$ref_lib = new RefLibrary();
		$school_years = $ref_lib->GetSchoolYear('recent_three');
		$school_year_gp = $school_years[0]['SemesterGroup'];
		
		$l_sql = "select * from SCHL_TuitionDue where SchoolYear = '" . $school_year_gp . "' and FamilyNmbr = " . $pFamilyNmbr;
		if ($l_rst = $this->cDbUtil->SelectTable($l_sql)) {
			return $l_rst;
		}
		else {
			return false;
		}
	}

	////// GetSchoolYearSemesterGroup
	function GetSchoolYearSemesterGroup($pSchoolYear, $pReturnType) {
    // return either school year array or semester group
    $schoolyears = array();
    $l_sql = "select SemesterGroup from REF_SchoolYear where SchoolYear = '" . $pSchoolYear . "'";
    if ($l_rst = $this->cDbUtil->SelectTable($l_sql)) {
      $semester_grp = $l_rst[0]['SemesterGroup'];
      if ($pReturnType == 'semester_grp') {
        return $semester_grp;
      }
      else {
        $l_sql = "select SchoolYear from REF_SchoolYear where SemesterGroup = '" . $semester_grp . "'";
        if ($l_rst = $this->cDbUtil->SelectTable($l_sql)) {
          for ($i = 0; $i < sizeof($l_rst); $i++) {
            array_push($schoolyears, $l_rst[$i]['SchoolYear']);
          }
        }
      }
    }
    return $schoolyears;
  }
  
	/****************  TuitionDue ************************/
	
	////// GetTuitionDue
	function GetTuitionDue() {
		/*************
		usage:
		GetTuitionDue(school_year);  <- all families
		GetTuitionDue(school_year, family_nmbr);
		*************/
		$argnum = func_num_args();
		$arglist = func_get_args();
		
    // get semester group
    $schoolyears = $this->GetSchoolYearSemesterGroup($arglist[0], 'school_years');
		//
    $l_sql = "select a.*, "
					 . "b.RegistrationDate, "
					 . "b.RegistrationMethod, "
           . "b.RegistrationFeeDue, "
           . "b.ManagementFeeDue, "
           . "b.LateFeeDue, "
					 . "b.TotalFeeTuition, "
					 . "b.FeeTuitionPaid, "
					 . "b.Refund, "
					 . "b.RefundCheckNmbr, "
					 . "b.Note, "
					 . "b.Status, "
					 . "b.RegistrationMethod, "
					 . "b.CheckNmbr "
					 . "from SCHL_Family a, SCHL_TuitionDue b "
					 . "where b.FamilyNmbr = a.FamilyNmbr ";
    for ($i = 0; $i < sizeof($schoolyears); $i++) {
      if ($i == 0) $l_sql = $l_sql . "and (SchoolYear = '" . $schoolyears[$i] . "' ";
      else $l_sql = $l_sql . "or SchoolYear = '" . $schoolyears[$i] . "' ";
    }
    $l_sql = $l_sql . ") ";
		if ($argnum == 2) {
			$l_sql = $l_sql . " and a.FamilyNmbr = " . $arglist[1];
		}
		if ($l_rst = $this->cDbUtil->SelectTable($l_sql)) {
			return $l_rst;
		}
		else {
			return false;
		}
	}

	////// CalculateTuitionFromDb
	function CalculateTuitionFromDb($pFamilyNmbr, $pRegMethod, $pRegDate) {
		$l_tuition = 0;
		$ref_lib = new RefLibrary();
		$semesters = $ref_lib->GetSchoolYear('recent_three');
		$current_school_year = $ref_lib->GetSchoolYear('active_year');
		// tuitions
		$l_sql = "select b.RegistrationNmbr, c.* " .
						 "from SCHL_FamilyMember a, " .
						 "SCHL_CourseRegistration b, " .
						 "SCHL_Tuition c " .
						 "where a.FamilyNmbr = " . $pFamilyNmbr . " " .
						 "and b.FamilyMemberNmbr = a.FamilyMemberNmbr " .
						 "and c.TuitionNmbr = b.TuitionNmbr " .
						 "and (b.SchoolYear = '" . $semesters[0]['SchoolYear'] . "' or b.SchoolYear = '" . $semesters[1]['SchoolYear'] . "' or b.SchoolYear = '" . $semesters[2]['SchoolYear'] . "') ";
		if ($l_rst = $this->cDbUtil->SelectTable($l_sql)) {
			for ($i = 0; $i < sizeof($l_rst); $i++) {
				$l_tuition = $l_tuition + $l_rst[$i]['Tuition'] + $l_rst[$i]['BookFee'] + $l_rst[$i]['LabFee'] + $l_rst[$i]['OtherFee'];
			}
			// registration fee
			$reg_sql = "select distinct(a.FamilyMemberNmbr) " .
							 "from SCHL_FamilyMember a, " .
							 "SCHL_CourseRegistration b " .
							 "where a.FamilyNmbr = " . $pFamilyNmbr . " " .
							 "and b.FamilyMemberNmbr = a.FamilyMemberNmbr " .
							 "and (b.SchoolYear = '" . $semesters[0]['SchoolYear'] . "' or b.SchoolYear = '" . $semesters[1]['SchoolYear'] . "' or b.SchoolYear = '" . $semesters[2]['SchoolYear'] . "') ";
			if ($student_rst = $this->cDbUtil->SelectTable($reg_sql)) {
				for ($k = 0; $k < sizeof($student_rst); $k++) {
					if ($reg_fee = $this->GetRegistrationFee($current_school_year[0]['SchoolYear'], $student_rst[$k]['FamilyMemberNmbr'], $pRegDate)) {
						$l_tuition = $l_tuition + $reg_fee[0]['RegistrationFee'];
					}
				}
			}
			// school fees
      $l_management_fee = 0;
      $l_late_fee = 0;
			if ($l_rst2 = $this->GetSchoolFees($current_school_year[0]['SchoolYear'], '', $pRegDate)) {
				for ($j = 0; $j < sizeof($l_rst2); $j++) {
					if ($l_rst2[$j]['FeeName_E'] == 'Management Fee') $l_management_fee = $l_rst2[$j]['Fee'];
					if ($l_rst2[$j]['FeeName_E'] == 'Late Fee') $l_late_fee = $l_rst2[$j]['Fee'];
          $l_tuition = $l_tuition + $l_rst2[$j]['Fee'];
				}
			}
			if ($pRegMethod == 'WEB') {
        $l_management_fee = $l_management_fee - 10;
        $l_tuition = $l_tuition - 10;
      }
      $l_tuition_info = array();
      $l_tuition_info['ManagementFeeDue'] = $l_management_fee;
      $l_tuition_info['LateFeeDue'] = $l_late_fee;
      $l_tuition_info['TuitionDue'] = $l_tuition;
			return $l_tuition_info;
		}
		else {
			return false;
		}
	}
	
	////// UpdateRegistrationFeeDue
	function UpdateRegistrationFeeDue($pFamilyMemberNmbr, $pRegistrationFeeNmbr, $pSchoolYear) {
    // get semester group
    $schoolyears = $this->GetSchoolYearSemesterGroup($pSchoolYear, 'school_years');
    $semester_grp = $this->GetSchoolYearSemesterGroup($pSchoolYear, 'semester_grp');
    // 
    $l_sql = "select * from SCHL_CourseRegistration where FamilyMemberNmbr = " . $pFamilyMemberNmbr . " ";
    for ($i = 0; $i < sizeof($schoolyears); $i++) {
      if ($i == 0) $l_sql = $l_sql . "and (SchoolYear = '" . $schoolyears[$i] . "' ";
      else $l_sql = $l_sql . "or SchoolYear = '" . $schoolyears[$i] . "' ";
    }
    $l_sql = $l_sql . ")";
    // no class regisration, delete registration due
    if (!($l_rst = $this->cDbUtil->SelectTable($l_sql))) {
		  $l_updatesql = "delete from SCHL_RegistrationFeeDue where FamilyMemberNmbr = " . $pFamilyMemberNmbr . " ";
      for ($i = 0; $i < sizeof($schoolyears); $i++) {
        if ($i == 0) $l_updatesql = $l_updatesql . "and (SchoolYear = '" . $schoolyears[$i] . "' ";
        else $l_updatesql = $l_updatesql . "or SchoolYear = '" . $schoolyears[$i] . "' ";
      }
      $l_updatesql = $l_updatesql . ")";
			$this->cDbUtil->RunSQL($l_updatesql);
    }
    else {
    // class registration exists, update registration due
      if ($pRegistrationFeeNmbr != '') {
        $l_sql = "select * from SCHL_RegistrationFeeDue where FamilyMemberNmbr = " . $pFamilyMemberNmbr . " ";
        for ($i = 0; $i < sizeof($schoolyears); $i++) {
          if ($i == 0) $l_sql = $l_sql . "and (SchoolYear = '" . $schoolyears[$i] . "' ";
          else $l_sql = $l_sql . "or SchoolYear = '" . $schoolyears[$i] . "' ";
        }
        $l_sql = $l_sql . ")";
        if (!($l_rst = $this->cDbUtil->SelectTable($l_sql))) {
			    if (!($l_regfeedue_nmbr = $this->cDbUtil->InsertTable(
					      "SCHL_RegistrationFeeDue",
					      "RegistrationFeeDueNmbr",
					      $pFamilyMemberNmbr,
                $pRegistrationFeeNmbr,
					      "'" . $pSchoolYear . "'"
				        )
              )
          ) {
            return false;
          }
        }
        else {
			    if ($pSchoolYear == $semester_grp) {
				    $l_updatesql = "update SCHL_RegistrationFeeDue set SchoolYear = '" . $pSchoolYear . " where FamilyMemberNmbr = " . $pFamilyMemberNmbr . " ";
            for ($i = 0; $i < sizeof($schoolyears); $i++) {
              if ($i == 0) $l_updatesql = $l_updatesql . "and (SchoolYear = '" . $schoolyears[$i] . "' ";
              else $l_updatesql = $l_updatesql . "or SchoolYear = '" . $schoolyears[$i] . "' ";
            }
            $l_updatesql = $l_updatesql . ")";
			      $this->cDbUtil->RunSQL($l_updatesql);
          }
        }
      }
    }
    return true;
  }

	////// UpdateTuitionDue
	function UpdateTuitionDue($pFamilyNmbr, $pSchoolYear, $pRegistrationFeeDue, $pManagementFeeDue, $pLateFeeDue, $pTuitionDue, $pTuitionPaid, $pCheckNmbr, $pRefund, $pRefundCheckNmbr, $pRegistrationDate, $pRegMethod, $pNote, $pStatus) {
    // get semester group
    $schoolyears = $this->GetSchoolYearSemesterGroup($pSchoolYear, 'school_years');
    $semester_grp = $this->GetSchoolYearSemesterGroup($pSchoolYear, 'semester_grp');
    //
		if ($pTuitionDue != '' && $pTuitionDue != 0) {
		  $l_sql = "select * from SCHL_TuitionDue where FamilyNmbr = " . $pFamilyNmbr . " ";
      for ($i = 0; $i < sizeof($schoolyears); $i++) {
        if ($i == 0) $l_sql = $l_sql . "and (SchoolYear = '" . $schoolyears[$i] . "' ";
        else $l_sql = $l_sql . "or SchoolYear = '" . $schoolyears[$i] . "' ";
      }
      $l_sql = $l_sql . ")";
      if ($l_rst = $this->cDbUtil->SelectTable($l_sql)) { // update
			  $l_updatesql = "Update SCHL_TuitionDue set ";
			  if ($pSchoolYear == $semester_grp) {
				  $l_updatesql = $l_updatesql . " SchoolYear = '" . $pSchoolYear . "', ";
        }
			  if ($pTuitionDue != '') {
				  $l_updatesql = $l_updatesql . " RegistrationUpdatedBy = " . getSession('LoginNmbr', 0) . ", ";
				  $l_updatesql = $l_updatesql . " RegistrationUpdaterRole = " . getSession('LoginRoleNmbr', 0) . ", ";
				  $l_updatesql = $l_updatesql . " RegistrationUpdatedDate = CURRENT_TIMESTAMP, ";
				  $l_updatesql = $l_updatesql . " RegistrationFeeDue = " . $pRegistrationFeeDue . ", ";
				  $l_updatesql = $l_updatesql . " ManagementFeeDue = " . $pManagementFeeDue . ", ";
				  $l_updatesql = $l_updatesql . " LateFeeDue = " . $pLateFeeDue . ", ";
				  $l_updatesql = $l_updatesql . " TotalFeeTuition = " . $pTuitionDue . ", ";
			  }
			  if ($pTuitionPaid != '') {
				  $l_updatesql = $l_updatesql . " FeeTuitionPaid = " . $pTuitionPaid . ", ";
				  if ($pCheckNmbr != '') $l_updatesql = $l_updatesql . " CheckNmbr = '" . $pCheckNmbr . "', ";
				  $l_updatesql = $l_updatesql . " ReceivedBy = " . getSession('LoginNmbr', 0) . ", ";
				  $l_updatesql = $l_updatesql . " ReceivedDate = CURRENT_TIMESTAMP, ";
			  }
			  if ($pRefund != '') {
				  $l_updatesql = $l_updatesql . " Refund = " . $pRefund . ", ";
				  if ($pRefundCheckNmbr != '') $l_updatesql = $l_updatesql . " RefundCheckNmbr = '" . $pRefundCheckNmbr . "', ";
				  $l_updatesql = $l_updatesql . " RefundBy = " . getSession('LoginNmbr', 0) . ", ";
				  $l_updatesql = $l_updatesql . " RefundDate = CURRENT_TIMESTAMP, ";
			  }
			  if ($pRegistrationDate != '') $l_updatesql = $l_updatesql . " RegistrationDate = '" . $pRegistrationDate . "', ";
			  if ($pRegMethod != '') $l_updatesql = $l_updatesql . " RegistrationMethod = '" . $pRegMethod . "', ";
			  if ($pNote != '') $l_updatesql = $l_updatesql . " Note = '" . $pNote . "', ";
			  if ($pStatus != '') $l_updatesql = $l_updatesql . " Status = '" . $pStatus . "', ";
			  $l_updatesql = rtrim(trim($l_updatesql), ',') . " where FamilyNmbr = " . $pFamilyNmbr . " and SchoolYear = '" . $pSchoolYear . "'";
			  $l_status = $this->cDbUtil->RunSQL($l_updatesql);
			  return $l_status;
		  }
		  else { // insert
			  if ($pTuitionPaid == '') $pTuitionPaid = 0;
			  $l_tuitionduenmbr = $this->cDbUtil->InsertTable(
					  "SCHL_TuitionDue",
					  "TuitionDueNmbr",
					  $pFamilyNmbr,
					  "'" . $pSchoolYear . "'",
					  "''",
					  getSession('LoginNmbr', 0),
					  getSession('LoginRoleNmbr', 0),
					  "'" . $pRegistrationDate . "'",
					  "'" . $pRegMethod . "'",
					  0,
					  0,
					  "'0000-00-00'",
            $pRegistrationFeeDue,
            $pManagementFeeDue,
            $pLateFeeDue,
					  $pTuitionDue,
					  0,
					  "''",
					  0,
					  "'0000-00-00'",
					  0,
					  "''",
					  0,
					  "'0000-00-00'",
					  "'" . $pNote . "'",
					  "'" . $pStatus . "'"
				  );
			  if ($l_tuitionduenmbr) {
				  $l_registration_id = "FCDREG" . str_pad($l_tuitionduenmbr, 4, "0", STR_PAD_LEFT);
				  $l_updatesql = "Update SCHL_TuitionDue set RegistrationID = '" . $l_registration_id . "' where TuitionDueNmbr = " . $l_tuitionduenmbr;
				  if ($this->cDbUtil->RunSQL($l_updatesql)) {
					  return $l_tuitionduenmbr;
				  }
				  else {
					  return false;
				  }
			  }
			  else {
				  return false;
			  }
		  }
    }
    else {
		  $l_updatesql = "delete from SCHL_TuitionDue where FamilyNmbr = " . $pFamilyNmbr . " and SchoolYear = '" . $pSchoolYear . "'";
			$l_status = $this->cDbUtil->RunSQL($l_updatesql);
			return $l_status;
    }
	}
	
	////// DeleteTuitionDue
	function DeleteTuitionDue($pTuitionDueNmbr) {
		$l_updatesql = "Delete from SCHL_TuitionDue where TuitionDueNmbr = " . $pTuitionDueNmbr;
		$l_status = $this->cDbUtil->RunSQL($l_updatesql);
		return $l_status;
	}
	
	/*************  Tuition *******************/
	
	////// GetTuition
	function GetTuition() {
		/*************
		usage:
		GetTuition(school_year);
		GetTuition(school_year, tuition_nmbr);
		*************/
		$argnum = func_num_args();
		$arglist = func_get_args();
		
		$l_sql = "select a.*, b.CourseCategory_E, b.CourseCategory_C " .
						 "from SCHL_Tuition a, REF_CourseCategory b " .
						 "where b.CourseCategoryNmbr= a.CourseCategoryNmbr and a.SchoolYear = '" . $arglist[0] . "' ";
		if ($argnum == 2) $l_sql = $l_sql . " and a.TuitionNmbr = " . $arglist[1];
		if ($l_rst = $this->cDbUtil->SelectTable($l_sql)) {
			return $l_rst;
		}
		else {
			return false;
		}
	}

	////// AddTuition
	function AddTuition($pCourseCategoryNmbr, $pSchoolYear, $pTuition, $pBookFee, $pLabFee, $pOtherFee, $pSessionType) {
		$l_coursetuitionnmbr = $this->cDbUtil->InsertTable(
				"SCHL_Tuition",
				"TuitionNmbr",
				$pCourseCategoryNmbr,
				"'" . $pSchoolYear . "'",
				"'" . $pTuition . "'",
				"'" . $pBookFee . "'",
				"'" . $pLabFee . "'",
				"'" . $pOtherFee . "'",
				"'" . $pSessionType . "'"
			);
		return $l_coursetuitionnmbr;
	}
	
	////// UpdateTuition
	function UpdateTuition($pTuitionNmbr, $pCourseCategoryNmbr, $pSchoolYear, $pTuition, $pBookFee, $pLabFee, $pOtherFee, $pSessionType) {
		$l_updatesql = "Update SCHL_Tuition set " .
				"CourseCategoryNmbr = " . $pCourseCategoryNmbr . ", " .
				"SchoolYear = '" . $pSchoolYear . "', " .
				"Tuition = '" . $pTuition . "', " .
				"BookFee = '" . $pBookFee . "', " .
				"LabFee = '" . $pLabFee . "', " .
				"OtherFee = '" . $pOtherFee . "', " .
				"SessionType = '" . $pSessionType . "' " .
				"where TuitionNmbr = " . $pTuitionNmbr;
		$l_status = $this->cDbUtil->RunSQL($l_updatesql);
		return $l_status;
	}
	
	////// DeleteTuition
	function DeleteTuition($pTuitionNmbr) {
		$l_updatesql = "Delete from SCHL_Tuition where TuitionNmbr = " . $pTuitionNmbr;
		$l_status = $this->cDbUtil->RunSQL($l_updatesql);
		return $l_status;
	}
	
	////// CalculateTuitionForClass
	function CalculateTuitionForClass($pClassNmbr, $pSchoolYear) {
		$l_tuition = 0;
		$l_sql = "select c.* " .
						 "from SCHL_Class a, " .
						 "SCHL_Course b, " .
						 "SCHL_Tuition c " .
						 "where a.ClassNmbr = " . $pClassNmbr . " " .
						 "and b.CourseNmbr = a.CourseNmbr " .
						 "and c.CourseCategoryNmbr = b.CourseCategoryNmbr " .
						 "and c.SchoolYear = '" . $pSchoolYear . "'";
		if ($l_rst = $this->cDbUtil->SelectTable($l_sql)) {
			return $l_rst;
		}
		else {
			return false;
		}
	}
	
	/*************  RegistrationFee *******************/
	
	////// GetRegistrationFee
	function GetRegistrationFee() {
		/*************
		usage:
		GetRegistrationFee();  <- all school_years
		GetRegistrationFee(school_year);
		GetRegistrationFee('', registrationfee_nmbr);
		GetRegistrationFee(school_year, familymember_nmbr, reg_date);
		*************/
		$argnum = func_num_args();
		$arglist = func_get_args();
		
		$status = false;
		switch ($argnum) {
			case 0:
				$l_sql = "select * from SCHL_RegistrationFee";
				if ($l_rst = $this->cDbUtil->SelectTable($l_sql)) {
					return $l_rst;
				}
				break;
			case 1:
				$l_sql = "select * from SCHL_RegistrationFee where SchoolYear = '" . $arglist[0] . "'";
				if ($l_rst = $this->cDbUtil->SelectTable($l_sql)) {
					return $l_rst;
				}
				break;
			case 2:
				$l_sql = "select * from SCHL_RegistrationFee where RegistrationFeeNmbr = " . $arglist[1];
				if ($l_rst = $this->cDbUtil->SelectTable($l_sql)) {
					return $l_rst;
				}
				break;
			case 3:
				if ($arglist[1] != 'no_check') { // need to check existance of registration
          $reg_sql = "select * from SCHL_CourseRegistration " .
								   "where FamilyMemberNmbr = " . $arglist[1];
				  if ($this->cDbUtil->SelectTable($reg_sql)) {
					  $l_sql = "select * from SCHL_RegistrationFee "
								   . "where SchoolYear = '" . $arglist[0] . "' "
								   . "and StartDate <= '" . $arglist[2] . "' "
								   . "and EndDate >= '" . $arglist[2] . "'";
					  if ($l_rst = $this->cDbUtil->SelectTable($l_sql)) {
						  return $l_rst;
					  }
				  }
        }
        else { // no need to check existance of registration -- for user website registration
					$l_sql = "select * from SCHL_RegistrationFee "
								 . "where SchoolYear = '" . $arglist[0] . "' "
								 . "and StartDate <= '" . $arglist[2] . "' "
								 . "and EndDate >= '" . $arglist[2] . "'";
					if ($l_rst = $this->cDbUtil->SelectTable($l_sql)) {
						return $l_rst;
					}
        }
				break;
			default:
		}
		return $status;
	}

	////// AddRegistrationFee
	function AddRegistrationFee($pSchoolYear, $pRegistrationFee, $pStartDate, $pEndDate) {
		$l_regfeenmbr = $this->cDbUtil->InsertTable(
				"SCHL_RegistrationFee",
				"RegistrationFeeNmbr",
				"'" . $pSchoolYear . "'",
				"'" . $pRegistrationFee . "'",
				"'" . $pStartDate . "'",
				"'" . $pEndDate . "'"
			);
		return $l_regfeenmbr;
	}
	
	////// UpdateRegistrationFee
	function UpdateRegistrationFee($pRegistrationFeeNmbr, $pSchoolYear, $pRegistrationFee, $pStartDate, $pEndDate) {
		$l_updatesql = "Update SCHL_RegistrationFee set " .
				"SchoolYear = '" . $pSchoolYear . "', " .
				"RegistrationFee = '" . $pRegistrationFee . "', " .
				"StartDate = '" . $pStartDate . "', " .
				"EndDate = '" . $pEndDate . "' " .
				"where RegistrationFeeNmbr = " . $pRegistrationFeeNmbr;
		$l_status = $this->cDbUtil->RunSQL($l_updatesql);
		return $l_status;
	}
	
	////// DeleteRegistrationFee
	function DeleteRegistrationFee($pRegistrationFeeNmbr) {
		$l_updatesql = "Delete from SCHL_RegistrationFee where RegistrationFeeNmbr = " . $pRegistrationFeeNmbr;
		$l_status = $this->cDbUtil->RunSQL($l_updatesql);
		return $l_status;
	}
	
	/*************  SchoolFees *******************/
	
	////// GetSchoolFees
	function GetSchoolFees() {
		/*************
		usage:
		GetSchoolFees();  <- all school_years
		GetSchoolFees(school_year);
		GetSchoolFees('', school_fees_nmbr);
		GetSchoolFees(school_year, '', regdate);
		*************/
		$argnum = func_num_args();
		$arglist = func_get_args();

    // get full school year
    if ($argnum == 1 || $argnum == 3) {
      if (is_int(strpos($arglist[0], 'Fall'))) {
        $schoolyear_parts = explode(' ', $pSchoolYear);
        $full_year = $schoolyear_parts[0] . '-' . ($schoolyear_parts[0] + 1);
      }
      else {
        if (is_int(strpos($arglist[0], 'Spring'))) {
          $schoolyear_parts = explode(' ', $pSchoolYear);
          $full_year = ($schoolyear_parts[0] - 1) . '-' . $schoolyear_parts[0];
        }
        else {
          $full_year = $arglist[0];
        }
      }
    }
    // sql
		$l_sql = "select * " .
						 "from SCHL_SchoolFees ";
		if ($argnum == 1) $l_sql = $l_sql . "where SchoolYear = '" . $full_year . "' ";
		if ($argnum == 2) $l_sql = $l_sql . "where SchoolFeesNmbr = '" . $arglist[1] . "' ";
		if ($argnum == 3) $l_sql = $l_sql . "where SchoolYear = '" . $full_year . "' and EffectiveDate < '" . $arglist[2] . "' ";
		if ($l_rst = $this->cDbUtil->SelectTable($l_sql)) {
			return $l_rst;
		}
		else {
			return false;
		}
	}

	////// AddSchoolFees
	function AddSchoolFees($pSchoolYear, $pFee, $pFeeName_E, $pFeeName_C, $pEffectiveDate) {
		$l_schoolfeesnmbr = $this->cDbUtil->InsertTable(
				"SCHL_SchoolFees",
				"SchoolFeesNmbr",
				"'" . $pSchoolYear . "'",
				"'" . $pFee . "'",
				"'" . $pFeeName_E . "'",
				"'" . $pFeeName_C . "'",
				"'" . $pEffectiveDate . "'"
			);
		return $l_schoolfeesnmbr;
	}
	
	////// UpdateSchoolFees
	function UpdateSchoolFees($pSchoolFeesNmbr, $pSchoolYear, $pFee, $pFeeName_E, $pFeeName_C, $pEffectiveDate) {
		$l_updatesql = "Update SCHL_SchoolFees set " .
				"SchoolYear = '" . $pSchoolYear . "', " .
				"Fee = '" . $pFee . "', " .
				"FeeName_E = '" . $pFeeName_E . "', " .
				"FeeName_C = '" . $pFeeName_C . "', " .
				"EffectiveDate = '" . $pEffectiveDate . "' " .
				"where SchoolFeesNmbr = " . $pSchoolFeesNmbr;
		$l_status = $this->cDbUtil->RunSQL($l_updatesql);
		return $l_status;
	}
	
	////// DeleteSchoolFees
	function DeleteSchoolFees($pSchoolFeesNmbr) {
		$l_updatesql = "Delete from SCHL_SchoolFees where SchoolFeesNmbr = " . $pSchoolFeesNmbr;
		$l_status = $this->cDbUtil->RunSQL($l_updatesql);
		return $l_status;
	}
	
}

/**
 *
 * @name 			AdministrativeTaskHandler
 * @type 			Class
 * @desc			
 * @function 	AdministrativeTaskHandler()
 *
 **/
class AdministrativeTaskHandler {
	var $cDbUtil;

	////// constructor
	function AdministrativeTaskHandler() {
		$this->cDbUtil = new DbUtil();
	}
	
	////// AddSchoolYear
	function AddSchoolYear($pNewSchoolYear, $pSemester, $pGroup, $pDisplayOrder) {
		$l_insertsql = "insert into REF_SchoolYear values (" .
				"'" . $pNewSchoolYear . "', " .
				"'" . $pSemester . "', " .
				"'" . $pGroup . "', " .
				$pDisplayOrder . ")";
		$l_status = $this->cDbUtil->RunSQL($l_insertsql);
		return $l_status;
	}
	
	////// UpdateSchoolYear
	function UpdateSchoolYear($pSchoolYear, $pNewSchoolYear, $pSemester, $pSemesterGroup, $pDisplayOrder) {
		$l_updatesql = "Update REF_SchoolYear set " .
				"SchoolYear = '" . $pNewSchoolYear . "', " .
				"Semester = '" . $pSemester . "', " .
				"SemesterGroup = '" . $pSemesterGroup . "', " .
				"DisplayOrder = " . $pDisplayOrder . " " .
				"where SchoolYear = '" . $pSchoolYear . "'";
		$l_status = $this->cDbUtil->RunSQL($l_updatesql);
		return $l_status;
	}
	
	////// DeleteSchoolYear
	function DeleteSchoolYear($pSchoolYear) {
		$l_updatesql = "Delete from REF_SchoolYear where SchoolYear = '" . $pSchoolYear . "'";
		$l_status = $this->cDbUtil->RunSQL($l_updatesql);
		return $l_status;
	}
	
	////// AddCourseCategory
	function AddCourseCategory($pCourseCategory_E, $pCourseCategory_C, $pCourseType) {
		$l_coursecategorynmbr = $this->cDbUtil->InsertTable(
				"REF_CourseCategory",
				"CourseCategoryNmbr",
				"'" . $pCourseCategory_E . "'",
				"'" . $pCourseCategory_C . "'",
				"'" . $pCourseType . "'"
			);
		return $l_coursecategorynmbr;
	}
	
	////// UpdateCourseCategory
	function UpdateCourseCategory($pCourseCategoryNmbr, $pCourseCategory_E, $pCourseCategory_C, $pCourseType) {
		$l_updatesql = "Update REF_CourseCategory set " .
				"CourseCategory_E = '" . $pCourseCategory_E . "', " .
				"CourseCategory_C = '" . $pCourseCategory_C . "', " .
				"CourseType = '" . $pCourseType . "' " .
				"where CourseCategoryNmbr = " . $pCourseCategoryNmbr;
		$l_status = $this->cDbUtil->RunSQL($l_updatesql);
		return $l_status;
	}
	
	////// DeleteCourseCategory
	function DeleteCourseCategory($pCourseCategoryNmbr) {
		$l_updatesql = "Delete from REF_CourseCategory where CourseCategoryNmbr = " . $pCourseCategoryNmbr;
		$l_status = $this->cDbUtil->RunSQL($l_updatesql);
		return $l_status;
	}
	
	////// AddCourseLevel
	function AddCourseLevel($pCourseLevel_E, $pCourseLevel_C) {
		$l_courselevelnmbr = $this->cDbUtil->InsertTable(
				"REF_CourseLevel",
				"CourseLevelNmbr",
				"'" . $pCourseLevel_E . "'",
				"'" . $pCourseLevel_C . "'"
			);
		return $l_courselevelnmbr;
	}
	
	////// UpdateCourseLevel
	function UpdateCourseLevel($pCourseLevelNmbr, $pCourseLevel_E, $pCourseLevel_C) {
		$l_updatesql = "Update REF_CourseLevel set " .
				"CourseLevel_E = '" . $pCourseLevel_E . "', " .
				"CourseLevel_C = '" . $pCourseLevel_C . "' " .
				"where CourseLevelNmbr = " . $pCourseLevelNmbr;
		$l_status = $this->cDbUtil->RunSQL($l_updatesql);
		return $l_status;
	}
	
	////// DeleteCourseLevel
	function DeleteCourseLevel($pCourseLevelNmbr) {
		$l_updatesql = "Delete from REF_CourseLevel where CourseLevelNmbr = " . $pCourseLevelNmbr;
		$l_status = $this->cDbUtil->RunSQL($l_updatesql);
		return $l_status;
	}
	
	////// AddClassroom
	function AddClassroom($pClassroom) {
		$l_classroomnmbr = $this->cDbUtil->InsertTable(
				"REF_Classroom",
				"ClassroomNmbr",
				"'" . $pClassroom . "'"
			);
		return $l_classroomnmbr;
	}
	
	////// UpdateClassroom
	function UpdateClassroom($pClassroomNmbr, $pClassroom) {
		$l_updatesql = "Update REF_Classroom set " .
				"Classroom = '" . $pClassroom . "' " .
				"where ClassroomNmbr = " . $pClassroomNmbr;
		$l_status = $this->cDbUtil->RunSQL($l_updatesql);
		return $l_status;
	}
	
	////// DeleteClassroom
	function DeleteClassroom($pClassroomNmbr) {
		$l_updatesql = "Delete from REF_Classroom where ClassroomNmbr = " . $pClassroomNmbr;
		$l_status = $this->cDbUtil->RunSQL($l_updatesql);
		return $l_status;
	}
	
	////// AddClassPeriod
	function AddClassPeriod($pClassPeriod_E, $pClassPeriod_C, $pClassTime) {
		$l_classperiodnmbr = $this->cDbUtil->InsertTable(
				"REF_ClassPeriod",
				"ClassPeriodNmbr",
				"'" . $pClassPeriod_E . "'",
				"'" . $pClassPeriod_C . "'",
				"'" . $pClassTime . "'"
			);
		return $l_classperiodnmbr;
	}
	
	////// UpdateClassPeriod
	function UpdateClassPeriod($pClassPeriodNmbr, $pClassPeriod_E, $pClassPeriod_C, $pClassTime) {
		$l_updatesql = "Update REF_ClassPeriod set " .
				"ClassPeriod_E = '" . $pClassPeriod_E . "', " .
				"ClassPeriod_C = '" . $pClassPeriod_C . "', " .
				"ClassTime = '" . $pClassTime . "' " .
				"where ClassPeriodNmbr = " . $pClassPeriodNmbr;
		$l_status = $this->cDbUtil->RunSQL($l_updatesql);
		return $l_status;
	}
	
	////// DeleteClassPeriod
	function DeleteClassPeriod($pClassPeriodNmbr) {
		$l_updatesql = "Delete from REF_ClassPeriod where ClassPeriodNmbr = " . $pClassPeriodNmbr;
		$l_status = $this->cDbUtil->RunSQL($l_updatesql);
		return $l_status;
	}
	
	////// AddMarkingPeriod
	function AddMarkingPeriod($pMarkingPeriod) {
		$l_insertsql = "insert into REF_MarkingPeriod values (" .
				"'" . $pMarkingPeriod . "')";
		$l_status = $this->cDbUtil->RunSQL($l_insertsql);
		return $l_status;
	}
	
	////// UpdateMarkingPeriod
	function UpdateMarkingPeriod($pMarkingPeriod, $pNewMarkingPeriod) {
		$l_updatesql = "Update REF_MarkingPeriod set " .
				"MarkingPeriod = '" . $pNewMarkingPeriod . "' " .
				"where MarkingPeriod = '" . $pMarkingPeriod . "'";
		$l_status = $this->cDbUtil->RunSQL($l_updatesql);
		return $l_status;
	}
	
	////// DeleteMarkingPeriod
	function DeleteMarkingPeriod($pMarkingPeriod) {
		$l_updatesql = "Delete from REF_MarkingPeriod where MarkingPeriod = '" . $pMarkingPeriod . "'";
		$l_status = $this->cDbUtil->RunSQL($l_updatesql);
		return $l_status;
	}
	
	////// AddFcdRole
	function AddFcdRole($pFcdRole_E, $pFcdRole_C) {
		$l_fcdrolenmbr = $this->cDbUtil->InsertTable(
				"REF_FcdRole",
				"FcdRoleNmbr",
				"'" . $pFcdRole_E . "'",
				"'" . $pFcdRole_C . "'"
			);
		return $l_fcdrolenmbr;
	}
	
	////// UpdateFcdRole
	function UpdateFcdRole($pFcdRoleNmbr, $pFcdRole_E, $pFcdRole_C) {
		$l_updatesql = "Update REF_FcdRole set " .
				"FcdRole_E = '" . $pFcdRole_E . "', " .
				"FcdRole_C = '" . $pFcdRole_C . "' " .
				"where FcdRoleNmbr = " . $pFcdRoleNmbr;
		$l_status = $this->cDbUtil->RunSQL($l_updatesql);
		return $l_status;
	}
	
	////// DeleteFcdRole
	function DeleteFcdRole($pFcdRoleNmbr) {
		$l_updatesql = "Delete from REF_FcdRole where FcdRoleNmbr = " . $pFcdRoleNmbr;
		$l_status = $this->cDbUtil->RunSQL($l_updatesql);
		return $l_status;
	}
	
	////// RunSQL
	function RunSQL() {
		$sql_array = explode(';', stripslashes(getSession('Sql', 0)));
		for ($i = 0; $i < sizeof($sql_array); $i++) {
			if (trim($sql_array[$i]) != '') {
				$l_sql = trim($sql_array[$i]);
				if (!$this->cDbUtil->RunSQL($l_sql)) {
					echo "Error running sql: " . $l_sql . "<br/>";
					return false;
				}
			}
		}
		return true;
	}
	
}

/**
 *
 * @name 			RefLibrary
 * @type 			Class
 * @desc			
 * @function 	RefLibrary()
 *
 **/
class RefLibrary {
	var $cDbUtil;

	////// constructor
	function RefLibrary() {
		$this->cDbUtil = new DbUtil();
	}
	
	////// GetRefValues
	function GetRefValues($pTableName) {
		/*************
		usage:
		GetRefValues(table_name);
		GetRefValues(table_name, column_name, column_value);
		*************/
		$argnum = func_num_args();
		$arglist = func_get_args();
		
		$l_sql = "select * from " . $arglist[0];
		if ($argnum > 1) {
      for ($i = 1; $i < ($argnum-1); $i=$i+2) {
        if ($i == 1) {
          $l_sql = $l_sql . " where " . $arglist[$i] . " = '" . $arglist[$i+1] . "' ";
        }
        else {
          $l_sql = $l_sql . " and " . $arglist[$i] . " = '" . $arglist[$i+1] . "' ";
        }
      }
    }
		if ($l_rst = $this->cDbUtil->SelectTable($l_sql)) {
			return $l_rst;
		}
		else {
			return false;
		}
	}

	////// GetSchoolYear
	function GetSchoolYear($pParam) {
		$l_sql = "select * from REF_SchoolYear";
		switch ($pParam) {
			case "all":
				$l_sql = $l_sql . " order by DisplayOrder desc";
				break;
			case "recent_three":
				$l_sql = $l_sql . " order by DisplayOrder desc limit 3";
				break;
			case "half_years":
				$l_sql = $l_sql . " where SchoolYear not like '%-%' order by DisplayOrder desc";
				break;
			case "full_years":
				$l_sql = $l_sql . " where SchoolYear like '%-%' order by DisplayOrder desc";
				break;
			case "active_year":
				$l_sql = $l_sql . " where SchoolYear like '%-%' order by DisplayOrder desc limit 1";
				break;
			default:
		}
		if ($l_rst = $this->cDbUtil->SelectTable($l_sql)) {
			return $l_rst;
		}
		else {
			return false;
		}
	}

}

/**
 *
 * @name 			ReportHandler
 * @type 			Class
 * @desc			
 * @function 	ReportHandler()
 *
 **/
class ReportHandler {
	var $cDbUtil;

	////// constructor
	function ReportHandler() {
		$this->cDbUtil = new DbUtil();
	}
	
	////// GetStudentByClass
	function GetStudentByClass($pClassNmbr, $pSchoolYear) {
		
		$l_sql = "select a.*, b.*, c.* "
					 . "from "
           . "SCHL_Family a, "
           . "SCHL_FamilyMember b, "
           . "SCHL_CourseRegistration c "
					 . "where "
           . "b.FamilyNmbr = a.FamilyNmbr "
           . "and c.FamilyMemberNmbr = b.FamilyMemberNmbr "
           . "and c.ClassNmbr = " . $pClassNmbr
           ;
		if ($pSchoolYear != '') {
      $l_sql = $l_sql . " and (";
			$l_sql = $l_sql . "c.SchoolYear = '" . $pSchoolYear . "' ";
      if (is_int(strpos($pSchoolYear, 'Fall'))) {
        $schoolyear_parts = explode(' ', $pSchoolYear);
        $full_year = $schoolyear_parts[0] . '-' . ($schoolyear_parts[0] + 1);
      }
      else {
        if (is_int(strpos($pSchoolYear, 'Spring'))) {
          $schoolyear_parts = explode(' ', $pSchoolYear);
          $full_year = ($schoolyear_parts[0] - 1) . '-' . $schoolyear_parts[0];
        }
      }
      $l_sql = $l_sql . " or c.SchoolYear = '" . $full_year . "' ";
      $l_sql = $l_sql . ")";

		  if ($l_rst = $this->cDbUtil->SelectTable($l_sql)) {
			  return $l_rst;
		  }
		  else {
			  return false;
		  }
		}
		else {
			return false;
		}
	}

	////// GetClassInfo
	function GetClassInfo($pClassNmbr, $pSchoolYear) {
		
		$l_sql = "select a.*, b.*, c.*, d.*, e.*, f.*, g.* "
					 . "from "
           . "SCHL_Class a, "
           . "SCHL_Course b, "
           . "REF_CourseLevel c, "
           . "REF_Classroom d, "
           . "REF_ClassPeriod e, "
           . "SCHL_TeachingAssignment f, "
           . "SCHL_Staff g "
					 . "where "
           . "a.ClassNmbr = " . $pClassNmbr . " "
           . "and b.CourseNmbr = a.CourseNmbr "
           . "and c.CourseLevelNmbr = a.CourseLevelNmbr "
           . "and d.ClassroomNmbr = a.ClassroomNmbr "
           . "and e.ClassPeriodNmbr = a.ClassPeriodNmbr "
           . "and f.ClassNmbr = a.ClassNmbr "
           . "and g.StaffNmbr = f.StaffNmbr "
           ;
		if ($pSchoolYear != '') {
      $l_sql = $l_sql . " and (";
			$l_sql = $l_sql . "f.SchoolYear = '" . $pSchoolYear . "' ";
      if (is_int(strpos($pSchoolYear, 'Fall'))) {
        $schoolyear_parts = explode(' ', $pSchoolYear);
        $full_year = $schoolyear_parts[0] . '-' . ($schoolyear_parts[0] + 1);
      }
      else {
        if (is_int(strpos($pSchoolYear, 'Spring'))) {
          $schoolyear_parts = explode(' ', $pSchoolYear);
          $full_year = ($schoolyear_parts[0] - 1) . '-' . $schoolyear_parts[0];
        }
      }
      $l_sql = $l_sql . " or f.SchoolYear = '" . $full_year . "' ";
      $l_sql = $l_sql . ")";

		  if ($l_rst = $this->cDbUtil->SelectTable($l_sql)) {
			  return $l_rst;
		  }
		  else {
			  return false;
		  }
		}
		else {
			return false;
		}
	}

	////// GetAllStudent
	function GetAllStudent($pSchoolYears, $pSortBy) {
		$l_sql = "SELECT "
					 . "a.FamilyNmbr, "
					 . "a.FamilyID, "
					 . "b.FamilyMemberNmbr, "
					 . "b.LastName as StudentLastName, "
					 . "b.FirstName as StudentFirstName, "
					 . "b.ChineseName as StudentChineseName, "
					 . "b.Gender as StudentGender, "
					 . "c.SchoolYear, "
					 . "e.CourseName_E, "
					 . "e.CourseName_C, "
					 . "f.CourseLevel_E, "
					 . "f.CourseLevel_C, "
					 . "h.LastName as TeacherLastName, "
					 . "h.FirstName as TeacherFirstName, "
					 . "h.ChineseName as TeacherChineseName, "
					 . "a.Street, "
					 . "a.City, "
					 . "a.State, "
					 . "a.ZipCode, "
					 . "a.HomeTelephone, "
					 . "a.Email, "
           . "m.RegistrationFee, "
					 . "j.Tuition, "
					 . "j.BookFee, "
					 . "j.LabFee, "
					 . "j.OtherFee, "
					 . "k.TotalFeeTuition, "
					 . "k.Refund, "
					 . "k.Note, "
					 . "k.FeeTuitionPaid "
					 . "FROM "
					 . "SCHL_Family a, "
					 . "SCHL_FamilyMember b, "
					 . "SCHL_CourseRegistration c, "
					 . "SCHL_Class d, "
					 . "SCHL_Course e, "
					 . "REF_CourseLevel f, "
					 . "SCHL_TeachingAssignment g, "
					 . "SCHL_Staff h, "
					 . "REF_CourseCategory i, "
					 . "SCHL_Tuition j, "
					 . "SCHL_TuitionDue k, "
					 . "SCHL_RegistrationFeeDue l, "
					 . "SCHL_RegistrationFee m "
					 . "WHERE "
					 . "b.FcdRoleNmbr = 7 "
					 . "and b.FamilyNmbr = a.FamilyNmbr "
					 . "and c.FamilyMemberNmbr = b.FamilyMemberNmbr "
					 . "and d.ClassNmbr = c.ClassNmbr "
					 . "and e.CourseNmbr = d.CourseNmbr "
					 . "and f.CourseLevelNmbr = d.CourseLevelNmbr "
					 . "and i.CourseCategoryNmbr = e.CourseCategoryNmbr "
					 . "and j.CourseCategoryNmbr = i.CourseCategoryNmbr "
					 . "and j.SchoolYear = c.SchoolYear "
					 . "and g.ClassNmbr = c.ClassNmbr "
					 . "and h.StaffNmbr = g.StaffNmbr "
					 . "and k.FamilyNmbr = a.FamilyNmbr "
					 . "and l.FamilyMemberNmbr = b.FamilyMemberNmbr "
					 . "and m.RegistrationFeeNmbr = l.RegistrationFeeNmbr "
           ;
		if ($pSchoolYears != '') {
      for ($i = 0; $i < sizeof($pSchoolYears); $i++) {
        if ($i == 0) {
          $l_sql = $l_sql . "and (c.SchoolYear = '" . $pSchoolYears[$i] . "' ";
        }
        else {
          $l_sql = $l_sql . "or c.SchoolYear = '" . $pSchoolYears[$i] . "' ";
        }
      }
      $l_sql = $l_sql . ")";
      for ($i = 0; $i < sizeof($pSchoolYears); $i++) {
        if ($i == 0) {
          $l_sql = $l_sql . "and (l.SchoolYear = '" . $pSchoolYears[$i] . "' ";
        }
        else {
          $l_sql = $l_sql . "or l.SchoolYear = '" . $pSchoolYears[$i] . "' ";
        }
      }
      $l_sql = $l_sql . ")";

      
      switch ($pSortBy) {
        case "FamilyID":
        	$l_sql = $l_sql . "ORDER BY a.FamilyID, b.FamilyMemberNmbr, e.CourseName_E, f.CourseLevel_E ";
          break;
        case "CourseName":
        	$l_sql = $l_sql . "ORDER BY e.CourseName_E, a.FamilyID, f.CourseLevel_E, b.FamilyMemberNmbr ";
          break;
        case "CourseLevel":
        	$l_sql = $l_sql . "ORDER BY f.CourseLevel_E, a.FamilyID, e.CourseName_E, b.FamilyMemberNmbr ";
          break;
        case "Teacher":
        	$l_sql = $l_sql . "ORDER BY TeacherLastName, a.FamilyID, e.CourseName_E, f.CourseLevel_E, b.FamilyMemberNmbr ";
          break;
        case "StudentGender":
        	$l_sql = $l_sql . "ORDER BY StudentGender, a.FamilyID, e.CourseName_E, f.CourseLevel_E, b.FamilyMemberNmbr ";
          break;
        default:
        	$l_sql = $l_sql . "ORDER BY a.FamilyID, e.CourseName_E, f.CourseLevel_E, b.FamilyMemberNmbr ";
      }

		  if ($l_rst = $this->cDbUtil->SelectTable($l_sql)) {
			  return $l_rst;
		  }
		  else {
			  return false;
		  }
		}
		else {
			return false;
		}
	}

}
	
	
?>
