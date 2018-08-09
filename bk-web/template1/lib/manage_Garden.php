<?php
	
	$homepath=$_SERVER['DOCUMENT_ROOT'];
	require($homepath.'/lib/connect_db.php');

	function getDataFromDB($name)

	{
		global $conn;
		openConnection();
		$sql = "SELECT $name FROM garden";

		$result=mysqli_query ($conn,$sql);

		if ($result->num_rows > 0) {

	    // output data of each row

		    while($row = $result->fetch_assoc()) {

		        $temp=$row["$name"];        

		    }

		    mysqli_close($conn);

		    return $temp;

		} else {

			mysqli_close($conn);

	    	return false;

		}

	}





	function setDataToDB($name,$data)

	{

		global $conn;
		openConnection();
	//--------------------//

		$sql="update garden set $name=$data where id=1";

		if(mysqli_query($conn,$sql)) { mysqli_close($conn);

			return true;}

		else {mysqli_close($conn);

			return false;}

	}



	function isWatering()
	{
		if(getDataFromDB("isWatering")) return "true";
		else return "false";
	}
	
	function setWatering($x)
	{
		setDataToDB("isWatering",$x);
	}
	
	function isMode()
	{
		if(getDataFromDB("mode")) return "true";
		else return "false";
	}
	
	function setMode($mode)
	{
		setDataToDB("mode",$mode);
	}
	

?>