<?php
	require_once("lib/readJson.php");
?>

<!--script xu ly CheckBox onClick Event-->
<script type="text/javascript">
	function handleClick(cb,name) {		
		var str = cb.checked;
		if(cb.checked && name=="mode"){
			//alert("Chuyển sang chế độ điều khiển tự động");
			document.getElementById("watering").disabled = true;
		}
		else {document.getElementById("watering").disabled = false;}
		/*Send GET method to uploadFromAndroid to proccess*/
		if (window.XMLHttpRequest){
	    xmlhttp=new XMLHttpRequest();
		}

		else
			{xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");}

		var PageToSendTo = "lib/uploadFromAndroid.php?";
		var MyVariable = str;
		var VariablePlaceholder = name+"=";
		var UrlToSend = PageToSendTo + VariablePlaceholder + MyVariable;
		xmlhttp.open("GET", UrlToSend, false);
		xmlhttp.send();	
		location.reload(false);
		}
</script>
<script type="text/javascript">
  setTimeout(function(){
    location = ''
  },2000)
</script>

<script type="text/javascript">
	function myFunction(){
		if(document.getElementById("mode").checked)
		{
			document.getElementById("watering").disabled=true;
		}
	}
</script>

<html>
<head>
	
	<title>Điều khiển</title>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<link rel="stylesheet" type="text/css" href="dieukhien.css">
	<link rel="stylesheet" type="text/css" href="normalize.css"><!--Reset CSS-->
</head>
<body onload="myFunction()">
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

	<!--Dieu khien-->
			<div class="row" id="dieukhien">
				<p class="title">Điều khiển</p>
				<!--Dieu khien may bom-->
				<div id="box5" class="col">
					<h2>Máy bơm</h2>
					<img src="img/watering-icon.png" alt="Máy bơm">
					<p>
						<?php
							if(getVariableFromJson("isWatering")=="true") echo 'Đang hoạt động...';
					  		else echo 'Không hoạt động';
						?>
					</p>
					<!-- Rectangular switch -->					
					<label class="switch">			
					  	<input type="checkbox" id="watering" onclick='handleClick(this,"isWatering");' 
					  	<?php 
					  		if(getVariableFromJson("isWatering")=="true") echo 'checked';
					  		else echo '';
					  	?>/>					
					  	<div class="slider"></div>			
					</label>
				</div>
				<!--Dieu khien che do-->
				<div id="box6" class="col">
					<h2>Chế độ</h2>
					<img src="img/mode2.png" alt="Mode">
					<p>
						<?php
							if(getVariableFromJson("isMode")=="true") echo 'Điều khiển tự động';
					  		else echo 'Điều khiển tay';
						?>
					</p>
					<!-- Rectangular switch -->					
					<label class="switch">			
					  	<input type="checkbox" id="mode" onclick='handleClick(this,"mode");' 
					  	<?php 
					  		if(getVariableFromJson("isMode")=="true") echo 'checked';
					  		else echo '!checked';
					  	?>/>				
					  	<div class="slider"></div>			
					</label>
				</div>
			</div>

</body>
</html>

