<?php
 
// Connect and query the database for the users
$conn = new PDO("mysql:host=localhost;dbname=mydatabase", 'myuser', 'mypassword');
$sql = "SELECT username, email FROM users ORDER BY username";
$results = $conn->query($sql);
 
// Pick a filename and destination directory for the file
// Remember that the folder where you want to write the file has to be writable
$filename = "/tmp/db_user_export_".time().".csv";
 
// Actually create the file
// The w+ parameter will wipe out and overwrite any existing file with the same name
$handle = fopen($filename, 'w+');
 
// Write the spreadsheet column titles / labels
fputcsv($handle, array('Username','Email'));
 
// Write all the user records to the spreadsheet
foreach($results as $row)
{
    fputcsv($handle, array($row['username'], $row['email']));
}
 
// Finish writing the file
fclose($handle);
 
?>