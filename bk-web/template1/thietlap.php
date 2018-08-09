<?php
	require_once("lib/manage_Garden.php");
	require_once("lib/readJson.php");
	require_once("lib/getdata.php");
?>
<!--Auto refresh page -->
<!--
<script type="text/javascript">
  setTimeout(function(){
    location = ''
  },10000)
</script>
-->
<?php
	if(isset($_POST['ButtonApply']))
	{
		if(isset($_POST['low-tempe'])) setDataToDB("setup_low_tempe",$_POST['low-tempe']);
		if(isset($_POST['high-tempe'])) setDataToDB("setup_high_tempe",$_POST['high-tempe']);
		if(isset($_POST['low-soil-moisture'])) setDataToDB("setup_low_soil_moisture",$_POST['low-soil-moisture']);
		if(isset($_POST['high-soil-moisture'])) setDataToDB("setup_high_soil_moisture",$_POST['high-soil-moisture']);
		if(isset($_POST['low-moisture'])) setDataToDB("setup_low_moisture",$_POST['low-moisture']);
		if(isset($_POST['high-moisture'])) setDataToDB("setup_high_moisture",$_POST['high-moisture']);
		//Convert to new json
		convertToJson(getDataFromDB("temperature"),getDataFromDB("moisture"),getDataFromDB("soil_moisture"),getDataFromDB("setup_high_tempe"),getDataFromDB("setup_low_tempe"),getDataFromDB("setup_high_soil_moisture"),getDataFromDB("setup_low_soil_moisture"),getDataFromDB("setup_high_moisture"),getDataFromDB("setup_low_moisture"),isWatering(),isMode());
		header("Location: thietlap.php");//chuyen huong
	}

?>

<html>
<head>
	<title>Thiết lập</title>
	<meta charset="utf-8">
	<!--<meta http-equiv="refresh" content="<?php echo $sec?>;URL='<?php echo $page?>'">-->
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<link rel="stylesheet" type="text/css" href="thietlap.css">
	<link rel="stylesheet" type="text/css" href="normalize.css"><!--Reset CSS-->
</head>
<body>
	<div id="container">
			<div id="menu">
				<ul>
					<li><a href="datn.php">Trang chủ</a></li>
					<li><a href="giamsat.php">Giám sát</a></li>
					<li><a href="thietlap.php">Thiết lập</a></li>
					<li><a href="dieukhien.php">Điều khiển</a></li>
					<li><a href="#">Thời tiết</a></li>
				</ul>
		</div>	<!--Menu-->

	<form class="setting-form" method="POST">
		<div class="row" id="thietlap">
				<p class="title">Thiết lập ngưỡng nhiệt độ</p>

			<!--=============Nhiet do nguong duoi==============-->
				<div id="box1" class="col">
					<h2>Nhiệt độ ngưỡng dưới (°C)</h2>
					<img src="img/low-temp.png" alt="Hình nhiệt độ">
					<input type="text" name="low-tempe" placeholder=<?php echo (int)getVariableFromJson("low_tempe"); ?> maxlength="3" size="1">
				</div>
			<!--=============Nhiet do nguong tren==============-->
				<div id="box2" class="col">			
					<h2>Nhiệt độ ngưỡng trên (°C)</h2>		
					<img src="img/high-tempe.png" alt="Hình quá nhiệt">
					<input type="text" name="high-tempe" placeholder=<?php echo  (int)getVariableFromJson("high_tempe"); ?> maxlength="3" size="1">
				</div>
				

				<p class="title" id="title_3">Thiết lập ngưỡng độ ẩm không khí</p>
				<!--=============Do am kk nguong duoi==============-->
				<div id="box-extra-1" class="col">
					<h2>Độ ẩm không khí ngưỡng dưới (%)</h2>
					<img src="img/low-humidity.png" alt="Hình độ ẩm không khí">
					<input type="text" name="low-moisture" placeholder=<?php echo (int)getVariableFromJson("low_moisture");  ?> maxlength="3" size="1">
				</div>
				<!--=============Do am kk nguong tren==============-->
				<div id="box-extra-2" class="col">
					<h2>Độ ẩm không khí ngưỡng trên (%)</h2>
					<img src="img/high-humidity.png" alt="Hình độ ẩm không khí">
					<input type="text" name="high-moisture" placeholder=<?php echo (int)getVariableFromJson("high_moisture"); ?> maxlength="3" size="1">
				</div>


				<p class="title" id="title_2">Thiết lập ngưỡng độ ẩm đất</p>
				<!--=============Do am nguong duoi==============-->
				<div id="box3" class="col">
					<h2>Độ ẩm đất ngưỡng dưới (%)</h2>
					<img src="img/low-soil-moisture.jpg" alt="Hình độ ẩm">
					<input type="text" name="low-soil-moisture" placeholder=<?php echo (int)getVariableFromJson("low_soil_moisture");  ?> maxlength="3" size="1">
				</div>
				<!--=============Do am nguong tren==============-->
				<div id="box4" class="col">
					<h2>Độ ẩm đất ngưỡng trên (%)</h2>
					<img src="img/high-soil-moisture.jpg" alt="Hình độ ẩm">
					<input type="text" name="high-soil-moisture" placeholder=<?php echo (int)getVariableFromJson("high_soil_moisture"); ?> maxlength="3" size="1">
				</div>
				<!--=============Button Apply==============-->
				<div id="box5">
					<button type="submit" name="ButtonApply">Apply</button>	
				</div>

		</div> <!--end row-->
	</form>
</body>
</html>