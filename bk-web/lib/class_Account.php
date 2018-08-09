<?php
	class Account{
		private $servername = "localhost";
		private $username = "root";
		private $password = "";
		private $database_name='mydb';
		private $table_name="login";

		function __construct($user,$pass)
		{
			$this->username=$user;
			$this->password=$pass;
		}
		function setUsername($user)
		{
			$this->username=$user;
		}
		function setPassword($pass)
		{
			$this->password=$pass;
		}
		function getUsername(){return $this->username;}
		function getPassword(){return $this->password;}
		function getDatabaseName() {return $this->database_name;}
		function getTableName(){return $this->table_name;}
	}
?>