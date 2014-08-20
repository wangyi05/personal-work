<?php

/**
 *
 *
 * @version $Id$
 * @copyright 2005
 **/

/**
 *
 * @name 		GetPostValue
 * @args 		none
 * @return	
 * @desc		
 *
 **/
function GetPostValue($pPostVal) {
	if (isset($_POST[$pPostVal])) return $_POST[$pPostVal];
	else return '';
}

/**
 *
 * @name 		GetValue
 * @args 		none
 * @return	
 * @desc		
 *
 **/
function GetValue($pArrayVal, $pFirstIdx, $pSecondIdx) {
	if (isset($pArrayVal[$pFirstIdx])) {
		if (isset($pArrayVal[$pFirstIdx][$pSecondIdx])) {
			return trim($pArrayVal[$pFirstIdx][$pSecondIdx]);
		}
	}
	return '';
}

/**
 *
 * @name 		checkSelectedOption
 * @args 		None
 * @return	'selected' or ''
 * @desc
 *
 **/
function checkSelectedOption($pSessionVarName, $pValue) {
	$result = "";
	if (isset($_SESSION[$pSessionVarName])) {
		if (is_array($_SESSION[$pSessionVarName]) && 
				(in_array($pValue, $_SESSION[$pSessionVarName]) || in_array(mysql_escape_string($pValue), $_SESSION[$pSessionVarName]))
				) {
			$result = ' selected';
		}
	}
	return $result;
}

/**
 *
 * @name 		SendEmail
 * @args 		none
 * @return	
 * @desc		
 *
 **/
function SendEmail($pTo, $pCC, $pFrom, $pSubject, $pMessage) {

	$additional_headers = "CC: " . $pCC . "\r\n" .
												"From: " . $pFrom . "\r\n" .
												"Reply-To: " . $pFrom . "\r\n" .
												"X-Mailer: PHP/" . phpversion();
	
	if (!mail($pTo, $pSubject, $pMessage, $additional_headers)) {
		echo "<b>Erro sending email!</b><br/>";
	}

}

/**
 *
 * @name 		GetConfigurationParam
 * @args 		1
 *					args[0] - parameter name
 * @return	parameter value
 * @desc
 *
 **/
function GetConfigurationParam($pParam) {
	
	include_once 'fcdconf.php';
	$params = get_fcd_configuration();
	return $params[$pParam];
	
	/****
	$paramvalue = "";
	$configfile = "FCD.conf";

	if (file_exists($configfile)) {
		$fp = fopen($configfile, "r") or die("could not open config file");
		while ($newLine = fgets($fp, 4096)) {
			if ($newLine != "" && substr($newLine, 0, 1) != ";") {
				$newlinearray = explode("=", $newLine);
				$param = trim($newlinearray[0]);
				if ($param == $pParam) {
					$valuearray = explode(";", $newlinearray[1]);
					$paramvalue = trim($valuearray[0]);
					break;
				}
			}
		}
		fclose($fp);
	}
	return $paramvalue;
	****/
	
}




?>
