<?php
		/*Include */
		require_once("lib/class_Account.php");
		require_once("lib/manage_account.php");
		/*Include*/


		if(isset($_POST['btn_login'])){
			$username=$_POST['username'];
			$password = $_POST["passwd"];
			//kt cac field khong duoc rong
			if($username=="" || $password=="" ) { echo "<div align='center'>Vui lòng nhập đầy đủ</div>";}
			else {
				$account=new Account($username,$password);
				if(login($account)) {
					//echo "<div align='center'>Login successfully</div>";
					header("Location: template1/datn.php");//chuyen huong
					exit;
				}
				else if(isUsernameExist($account)) echo "<div align='center'>Sai mật khẩu</div>";
				else {echo "<div align='center'>Không tồn tại tài khoản</div>";}
			}
		}
		else if(isset($_POST['btn_swapform_doimatkhau']))
		{
			header("Location: changepass.php");//chuyen huong
		}
		
	?>
<!DOCTYPE html>
<html>
<head>
	<title>LOGIN</title>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<link rel="stylesheet" type="text/css" href="style_register.css">
</head>
<body>
		<div id="logo">
			<span>
				<img src="template1/img/logo-clc.png" alt="Khoa dao tao chat luong cao" width="160px" height="160px" >
				<img src="template1/img/logo-spkt.png" alt="Dai hoc su pham ky thuat" width="160px" height="160px">
				</span>
		</div>
		<div id="slogan">
					<p>TRƯỜNG ĐẠI HỌC SƯ PHẠM KỸ THUẬT THÀNH PHỐ HỒ CHÍ MINH</p>
					<p>KHOA ĐÀO TẠO CHẤT LƯỢNG CAO</p>
		</div>
		<div class="login-page">
		 <div class="form">
		    <form class="login-form" method="POST">
		      <input type="text" name="username" placeholder="username"/>
		      <input type="password" name="passwd" placeholder="password"/>
		      <button  type="submit" name="btn_login">ĐĂNG NHẬP</button>		
		      <button id="btn_swapform_doimatkhau" class="btn-swap-form" type="submit" name="btn_swapform_doimatkhau">Đổi mật khẩu</button>	
		    </form>
		   </div> 
		</div>

	
</body>
</html>