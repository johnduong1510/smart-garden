<?php
	require_once("manage_Garden.php");
	require_once("getdata.php");

	if(isset($_GET['mode']))
	{
		if($_GET['mode']=='true') $mode=1;
		else if($_GET['mode']=='false') $mode=0;
		setDataToDB("mode",$mode);
		echo "mode:OK";
	}
	if(isset($_GET['setup_low_tempe']))
	{
		setDataToDB("setup_low_tempe",$_GET['setup_low_tempe']);
		echo "setup_low_tempe:OK";
	}
	if(isset($_GET['setup_high_tempe']))
	{
		setDataToDB("setup_high_tempe",$_GET['setup_high_tempe']);
		echo "setup_high_tempe:OK";
	}
	if(isset($_GET['setup_low_soil_moisture']))
	{
		setDataToDB("setup_low_soil_moisture",$_GET['setup_low_soil_moisture']);
		echo "setup_low_soil_moisture:OK";
	}
	if(isset($_GET['setup_high_soil_moisture']))
	{
		setDataToDB("setup_high_soil_moisture",$_GET['setup_high_soil_moisture']);
		echo "setup_high_soil_moisture:OK";
	}
	if(isset($_GET['setup_high_moisture']))
	{
		setDataToDB("setup_high_moisture",$_GET['setup_high_moisture']);
		echo "setup_high_moisture:OK";
	}
	if(isset($_GET['setup_low_moisture']))
	{
		setDataToDB("setup_low_moisture",$_GET['setup_low_moisture']);
		echo "setup_low_moisture:OK";
	}
	if(isset($_GET['isWatering']))
	{
		setDataToDB("isWatering",$_GET['isWatering']);
		echo "isWatering:OK";
	}
	
	convertToJson(getDataFromDB("temperature"),getDataFromDB("moisture"),getDataFromDB("soil_moisture"),getDataFromDB("setup_high_tempe"),getDataFromDB("setup_low_tempe"),getDataFromDB("setup_high_soil_moisture"),getDataFromDB("setup_low_soil_moisture"),getDataFromDB("setup_high_moisture"),getDataFromDB("setup_low_moisture"),isWatering(),isMode());
?>