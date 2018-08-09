<?php
	$homepath=$_SERVER['DOCUMENT_ROOT'];
	require_once($homepath.'/lib/connect_db.php');
	/**************************************************************************************/
	function login($acc)
	{
		$table_name=$acc->getTableName();
		$user=$acc->getUserName();
		$pass=$acc->getPassword();
		global $conn;
		openConnection();
		//$conn = mysqli_connect('localhost', 'id1433618_root', 'VyLuan1510', 'id1433618_mydb');
		//query username-pass
		$sql="select * from $table_name where username='$user' and password='$pass'";		
		$result=mysqli_query ($conn,$sql);
		if($result->num_rows >0){
			mysqli_close($conn);
			return true;
		} 
		else {
			mysqli_close($conn);
			return false;
		}
	}
	/**************************************************************************************/
	if(isset($_GET['username'])&&($_GET['password']))
	{
		$homepath=$_SERVER['DOCUMENT_ROOT'];
		include ($homepath."/lib/class_Account.php");
		$acc=new Account($_GET['username'],$_GET['password']);
		if(login($acc)) print "login successfully";
		else echo "login failed";
	}

	/*
	if(isWatering()) $isWatering="true";
	else $isWatering="false";
		
	if(isMode()) $isMode="true";
	else $isMode="false";
	*/

	function convertToJson($temperature,$moisture,$soil_moisture,$high_tempe,$low_tempe,$high_soil_moisture,$low_soil_moisture,$high_moisture,$low_moisture,$isWatering,$isMode)
	{
		$json=json_encode(new ConvertToJson($temperature,$soil_moisture,$moisture,$high_tempe,$low_tempe,$high_soil_moisture,
			$low_soil_moisture,$high_moisture,$low_moisture,$isWatering,$isMode));
		//var_dump($json);
		$fp=fopen($homepath=$_SERVER['DOCUMENT_ROOT'].'/template1/lib/data.json', 'w');
		fwrite($fp, $json);
		fclose($fp);
	}

	
	class ConvertToJson{
			var $temperature;
			var $soil_moisture;
			var $moisture;
			var $high_tempe;
			var $low_tempe;
			var $high_soil_moisture;
			var $low_soil_moisture;
			var $high_moisture;
			var $low_moisture;
			var $isWatering;
			var $isMode;
			function __construct($tempe,$soil_moisture,$moisture,$high_tempe,$low_tempe,$high_soil_moisture,$low_soil_moisture,$high_moisture,$low_moisture,$water,$mode)
			{
				$this->temperature=$tempe;
				$this->soil_moisture=$soil_moisture;
				$this->moisture=$moisture;
				$this->high_tempe=$high_tempe;
				$this->low_tempe=$low_tempe;
				$this->high_soil_moisture=$high_soil_moisture;
				$this->low_soil_moisture=$low_soil_moisture;
				$this->high_moisture=$high_moisture;
				$this->low_moisture=$low_moisture;
				$this->isWatering=$water;
				$this->isMode=$mode;
			}
	}


?>