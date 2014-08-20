<?php
/**
 *
 * @name 		GetAdmin
 * @args 		1
 *					args[0] = subtask
 * @return	admin website template
 * @desc		
 *
 **/
function GetAdmin($pTask)
{
?>
	<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
	<html>
	<head>
	<title>fcdschool admin</title>
	<meta http-equiv="Content-Type" content="text/html"; charset="UTF-8">
	<link rel="stylesheet" type="text/css" href="stylesheet/fcd.css" />
	<script src="./javascript/FCD.js"></script>
	</head>
	
	<body leftmargin="0" topmargin="0">
	<!-- ***************************************** -->
	<!--								Frame 1										 -->
	<!-- ***************************************** -->
		<img src="./images/logo.gif" border="0" width="800"/-->
		<form name="form1" method="post" enctype="multipart/form-data" action="FCD_AdminMain.php">
		<table border="0" width="800">
			<tr>
				<td align="right">
				<?php if ($pTask == 'Login') { ?>
				&nbsp;
				<?php } else { ?>
				<a href="FCD_AdminMain.php?_Task=logout">log out</a>
				<?php } ?>
				</td>
			</tr>
			<tr>
				<td align="center">
					<img src="./images/adminBG.gif" width="250">
				</td>
			</tr>
<?php
	switch ($pTask) {
		case "Login":
			GetLogin();
			break;
		case "Options":
			GetAdminOptions();
			break;
		case "BackToOptions":
			unsetSessionForAdminCancel();
			GetAdminOptions();
			break;
		case "BackToRegOptions":
			unsetSessionForAdminCancel();
			GetManageRegistration();
			break;
		case "SelectFrame":
			unsetSessionForChangeFrame();
			GetManageWebsite();
			break;
		case "SelectSubject":
			unsetSessionForChangeSubject();
			GetManageWebsite();
			break;
		case "ManageWebsite":
			GetManageWebsite();
			break;
		case "RefreshManageWebsite":
			GetManageWebsite();
			break;
		case "UpdateWebsite":
			AdmUpdateWebsite(getSession('LanguageNmbr', 0));
			GetManageWebsite();
			break;
		case "DeleteSection":
			for ($i = 0; $i < sizeof($_SESSION['SectionToDelete']); $i++) {
				AdmDeleteSection(getSession('SectionToDelete', $i));
			}
			GetManageWebsite();
			break;
		case "UpdatePhotogroup":
			AdmUpdatePhotogroup(getSession('PhotogroupEnglishLabel', 0), getSession('PhotogroupChineseLabel', 0));
			GetManageWebsite();
			break;
		case "DeletePhotogroup":
			for ($i = 0; $i < sizeof($_SESSION['PhotogroupToDelete']); $i++) {
				AdmDeletePhotogroup(getSession('PhotogroupToDelete', $i));
			}
			GetManageWebsite();
			break;
		case "ManageRegistration":
			GetManageRegistration();
			break;
		case "ViewRegFamilies":
			GetRegisteredFamilies();
			break;
		case "DisplayFamilyInfo":
			GetDisplayFamilyInfo(getSession('FamilyNmbr', 0));
			break;
		case "UpdateTuitionStatus":
			AdmUpdateTuitionStatus();
			GetRegisteredFamilies();
			break;

		case "ManageRootStuff":
			GetManageRootStuff();
			break;
		case "SubmitRootStuff":
			AdmRootStuff();
			GetManageRootStuff();
			break;
		default:
			GetAdminOptions();
	}
?>
		</table>
		</form>
		<p>&nbsp;</p>
		

	</body>
	</html>
<?php
}

/**
 *
 * @name 		GetManageWebsite
 * @args 		none
 * @return	admin website template
 * @desc		
 *
 **/
function GetManageWebsite() {
	$framearray = AdmGetReferenceTable('PAGE_Frame', '', '');
	$subjectarray = AdmGetReferenceTable('REF_Subject', 'SubjectType', 'dynamic');
	$languagearray = AdmGetReferenceTable('REF_Language', '', '');
?>
	<table border="0" width="500" align="center" cellspacing="0" cellpadding="0">
			<tr>
				<td align="center">
					<table width="500" border="0" align="center">
					<tr>
						<td>&nbsp;</td>
					</tr>
						<tr>
							<td align="center">
								<font size="3" color="darkred"><b>FCD Website Management</b></font><br/>
							</td>
						</tr>
						<tr height="50">
							<td>&nbsp;</td>
						</tr>
						<tr>
							<td class="labelfont">Edit this frame:</td>
						</tr>
				    <tr>
				      <td align="left"> 
								<select name="FrameNmbr__" size="1" style="width: 150px"
								onChange="document.form1.subjectid__.value='WEBSITE';document.form1.subtask__.value='refresh_website';document.form1.submit();" />
									<option value=""></option>
<?php
	for ($m = 0; $m < sizeof($framearray); $m++) {
		if ($m > 0) {
?>
									<option value="<?php echo $framearray[$m]['FrameNmbr']; ?>"
									<?php if (getSession('FrameNmbr', 0) == $framearray[$m]['FrameNmbr']) echo ' selected'; ?>><?php echo $framearray[$m]['FrameName']; ?></option>
<?php
		}
	}
?>
								</select>
				      </td>
				    </tr>
<?php
	if (getSession('FrameNmbr', 0) != 2) {
?>
						<tr>
							<td class="labelfont">Edit this web page:</td>
						</tr>
				    <tr>
				      <td align="left"> 
								<select name="SubjectID__" size="1" style="width: 350px"
								onChange="document.form1.subjectid__.value='WEBSITE';document.form1.subtask__.value='refresh_website';document.form1.submit();" />
<?php
		if (getSession('FrameNmbr', 0) == 4) {
?>
									<option value="ROLLINGTEXT">Rolling announcement</option>
<?php
		}
		elseif (getSession('FrameNmbr', 0) == 5) {
?>
									<option value="NOTICE">Notice</option>
<?php
		}
		else {
?>
									<option value=""></option>
<?php
			for ($n = 0; $n < sizeof($subjectarray); $n++) {
				if ($subjectarray[$n]['SubjectID'] != 'ROLLINGTEXT' && $subjectarray[$n]['SubjectID'] != 'NOTICE') {
?>
									<option value="<?php echo $subjectarray[$n]['SubjectID']; ?>"
									<?php if (getSession('SubjectID', 0) == $subjectarray[$n]['SubjectID']) echo ' selected'; ?>><?php echo $subjectarray[$n]['Subject_E'] . '('. $subjectarray[$n]['Subject_C'] . ')'; ?></option>
<?php
				}
			}
		}
?>
								</select>
				      </td>
				    </tr>
<?php
	}
	if (getSession('FrameNmbr', 0) != 2) {
?>
						<tr>
							<td class="labelfont">Language:</td>
						</tr>
				    <tr>
				      <td align="left"> 
								<select name="LanguageNmbr__" size="1" style="width: 150px" 
								onChange="document.form1.subjectid__.value='WEBSITE';document.form1.subtask__.value='refresh_website';document.form1.submit();" />
									<option value=""></option>
<?php
		for ($k = 0; $k < sizeof($languagearray); $k++) {
?>
									<option value="<?php echo $languagearray[$k]['LanguageNmbr']; ?>" 
									<?php if (getSession('LanguageNmbr', 0) == $languagearray[$k]['LanguageNmbr']) echo ' selected'; ?>><?php echo $languagearray[$k]['Language']; ?></option>
<?php
		}
?>
								</select>
				      </td>
				    </tr>
<?php
	}
?>
						<tr>
							<td class="labelfont">Select task:</td>
						</tr>
				    <tr>
				      <td align="left" class="labelfont">
<?php
	if (getSession('FrameNmbr', 0) != 2) {
?>
								<input type="radio" name="WebsiteTask__" value="UpdateWebsite" 
								<?php if (getSession('WebsiteTask', 0) == 'UpdateWebsite') echo ' checked'; ?>
								onClick="document.form1.subjectid__.value='WEBSITE';document.form1.subtask__.value='refresh_website';if (CheckFrameSubjectLanguage()) document.form1.submit();" />
								&nbsp;&nbsp;Add
								<input type="radio" name="WebsiteTask__" value="DeleteSection" 
								<?php if (getSession('WebsiteTask', 0) == 'DeleteSection') echo ' checked'; ?>
								onClick="document.form1.subjectid__.value='WEBSITE';document.form1.subtask__.value='refresh_website';if (CheckFrameSubjectLanguage()) document.form1.submit();" />
								&nbsp;&nbsp;Delete
<?php
	}
	else {
?>
								<input type="radio" name="WebsiteTask__" value="UpdatePhotogroup" <?php if (getSession('WebsiteTask', 0) == 'UpdatePhotogroup') echo ' checked'; ?>
								onClick="document.form1.subjectid__.value='WEBSITE';document.form1.subtask__.value='refresh_website';document.form1.submit();" />
								&nbsp;&nbsp;Add photo group
								<input type="radio" name="WebsiteTask__" value="DeletePhotogroup" <?php if (getSession('WebsiteTask', 0) == 'DeletePhotogroup') echo ' checked'; ?>
								onClick="document.form1.subjectid__.value='WEBSITE';document.form1.subtask__.value='refresh_website';document.form1.submit();" />
								&nbsp;&nbsp;Delete photo group
<?php
	}
?>
				      </td>
				    </tr>
				  </table>
					<table width="500" border="0" align="center">
				    <tr>
				      <td height="50"> 
								<hr/>
				      </td>
				    </tr>
				  </table>
<?php
	if (getSession('WebsiteTask', 0) == 'UpdateWebsite') {
		if (getSession('FrameNmbr', 0) == '4') {
?>
					<table width="500" border="0" align="center">
						<tr>
							<td class="labelfont">
								<b>Announcement Message:</b><br/>
								<font color="#686868">(Please make it as short as possible):</font>
							</td>
						</tr>
				    <tr>
				      <td align="left" class="labelfont"> 
								<input type="text" name="WebsiteItemAnnouncement__" size="50" />
				      </td>
				    </tr>
				  </table>
<?php
		}
		else {
?>
					<table width="500" border="0" align="center">
						<tr>
							<td class="labelfont"><b>Author:</b></td>
						</tr>
				    <tr>
				      <td align="left" class="labelfont"> 
								<input type="text" name="WebsiteItemAuthor__" size="30" />
				      </td>
				    </tr>
						<tr>
							<td class="labelfont"><b>Title:</b></td>
						</tr>
				    <tr>
				      <td align="left" class="labelfont"> 
								<input type="text" name="WebsiteItemTitle__" size="40" />
				      </td>
				    </tr>
						<tr>
							<td class="labelfont"><b>Sub-Title:</b></td>
						</tr>
				    <tr>
				      <td align="left" class="labelfont"> 
								<input type="text" name="WebsiteItemSubtitle__" size="40" />
				      </td>
				    </tr>
				  </table>
<?php
			if (substr(getSession('SubjectID', 0), 0, 6) != 'ALBUM-') {
?>
					<table width="500" border="0" align="center">
<?php
				if (getSession('LoginRole', 0) == 'NOBODY') {
?>
						<tr>
							<td class="labelfont"><b>Abstract:</b></td>
						</tr>
				    <tr>
				      <td align="left" class="labelfont"> 
								<textarea name="WebsiteItemAbstract__" cols="40" rows="3"></textarea>
				      </td>
				    </tr>
<?php
				}
				if (getSession('SubjectID', 0)	!= 'CSLHOMEWORK') {
?>
						<tr>
							<td class="labelfont"><b>Full content:</b></td>
						</tr>
				    <tr>
				      <td align="left" class="labelfont"> 
								<textarea name="WebsiteItemFullContent__" cols="40" rows="5"></textarea>
				      </td>
				    </tr>
<?php
				}
?>
				  </table>
<?php
			}
?>
					<table width="500" border="0" align="center">
<?php
			if (getSession('SubjectID', 0)	!= 'NEWS'
			&&  getSession('SubjectID', 0)	!= 'STUDENTWORK'
			&&  getSession('SubjectID', 0)	!= 'FORUM'
			&&  getSession('SubjectID', 0)	!= 'PARENTMAILBOX'
			&&  getSession('SubjectID', 0)	!= 'TEACHING'
			&&  getSession('SubjectID', 0)	!= 'CSLHOMEWORK'
			) {
?>
						<tr>
							<td class="labelfont">
								<b>Image file name (thumbnail):</b><br/>
								<font color="#686868">Note: The image file for the thumbnail should be less than 8 KB</font>
							</td>
						</tr>
				    <tr>
				      <td align="left" class="labelfont"> 
								<input type="file" name="WebsiteItemThumbnail__" size="30" />
							</td>
				    </tr>
<?php
			}
?>
						<tr>
							<td class="labelfont">
								<b>Image file name (original):</b><br/>
							</td>
						</tr>
				    <tr>
				      <td align="left" class="labelfont"> 
								<input type="file" name="WebsiteItemImage__" size="30" />
				      </td>
				    </tr>
				  </table>
<?php
			if (getSession('LoginRole', 0) == 'Administrator') {
?>
					<table width="500" border="0" align="center">
						<tr>
							<td class="labelfont"><b>Html file name:</b></td>
						</tr>
				    <tr>
				      <td align="left" class="labelfont"> 
								<input type="text" name="WebsiteItemHtml__" size="40" />
				      </td>
				    </tr>
				  </table>

<?php 
			}
/**************** 
?>
					<table width="500" border="0" align="center">
						<tr>
							<td class="labelfont">URL:</td>
						</tr>
				    <tr>
				      <td align="left" class="labelfont"> 
								<input type="text" name="WebsiteItemUrl__" size="40" />
				      </td>
				    </tr>
						<tr>
							<td class="labelfont">URL display label:</td>
						</tr>
				    <tr>
				      <td align="left" class="labelfont"> 
								<input type="text" name="WebsiteItemUrlText__" size="40" />
				      </td>
				    </tr>
				  </table>
<?php 
****************/
		}
	}
	if (getSession('WebsiteTask', 0) == 'DeleteSection') {
		$titlearray = AdmGetAllSectionTitles(getSession('FrameNmbr', 0), getSession('SubjectID', 0), getSession('LanguageNmbr', 0));
?>
					<table width="550" border="1" align="center">
						<tr>
							<td width="50">&nbsp;</td>
				      <td width="500" align="center" class="labelfont">Current Title(s)</td>
						</tr>
<?php
		for ($i = 0; $i < sizeof($titlearray); $i++) {
?>
				    <tr>
							<td>&nbsp;<input type="checkbox" name="SectionToDelete[]" value="<?php echo $titlearray[$i]['SectionNmbr']; ?>"/></td>
							<td>&nbsp;<?php echo $titlearray[$i]['Content']; ?></td>
				    </tr>
<?php
		}
?>
				  </table>
<?php
	}
	if (getSession('WebsiteTask', 0) == 'UpdatePhotogroup') {
?>
					<table width="550" border="0" align="center">
						<tr>
							<td class="labelfont">
								The following label will appear as the sub-menu for the Photo link.
								Please make the label as SHORT as possible.
							</td>
						</tr>
						<tr>
							<td>&nbsp;</td>
						</tr>
						<tr>
							<td class="labelfont">Display label (English):</td>
						</tr>
				    <tr>
				      <td align="left" class="labelfont"> 
								<input type="text" name="PhotogroupEnglishLabel__" size="20" />
				      </td>
				    </tr>
						<tr>
							<td class="labelfont">Display label (中文):</td>
						</tr>
				    <tr>
				      <td align="left" class="labelfont"> 
								<input type="text" name="PhotogroupChineseLabel__" size="20" />
				      </td>
				    </tr>
				  </table>
<?php
	}
	if (getSession('WebsiteTask', 0) == 'DeletePhotogroup') {
		$labelarray = AdmGetReferenceTable('REF_Subject', 'SubjectType', 'dynamic');
?>
					<table width="550" border="1" align="center">
						<tr>
							<td width="50">&nbsp;</td>
				      <td width="500" align="center" class="labelfont">Photo Group Label(s)</td>
						</tr>
<?php
		for ($i = 0; $i < sizeof($labelarray); $i++) {
			if (substr($labelarray[$i]['SubjectID'], 0, 5) == "ALBUM") {
?>
				    <tr>
							<td>&nbsp;<input type="checkbox" name="PhotogroupToDelete[]" value="<?php echo $labelarray[$i]['SubjectID']; ?>"/></td>
							<td>&nbsp;<?php echo $labelarray[$i]['Subject_E'] . '(' . $labelarray[$i]['Subject_C'] . ')'; ?></td>
				    </tr>
<?php
			}
		}
?>
				  </table>
<?php
	}
?>
					<table width="500" border="0" align="center">
				    <tr>
				      <td align="right"> 
				        <input type="button" name="BackToOptions" value="Cancel" class="smallwhitesubmit"
								onClick="document.form1.subjectid__.value='WEBSITE';document.form1.subtask__.value='cancel_website';document.form1.submit();" />
				        <input type="button" name="Reg" value="Submit" class="smallwhitesubmit"
								onClick="document.form1.subjectid__.value='WEBSITE';document.form1.subtask__.value='submit_update_website';if (Check<?php echo getSession('WebsiteTask', 0); ?>())document.form1.submit();" />
				      </td>
				    </tr>
				  </table>
				</td>
			</tr>
			<tr>
				<td height="10">&nbsp;</td>
			</tr>
	</table>
<?php
}

/**
 *
 * @name 		GetManageRootStuff
 * @args 		none
 * @return	admin website template
 * @desc		
 *
 **/
function GetManageRootStuff()
{
?>
			<tr>
				<td height="50">&nbsp;<input type="hidden" name="_Task" value="" /></td>
			</tr>
			<tr>
				<td align="right">
					<table width="500" border="0" align="center">
				    <tr>
				      <td align="left">
				      	update &nbsp;&nbsp;
				        <input type="text" name="TableName__" size="30" value="<?php echo getSession('TableName', 0); ?>"/>
				      </td>
				    </tr>
				    <tr>
				      <td align="left">
				      	set &nbsp;&nbsp;
				        <input type="text" name="SetColumnName__" size="30" value="<?php echo getSession('SetColumnName', 0); ?>"/>
				      </td>
				    </tr>
				    <tr>
				      <td align="left">
				      	= &nbsp;&nbsp;
				        <input type="text" name="SetValue__" size="30" value="<?php echo getSession('SetValue', 0); ?>"/>
				      </td>
				    </tr>
				    <tr>
				      <td align="left">
				      	where &nbsp;&nbsp;
				        <input type="text" name="WhereColumnName__" size="30" value="<?php echo getSession('WhereColumnName', 0); ?>"/>
				      </td>
				    </tr>
				    <tr>
				      <td align="left">
				      	= &nbsp;&nbsp;
				        <input type="text" name="WhereValue__" size="30" value="<?php echo getSession('WhereValue', 0); ?>"/>
				      </td>
				    </tr>
				    <tr>
				      <td align="right"> 
				        <input type="submit" name="SubmitRootStuff" value="Submit" class="bigwhitesubmit"
								onClick="document.form1._Task.value='SubmitRootStuff';" />
				      </td>
				    </tr>
				    <tr>
				      <td align="right"> 
				        <input type="button" name="BackToOptions" value="Cancel" class="smallwhitesubmit"
								onClick="document.form1._Task.value='BackToOptions'; document.form1.submit();" />
				      </td>
				    </tr>
				  </table>
				</td>
			</tr>
			<tr>
				<td height="20">&nbsp;</td>
			</tr>
<?php
}








?>










