<?php

/**
 *
 *
 * @version $Id$
 * @copyright 2005
 **/

/**
 *
 * @name 		AdminTemplate_SchoolFees
 * @args 		0
 * @return	template display status
 * @desc		Display school fee administration page		
 *
 **/
function AdminTemplate_SchoolFees() {
	$form_status = true;
	$ref_lib = new RefLibrary();
	$school_years = $ref_lib->GetSchoolYear('full_years');
	$schoolfee_handler = new TuitionFeeHandler();
	$school_fees = $schoolfee_handler->GetSchoolFees();
	if (getSession('SchoolFeesNmbr', 0) != '') {
		$selected_schoolfee_info = $schoolfee_handler->GetSchoolFees('', getSession('SchoolFeesNmbr', 0));
		$selected_schoolfee_year = $selected_schoolfee_info[0]['SchoolYear'];
		$selected_schoolfee = $selected_schoolfee_info[0]['Fee'];
		$selected_schoolfee_name_e = $selected_schoolfee_info[0]['FeeName_E'];
		$selected_schoolfee_name_c = $selected_schoolfee_info[0]['FeeName_C'];
		$selected_schoolfee_date = $selected_schoolfee_info[0]['EffectiveDate'];
	}
	else {
		$selected_schoolfee_year = '';
		$selected_schoolfee = '';
		$selected_schoolfee_name_e = '';
		$selected_schoolfee_name_c = '';
		$selected_schoolfee_date = date("Y-m-d");
	}
	setSession('SchoolYear__', $selected_schoolfee_year);
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
							<font size="3" color="darkred"><b>FCD School Fees</b></font><br/>
						</td>
					</tr>
					<tr height="50">
						<td>&nbsp;</td>
					</tr>
        	<tr>
        		<td align="left" style="font-size: 14px;color: darkgreen;">
        			School Year
        			&nbsp;&nbsp;
							<select name="SchoolYear__" size="1" style="width: 150px;">
								<option value=""></option>
								<?php
								for ($i = 0; $i < sizeof($school_years); $i++) {
									echo "<option value=\"" . $school_years[$i]['SchoolYear'] . "\" " . checkSelectedOption("SchoolYear", $school_years[$i]['SchoolYear']) . ">" . $school_years[$i]['SchoolYear']  . "</option>\n";
								}
								?>
							</select>
        		</td>
					</tr>
					<tr>
						<td>&nbsp;</td>
					</tr>
					<tr align="center">
						<td class="contentfont">
		          <table border="0" bgcolor="#C1E8BE" class="thinborder" style="font-size: 12px;">
		          	<tr>
		          		<td width="200" align="right">School Fee Name (English)</td>
		          		<td width="20">&nbsp;</td>
		          		<td width="280" align="left">
										<input type="text" name="SchoolFeeName_E__" value="<?php echo $selected_schoolfee_name_e; ?>" style="width: 250px;" />
		          		</td>
								</tr>
		          	<tr>
		          		<td align="right">School Fee Name (Chinese)</td>
		          		<td>&nbsp;</td>
		          		<td align="left">
										<input type="text" name="SchoolFeeName_C__" value="<?php echo $selected_schoolfee_name_c; ?>" style="width: 250px;" />
		          		</td>
								</tr>
		          	<tr>
		          		<td align="right">Fee ($)</td>
		          		<td>&nbsp;</td>
		          		<td align="left">
										<input type="text" name="SchoolFee__" value="<?php echo $selected_schoolfee; ?>" style="width: 100px;" />
		          		</td>
								</tr>
		          	<tr>
		          		<td align="right">Effective Date</td>
		          		<td>&nbsp;</td>
		          		<td align="left">
										<input type="text" name="EffectiveDate__" value="<?php echo $selected_schoolfee_date; ?>" style="width: 100px;" />
										&nbsp;&nbsp;&nbsp;(yyyy-mm-dd)
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
							onClick="if (CheckSchoolFeesDelete()){document.form1.subjectid__.value='ACCOUNTING';document.form1.subtask__.value='delete_school_fee';document.form1.submit();}" />
							<input type="button" name="Submit" value="Submit" style="width: 100px;font-size: 12px;"
							onClick="if(CheckSchoolFees()){document.form1.subjectid__.value='ACCOUNTING';document.form1.subtask__.value='add_school_fee';document.form1.submit();}" />
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
		          		<td width="230" align="center">School Fee Name</td>
		          		<td width="60" align="center">Fee</td>
		          		<td width="80" align="center">School Year</td>
		          		<td width="80" align="center">Effective Date</td>
								</tr>
<?php
	if (isset($school_fees[0])) {
		for ($i = 0; $i < sizeof($school_fees); $i++) {
?>
		          	<tr>
		          		<td align="center">
		          			<input type="radio" name="SchoolFeesNmbr__" value="<?php echo $school_fees[$i]['SchoolFeesNmbr']; ?>" <?php if (getSession('SchoolFeesNmbr', 0) == $school_fees[$i]['SchoolFeesNmbr']) echo 'checked'; ?>
										onClick="document.form1.subjectid__.value='ACCOUNTING';document.form1.subtask__.value='refresh_school_fee';document.form1.submit();"
		          			/>
		          		</td>
		          		<td align="center">&nbsp;<?php echo $school_fees[$i]['FeeName_E'] . ' (' . $school_fees[$i]['FeeName_C'] . ')'; ?></td>
		          		<td align="center">&nbsp;<?php echo $school_fees[$i]['Fee']; ?></td>
		          		<td align="center">&nbsp;<?php echo $school_fees[$i]['SchoolYear']; ?></td>
		          		<td align="center">&nbsp;<?php echo $school_fees[$i]['EffectiveDate']; ?></td>
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
	return $form_status;
}

/**
 *
 * @name 		AdminTemplate_RegistrationFee
 * @args 		0
 * @return	template display status
 * @desc		Display registration fee administration page		
 *
 **/
function AdminTemplate_RegistrationFee() {
	$form_status = true;
	$ref_lib = new RefLibrary();
	$school_years = $ref_lib->GetSchoolYear('all');
	$regfee_handler = new TuitionFeeHandler();
	$reg_fees = $regfee_handler->GetRegistrationFee();
	if (getSession('RegistrationFeeNmbr', 0) != '') {
		$selected_regfee_info = $regfee_handler->GetRegistrationFee('', getSession('RegistrationFeeNmbr', 0));
		$selected_regfee_year = $selected_regfee_info[0]['SchoolYear'];
		$selected_regfee = $selected_regfee_info[0]['RegistrationFee'];
		$selected_start_date = $selected_regfee_info[0]['StartDate'];
		$selected_end_date = $selected_regfee_info[0]['EndDate'];
	}
	else {
		$selected_regfee_year = '';
		$selected_regfee = '';
		$selected_start_date = date("Y-m-d");
		$selected_end_date = date("Y-m-d");
	}
	setSession('SchoolYear__', $selected_regfee_year);
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
							<font size="3" color="darkred"><b>FCD Registration Fee</b></font><br/>
						</td>
					</tr>
					<tr height="50">
						<td>&nbsp;</td>
					</tr>
        	<tr>
        		<td align="left" style="font-size: 14px;color: darkgreen;">
        			School Year
        			&nbsp;&nbsp;
							<select name="SchoolYear__" size="1" style="width: 150px;">
								<option value=""></option>
								<?php
								for ($i = 0; $i < sizeof($school_years); $i++) {
									echo "<option value=\"" . $school_years[$i]['SchoolYear'] . "\" " . checkSelectedOption("SchoolYear", $school_years[$i]['SchoolYear']) . ">" . $school_years[$i]['SchoolYear']  . "</option>\n";
								}
								?>
							</select>
        		</td>
					</tr>
					<tr>
						<td>&nbsp;</td>
					</tr>
					<tr align="center">
						<td class="contentfont">
		          <table border="0" bgcolor="#C1E8BE" class="thinborder" style="font-size: 12px;">
		          	<tr>
		          		<td width="200" align="right">Registration Fee</td>
		          		<td width="20">&nbsp;</td>
		          		<td width="280" align="left">
										<input type="text" name="RegistrationFee__" value="<?php echo $selected_regfee; ?>" style="width: 250px;" />
		          		</td>
								</tr>
		          	<tr>
		          		<td align="right">Start Date</td>
		          		<td>&nbsp;</td>
		          		<td align="left">
										<input type="text" name="StartDate__" value="<?php echo $selected_start_date; ?>" style="width: 100px;" />
										&nbsp;&nbsp;&nbsp;(yyyy-mm-dd)
		          		</td>
								</tr>
		          	<tr>
		          		<td align="right">End Date</td>
		          		<td>&nbsp;</td>
		          		<td align="left">
										<input type="text" name="EndDate__" value="<?php echo $selected_end_date; ?>" style="width: 100px;" />
										&nbsp;&nbsp;&nbsp;(yyyy-mm-dd)
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
							onClick="if(CheckRegistrationFeeDelete()){document.form1.subjectid__.value='ACCOUNTING';document.form1.subtask__.value='delete_reg_fee';document.form1.submit();}" />
							<input type="button" name="Submit" value="Submit" style="width: 100px;font-size: 12px;"
							onClick="if(CheckRegistrationFee()){document.form1.subjectid__.value='ACCOUNTING';document.form1.subtask__.value='add_reg_fee';document.form1.submit();}" />
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
		          		<td width="120" align="center">School Year</td>
		          		<td width="110" align="center">Registration Fee</td>
		          		<td width="110" align="center">Start Date</td>
		          		<td width="110" align="center">End Date</td>
								</tr>
<?php
	if (isset($reg_fees[0])) {
		for ($i = 0; $i < sizeof($reg_fees); $i++) {
?>
		          	<tr>
		          		<td align="center">
		          			<input type="radio" name="RegistrationFeeNmbr__" value="<?php echo $reg_fees[$i]['RegistrationFeeNmbr']; ?>" <?php if (getSession('RegistrationFeeNmbr', 0) == $reg_fees[$i]['RegistrationFeeNmbr']) echo 'checked'; ?>
										onClick="document.form1.subjectid__.value='ACCOUNTING';document.form1.subtask__.value='refresh_reg_fee';document.form1.submit();"
		          			/>
		          		</td>
		          		<td align="center">&nbsp;<?php echo $reg_fees[$i]['SchoolYear']; ?></td>
		          		<td align="center">&nbsp;<?php echo $reg_fees[$i]['RegistrationFee']; ?></td>
		          		<td align="center">&nbsp;<?php echo $reg_fees[$i]['StartDate']; ?></td>
		          		<td align="center">&nbsp;<?php echo $reg_fees[$i]['EndDate']; ?></td>
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
	return 	$form_status;
}

/**
 *
 * @name 		AdminTemplate_PaymentStatus
 * @args 		0
 * @return	template display status
 * @desc		Display payment status administration page		
 *
 **/
function AdminTemplate_PaymentStatus() {
	$form_status = true;
	if (getSession('FamilyNmbr', 0) == '') { // First page for updating tuition due (list of all family status)
	  $ref_lib = new RefLibrary();
	  $school_years = $ref_lib->GetSchoolYear('full_years');
	  if (getSession('SchoolYear', 0) != '') {
		  $tuition_handler = new TuitionFeeHandler();
		  $payment_status = $tuition_handler->GetTuitionDue(getSession('SchoolYear', 0));
	  }
?>
	<table border="0" width="600" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td>
				<table width="600" align="center" cellspacing="0" cellpadding="0">
					<tr>
						<td>&nbsp;</td>
					</tr>
					<tr>
						<td align="center">
							<font size="3" color="darkred"><b>FCD School Family Dues</b></font><br/>
						</td>
					</tr>
					<tr>
						<td>&nbsp;</td>
					</tr>
					<tr align="left">
						<td class="contentfont">
		          <table border="0" style="font-size: 12px;">
		          	<tr>
		          		<td align="right">School Year</td>
		          		<td>&nbsp;</td>
		          		<td>
										<select name="SchoolYear__" size="1" style="width: 150px;"
										onChange="document.form1.subjectid__.value='ACCOUNTING';document.form1.subtask__.value='refresh_tuitiondue';document.form1.submit();"
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
		          </table>
		        </td>
		      </tr>
					<tr>
						<td>&nbsp;</td>
					</tr>
					<tr align="center">
						<td class="contentfont">
		          <table border="1" bgcolor="#C1E8BE" class="thinborder" style="font-size: 12px;">
		          	<tr>
		          		<td width="50" align="center">&nbsp;</td>
		          		<td width="150" align="center">Family ID</td>
		          		<td width="100" align="center">Due ($)</td>
		          		<td width="100" align="center">Paid ($)</td>
		          		<td width="100" align="center">Refund ($)</td>
		          		<td width="100" align="center">Status</td>
								</tr>
<?php
	  if (isset($payment_status[0])) {
		  for ($i = 0; $i < sizeof($payment_status); $i++) {
?>
		          	<tr>
		          		<td align="center">&nbsp;
										<input type="radio" name="FamilyNmbr__" value="<?php echo $payment_status[$i]['FamilyNmbr']; ?>" />
		          		</td>
		          		<td align="center">&nbsp;
										<?php echo $payment_status[$i]['FamilyID']; ?>
		          		</td>
		          		<td align="center">&nbsp;
										<?php echo $payment_status[$i]['TotalFeeTuition']; ?>
		          		</td>
		          		<td align="center">&nbsp;
										<?php echo $payment_status[$i]['FeeTuitionPaid']; ?>
		          		</td>
		          		<td align="center">&nbsp;
										<?php echo $payment_status[$i]['Refund']; ?>
		          		</td>
		          		<td align="center">&nbsp;
										<?php echo $payment_status[$i]['Status']; ?>
		          		</td>
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
	<table border="0" width="500" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td align="right">
				<input type="button" name="Submit" value="Back to management page" style="width: 180px;font-size: 12px;"
				onClick="document.form1.subjectid__.value='CANCELSUBTASK';document.form1.subtask__.value='';document.form1.submit();" />
				<input type="button" name="Submit" value="Next" style="width: 100px;font-size: 12px;"
				onClick="
        if (CheckRadioCheckbox(document.form1.FamilyNmbr__)) {
          document.form1.subjectid__.value='ACCOUNTING';document.form1.subtask__.value='edit_payment_status_next';document.form1.submit();
        }
        else {
          alert('You need to select a family.');
        }
        " />
		  </td>
		</tr>
	</table>
<?php
  }
  else { // Second page for updating tuition due
	  $ref_lib = new RefLibrary();
	  $school_years = $ref_lib->GetSchoolYear('full_years');
	  if (getSession('SchoolYear', 0) != '') {
		  $tuition_handler = new TuitionFeeHandler();
		  $payment_status = $tuition_handler->GetTuitionDue(getSession('SchoolYear', 0), getSession('FamilyNmbr', 0));
	  }
?>
	<table border="0" width="600" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td>
				<table width="600" align="center" cellspacing="0" cellpadding="0">
					<tr>
						<td>&nbsp;</td>
					</tr>
					<tr>
						<td align="center">
							<font size="3" color="darkred"><b>FCD School Family Dues</b></font><br/>
						</td>
					</tr>
					<tr>
						<td>&nbsp;</td>
					</tr>
					<tr align="center">
						<td class="contentfont">
		          <table border="0" class="noborder" style="font-size: 12px;">
		          	<tr>
		          		<td width="180" align="right"><b>Family ID</b></td>
		          		<td width="20" align="center">&nbsp;</td>
		          		<td width="400" align="left"><?php echo $payment_status[0]['FamilyID']; ?></td>
								</tr>
		          	<tr>
		          		<td align="right"><b>School Year:</b></td>
		          		<td align="center">&nbsp;</td>
		          		<td align="left"><?php echo getSession('SchoolYear', 0); ?></td>
								</tr>
              </table>
              <br/>
		          <table border="0" bgcolor="#C1E8BE" class="thinborder" style="font-size: 12px;">
		          	<tr>
		          		<td width="180" align="right">Due:</td>
		          		<td width="20" align="center">&nbsp;</td>
		          		<td width="400" align="left">$<?php echo $payment_status[0]['TotalFeeTuition']; ?></td>
								</tr>
		          	<tr>
		          		<td align="right">Paid:</td>
		          		<td align="center">&nbsp;</td>
		          		<td align="left">
										<input type="text" name="TuitionPaid__" value="<?php echo $payment_status[0]['FeeTuitionPaid']; ?>" style="width: 150px;" />
		          		</td>
								</tr>
		          	<tr>
		          		<td align="right">Check Number:</td>
		          		<td align="center">&nbsp;</td>
		          		<td align="left">
										<input type="text" name="CheckNmbr__" value="<?php echo $payment_status[0]['CheckNmbr']; ?>" style="width: 150px;" />
		          		</td>
								</tr>
		          	<tr>
		          		<td align="right">Refund:</td>
		          		<td align="center">&nbsp;</td>
		          		<td align="left">
										<input type="text" name="Refund__" value="<?php echo $payment_status[0]['Refund']; ?>" style="width: 150px;" />
		          		</td>
								</tr>
		          	<tr>
		          		<td align="right">Refund Check Number:</td>
		          		<td align="center">&nbsp;</td>
		          		<td align="left">
										<input type="text" name="RefundCheckNmbr__" value="<?php echo $payment_status[0]['RefundCheckNmbr']; ?>" style="width: 150px;" />
		          		</td>
								</tr>
		          	<tr>
		          		<td align="right" valign="top">Note:</td>
		          		<td align="center">&nbsp;</td>
		          		<td align="left">
								    <textarea name="RegNote__" cols="30" rows="2"><?php echo $payment_status[0]['Note']; ?></textarea>
		          		</td>
								</tr>
		          	<tr>
		          		<td align="right">Status:</td>
		          		<td align="center">&nbsp;</td>
		          		<td align="left">
										<select name="RegStatus__" size="1" style="width: 100px;">
											<option value="OPEN" <?php if ($payment_status[0]['Status'] == 'OPEN') echo 'selected'; ?>>Open</option>
											<option value="CLOSED" <?php if ($payment_status[0]['Status'] == 'CLOSED') echo 'selected'; ?>>Closed</option>
										</select>
		          		</td>
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
	<table border="0" width="600" align="center" cellspacing="0" cellpadding="0">
		<tr>
			<td align="right">
				<input type="button" name="Submit" value="Cancel" style="width: 180px;font-size: 12px;"
				onClick="document.form1.subjectid__.value='ACCOUNTING';document.form1.subtask__.value='back_to_payment_status_list';document.form1.submit();" />
				<input type="button" name="Submit" value="Update" style="width: 100px;font-size: 12px;"
				onClick="document.form1.subjectid__.value='ACCOUNTING';document.form1.subtask__.value='submit_payment_status';document.form1.submit();" />
		  </td>
		</tr>
	</table>
<?php
  }
  return 	$form_status;
}

/**
 *
 * @name 		AdminTemplate_Tuition
 * @args 		0
 * @return	template display status
 * @desc		Display tuition administration page		
 *
 **/
function AdminTemplate_Tuition() {
	$form_status = true;
	$ref_lib = new RefLibrary();
	$school_years = $ref_lib->GetSchoolYear('all');
	if (getSession('SchoolYear', 0) != '') {
		$course_categories = $ref_lib->GetRefValues('REF_CourseCategory');
		$tuition_handler = new TuitionFeeHandler();
		$tuitions = $tuition_handler->GetTuition(getSession('SchoolYear', 0));
	}
	if (getSession('TuitionNmbr', 0) != '') {
		$selected_tuitionfee = $tuition_handler->GetTuition(getSession('SchoolYear', 0), getSession('TuitionNmbr', 0));
		$selected_course_catnmbr = $selected_tuitionfee[0]['CourseCategoryNmbr'];
		$selected_tuition = $selected_tuitionfee[0]['Tuition'];
		$selected_bookfee = $selected_tuitionfee[0]['BookFee'];
		$selected_labfee = $selected_tuitionfee[0]['LabFee'];
		$selected_otherfee = $selected_tuitionfee[0]['OtherFee'];
	}
	else {
		$selected_course_catnmbr = '';
		$selected_tuition = '';
		$selected_bookfee = '';
		$selected_labfee = '';
		$selected_otherfee = '';
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
							<font size="3" color="darkred"><b>FCD School Tuition and Class Fees</b></font><br/>
						</td>
					</tr>
					<tr height="50">
						<td>&nbsp;</td>
					</tr>
        	<tr>
        		<td align="left" style="font-size: 14px;color: darkgreen;">
        			School Year
        			&nbsp;&nbsp;
							<select name="SchoolYear__" size="1" style="width: 150px;"
							onChange="document.form1.subjectid__.value='ACCOUNTING';document.form1.subtask__.value='refresh_tuition';document.form1.submit();"
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
					<tr>
						<td>&nbsp;</td>
					</tr>
					<tr align="center">
						<td class="contentfont">
		          <table border="0" bgcolor="#C1E8BE" class="thinborder" style="font-size: 12px;">
		          	<tr>
		          		<td width="150">&nbsp;</td>
		          		<td width="20">&nbsp;</td>
		          		<td width="330">&nbsp;</td>
								</tr>
		          	<tr>
		          		<td align="right">Course Category</td>
		          		<td>&nbsp;</td>
		          		<td>
										<select name="CourseCategoryNmbr__" size="1" style="width: 250px;">
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
		          	<tr>
		          		<td align="right">Tuition</td>
		          		<td>&nbsp;</td>
		          		<td>
										<input type="text" name="Tuition__" value="<?php echo $selected_tuition; ?>" style="width: 100px;" />
		          		</td>
								</tr>
		          	<tr>
		          		<td align="right">Book Fee</td>
		          		<td>&nbsp;</td>
		          		<td>
										<input type="text" name="BookFee__" value="<?php echo $selected_bookfee; ?>" style="width: 100px;" />
		          		</td>
								</tr>
		          	<tr>
		          		<td align="right">Lab Fee</td>
		          		<td>&nbsp;</td>
		          		<td>
										<input type="text" name="LabFee__" value="<?php echo $selected_labfee; ?>" style="width: 100px;" />
		          		</td>
								</tr>
		          	<tr>
		          		<td align="right">Other Fee</td>
		          		<td>&nbsp;</td>
		          		<td>
										<input type="text" name="OtherFee__" value="<?php echo $selected_otherfee; ?>" style="width: 100px;" />
		          		</td>
								</tr>
		          	<tr>
		          		<td>&nbsp;</td>
		          		<td>&nbsp;</td>
		          		<td>&nbsp;</td>
								</tr>
		          </table>
		        </td>
		      </tr>
					<tr height="50" valign="center">
						<td align="right">
							<input type="button" name="Submit" value="Back to management page" style="width: 180px;font-size: 12px;"
							onClick="document.form1.subjectid__.value='CANCELSUBTASK';document.form1.subtask__.value='';document.form1.submit();" />
							<input type="button" name="Submit" value="Delete" style="width: 100px;font-size: 12px;"
							onClick="if(CheckTuitionDelete()){document.form1.subjectid__.value='ACCOUNTING';document.form1.subtask__.value='delete_tuition';document.form1.submit()};" />
							<input type="button" name="Submit" value="Submit" style="width: 100px;font-size: 12px;"
							onClick="if(CheckTuition()){document.form1.subjectid__.value='ACCOUNTING';document.form1.subtask__.value='add_tuition';document.form1.submit();}" />
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
		          		<td width="170" align="center">Course Category</td>
		          		<td width="70" align="center">Tuition</td>
		          		<td width="70" align="center">Book Fee</td>
		          		<td width="70" align="center">Lab Fee</td>
		          		<td width="70" align="center">Other Fee</td>
								</tr>
<?php
	if (isset($tuitions[0])) {
		for ($i = 0; $i < sizeof($tuitions); $i++) {
?>
		          	<tr>
		          		<td align="center">
		          			<input type="radio" name="TuitionNmbr__" value="<?php echo $tuitions[$i]['TuitionNmbr']; ?>" <?php if (getSession('TuitionNmbr', 0) == $tuitions[$i]['TuitionNmbr']) echo 'checked'; ?>
										onClick="document.form1.subjectid__.value='ACCOUNTING';document.form1.subtask__.value='refresh_tuition';document.form1.submit();"
		          			/>
		          		</td>
		          		<td><?php echo $tuitions[$i]['CourseCategory_E'] . ' (' . $tuitions[$i]['CourseCategory_C'] . ')'; ?></td>
		          		<td align="center"><?php echo $tuitions[$i]['Tuition']; ?></td>
		          		<td align="center"><?php echo $tuitions[$i]['BookFee']; ?></td>
		          		<td align="center"><?php echo $tuitions[$i]['LabFee']; ?></td>
		          		<td align="center"><?php echo $tuitions[$i]['OtherFee']; ?></td>
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
	return 	$form_status;
}

/**
 *
 * @name 		AdminTemplate_Accounting_ViewReport
 * @args 		0
 * @return	template display status
 * @desc		Display accounting report administration page		
 *
 **/
function AdminTemplate_Accounting_ViewReport($pTarget) {
	$form_status = true;
	switch ($pTarget) {
		case "regist":
			break;
		case "under_construction":
?>
	<table border="0" width="500" align="center" cellspacing="0" cellpadding="0">
		<tr height="300"> 
			<td align="center">
				<b>Under Construction ...... </b>
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
	return 	$form_status;
}



?>

