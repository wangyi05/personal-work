<?php

/**
 *
 *
 * @version $Id$
 * @copyright 2005
 **/

include_once 'LIB_Session.inc';

//echo GetSubjectID() . '--' . GetSectionNmbr() . '--' . GetSubtask() . '--' . GetHtml() . '----------------------------<BR>';
//echo GetSession('FamilyNmbr', 0) . '----------------------------<BR>';

// session handling
if ((GetSubjectID() == "REGIST" || GetSubjectID() == "GRADEREPORT")
		&& GetSubtask() != 'main' 
		&& GetSubtask() != 'login' 
		&& GetSubtask() != 'cancel' 
		&& GetSubtask() != 'forgotpassword'
	) { // reg or grade
	if (strlen(session_id()) < 5) session_start();
	if (GetSubtask() == 'createaccount') session_unset();
	if (isset($_POST['subjectid__'])) setSession('subjectid__');
	if (isset($_POST['subtask__'])) setSession('subtask__');
}
else { // website
	if (strlen(session_id()) > 5) unsetSession();
}

include_once 'FCD_Registration.inc';
include_once 'FCD_GradeReport.inc';
include_once 'FCD_Templates.inc';
include_once 'LIB_Utilities.inc';
include_once 'LIB_DbUtilities.inc';
include_once 'LIB_DbTaskHandlers.inc';
include_once 'LIB_SharedFormModules.inc';


// display error messages 0 = no, 1 = yes
$debug = 0;
if ($debug) {
	//error_reporting(E_ALL);
	ini_set("display_errors","1");
}



// task
if (GetSubjectID() == "REGIST" && GetSubtask() == 'submit') {
	UpdateAllTables();
	GetPrintRegistration();
	unsetSession();
}
else {
	switch (GetSubjectID()) {
		case "REGIST":
			switch (GetSubtask()) {
				case "checklogin":
					if (CheckStudentLogin()) GetWebSite(GetSubjectID(), GetLanguage(), GetSectionNmbr(), 'accountreport', GetHtml());
					else GetWebSite(GetSubjectID(), GetLanguage(), GetSectionNmbr(), 'login', GetHtml());
					break;
				default:
					GetWebSite(GetSubjectID(), GetLanguage(), GetSectionNmbr(), GetSubtask(), GetHtml());
			}
			break;
		case "GRADEREPORT":
			switch (GetSubtask()) {
				case "checklogin":
					if (CheckStudentLogin()) GetWebSite(GetSubjectID(), GetLanguage(), GetSectionNmbr(), 'gradeinfo', GetHtml());
					else GetWebSite(GetSubjectID(), GetLanguage(), GetSectionNmbr(), 'login', GetHtml());
					break;
				default:
					GetWebSite(GetSubjectID(), GetLanguage(), GetSectionNmbr(), GetSubtask(), GetHtml());
			}
			break;
		default:
			GetWebSite(GetSubjectID(), GetLanguage(), GetSectionNmbr(), GetSubtask(), GetHtml());
	}

}



/**
 *
 * @name 		GetSubjectID
 * @args 		none
 * @return	subject_id
 * @desc		
 *
 **/
function GetSubjectID()
{
	$subject_id = "";
	if (isset($_GET['subjectid'])) {
		$subject_id = $_GET['subjectid'];
	}
	else {
		if (isset($_POST['subjectid__'])) {
			$subject_id = $_POST['subjectid__'];
		}
		else {
			$subject_id = 'HOME';  // default = home_page
		}
	}
	return $subject_id;
	
}

/**
 *
 * @name 		GetLanguage
 * @args 		none
 * @return	language
 * @desc		
 *
 **/
function GetLanguage()
{
	$language_nmbr = "";
	if (isset($_GET['languagenmbr'])) {
		$language_nmbr = $_GET['languagenmbr'];
	}
	else {
		if (isset($_POST['languagenmbr__'])) {
			$language_nmbr = $_POST['languagenmbr__'];
		}
		else {
			if (isset($_GET['languagenmbr__'])) {
				$language_nmbr = $_GET['languagenmbr__'];
			}
			else {
				$language_nmbr = 2;  // default = English
			}
		}
	}
	return $language_nmbr;
	
}

/**
 *
 * @name 		GetSubtask
 * @args 		none
 * @return	subtaske
 * @desc		
 *
 **/
function GetSubtask()
{
	$subtask = "";
	if (isset($_GET['subtask'])) {
		$subtask = $_GET['subtask'];
	}
	else {
		if (isset($_POST['subtask__'])) {
			$subtask = $_POST['subtask__'];
		}
		else {
			$subtask = 'main';  // default = main
		}
	}
	if (GetSubjectID() == "REGIST" && getSession('subtask', 0) != "" && getSession('subtask', 0) != "main") {
		$subtask = getSession('subtask', 0);
	}

	return $subtask;
	
}

/**
 *
 * @name 		GetSectionNmbr
 * @args 		none
 * @return	sectionnmbr
 * @desc		
 *
 **/
function GetSectionNmbr()
{
	$sectionnmbr = "";
	if (isset($_GET['sectionnmbr'])) {
		$sectionnmbr = $_GET['sectionnmbr'];
	}
	else {
		if (isset($_POST['sectionnmbr__'])) {
			$sectionnmbr = $_POST['sectionnmbr__'];
		}
	}
	return $sectionnmbr;
	
}

/**
 *
 * @name 		GetHtml
 * @args 		none
 * @return	html file url
 * @desc		
 *
 **/
function GetHtml()
{
	$htmlurl = "";
	if (isset($_GET['htmlfile'])) {
		$htmlurl = "./html/" . $_GET['htmlfile'];
	}
	return $htmlurl;
	
}


if ($debug && function_exists('printSession')) {
	printSession();
}






?>
