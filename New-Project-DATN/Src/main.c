/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"
#include "string.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Error_Handler(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM2_Init(void);
static void MX_USART2_UART_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/*Declare Variables*/
uint16_t ADC_Value[1];
uint8_t soil_humidity;
uint8_t temperature;
uint8_t humidity;
int delayMicro;
GPIO_PinState flagMicro;
int count=0;
char tam[1];
char receive[300];
char each_command[50];
char nhietdo[9];
char doamdat[9];
char nhietdothap[9];
char nhietdocao[9];
char doamdatcao[9];
char doamdatthap[9];
char doamkk[9];
char doamkkthap[10];
char doamkkcao[10];
int high_temperature=0;
int low_temperature=0;
int high_soilhumidity=0;
int low_soilhumidity=0;
int high_humidity=0;
int low_humidity=0;
char highTemperature[]="Set3";
char lowTemperature[]="Set2";
char highSoilHumidity[]="Set6";
char lowSoilHumidity[]="Set5";
char highHumidity[]="Set14";
char lowHumidity[]="Set13";
char watering_on[]="7=1";
char watering_off[]="7=0";
char mode_auto[]="8=1";
char mode_manual[]="8=0";
char set_watering_on[]="Set11";
char set_watering_off[]="Set12";
char set_mode_manual[]="Set8";
char set_mode_auto[]="Set7";
int watering_flag;
char command[100];
int mode;
/*************************************AT Commands*************************************/
char AT_RST[]="AT+RST\r\n";
char AT_CWJAP[]="AT+CWJAP=\"Wireless_plus\",\"sinrc1249\"\r\n";
char AT_CIFSR[]="AT+CIFSR\r\n";  
char AT_CIPSEND[]="AT+CIPSEND=0,20\r\n";
char AT_CIPSTART[]="AT+CIPSTART=\"TCP\",\"vuonthongminh.esy.es\",80\r\n";
/*************************************AT Commands*************************************/
/*************************************************************************************/
/*************************************GET REQUEST*************************************/
char GET[]="GET /upload.php?";
char HOST[]=" HTTP/1.1\r\nHost: vuonthongminh.esy.es\r\n\r\n";
char GET_REQUEST[200];
/*************************************GET REQUEST*************************************/
/*************************************************************************************/
/*Declare Functions*/
void delayMicroSeconds(uint32_t delay);
int DHT11_START(GPIO_TypeDef *gpiox,uint16_t gpio_pin,uint8_t data[40]);
uint8_t bits2byte(uint8_t data[8]);
int parse(uint8_t data[40],uint8_t *ptemperature,uint8_t *phumidity);
int DHT11_CONFIRM(GPIO_TypeDef *gpiox,uint16_t gpio_pin,int us,GPIO_PinState level);
int DHT11_READ(GPIO_TypeDef *gpiox,uint16_t gpio_pin, uint8_t *ptemperature,uint8_t *phumidity,uint8_t pdata[40]);
void GPIO_INPUT(GPIO_TypeDef *gpiox,uint16_t gpio_pin);
void GPIO_Output(GPIO_TypeDef *gpiox,uint16_t gpio_pin,GPIO_PinState level);
void collectData(int delay);
void clear_receive(void);
void esp_init(void);
void clear(char data[]);
void getCommand(char data[]);
void getEachCommand(char data[]);
void doCommand(char command[]);
void toggleWatering(void);
void getValue(char command[]);
void sendAllGetRequest(void);
void getAllGetRequest(void);
char *getTemperature(void);
char *getHighTemperature(void);
char *getLowTemperature(void);
char *getSoilHumidity(void);
char *getHighSoilHumidity(void);
char *getLowSoilHumidity(void);
char *getHumidity(void);
char *getLowHumidity(void);
char *getHighHumidity(void);
void autoControlling(int mode);
/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_TIM2_Init();
  MX_USART2_UART_Init();

  /* USER CODE BEGIN 2 */
	HAL_UART_Receive_IT(&huart2,(uint8_t*)tam,1);
	//esp_init();
	mode=1; //Set Mode=Auto
	watering_flag=0;
  /* USER CODE END 2 */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
			collectData(100);		
			clear(GET_REQUEST);
			getAllGetRequest();
			HAL_Delay(1);
			sendAllGetRequest();
			autoControlling(mode);
  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* ADC1 init function */
static void MX_ADC1_Init(void)
{

  ADC_ChannelConfTypeDef sConfig;

    /**Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) 
    */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ENABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = ENABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

    /**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
    */
  sConfig.Channel = ADC_CHANNEL_6;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

}

/* TIM2 init function */
static void MX_TIM2_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 50;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 1;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }

}

/* USART2 init function */
static void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }

}

/** 
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void) 
{
  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA2_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */
void autoControlling(int mode)
{
	if (mode) { //kiem tra che do tu dong Auto ?
				if(soil_humidity<=low_soilhumidity){watering_flag=1; toggleWatering(); } //do am nho huong nguong thi bat may bom
				else if(soil_humidity>=high_soilhumidity &&watering_flag==1) {watering_flag=0; toggleWatering();}
			}
}

void getAllGetRequest(void)
{
	int len1=strlen(GET);
	/*Add GET string to GET_REQUEST*/
	for(int i=0;i<len1;i++) GET_REQUEST[i]=GET[i];
	/*Add temperature into a string*/
	len1=strlen(getTemperature());
	int len2=strlen(GET_REQUEST);
	int j=0;
	for(int i=len2;i<(len1+len2);i++) GET_REQUEST[i]=nhietdo[j++];
	GET_REQUEST[len1+len2]='&';//Add '&' symbol
	/*Add soil-humidity to GET_REQUEST*/
	j=0;
	len1=strlen(getSoilHumidity());
	len2=strlen(GET_REQUEST);
	for(int i=len2;i<(len1+len2);i++) GET_REQUEST[i]=doamdat[j++];
	GET_REQUEST[len1+len2]='&';//Add '&' symbol
	/*Add humidity to GET_REQUEST*/
	j=0;
	len1=strlen(getHumidity());
	len2=strlen(GET_REQUEST);
	for(int i=len2;i<(len1+len2);i++) GET_REQUEST[i]=doamkk[j++];
	GET_REQUEST[len1+len2]='&';//Add '&' symbol
	/*Add high-tempe to GET_REQUEST*/
	j=0;
	len1=strlen(getHighTemperature());
	len2=strlen(GET_REQUEST);
	for(int i=len2;i<(len1+len2);i++) GET_REQUEST[i]=nhietdocao[j++];
	GET_REQUEST[len1+len2]='&';//Add '&' symbol
	/*Add low-tempe to GET_REQUEST*/
	j=0;
	len1=strlen(getLowTemperature());
	len2=strlen(GET_REQUEST);
	for(int i=len2;i<(len1+len2);i++) GET_REQUEST[i]=nhietdothap[j++];
	GET_REQUEST[len1+len2]='&';//Add '&' symbol
	/*Add high-soil-moisture to GET_REQUEST*/
	j=0;
	len1=strlen(getHighSoilHumidity());
	len2=strlen(GET_REQUEST);
	for(int i=len2;i<(len1+len2);i++) GET_REQUEST[i]=doamdatcao[j++];
	GET_REQUEST[len1+len2]='&';//Add '&' symbol
	/*Add low-soil-moisture to GET_REQUEST*/
	j=0;
	len1=strlen(getLowSoilHumidity());
	len2=strlen(GET_REQUEST);
	for(int i=len2;i<(len1+len2);i++) GET_REQUEST[i]=doamdatthap[j++];
	GET_REQUEST[len1+len2]='&';//Add '&' symbol
	/*Add high-moisture to GET_REQUEST*/
	j=0;
	len1=strlen(getHighHumidity());
	len2=strlen(GET_REQUEST);
	for(int i=len2;i<(len1+len2);i++) GET_REQUEST[i]=doamkkcao[j++];
	GET_REQUEST[len1+len2]='&';//Add '&' symbol
	/*Add low-moisture to GET_REQUEST*/
	j=0;
	len1=strlen(getLowHumidity());
	len2=strlen(GET_REQUEST);
	for(int i=len2;i<(len1+len2);i++) GET_REQUEST[i]=doamkkthap[j++];
	GET_REQUEST[len1+len2]='&';//Add '&' symbol
	/*Add watering status to GET_REQUEST*/
	j=0;
	len2=strlen(GET_REQUEST);
	if(watering_flag){
		len1=strlen(watering_on);
		for(int i=len2;i<(len1+len2);i++) GET_REQUEST[i]=watering_on[j++];
	}
	else 
	{
		len1=strlen(watering_off);
		for(int i=len2;i<(len1+len2);i++) GET_REQUEST[i]=watering_off[j++];
	}
	GET_REQUEST[len1+len2]='&';//Add '&' symbol
	/*Add mode to GET_REQUEST*/
	j=0;
	len2=strlen(GET_REQUEST);
	if(mode){
		len1=strlen(mode_auto);
		for(int i=len2;i<(len1+len2);i++) GET_REQUEST[i]=mode_auto[j++];
	}
	else 
	{
		len1=strlen(mode_manual);
		for(int i=len2;i<(len1+len2);i++) GET_REQUEST[i]=mode_manual[j++];
	}
	
	
	/*Add HOST*/
	j=0;
	len1=strlen(HOST);
	len2=strlen(GET_REQUEST);
	for(int i=len2;i<(len1+len2);i++) GET_REQUEST[i]=HOST[j++];
	
	GET_REQUEST[len1+len2]='\0';
		
}

/*Ham chuyen nhiet do sang dang chuoi, gui den client*/
/*Chuoi gui di co dang: 1=xxx voi xxx la 3 so nguyen*/
char *getTemperature(void)
{
	
	nhietdo[0]='1';
	nhietdo[1]='=';
	nhietdo[2]=(char)(temperature/100)+'0'; //lay hang tram chuyen sang chuoi
	nhietdo[3]=(char)(temperature/10%10)+'0';//lay hang chuc chuyen sang chuoi
	nhietdo[4]=(char)(temperature%10)+'0';//lay hang don vi chuen sang chuoi
	return (char *)nhietdo;
}

/*Ham nay chuyen do am sang dang chuoi*/
/*Chuoi gui di co dang: 4=xxx voi xxx la 3 so nguyen*/
char *getSoilHumidity(void)
{

	doamdat[0]='4';
	doamdat[1]='=';
	doamdat[2]=(char)(soil_humidity/100)+'0';
	doamdat[3]=(char)(soil_humidity/10%10)+'0';
	doamdat[4]=(char)(soil_humidity%10)+'0';
	return (char *)doamdat;
}

/*Ham lay nhiet do nguong cao chuyen sang chuoi*/
/*Chuoi gui di co dang: 3=xxx voi xxx la 3 so nguyen*/
char *getHighTemperature(void)
{
	
	nhietdocao[0]='3';
	nhietdocao[1]='=';
	nhietdocao[2]=(char)(high_temperature/100)+'0';
	nhietdocao[3]=(char)(high_temperature/10%10)+'0';
	nhietdocao[4]=(char)(high_temperature%10)+'0';
	return (char *)nhietdocao;
}

/*Ham lay nhiet do nguong thap chuyen sang chuoi*/
/*Chuoi gui di co dang: 2=xxx voi xxx la 3 so nguyen*/
char *getLowTemperature(void)
{
	nhietdothap[0]='2';
	nhietdothap[1]='=';
	nhietdothap[2]=(char)(low_temperature/100)+'0';
	nhietdothap[3]=(char)(low_temperature/10%10)+'0';
	nhietdothap[4]=(char)(low_temperature%10)+'0';
	return (char *)nhietdothap;
}


/*Ham lay do am nguong cao chuyen sang chuoi*/
/*Chuoi gui di co dang: 6==xxx voi xxx la 3 so nguyen*/
char *getHighSoilHumidity(void)
{
	doamdatcao[0]='6';
	doamdatcao[1]='=';
	doamdatcao[2]=(char)(high_soilhumidity/100)+'0';
	doamdatcao[3]=(char)(high_soilhumidity/10%10)+'0';
	doamdatcao[4]=(char)(high_soilhumidity%10)+'0';
	return (char *)doamdatcao;
}

/*Ham lay do am nguong thap chuyen sang chuoi*/
/*Chuoi gui di co dang: 5==xxx voi xxx la 3 so nguyen*/
char *getLowSoilHumidity(void)
{
	doamdatthap[0]='5';
	doamdatthap[1]='=';
	doamdatthap[2]=(char)(low_soilhumidity/100)+'0';
	doamdatthap[3]=(char)(low_soilhumidity/10%10)+'0';
	doamdatthap[4]=(char)(low_soilhumidity%10)+'0';
	return (char*)doamdatthap;
}
char *getHumidity(void)
{
	doamkk[0]='9';
	doamkk[1]='=';
	doamkk[2]=(char)(humidity/100)+'0';
	doamkk[3]=(char)(humidity/10%10)+'0';
	doamkk[4]=(char)(humidity%10)+'0';
	return (char*)doamkk;
}
char *getLowHumidity(void)
{
	doamkkthap[0]='1';
	doamkkthap[1]='0';
	doamkkthap[2]='=';
	doamkkthap[3]=(char)(low_humidity/100)+'0';
	doamkkthap[4]=(char)(low_humidity/10%10)+'0';
	doamkkthap[5]=(char)(low_humidity%10)+'0';
	return (char*)doamkkthap;
}
char *getHighHumidity(void)
{
	doamkkcao[0]='1';
	doamkkcao[1]='1';
	doamkkcao[2]='=';
	doamkkcao[3]=(char)(high_humidity/100)+'0';
	doamkkcao[4]=(char)(high_humidity/10%10)+'0';
	doamkkcao[5]=(char)(high_humidity%10)+'0';
	return (char*)doamkkcao;
}

void sendAllGetRequest(void)
{
	/*Connect to Website*/
	HAL_Delay(10);
	clear_receive();
	int len=strlen(AT_CIPSTART);
	HAL_UART_Transmit_IT(&huart2,(uint8_t *)AT_CIPSTART,len);
	HAL_Delay(200);
	
	/*Send length of bytes will be sent*/
	clear_receive();
	len=strlen("AT+CIPSEND=120\r\n");
	HAL_UART_Transmit_IT(&huart2,(uint8_t *)"AT+CIPSEND=120\r\n",len);
	HAL_Delay(200);
	clear_receive();
	
	/*Send GET Request*/
	len=strlen(GET_REQUEST);
	HAL_UART_Transmit_IT(&huart2,(uint8_t *)GET_REQUEST,len);
	
	/*Close connection*/
	len=strlen("AT+CIPCLOSE\r\n");
	HAL_UART_Transmit_IT(&huart2,(uint8_t *)"AT+CIPCLOSE\r\n",len);
}

/*Tach noi dung sau ky tu : dua vao bien command*/
void getCommand(char data[])
{
	clear(command);
	int len=strlen(data);
	int j=0,start=0,end=0;
	for(int i=0;i<len;i++)
	{
		if(data[i]=='{') start=i+1; 
		else if(data[i]=='}') end=i-1;
	}
	for(int i=start;i<=end;i++) command[j++]=data[i];
	
}
/*Ham thuc thi lenh tu bien command*/
void doCommand(char command[])
{
		if(strcmp(command,set_watering_on)==0) {watering_flag=1; toggleWatering();}
		else if(strcmp(command,set_watering_off)==0) {watering_flag=0; toggleWatering();}
		else if(strcmp(command,set_mode_auto)==0) {mode=1;}
		else if(strcmp(command,set_mode_manual)==0) {mode=0;}
		/**/
		getValue(command);
}
void getEachCommand(char data[])
{
	int len=strlen(data);
	int start=0;
	int j=0;
	int l=0;
	for(int i=0;i<len;i++)
	{
		if(data[i]==';') 
		{
			//for(int a=0;a<100000000;a++){}//For delay purpose
			clear(each_command); j=0;
			for(int k=start;k<i;k++) each_command[j++]=data[k];
			doCommand(each_command); 		
			start=i+1;		
		}
		
	}
}
/*Ham tach gia tri */
void getValue(char command[])
{
	int len=strlen(command);
	char tam[len];
	int vitri=0;
	for(int i=0;i<len;i++) tam[i]=0; //Clear tam[] 
	for(int i=0;i<len;i++) if(command[i]=='=') {vitri=i-1;break;} //Tim vi tri truoc ky tu '='
	for(int i=0;i<=vitri;i++) tam[i]=command[i];
	/*Lay gia tri nhiet do va do am dat*/
	if(strcmp(tam,highTemperature)==0) 
	{
		int count=vitri+2;//Lay vi tri dau tien cua so
		high_temperature=(command[count++]-'0')*100;
		high_temperature+=(command[count++]-'0')*10;
		high_temperature+=(command[count]-'0');
	}
	else if(strcmp(tam,lowTemperature)==0)
	{
		int count=vitri+2;
		low_temperature=(command[count++]-'0')*100;
		low_temperature+=(command[count++]-'0')*10;
		low_temperature+=(command[count]-'0');
	}
	else if(strcmp(tam,highSoilHumidity)==0)
	{
		int count=vitri+2;
		high_soilhumidity=(command[count++]-'0')*100;
		high_soilhumidity+=(command[count++]-'0')*10;
		high_soilhumidity+=(command[count]-'0');
	}
	else if(strcmp(tam,lowSoilHumidity)==0)
	{
		int count=vitri+2;
		low_soilhumidity=(command[count++]-'0')*100;
		low_soilhumidity+=(command[count++]-'0')*10;
		low_soilhumidity+=(command[count]-'0');
	}
	else if(strcmp(tam,lowHumidity)==0)
	{
		int count=vitri+2;
		low_humidity=(command[count++]-'0')*100;
		low_humidity+=(command[count++]-'0')*10;
		low_humidity+=(command[count]-'0');
	}
	else if(strcmp(tam,highHumidity)==0)
	{
		int count=vitri+2;
		high_humidity=(command[count++]-'0')*100;
		high_humidity+=(command[count++]-'0')*10;
		high_humidity+=(command[count]-'0');
	}
}
/*Ham bat tat may bom dua tren wa	tering_flag*/
void toggleWatering(void)
{
	if(watering_flag==0) {HAL_GPIO_WritePin(GPIOD,GPIO_PIN_14,0);
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4,1);
	} //Tat may bom
	else {HAL_GPIO_WritePin(GPIOD,GPIO_PIN_14,1);
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4,GPIO_PIN_RESET);
	}//Bat may bom
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance==huart2.Instance)
	{	
		if(count>=280) clear_receive();
		receive[count++]=tam[0]; 
		if(tam[0]=='}') { getCommand(receive); clear_receive(); getEachCommand(command); clear(command);}
		HAL_UART_Receive_IT(&huart2,(uint8_t*)tam,1);
	}
}
/*Ham xoa bien receive de nhan chuoi moi*/
void clear_receive(void)
{
	for(int i=0;i<100;i++)
	{
		receive[i]=0;
	}
	count=0;
}
void clear(char data[])
{
	int len=strlen(data);
	for(int i=0;i<len;i++) data[i]=0;
}
/*Ham khoi tao thiet lap ESP8266*/
void esp_init(void)
{
	int len=0;
	/*Reset ESP*/
	clear_receive();
	len=strlen(AT_RST);
	HAL_UART_Transmit_IT(&huart2,(uint8_t *)AT_RST,len);
	HAL_Delay(3000);

	/*Dang nhap vao SSID,Password*/
	
	clear_receive(); //38 //44
	len=strlen(AT_CWJAP);
	HAL_UART_Transmit_IT(&huart2,(uint8_t *)AT_CWJAP,len);
	HAL_Delay(8000);
	
	clear_receive();

}
void collectData(int delay)
{
	HAL_ADC_Start_DMA(&hadc1,(uint32_t *)ADC_Value,1);
	DHT11_READ(GPIOA,GPIO_PIN_1,&temperature,&humidity,NULL);
	HAL_Delay(delay);
}

void GPIO_Output(GPIO_TypeDef *gpiox,uint16_t gpio_pin,GPIO_PinState level)
{
	GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
	if(gpiox==GPIOA) __HAL_RCC_GPIOA_CLK_ENABLE();
	else if(gpiox==GPIOB) __HAL_RCC_GPIOB_CLK_ENABLE();
	else if(gpiox==GPIOC) __HAL_RCC_GPIOC_CLK_ENABLE();
	else if(gpiox==GPIOD) __HAL_RCC_GPIOD_CLK_ENABLE();
	else if(gpiox==GPIOE) __HAL_RCC_GPIOE_CLK_ENABLE();
  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(gpiox, gpio_pin, level);
  /*Configure GPIO pin : PA1 */
  GPIO_InitStruct.Pin = gpio_pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(gpiox, &GPIO_InitStruct);
}
void GPIO_INPUT(GPIO_TypeDef *gpiox,uint16_t gpio_pin)
{
	 GPIO_InitTypeDef GPIO_InitStruct;
  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
	if(gpiox==GPIOA) __HAL_RCC_GPIOA_CLK_ENABLE();
	else if(gpiox==GPIOB) __HAL_RCC_GPIOB_CLK_ENABLE();
	else if(gpiox==GPIOC) __HAL_RCC_GPIOC_CLK_ENABLE();
	else if(gpiox==GPIOD) __HAL_RCC_GPIOD_CLK_ENABLE();
	else if(gpiox==GPIOE) __HAL_RCC_GPIOE_CLK_ENABLE();
	
  /*Configure GPIO pin : PA1 */
  GPIO_InitStruct.Pin = gpio_pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

int parse(uint8_t data[40],uint8_t *ptemperature,uint8_t *phumidity)
{
	uint8_t humidity = bits2byte(data);
  uint8_t humidity2 = bits2byte(data + 8);
  uint8_t temperature = bits2byte(data + 16);
  uint8_t temperature2 = bits2byte(data + 24);
  uint8_t check = bits2byte(data + 32);
  uint8_t expect = humidity + humidity2 + temperature + temperature2;
  if (check != expect) return 105;
  *ptemperature = temperature;
  *phumidity = humidity;
  return 0;
}

uint8_t bits2byte(uint8_t data[8])
{
	uint8_t v=0;
	for(int i=0;i<8;i++)
	{
		v+=data[i] << (7-i);
	}
	return v;
}
int DHT11_CONFIRM(GPIO_TypeDef *gpiox,uint16_t gpio_pin,int us,GPIO_PinState level)
{
	int count=us/10+1;
	GPIO_PinState ok=0;
	for (int i = 0; i < count; i++) {
		if (HAL_GPIO_ReadPin(gpiox,gpio_pin) != level) {
			ok=1;
			break;
		}
  delayMicroSeconds(10);
  }
	if(!ok) return -1;
	return 0;
}

int DHT11_START(GPIO_TypeDef *gpiox,uint16_t gpio_pin,uint8_t data[40])
{
	memset(data,0,40);
	GPIO_Output(gpiox,gpio_pin,1);
	HAL_GPIO_WritePin(gpiox,gpio_pin,0);
	HAL_Delay(20);
	HAL_GPIO_WritePin(gpiox,gpio_pin,1);
	delayMicroSeconds(30);
	GPIO_INPUT(gpiox,gpio_pin);
	
	if(DHT11_CONFIRM(gpiox,gpio_pin,80,0)) return 100;
	if(DHT11_CONFIRM(gpiox,gpio_pin,80,1)) return 101;
	
	for(int j=0;j<40;j++)
	{
		if(DHT11_CONFIRM(gpiox,gpio_pin,50,0)) return 102;
		GPIO_PinState ok=0;
		int tick=0;
		for(int i=0;i<8;i++,tick++)
		{
			if(HAL_GPIO_ReadPin(gpiox,gpio_pin)!=1)
			{
				ok=1;
				break;
			}
			delayMicroSeconds(10);
		}
		if(!ok) return 103;
		data[j]=(tick>3 ? 1:0);
	}
	if(DHT11_CONFIRM(gpiox,gpio_pin,50,0)) return 104;
	return 0;
}

int DHT11_READ(GPIO_TypeDef *gpiox,uint16_t gpio_pin, uint8_t *ptemperature,uint8_t *phumidity,uint8_t pdata[40])
{
	int ret=0;
	uint8_t data[40]={0};
	if((ret=DHT11_START(gpiox,gpio_pin,data))!=0) return ret;
	
	uint8_t temperature=0,humidity=0;
	if((ret=parse(data,&temperature,&humidity))!=0) return ret;
	
	if(pdata){memcpy(pdata,data,40);}
	if(ptemperature) *ptemperature=temperature;
	if(phumidity) *phumidity=humidity;
	return ret;
}

void delayMicroSeconds(uint32_t delay)
{
	delayMicro=delay;
	delayMicro/=2;
	HAL_TIM_Base_Start_IT(&htim2);
	for(int i=0;i<delayMicro;i++)
		if(flagMicro) {flagMicro=0; break;}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim2.Instance==htim->Instance)
	{
		delayMicro--;
		if(delayMicro==0){flagMicro=1; HAL_TIM_Base_Stop_IT(htim);}
	}
}
/*Ham ngat ADC, sau khi xu ly ADC bang DMA xong thi nhay vao ham ngat nay de xu ly*/
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	if(hadc->Instance==hadc1.Instance)
		//Chuyen doi ADC sang do am/
		soil_humidity=100-(ADC_Value[0])*0.02442;
		//getSoilHumidity();//Chuyen doi do am sang dang chuoi
	}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
