<?php

	require_once("lib/class_Account.php");
	require_once("lib/connect_db.php");
	



	//---------Create Table 1 'login'

	$table_name="login";		

	$field_1="id INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY";

	$field_2="username varchar(100) NOT NULL";

	$field_3="password varchar(100) NOT NULL";



	$sql = "CREATE TABLE $table_name ($field_1,

		$field_2,$field_3)";

	openConnection();
	
	mysqli_query ($conn,$sql);

	$sql="INSERT INTO $table_name (id,username,password) VALUES (1,'admin','admin')";

	mysqli_query ($conn,$sql);

	mysqli_close($conn);

	//-----------END---------------------

	

	//----------Create Table 2 'garden'

	//Second Table

	$table_name_2='garden';

	$field_2_1=$field_1;

	$field_2_2="temperature INT(3) UNSIGNED";

	$field_2_3="soil_moisture INT(3) UNSIGNED";
	$field_2_extra_1="moisture INT(3) UNSIGNED";

	$field_2_4="setup_high_tempe INT(3) UNSIGNED";

	$field_2_5="setup_low_tempe INT(3) UNSIGNED";

	$field_2_6="setup_high_soil_moisture INT(3) UNSIGNED";

	$field_2_7="setup_low_soil_moisture INT(3) UNSIGNED";
	$field_2_extra_2="setup_high_moisture INT(3) UNSIGNED";
	$field_2_extra_3="setup_low_moisture INT(3) UNSIGNED";
	$field_2_8="isWatering BOOLEAN";

	$field_2_9="mode BOOLEAN";

	openConnection();

	$sql = "CREATE TABLE $table_name_2 ($field_2_1, $field_2_2,$field_2_extra_1,$field_2_3, $field_2_4, $field_2_5, $field_2_6, $field_2_7,$field_2_extra_2,$field_2_extra_3,$field_2_8, $field_2_9)";

	mysqli_query ($conn,$sql);

	$sql="INSERT INTO $table_name_2 (id,temperature, 	soil_moisture,moisture,setup_high_tempe,setup_low_tempe,setup_high_soil_moisture,setup_low_soil_moisture,setup_high_moisture,setup_low_moisture,isWatering,mode) VALUES (1,0,0,0,0,0,0,0,0,0,0,1)";

	mysqli_query ($conn,$sql);

	mysqli_close($conn);

	//End Second Table

	//----------END--------------------



	

	



	function isUsernameExist($acc)

	{

		global $account;

		global $conn;

		$account=$acc;

		$table_name=$account->getTableName();

		$user=$account->getUsername();

		

		$sql="select * from $table_name where username='$user'";

		openConnection();

		$result=mysqli_query ($conn,$sql);

		if($result->num_rows >0){

			return true;

		} 

		else {

			$conn->close();

			return false;

		}

	}



	function insertNewAccount($acc)

	{

		openConnection();

		global $account;

		global $conn;

		global $table_name;	

		$account=$acc;

		$username=$account->getUserName();

		$password=$account->getPassword();

		$sql="insert into $table_name(username,password) values ('$username','$password')";

		if($conn->query($sql))

		{

			return true;

		}else {return false;}

	}



	function login($acc)

	{

		global $conn;

		global $account;

		global $table_name;

		$account=$acc;

		$table_name=$account->getTableName();

		$user=$account->getUserName();

		$pass=$account->getPassword();

		//query username-pass

		$sql="select * from $table_name where username='$user' and password='$pass'";		

		openConnection();

		$result=mysqli_query ($conn,$sql);

		if($result->num_rows >0){

			return true;

		} 

		else {

			$conn->close();

			return false;

		}

	}

	function changePassword($acc,$newpasswd)

	{

		global $conn;

		global $account;

		global $table_name;

		$account=$acc;

		$user=$account->getUserName();

		$pass=$account->getPassword();

		openConnection();

		//query username-pass

		$sql="select * from $table_name where username='$user' and password='$pass'";		

		$result=$conn->query($sql);

		if($result->num_rows >0){

			$sql="update $table_name set password='$newpasswd' 

			where username='$user' and password='$pass'";

			if($conn->query($sql)) return true;

			return false;

		} 

		else {echo "<div align='center'>Không tồn tại tài khoản</div>";}

	}

?>