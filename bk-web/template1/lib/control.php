<?php

	function sendStatusString(){
		global $chuoi;
		$chuoi= '{' . $chuoi . '}';
		echo $chuoi;
	}
	
	function syncFromWebToARM($name,$data)
	{
		$tam=getDataFromDB($name);
		if($tam<10) $tam='00' . $tam;
		else if($tam<100) $tam='0' . $tam;
		if($tam!=$data)
		{
			global $chuoi;
			switch ($name) {
				case 'setup_low_tempe':
					$chuoi=$chuoi . "Set2=" . $tam . ';';
					break;
				case 'setup_high_tempe':
					$chuoi=$chuoi . "Set3=" . $tam . ';';
					break;
				case 'setup_low_soil_moisture':
					$chuoi=$chuoi . "Set5=" . $tam . ';';
					break;
				case 'setup_high_soil_moisture':
					$chuoi=$chuoi . "Set6=" . $tam . ';';
					break;
				case 'setup_high_moisture':
					$chuoi=$chuoi . "Set14=" . $tam . ';';
					break;	
				case 'setup_low_moisture':
					$chuoi=$chuoi . "Set13=" . $tam . ';';
					break;		
				case 'isWatering':
					//neu watering trong db la 0 va ARM la 1
					//dong bo ARM Set12=water off
					$water=(int)getDataFromDB($name);
					if( $water < $data) $chuoi=$chuoi . 'Set12;';
					else if($water > $data) $chuoi=$chuoi . 'Set11;';
					break;
				case 'mode':
					//neu mode trong db la 0 va ARM la 1
					//dong bo cho ARM la mode=manual=Set8
					$mode=(int)getDataFromDB($name);
					if( $mode < $data) $chuoi=$chuoi . 'Set8;';
					else if($mode > $data) $chuoi=$chuoi . 'Set7;';
					break;
				default:					
					break;
			}
			
		} 
	}
?>