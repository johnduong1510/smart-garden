<?php
	$page = $_SERVER['PHP_SELF'];
	$sec = "1";
?>
<?php
	require_once("lib/readJson.php");
?>
<!--Auto refresh page -->

<script type="text/javascript">
  setTimeout(function(){
    location = ''
  },1000)
</script>

<html>
<head>
	<title>Giám sát</title>
	<meta charset="utf-8">
	<!--<meta http-equiv="refresh" content="<?php echo $sec?>;URL='<?php echo $page?>'">-->
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<link rel="stylesheet" type="text/css" href="giamsat.css">
	<link rel="stylesheet" type="text/css" href="normalize.css"><!--Reset CSS-->
</head>
<body >
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

	<!--Giam sat-->
			<div class="row" id="giamsat">
				<p class="title">Giám sát</p>
			<!--=============Nhiet do==============-->
				<div id="box1" class="col">
					<h2>Nhiệt độ</h2>
					<img src="img/thermometer-icon.png" alt="Nhiệt độ">
					<p id="temperature">
					<?php
						echo (int)getVariableFromJson("temperature").'°C';
					?>	
					</p>
				</div>
			<!--=============Do am khong khi==============-->
				<div id="box-extra-01" class="col">
					<h2>Độ ẩm không khí</h2>
					<img src="img/humudity-icon.png" alt="Độ ẩm không khí">
					<p id="humidity">
					<?php
						echo (int)getVariableFromJson("moisture").'%';
					?>
					</p>
				</div>
			<!--=============Do am dat==============-->
				<div id="box2" class="col">
					<h2>Độ ẩm đất</h2>
					<img src="img/soil-humidity-icon.png" alt="Độ ẩm đất">
					<p id="soil-humidity">
					<?php
						echo (int)getVariableFromJson("soil_moisture").'%';
					?>
					</p>
				</div>	

			<!--=============Setup nguong nhiet do==============-->	
				<div id="box3" class="col">
					<h2>Nhiệt độ ngưỡng</h2>
					<img src="img/settingstemp-icon.png" alt="Ngưỡng nhiệt độ">
					<p class="low-settings">
						<?php
							echo (int)getVariableFromJson("low_tempe").'°C';
						?>
					</p>
					<p class="high-settings">
						<?php
							echo (int)getVariableFromJson("high_tempe").'°C';
						?>
					</p>
				</div>	
			<!--=============Setup nguong do am khong khi==============-->
				<div id="box-extra-2" class="col">
					<h2>Độ ẩm không khí ngưỡng</h2>
					<img src="img/setting-humidity.png" alt="Ngưỡng độ ẩm đất">
					<p class="low-settings">
						<?php
							echo (int)getVariableFromJson("low_moisture").'%';
						?>
					</p>
					<p class="high-settings">
						<?php
							echo (int)getVariableFromJson("high_moisture").'%';
						?>
					</p>
				</div>		

			<!--=============Setup nguong do am dat==============-->
				<div id="box4" class="col">
					<h2>Độ ẩm đất ngưỡng</h2>
					<img src="img/settingssoilhumidity-icon.png" alt="Ngưỡng độ ẩm đất">
					<p class="low-settings">
						<?php
							echo (int)getVariableFromJson("low_soil_moisture").'%';
						?>
					</p>
					<p class="high-settings">
						<?php
							echo (int)getVariableFromJson("high_soil_moisture").'%';
						?>
					</p>
				</div>
			
			</div> <!--end row-->
</body>
</html>