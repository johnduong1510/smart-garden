	<?php
	//--------------Luu y---------------------
	/*
		Dữ liệu từ ESP8266 gửi lên
			+ Nhiệt độ kí hiệu là 1=xxx
			+ Nhiệt độ ngưỡng dưới là 2=xxx
			+ Nhiệt độ ngưỡng trên là 3=xxx
			+ Độ ẩm đất kí hiệu là 4=xxx
			+ Độ ẩm đất ngưỡng dưới là 5=xxx
			+ Độ ẩm đất ngưỡng trên là 6=xxx
			+ Điều khiển máy bơm là 7=x
			+ Điều khiển chế độ là 8=x
			+ Độ ẩm kk là 9=xxx
			+ Độ ẩm kk ngưỡng dưới là 10=xxx
			+ Độ ẩm kk ngưỡng trên là 11=xxx
	*/
	//--------------END------------------------	
	require_once("template1/lib/manage_Garden.php");
	require_once("template1/lib/getdata.php");
	require_once("template1/lib/control.php");
	//------------------------------------------
	if(isset($_GET['1']))
	{
		setDataToDB("temperature",$_GET['1']);
	}
	if(isset($_GET['4']))
	{
		setDataToDB("soil_moisture",$_GET['4']);
	}
	if(isset($_GET['9']))
	{
		setDataToDB("moisture",$_GET['9']);
	}
	if(isset($_GET['2']))
	{
		syncFromWebToARM("setup_low_tempe",$_GET['2']);		
	}
	if(isset($_GET['3']))
	{
		syncFromWebToARM("setup_high_tempe",$_GET['3']);	
	}
	if(isset($_GET['5']))
	{
		syncFromWebToARM("setup_low_soil_moisture",$_GET['5']);	
	}
	if(isset($_GET['6']))
	{
		syncFromWebToARM("setup_high_soil_moisture",$_GET['6']);	
	}
	/*Neu che do khac nhau thi sync tu database Web->ARM*/
	/*Mac dinh Web va ARM deu co mode=1. Neu co bat ky su chinh sua nao tu database cua Web thi sync Web sang ARM.*/
	if(isset($_GET['8']))
	{
		syncFromWebToARM("mode",$_GET['8']);
	}
	/*Neu mode o database la 0-Manual thi cho phep sync watering tu database->ARM*/
	if(isset($_GET['7']))
	{
		if(!(int)getDataFromDB('mode')) syncFromWebToARM("isWatering",$_GET['7']);
		else setDataToDB("isWatering",$_GET['7']);
	}
	if(isset($_GET['10']))
	{
		syncFromWebToARM("setup_low_moisture",$_GET['10']);	
	}
	if(isset($_GET['11']))
	{
		syncFromWebToARM("setup_high_moisture",$_GET['11']);
	}

	/*Write data to json file*/
	convertToJson(getDataFromDB("temperature"),getDataFromDB("moisture"),getDataFromDB("soil_moisture"),getDataFromDB("setup_high_tempe"),getDataFromDB("setup_low_tempe"),getDataFromDB("setup_high_soil_moisture"),getDataFromDB("setup_low_soil_moisture"),getDataFromDB("setup_high_moisture"),getDataFromDB("setup_low_moisture"),isWatering(),isMode());
	/*Update back to ARM*/
	sendStatusString();
?>