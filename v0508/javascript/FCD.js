 
/*
 *
 * @name 		CheckCookie
 * @args 		None
 * @returns	boolean
 * @desc		Test cookie
 *
 */
function CheckCookie()
{
	Set_Cookie( 'test', 'none', '', '/', '', '' );
	if ( Get_Cookie( 'test' ) ) {
		Delete_Cookie('test', '/', '');
		return true;
	}
	else
	{
		alert( 'You need to enable cookies for your browser.' );
		return false;
	}

}

function Get_Cookie( name ) {
	
	var start = document.cookie.indexOf( name + "=" );
	var len = start + name.length + 1;
	if ( ( !start ) && ( name != document.cookie.substring( 0, name.length ) ) )
	{
		return null;
	}
	if ( start == -1 ) return null;
	var end = document.cookie.indexOf( ";", len );
	if ( end == -1 ) end = document.cookie.length;
	return unescape( document.cookie.substring( len, end ) );
}

/*
only the first 2 parameters are required, the cookie name, the cookie
value. Cookie time is in milliseconds, so the below expires will make the 
number you pass in the Set_Cookie function call the number of days the cookie
lasts, if you want it to be hours or minutes, just get rid of 24 and 60.

Generally you don't need to worry about domain, path or secure for most applications
so unless you need that, leave those parameters blank in the function call.
*/
function Set_Cookie( name, value, expires, path, domain, secure ) {
	// set time, it's in milliseconds
	var today = new Date();
	today.setTime( today.getTime() );
	// if the expires variable is set, make the correct expires time, the
	// current script below will set it for x number of days, to make it
	// for hours, delete * 24, for minutes, delete * 60 * 24
	if ( expires )
	{
		expires = expires * 1000 * 60 * 60 * 24;
	}
	//alert( 'today ' + today.toGMTString() );// this is for testing purpose only
	var expires_date = new Date( today.getTime() + (expires) );
	//alert('expires ' + expires_date.toGMTString());// this is for testing purposes only

	document.cookie = name + "=" +escape( value ) +
		( ( expires ) ? ";expires=" + expires_date.toGMTString() : "" ) + //expires.toGMTString()
		( ( path ) ? ";path=" + path : "" ) + 
		( ( domain ) ? ";domain=" + domain : "" ) +
		( ( secure ) ? ";secure" : "" );
}

function Delete_Cookie( name, path, domain ) {
	if ( Get_Cookie( name ) ) document.cookie = name + "=" +
			( ( path ) ? ";path=" + path : "") +
			( ( domain ) ? ";domain=" + domain : "" ) +
			";expires=Thu, 01-Jan-1970 00:00:01 GMT";
}



/*
 *
 * @name 		alertbox
 * @args 		None
 * @returns	None
 * @desc		Test script
 *
 */
function alertbox()
{
	alert("HI");
}


/*
 *
 * @name 		Ding
 * @args 		2
 * @returns	None
 * @desc		Set element_name and element_type
 *
 */
function Ding(pElementName, pElementType)
{
	if (navigator.appName == "Microsoft Internet Explorer") {
		document.form1._ScrollPosition.value = document.body.scrollTop;
		if (pElementName != "" || pElementType != "") {
			document.form1._ElementName.value = pElementName;
			document.form1._ElementType.value = pElementType;
		}
	}
	else{
		document.form1._ScrollPosition.value = window.pageYOffset;
		if (pElementName != "" || pElementType != "") {
			document.form1._ElementName.value = pElementName;
			document.form1._ElementType.value = pElementType;
		}
	}
}


/*
 *
 * @name 		PopulateElementField
 * @args 		2
 * @returns	None
 * @desc		Populate input box when entry in elementList dropdown list is clicked
 *
 */
function PopulateElementField(element, elementList)
{
	element.value = elementList.options[elementList.selectedIndex].text;
}



/*
 *
 * @name 		CheckInputBoxEntry
 * @args 		2
 * @returns	None
 * @desc		Check to see if the required field is entered
 *
 */
function CheckInputBoxEntry(pFormElement, pName)
{
	if (pFormElement.value.length < 1) {
		alert("You need to enter " + pName);
		return false;
	}
	else {
		return true;
	}
}


/*
 *
 * @name 		CheckRadioCheckbox
 * @args 		1
 * @returns	None
 * @desc		Check to see if any radio or checkbox is checked
 *
 */
function CheckRadioCheckbox(pRadioElement)
{
  var radioChecked = -1;
	
	if (pRadioElement.length) { // more than one entry
		for (i=0; i<pRadioElement.length; i++) {
			if (pRadioElement[i].checked) {
				radioChecked = i;
			}
		}
	}
	else { // single entry
		if (pRadioElement.checked) {
			radioChecked = 0;
		}
	}

	if (radioChecked == -1) {
		return false;
	}
	else {
		return true;
	}
	
}



/*
 *
 * @name 		CheckCheckboxArray
 * @args 		1
 * @returns	None
 * @desc		Check to see if any checkbox is checked
 *					arg[0] needs to be string and in 'name[]' format
 *
 */
function CheckCheckboxArray(pCheckboxElement) {
  var checkboxChecked = -1;

	if (document.form1[pCheckboxElement].length) { // more than one entry
		for (var i = 0; i < document.form1[pCheckboxElement].length; i++) {
			if (document.form1[pCheckboxElement][i].checked) {
				checkboxChecked = i;
			}
		}
	}
	else {
		if (document.form1[pCheckboxElement].checked) {
			checkboxChecked = 0;
		}
	}

	if (checkboxChecked == -1) {
		return false;
	}
	else {
		return true;
	}

}




/*
 *
 * @name 		UncheckRadio
 * @args 		1
 * @returns	None
 * @desc		uncheck radio button
 *
 */
function UncheckRadio(pRadioElement)
{
	if (pRadioElement.length) {
		for (i=0; i<pRadioElement.length; i++) {
			pRadioElement[i].checked = false;
		}
	}
	else {
		pRadioElement.checked = false;
	}
	
}



/*
 *
 * @name 		GetCheckRadioCheckboxValue
 * @args 		2
 * @returns	None
 * @desc		if any radio or checkbox is checked, return value
 *
 */
function GetCheckRadioCheckboxValue(pRadioElement)
{
  var radioCheckedValue = "";
	
  // more than one entry
	for (i=0; i<pRadioElement.length; i++) {
		if (pRadioElement[i].checked) {
			radioCheckedValue = pRadioElement[i].value;
		}
	}
  // single entry
	if (pRadioElement.checked) {
		radioCheckedValue = pRadioElement.value;
	}
	return radioCheckedValue;
	
}


/*
 *
 * @name 		SubmitForm
 * @args 		2
 * @returns	None
 * @desc		Submit the form with the provided value for the parameter
 *
 */
function SubmitForm(pForm, pSubmitValue)
{
	pForm.JsSubmit__.value = pSubmitValue;
	pForm.submit();
}




/*
 *
 * @name 		popup
 * @args 		4
 * @returns	boo
 * @desc		popup help window
 *
 */
function popup(mylink, windowname)
{
	if (! window.focus)
		return true;
	var href;
	if (typeof(mylink) == 'string') href=mylink;
	else href=mylink.href;
	if (windowname == "help") {
		window.open(href, windowname, 'width=350,height=300,left=300,top=300,scrollbars=1,resizable=1,status=0,toolbar=0,location=0,menubar=0;directories=0');
	}
	else {
		debugWindow = window.open(href, windowname, 'width=700,height=700,left=50,top=50,scrollbars=1,resizable=1,status=0,toolbar=0,location=0,menubar=0;directories=0');
		if (windowname == "create files") {
    	debugWindow.document.writeln('<b>Uploading files &nbsp;......</b><br/><br/>(Please be patient, this process may take up to several minutes)<br/><br/>'); 
		}
		//window.open(href, windowname, ',,,,scrollbars=yes');
	}
	return false;
}



/*
 *
 * @name 		messagepopup
 * @args 		none
 * @returns	boo
 * @desc		popup message window
 *
 */
function messagepopup()
{
	if (! window.focus) {
		return true;
	}
	debugWindow = window.open("","debugWin","toolbar=no,scrollbars,width=800,height=800"); 
  debugWindow.document.writeln('<html>'); 
  debugWindow.document.writeln('<head>'); 
  debugWindow.document.writeln('<title>Message</title>'); 
  debugWindow.document.writeln('</head>'); 
  debugWindow.document.writeln('<body><font face="verdana,arial">'); 
  debugWindow.document.writeln('Processing ...'); 
	return true;
}


		
	
/*
 *
 * @name 		CheckStudentInfo
 * @args 		None
 * @returns	None
 * @desc		Check submit value for StudentInfo page
 *
 */
function CheckStudentInfo()
{
	if (document.form1.FatherLastName.value == "" && document.form1.MotherLastName.value == "" && document.form1.FatherChineseName.value == "" && document.form1.MotherChineseName.value == "") {
		alert ("You need to enter at least one parent name.");
		return false;
	} 
	else {
		if (document.form1.Street.value == "") {
			alert ("You need to enter street address.");
			return false;
		}
		else {
			if (document.form1.City.value == "") {
				alert ("You need to enter city.");
				return false;
			}
			else {
				if (document.form1.Zip.value == "") {
					alert ("You need to enter zip code.");
					return false;
				}
				else {
					if (document.form1.HomeTelephone.value == "") {
						alert ("Home telephone number is required.");
						return false;
					}
					else {
						if (document.form1.Password__) {
							if (document.form1.Password__.value != "") {
								if (document.form1.UserName__.value != "") {
									if (document.form1.ConfirmPassword__.value != "") {
										if (document.form1.Password__.value != document.form1.ConfirmPassword__.value) {
											alert ("The passwords you entered must be exactly the same.  Please try again");
											return false;
										}
										else {
											document.form1.Password__.value = hex_hmac_md5(document.form1.UserName__.value, document.form1.Password__.value);
											return true;
										}
									}
									else {
										alert ("Confirm Password!");
										return false;
									}
								}
								else {
									alert ("User name is required if you want to change the login information!");
									return false;
								}
							}
						}
					}
				}
			}
		}
	}
	/***
	studentcount = 0;
	for (i = 0; i < document.form1.elements.length; i++) {
		if (document.form1.elements[i].name.substr(0, 15) == "StudentLastName") {
			if (document.form1.elements[i].value != "") {
				studentcount++;
			}
		}
	}
	if (studentcount == 0) {
		alert ("You need to enter least one student name to continue.");
		return false;
	}

	isadultcount = 0;
	for (j = 0; j < document.form1.elements.length; j++) {
		if (document.form1.elements[j].name.substr(0, 14) == "StudentIsAdult") {
			if (CheckRadioCheckbox(document.form1.elements[j])) {
				isadultcount++;
			}
		}
	}
	if (isadultcount < studentcount) {
		alert ("You need indicate whether the student is an adult or not.");
		return false;
	}

	childrencount = 0;
	for (k = 0; k < document.form1.elements.length; k++) {
		if (document.form1.elements[k].name.substr(0, 14) == "StudentIsAdult") {
			if (GetCheckRadioCheckboxValue(document.form1.elements[k]) == "no") {
				childrencount++;
			}
		}
	}
	birthdaycount = 0;
	for (l = 0; l < document.form1.elements.length; l++) {
		if (document.form1.elements[l].name.substr(0, 15) == "StudentBirthDay") {
			if (document.form1.elements[l].value != "") {
				birthdaycount++;
			}
		}
	}
	if (birthdaycount < childrencount) {
		alert ("Birthday for student under age 18 is required.");
		return false;
	}
	***/
	return true;

}


/*
 *
 * @name 		CheckStaffInfo
 * @args 		None
 * @returns	None
 * @desc		Check submit value for StudentInfo page
 *
 */
function CheckStaffInfo()
{
	if (document.form1.LastName__.value == "") {
		alert ("Last name is missing.");
		return false;
	} 
	else {
		if (document.form1.FirstName__.value == "") {
			alert ("First name is missing.");
			return false;
		} 
		else {
			if (document.form1.Street__.value == "") {
				alert ("You need to enter street address.");
				return false;
			}
			else {
				if (document.form1.City__.value == "") {
					alert ("You need to enter city.");
					return false;
				}
				else {
					if (document.form1.Zip__.value == "") {
						alert ("You need to enter zip code.");
						return false;
					}
					else {
						if (document.form1.HomeTelephone__.value == "") {
							alert ("Home telephone number is required.");
							return false;
						}
						else {
							if (document.form1.FcdRoleNmbr__.selectedIndex < 1) {
								alert ("Role is required.");
								return false;
							}
							else {
								if (document.form1.Password__.value != "") {
									if (document.form1.UserName__.value != "") {
										if (document.form1.ConfirmPassword__.value != "") {
											if (document.form1.Password__.value != document.form1.ConfirmPassword__.value) {
												alert ("The passwords you entered must be exactly the same.  Please try again");
												return false;
											}
											else {
												document.form1.Password__.value = hex_hmac_md5(document.form1.UserName__.value, document.form1.Password__.value);
												return true;
											}
										}
										else {
											alert ("Confirm Password!");
											return false;
										}
									}
									else {
										alert ("User name is required if you want to change the login information!");
										return false;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return true;

}


/*
 *
 * @name 		CheckLogin
 * @args 		1
 * @returns	None
 * @desc		Check login info and encrypt password
 *
 */
function CheckLogin()
{
	if (document.form1.UserName__.value != "") {
		if (document.form1.Password__.value != "") {
			document.form1.Password__.value = hex_hmac_md5(document.form1.UserName__.value, document.form1.Password__.value);
			return true;
		}
		else {
			alert ("Password is empty!");
			return false;
		}
	}
	else {
		alert ("User name is empty!");
		return false;
	}
}


	

/*
 *
 * @name 		CheckRegPeriod
 * @args 		1
 * @returns	None
 * @desc		Check for Registration period
 *
 */
function CheckRegPeriod(pFormElement)
{
	if (!CheckRadioCheckbox(pFormElement)) {
		alert ("Please select which semester to register.");
		return false;
	}
	return true;
	
}


/*
 *
 * @name 		CheckFrameSubjectLanguage
 * @args 		None
 * @returns	None
 * @desc		Check submit value for admin website update
 *
 */
function CheckFrameSubjectLanguage()
{
	if (document.form1.LanguageNmbr__.value == "") {
		alert ("What is the display language?");
		UncheckRadio(document.form1.WebsiteTask__);
		return false;
	}
	if (document.form1.FrameNmbr__.value == "") {
		alert ("Which frame?");
		UncheckRadio(document.form1.WebsiteTask__);
		return false;
	}
	if (document.form1.SubjectID__.value == "") {
		alert ("Which web page?");
		UncheckRadio(document.form1.WebsiteTask__);
		return false;
	}
	return true;
	
}
	
	
/*
 *
 * @name 		CheckUpdateWebsite
 * @args 		None
 * @returns	None
 * @desc		Check submit value for admin website update
 *
 */
function CheckUpdateWebsite()
{
	if (document.form1.WebsiteItemAnnouncement__) {
		if (document.form1.WebsiteItemAnnouncement__.value == "") {
			alert ("Announcement is required.");
			return false;
		}
	}
	else {
		if (document.form1.WebsiteItemTitle__) {
			if (document.form1.WebsiteItemTitle__.value == "") {
				alert ("Title is required.");
				return false;
			}
		}
		if (document.form1.WebsiteItemAbstract__ && document.form1.WebsiteItemFullContent__) {
			if (document.form1.WebsiteItemAbstract__.value != "" && document.form1.WebsiteItemFullContent__.value == "") {
				alert ("Full content is needed for the abstract you entered.");
				return false;
			}
		}
		if (document.form1.WebsiteItemThumbnail__ && document.form1.WebsiteItemImage__) {
			if (document.form1.WebsiteItemThumbnail__.value != "" && document.form1.WebsiteItemImage__.value == "") {
				alert ("Image file name is needed for the thumbnail you entered.");
				return false;
			}
		}
	}
	return true;
	
}


/*
 *
 * @name 		CheckDeleteSection
 * @args 		None
 * @returns	None
 * @desc		Check submit value for admin delete section
 *
 */
function CheckDeleteSection()
{
	if (!CheckCheckboxArray("SectionToDelete[]")) {
		alert ("You need to select at least one title to delete.");
		return false;
	}
	return true;
	
}


/*
 *
 * @name 		CheckUpdatePhotogroup
 * @args 		None
 * @returns	None
 * @desc		Check submit value for admin add photo group section
 *
 */
function CheckUpdatePhotogroup()
{
	if (document.form1.PhotogroupEnglishLabel__) {
		if (document.form1.PhotogroupEnglishLabel__.value == "") {
			alert ("English label is required.");
			return false;
		}
	}
	if (document.form1.PhotogroupChineseLabel__) {
		if (document.form1.PhotogroupChineseLabel__.value == "") {
			alert ("Chinese label is required.");
			return false;
		}
	}
	return true;
	
}


/*
 *
 * @name 		CheckDeletePhotogroup
 * @args 		None
 * @returns	None
 * @desc		Check submit value for admin delete photo group section
 *
 */
function CheckDeletePhotogroup()
{
	if (confirm('This will delete all the photos belonging to the selected group, continue?')) {
		if (!CheckCheckboxArray("PhotogroupToDelete[]")) {
			alert ("You need to select at least one photo group to delete.");
			return false;
		}
	}
	else {
		return false;
	}
	return true;
		
}


/*
 *
 * @name 		HandleEnter
 * @args 		2
 * @returns	None
 * @desc		handles Enter key
 *
 */
function HitEnter(pFormElement, pEvent) {
	var keyCode = pEvent.keyCode ? pEvent.keyCode : pEvent.which ? pEvent.which : pEvent.charCode;
	if (keyCode == 13) {
		return true;
	}
	return false;

}      










/*
 *
 * @name 		CheckRegistrationAdmin
 * @args 		None
 * @returns	None
 * @desc		
 *
 */
function CheckRegistrationAdmin() {
	if (document.form1.SchoolYear__.value != '') {
		if(document.form1.RegDate__.value != '') {
			if (document.form1.RegMethod__.selectedIndex > 0) {
				if(document.form1.FamilyMemberNmbr__.selectedIndex >= 0) {
					if (document.form1.ClassNmbr__.selectedIndex >= 0) {
						return true;
					}
				}
			}
		}
	}
	alert('You need to enter all fields!');
	return false;
}

/*
 *
 * @name 		CheckRegistrationAdminDelete
 * @args 		None
 * @returns	None
 * @desc		
 *
 */
function CheckRegistrationAdminDelete()
{
	if (!CheckRadioCheckbox(document.form1.RegistrationNmbr__)) {
		alert ("You need to select a registration to delete!");
		return false;
	}
	return true;
		
}

/*
 *
 * @name 		CheckSchoolFees
 * @args 		None
 * @returns	None
 * @desc		
 *
 */
function CheckSchoolFees() {
	if (document.form1.SchoolYear__.value != '') {
		if (document.form1.SchoolFeeName_E__.value != '') {
			if (document.form1.SchoolFeeName_C__.value != '') {
				if (document.form1.SchoolFee__.value != '') {
					if (document.form1.EffectiveDate__.value != '') {
						return true;
					}
				}
			}
		}
	}
	alert('You need to enter all fields!');
	return false;
}

/*
 *
 * @name 		CheckSchoolFeesDelete
 * @args 		None
 * @returns	None
 * @desc		
 *
 */
function CheckSchoolFeesDelete()
{
	if (!CheckRadioCheckbox(document.form1.SchoolFeesNmbr__)) {
		alert ("You need to select a school fee to delete!");
		return false;
	}
	return true;
		
}

/*
 *
 * @name 		RegistrationFee
 * @args 		None
 * @returns	None
 * @desc		
 *
 */
function CheckRegistrationFee() {
	if (document.form1.SchoolYear__.value != '') {
		if (document.form1.RegistrationFee__.value != '') {
			if (document.form1.StartDate__.value != '') {
				if (document.form1.EndDate__.value != '') {
					return true;
				}
			}
		}
	}
	alert('You need to enter all fields!');
	return false;
}

/*
 *
 * @name 		CheckRegistrationFeeDelete
 * @args 		None
 * @returns	None
 * @desc		
 *
 */
function CheckRegistrationFeeDelete()
{
	if (!CheckRadioCheckbox(document.form1.RegistrationFeeNmbr__)) {
		alert ("You need to select a registration fee to delete!");
		return false;
	}
	return true;
		
}

/*
 *
 * @name 		CheckTuition
 * @args 		None
 * @returns	None
 * @desc		
 *
 */
function CheckTuition() {
	if (document.form1.SchoolYear__.value != '') {
		if (document.form1.CourseCategoryNmbr__.selectedIndex > 0) {
			if (document.form1.Tuition__.value != '') {
				return true;
			}
		}
	}
	alert('School Year, Course Category, and Tuition are required!');
	return false;
}

/*
 *
 * @name 		CheckTuitionDelete
 * @args 		None
 * @returns	None
 * @desc		
 *
 */
function CheckTuitionDelete()
{
	if (!CheckRadioCheckbox(document.form1.TuitionNmbr__)) {
		alert ("You need to select a tuition to delete!");
		return false;
	}
	return true;
		
}



