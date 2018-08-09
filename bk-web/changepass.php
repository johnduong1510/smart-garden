<!DOCTYPE html>
<html>
<head>
	<title>CHANGE PASSWORD</title>
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
		      <input type="password" name="oldpasswd" placeholder="old password"/>
		      <input type="password" name="newpasswd" placeholder="new password">
		      <input type="password" name="confirmedpasswd" placeholder="confirmed password">
		      <button  type="submit" name="btn_changepasswd">ĐỔI MẬT KHẨU</button>		
		      <button id="btn_swapform_login" class="btn-swap-form" type="submit" name="btn_swapform_login">Đăng nhập</button>	
		    </form>
		   </div> 
		</div>
		<?php
			/*Include */
			require_once("lib/connection.php");
			require_once("lib/class_Account.php");
			require_once("lib/manage_account.php");
			/*Include*/

			if(isset($_POST['btn_changepasswd']))
			{
				$username=$_POST['username'];
				$password = $_POST["oldpasswd"];
				$newpasswd=$_POST['newpasswd'];
				$confirmedpasswd=$_POST['confirmedpasswd'];
				//kt cac field khong duoc rong
				if($username=="" || $password=="" || $newpasswd=="" || $confirmedpasswd=="") {
					echo "<div align='center'>Vui lòng nhập đầy đủ</div>";
				}
				else if($newpasswd!=$confirmedpasswd){
					echo "<div align='center'>Vui lòng nhập mật khẩu mới trùng nhau</div>";
				}
				else{
					$account=new Account($username,$password);
					if(changePassword($account,$newpasswd)) {
						echo "<div align='center'>Đổi mật khẩu thành công</div>";
					}
					else echo "<div align='center'>Đổi mật khẩu thất bại</div>";
				}
				
			}
			else if (isset($_POST['btn_swapform_login'])) {
				header("Location: index.php");//chuyen huong
			}
		?>
</body>
</html>