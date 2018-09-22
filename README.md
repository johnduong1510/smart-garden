# smart-garden
IoT device using combination of ARM STM32F4 and wireless device ESP8266-01. ARM device collects environtment data such as temperature, humidity, soil humidity from sensors, reads data, converts into readable data. These data pushed to webservice (use PHP) by ESP8266 device. All information showed on Android application. We can check environment real time and control to water your garden.

To config STM32F4 pin easily i use CubeMX, download and install CubeMX, choose your board and download all necessary library related to your board.
I use Keil-C to be my IDE and after config CubeMX you can connect to Keil-C to continue programming. (There are a lot tutorials about config ARM board using CubeMX).

Read wiki "Smart Garden" for full detais about sensors, algorithms...
https://github.com/johnduong1510/smart-garden/wiki/Smart-Garden-Using-ARM32-STMF4-and-ESP8266-01

The main source file is located "smart-garden/New-Project-DATN/Src/main.c"

