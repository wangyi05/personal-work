<?php

/**
 * 
 *
 * @version $Id$
 * @copyright 2004 
 **/


/**
 *
 * @name 		setSession
 * @args 		Variable length
 *					arg[0] = session_variable_name
 *					arg[1] = session_variable_value
 *					arg[2] = session_variable_index
 * @return	None
 * @desc		If name and value are provided, this function sets the corresponding
 *					session variable.  if only name is provided, it sets the corresponding
 *					session variable to the value of the post variable with the same name.
 *					Otherwise, it sets all submitted form vaiables as session variables.
 *
 **/
function setSession()
{
	$argnum = func_num_args();
	$arglist = func_get_args();

	switch ($argnum) {
		case 3: // for editing existing record
			if (trim($arglist[1]) != "") {
				finishSetSession($arglist[0], $arglist[1], $arglist[2], false);
			}
			break;
		case 2:
			if (trim($arglist[1]) != "") {
				finishSetSession($arglist[0], $arglist[1], "", false);
			}
			break;
		case 1:
			if ($_POST[$arglist[0]] != "") {
				finishSetSession($arglist[0], $_POST[$arglist[0]], "", false);
			}
			break;
		default:
			foreach ($_POST as $name => $value) {
				if ($name != "Submit") {
					if (!is_array($value) && trim($value) == "") {
						if (substr($name, -2) === '__') { // non-repeatable - variables end with '__'
							finishSetSession($name, $value, "", false);
						}
            else {
            }
					}
					else {
						finishSetSession($name, $value, "", false);
					}
				}
			}
	}

}

/**
 *
 * @name 		setSessionDupAllowed
 * @args 		Variable length
 *					arg[0] = session_variable_name
 *					arg[1] = session_variable_value
 *					arg[2] = session_variable_index
 * @return	None
 * @desc		Duplicate session values allowed.
 *					If name and value are provided, this function sets the corresponding
 *					session variable.  if only name is provided, it sets the corresponding
 *					session variable to the value of the post variable with the same name.
 *					Otherwise, it sets all submitted form vaiables as session variables.
 *
 **/
function setSessionDupAllowed()
{
	$argnum = func_num_args();
	$arglist = func_get_args();

	switch ($argnum) {
		case 3: // for editing existing record
			if (trim($arglist[1]) != "") {
				finishSetSession($arglist[0], $arglist[1], $arglist[2], true);
			}
			break;
		case 2:
			if (trim($arglist[1]) != "") {
				finishSetSession($arglist[0], $arglist[1], "", true);
			}
			break;
		case 1:
			if ($_POST[$arglist[0]] != "") {
				finishSetSession($arglist[0], $_POST[$arglist[0]], "", true);
			}
			break;
		default:
			foreach ($_POST as $name => $value) {
				if ($name != "Submit") {
					if (trim($value) == "") {
						if (substr($name, -2) === '__') { // non-repeatable - variables end with '__'
							finishSetSession($name, $value, "", true);
						}
					}
					else {
						finishSetSession($name, $value, "", true);
					}
				}
			}
	}

}

function finishSetSession($pPostVarName, $pPostVarValue, $pSessionIndex, $pForce)
{
	if (is_array($pPostVarValue)) $postvarvalue = $pPostVarValue;
	else $postvarvalue = $pPostVarValue;
	
	if (is_int(strpos($pPostVarName, '_')) && strpos($pPostVarName, '_') == 0) { // variables start with '_', session varaiable is not an array.
		$_SESSION[$pPostVarName] = $postvarvalue;
	}
	else { // metadata element, session variable should be an array.
		if (substr($pPostVarName, -2) === '__') { // non-repeatable - variables end with '__'
			$sessionname = substr($pPostVarName, 0, -2);
			if (trim($postvarvalue) == "") {
				if (getSession($sessionname, 0) != "") { // unset existing session
					unsetSession($sessionname, 0);
				}
			}
			else { // only set session if not empty
				$tmparray = array();
				array_push($tmparray, $postvarvalue);
				$_SESSION[$sessionname] = $tmparray;
			}
		}
		else { // repeatable
      if (isset($postvarvalue)) {
			  if (is_array($postvarvalue)) { // repeatable-dropdown
				  $tmparray = array();
				  for ($pindex = 0; $pindex < sizeof($postvarvalue); $pindex++) {
					  array_push($tmparray, $postvarvalue[$pindex]);
				  }
				  $_SESSION[$pPostVarName] = $tmparray;
			  }
			  else { // repeatable input box
				  if ($pSessionIndex != "") { // editing
					  if (isset($_SESSION[$pPostVarName][$pSessionIndex])) {
						  $_SESSION[$pPostVarName][$pSessionIndex] = $postvarvalue;
					  }
				  }
				  else { // add
					  if (isset($_SESSION[$pPostVarName])) {
						  if ($pForce) { // session can have duplicate values
							  array_push($_SESSION[$pPostVarName], $postvarvalue);
						  }
						  else {
							  if (!in_array($postvarvalue, $_SESSION[$pPostVarName])) {
								  array_push($_SESSION[$pPostVarName], $postvarvalue);
							  }
						  }
					  }
					  else {
						  $tmparray = array();
						  array_push($tmparray, $postvarvalue);
						  $_SESSION[$pPostVarName] = $tmparray;
					  }
				  }
			  }
      }
      else {
        unsetSession($pPostVarName);
      }
		}
	}
		
}

/**
 *
 * @name 		getSession
 * @args 		Variable length
 *					arg[0] = session_variable_name
 *					arg[1] = session_variable_index
 * @return	session_variable_value
 * @desc		This function returns the specified session variable value.
 *
 **/
function getSession()
{
	$argnum = func_num_args();
	$arglist = func_get_args();
	$sessionvalue = "";

	if(isset($_SESSION[$arglist[0]])) {
		if(is_array($_SESSION[$arglist[0]])) {
			if(isset($_SESSION[$arglist[0]][$arglist[1]])) {
				$sessionvalue = $_SESSION[$arglist[0]][$arglist[1]];
			}
		}
		else {
			$sessionvalue = $_SESSION[$arglist[0]];
		}
	}
	//return $sessionvalue;
	return $sessionvalue;

}

/**
 *
 * @name 		getSessionCount
 * @args 		Fixed
 *					arg[0] = session_variable_name
 * @return	session_variable_count
 * @desc		This function returns the specified session variable count.
 *
 **/
function getSessionCount($pVariable, $pOption)
{
	$sessioncount = 0;

	if ($pOption == '*') { // name like ...
		foreach ($_SESSION as $name => $value) {
			if (is_int(strpos($name, $pVariable))) {
				$sessioncount++;
			}
		}
	}
	else {
		if(isset($_SESSION[$pVariable])) {
			if(is_array($_SESSION[$pVariable])) {
				$sessioncount = sizeof($_SESSION[$pVariable]);
			}
			else {
				$sessioncount = 1;
			}
		}
		else {
			$sessioncount = 0;
		}
	}
	return $sessioncount;

}

/**
 *
 * @name 		unsetSession
 * @args 		Variable length
 *					arg[0] = session_variable_name
 *					arg[1] = session_variable_index
 *					arg[2] = is_group_flag
 * @return	None
 * @desc		If name is provided, this function unsets the corresponding
 *					session variable.  Otherwise, it unsets all session variables.
 *
 **/
function unsetSession()
{
	global $GroupLib;
	$argnum = func_num_args();
	$arglist = func_get_args();
	
	switch ($argnum) {
		case 1: // individual session variable with NO index
			if(isset($_SESSION[$arglist[0]])) {
				session_unregister($arglist[0]);
			}
			break;
		case 2: // individual session variable with index
			if(isset($_SESSION[$arglist[0]])) {
				if(is_array($_SESSION[$arglist[0]])) {
					if(isset($_SESSION[$arglist[0]][$arglist[1]])) {
						if (sizeof($_SESSION[$arglist[0]]) == 1) {
							session_unregister($arglist[0]);
						}
						else {
							unset($_SESSION[$arglist[0]][$arglist[1]]);
						}
					}
				}
				else {
					session_unregister($arglist[0]);
				}
			}
			break;
		case 3: // group
			foreach ($GroupLib as $elementname => $grpnmbr) {
				if ($grpnmbr == $arglist[0]) {
					if(isset($_SESSION[$elementname])) {
						if(is_array($_SESSION[$elementname])) {
							if(isset($_SESSION[$elementname][$arglist[1]])) {
								if (sizeof($_SESSION[$elementname]) == 1) {
									session_unregister($elementname);
								}
								else {
									unset($_SESSION[$elementname][$arglist[1]]);
								}
							}
						}
						else {
							session_unregister($elementname);
						}
					}
				}
			}
			break;
		default: // all
			if (isset($_SESSION)) {
				foreach ($_SESSION as $name => $value) {
					session_unregister($name);
					//unset($_SESSION[$name]);
					//session_unset($name);
				}
				session_unset();
				session_destroy();
				$_SESSION = array();
	
	
				// unset posted html form variables
				unset($_POST);
			}
	}
	
}

/**
 *
 * @name 		unsetSessionForCancel
 * @args 		None
 * @return	None
 * @desc		unset all session variables except 'languagenmbr'
 *
 **/
function unsetSessionForCancel()
{
	foreach ($_SESSION as $name => $value) {
		if ($name != "languagenmbr") {
			session_unregister($name);
		}
	}
	
}

/**
 *
 * @name 		unsetSessionForReg
 * @args 		None
 * @return	None
 * @desc		
 *
 **/
function unsetSessionForReg()
{
	foreach ($_SESSION as $name => $value) {
		if (is_int(strpos($name, "ChineseClass"))
				|| is_int(strpos($name, "CultureClass"))
				|| is_int(strpos($name, "Tuition"))
				|| is_int(strpos($name, "RegFee"))
				|| is_int(strpos($name, "Subtotal"))
				|| is_int(strpos($name, "ManageFee"))
				|| is_int(strpos($name, "Total"))
				) {
			session_unregister($name);
		}
	}
	
}

/**
 *
 * @name 		unsetSessionForWebEdit
 * @args 		None
 * @return	None
 * @desc		
 *
 **/
function unsetSessionForWebEdit()
{
	foreach ($_SESSION as $name => $value) {
		if (is_int(strpos($name, "FrameNmbr"))
				|| is_int(strpos($name, "SubjectID"))
				|| is_int(strpos($name, "LanguageNmbr"))
				|| is_int(strpos($name, "WebsiteTask"))
				|| is_int(strpos($name, "WebsiteItemAnnouncement"))
				|| is_int(strpos($name, "WebsiteItemAuthor"))
				|| is_int(strpos($name, "WebsiteItemTitle"))
				|| is_int(strpos($name, "WebsiteItemSubtitle"))
				|| is_int(strpos($name, "WebsiteItemAbstract"))
				|| is_int(strpos($name, "WebsiteItemFullContent"))
				|| is_int(strpos($name, "WebsiteItemThumbnail"))
				|| is_int(strpos($name, "WebsiteItemImage"))
				|| is_int(strpos($name, "WebsiteItemHtml"))
				|| is_int(strpos($name, "SectionToDelete"))
				|| is_int(strpos($name, "PhotogroupEnglishLabel"))
				|| is_int(strpos($name, "PhotogroupChineseLabel"))
				|| is_int(strpos($name, "PhotogroupToDelete"))
				) {
			session_unregister($name);
		}
	}
	
}

/**
 *
 * @name 		unsetSessionForChangeFrame
 * @args 		None
 * @return	None
 * @desc		
 *
 **/
function unsetSessionForChangeFrame()
{
	foreach ($_SESSION as $name => $value) {
		if (is_int(strpos($name, "SubjectID"))
				|| is_int(strpos($name, "LanguageNmbr"))
				|| is_int(strpos($name, "WebsiteTask"))
				|| is_int(strpos($name, "WebsiteItemAnnouncement"))
				|| is_int(strpos($name, "WebsiteItemAuthor"))
				|| is_int(strpos($name, "WebsiteItemTitle"))
				|| is_int(strpos($name, "WebsiteItemSubtitle"))
				|| is_int(strpos($name, "WebsiteItemAbstract"))
				|| is_int(strpos($name, "WebsiteItemFullContent"))
				|| is_int(strpos($name, "WebsiteItemThumbnail"))
				|| is_int(strpos($name, "WebsiteItemImage"))
				|| is_int(strpos($name, "WebsiteItemHtml"))
				|| is_int(strpos($name, "SectionToDelete"))
				|| is_int(strpos($name, "PhotogroupEnglishLabel"))
				|| is_int(strpos($name, "PhotogroupChineseLabel"))
				|| is_int(strpos($name, "PhotogroupToDelete"))
				) {
			session_unregister($name);
		}
	}
	
}

/**
 *
 * @name 		unsetSessionForChangeSubject
 * @args 		None
 * @return	None
 * @desc		
 *
 **/
function unsetSessionForChangeSubject()
{
	foreach ($_SESSION as $name => $value) {
		if (is_int(strpos($name, "LanguageNmbr"))
				|| is_int(strpos($name, "WebsiteTask"))
				|| is_int(strpos($name, "WebsiteItemAnnouncement"))
				|| is_int(strpos($name, "WebsiteItemAuthor"))
				|| is_int(strpos($name, "WebsiteItemTitle"))
				|| is_int(strpos($name, "WebsiteItemSubtitle"))
				|| is_int(strpos($name, "WebsiteItemAbstract"))
				|| is_int(strpos($name, "WebsiteItemFullContent"))
				|| is_int(strpos($name, "WebsiteItemThumbnail"))
				|| is_int(strpos($name, "WebsiteItemImage"))
				|| is_int(strpos($name, "WebsiteItemHtml"))
				|| is_int(strpos($name, "SectionToDelete"))
				|| is_int(strpos($name, "PhotogroupEnglishLabel"))
				|| is_int(strpos($name, "PhotogroupChineseLabel"))
				|| is_int(strpos($name, "PhotogroupToDelete"))
				) {
			session_unregister($name);
		}
	}
	
}

/**
 *
 * @name 		unsetSessionForNextTask
 * @args 		None
 * @return	None
 * @desc		
 *
 **/
function unsetSessionForNextTask($pTarget)
{
	switch ($pTarget) {
		case 'admin':
			foreach ($_SESSION as $name => $value) {
				if ($name != "LoginNmbr"
				&& $name != "LoginRole"
				&& $name != "LoginRoleNmbr") {
					session_unregister($name);
				}
			}
			break;
		case 'website':
			foreach ($_SESSION as $name => $value) {
				if ($name != "FamilyNmbr") {
					session_unregister($name);
				}
			}
			break;
		default:
	}
	
}

function sessionValueExists($pValue, $pSessionVar)
{ // does the vaule exists for the session variable?
	$valueexists = false;

	if (substr($pValue, -1, 1) == "*") { // part of session variable name
		foreach ($_SESSION as $name => $value) {
			if (is_int(strpos($name, $pSessionVar))) {
				if (is_array($value)) {
					if (in_array($pValue, $value)) {
						$valueexists = true;
						break;
					}
				}
				else {
					if ($value == $pValue) {
						$valueexists = true;
						break;
					}
				}
			}
		}
	}
	else { // definite session variable name
		if (isset($_SESSION[$pSessionVar])) {
			if (is_array($_SESSION[$pSessionVar])) {
				if (in_array($pValue, $_SESSION[$pSessionVar])) {
					$valueexists = true;
				}
			}
			else {
				if ($_SESSION[$pSessionVar] == $pValue) {
					$valueexists = true;
				}
			}
		}
	}
	return $valueexists;

}

/**
 *
 * @name 		unsetPOST
 * @args 		1
 *					arg[0] = group_nmbr
 * @return	none
 * @desc		
 *
 **/
function unsetPOST($pGroupNmbr)
{
	foreach ($_POST as $postname => $postvalue) {
		if (is_int(strpos($postname, "GROUP" . $pGroupNmbr))) {
			unset($_POST[$postname]);
		}
	}
	
}

/**
 *
 * @name 		printSession
 * @args 		None
 * @return	None
 * @desc		print all session variable names and values
 *
 **/
function printSession()
{
	if (strlen(session_id()) > 5) {
		foreach ($_SESSION as $name => $value) {
			if (is_array($value)) {
				foreach ($value as $index => $arrayvalue) {
					echo $name . "[" . $index . "]" . "-->" . $arrayvalue . "<BR>";
				}
			}
			else {
				echo $name . "-->" . $value . "<BR>";
			}
		}
	}
}

/**
 *
 * @name 		unsetSessionForAdminCancel
 * @args 		None
 * @return	None
 * @desc		unset all session variables except 'USERROLE'
 *
 **/
function unsetSessionForAdminCancel()
{
	foreach ($_SESSION as $name => $value) {
		if ($name != "USERROLE") {
			session_unregister($name);
		}
	}
	
}




?>
