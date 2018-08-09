<?php
	$jsonpath="lib/data.json";
	function getVariableFromJson($variable)
	{
		global $jsonpath;
		$json=file_get_contents($jsonpath);
		$arrayjson=json_decode($json, true);
		return $arrayjson[$variable];
	}
?>