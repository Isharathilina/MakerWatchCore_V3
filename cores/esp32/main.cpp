#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_task_wdt.h"
#include "Arduino.h"


#include "maker_watch/Wire.h"
#include "maker_watch/i2cscanner.h"

//[alredy included from arduino.h]
//#include "maker_watch/display/TFT_eSPI.h"  
//#include "maker_watch/pinhandle.h" 
#include "maker_watch/ioExtender.h"

extern uint8_t ex16bitCount;
extern uint8_t ex8bitCount;

extern TFT_eSPI tft;
extern TFT_eSprite console;


SemaphoreHandle_t i2cSemarphore;
byte watchInterruptPin = 27; // maker watch interrup pin 27
volatile byte interruptFlag=0;  // for enable interrupt


bool loopTaskWDTEnabled;
uint8_t i2cBridgeAddress = 0x70;
uint8_t batteryControllerI2cAddress = 0x75;


TaskHandle_t loopTaskHandle = NULL;

#if CONFIG_AUTOSTART_ARDUINO

 void IRAM_ATTR interruptTrigger()
 {
	 interruptFlag=1;
	 
 }
 


void loopTask(void *pvParameters)
{	

	//enable battery i2c bus
	Wire.beginTransmission(i2cBridgeAddress); // transmit to i2c bridge 
	Wire.write(2);       // 2 battery addr
	Wire.endTransmission(); 

	// set time out data 
	Wire.beginTransmission(batteryControllerI2cAddress); // transmit to device 
	Wire.write(0x04);        // time out register
	Wire.write(0xF7);        // set 64s  (last two bit :-  11 for 64s, 10 for 32s)  default val = 183 = ‭10110111‬  
	Wire.endTransmission();    // stop transmitting

	
	
	// get battery data
	uint8_t batteryCapasity;
	uint8_t tempBtteryCapasity;
	
	for(int i=0; i<10; i++)
	{
        
    Wire.beginTransmission(batteryControllerI2cAddress); // transmit to device 
    Wire.write(0xA2);        // config input register (A2 is batcap data register)
    Wire.endTransmission();    // stop transmitting
        
    Wire.beginTransmission(batteryControllerI2cAddress); // transmit to device for read
    Wire.requestFrom(batteryControllerI2cAddress, 1);   // read 1 byte
    tempBtteryCapasity =+ Wire.read();    // receive a byte as character
    Wire.endTransmission(); // end transmission
	
	delay(100); 
	}
	
	batteryCapasity = tempBtteryCapasity/10;
	
	
	
	//enable extanal i2c bus
	Wire.beginTransmission(i2cBridgeAddress); // transmit to i2c bridge 
	Wire.write(1);       // 2 battery addr
	Wire.endTransmission(); 


	delay(1000); // wait for display service ready
	
	i2cscanservice(); //scan i2c bus
	selectDevice(); // identify connect device 
	
	// configer display
	tft.init();
	console.createSprite(128, 128);
    consoleClear();
	
	CpinMode(watchInterruptPin, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(watchInterruptPin), interruptTrigger, FALLING);  // start innterupt HIGH CHANGE LOW 34
	
	
	consoleLog("Battery :- ",TFT_GREEN);
	//consoleLog(batteryCapasity,TFT_GREEN);
	//MakerDisplay.print(batteryCapasity,TFT_GREEN);
	char cstr[20];
	itoa(batteryCapasity, cstr, 10);
	consoleLog(cstr, TFT_RED);
	delay(2000); 
	consoleClear();
	
	
	
    setup();
	/*
	// for test
	
	int io16bit = 0x58;
	  Wire.beginTransmission(io16bit); // transmit to device 
      Wire.write(0x06);        // config register p0
      Wire.write(255);        // data 0 out 1in
      Wire.endTransmission();    // stop transmitting

      Wire.beginTransmission(io16bit); // transmit to device 
      Wire.write(0x07);        // config register p0
      Wire.write(254);        // data
      Wire.endTransmission();    // stop transmitting
	  
	  */
	
    for(;;) 
	{
        if(loopTaskWDTEnabled){
            esp_task_wdt_reset();
        }
		
		//xSemaphoreTake(i2cSemarphore, portMAX_DELAY);  //lock i2c
        loop();
		
			//i2cscanservice();
			//selectDevice(); // identify connect device  
			
			
			 //Serial.print("testfun:- ");
			//runPinInterrupt(9);
				//runPinInterrupt(5,-1);
			//testfun();
			// _callbackPin[5]();  
			//_callbackPinConfig[1];
			// Serial.print("expender:- ");
			// Serial.println(mappedExpander);
			// Serial.print("pin number:- ");
			// Serial.println(mappedPinNo); //ex8bitCount
			
			/*
			
			Serial.print("ex8bitCount :- "); //
			Serial.println(ex8bitCount); //
			
			Serial.print("ex16bitCount :- "); //
			Serial.println(ex16bitCount); //
			Serial.println(); 
			
			*/

			//Serial.println(ex16bitCount); //
			//Serial.println(acc); 
			 //display1.print("helow");
			
			//xSemaphoreTake(i2cSemarphore, portMAX_DELAY);  //lock i2c 	 
			//Serial.println("  running main");
			//delay(1000);
			//xSemaphoreGive(i2cSemarphore); // release semaphore
			//delay(1000);
			
			//runCallBack(ptr_my_callback);



			 
			// while( xSemaphoreTake( i2cSemarphore, portMAX_DELAY ) != pdPASS );
			//if(interruptFlag==1)
		//{
		
			//xSemaphoreTake(i2cSemarphore, portMAX_DELAY);  //lock i2c 	 
			//i2cscanservice();
			//selectDevice(); // identify connect device  
			//Serial.println("interrupt trigger");  
			//interruptPinDrive(); // check pin interrupt occur and drive relevent callback function
			
			//xSemaphoreGive(i2cSemarphore); // release semaphore
			 //delay(1000);
			
			
			// Serial.println("interrupt trigger 11");
			
			//Serial.println(numberOfDevices); 
			//Serial.println(ex8bitCount);
			//consoleLog("Hi ishara", TFT_RED);
			// delay(2000);

			//interruptFlag = 0;
		//}

		//xSemaphoreGive(i2cSemarphore); // release semaphore
		
    }
}



 void i2cScanService(void *pvParameters)
{

    for(;;) 
	{
		
		if(interruptFlag==1)
		{
		
			xSemaphoreTake(i2cSemarphore, portMAX_DELAY);  //lock i2c 	 
			//i2cscanservice();
			//selectDevice(); // identify connect device  
			Serial.println("interrupt trigger");  
			//runPinInterrupt(1,1);	
			interruptPinDrive(); // check pin interrupt occur and drive relevent callback function
			
			//EX16_1.getInterruptedPin(); 
			
			xSemaphoreGive(i2cSemarphore); // release semaphore
			 //delay(1000);
			
			
			 
			
			//Serial.println(numberOfDevices); 
			//Serial.println(ex8bitCount);
			//consoleLog("Hi ishara", TFT_RED);
			// delay(2000);

			interruptFlag = 0;
		}


			//xSemaphoreTake(i2cSemarphore, portMAX_DELAY);  //lock i2c 	 
			
			
			
			//interruptPinDrive(); // check pin interrupt occur and drive relevent callback function
			//runPinInterrupt(25);
			//runPinInterrupt(5,-1);
			//xSemaphoreGive(i2cSemarphore); // release semaphore
			
			  
			
			//Serial.print("ex8bitCount ");
			//Serial.println(ex8bitCount);
			//Serial.print("ex16bitCount ");
			//Serial.println(ex16bitCount);

			//delay(1000);


    }
}

 
 
extern "C" void app_main()
{
    loopTaskWDTEnabled = false;
    initArduino();
	
	Wire.begin(15,4); // maker watch i2c pin 15,4
	Serial.begin(9600);
	
	//pinMode(watchInterruptPin, INPUT_PULLUP); //INPUT_PULLUP
	//attachInterrupt(digitalPinToInterrupt(watchInterruptPin), interruptTrigger, FALLING); //aw 9523 is open drain low lavel active, with pull up resister

	i2cSemarphore = xSemaphoreCreateMutex();  //create i2c semarphore
	//delay(1000);
    xTaskCreateUniversal(loopTask, "loopTask", 8192, NULL, 2, &loopTaskHandle, CONFIG_ARDUINO_RUNNING_CORE);
	xTaskCreateUniversal(i2cScanService, "i2cScanService", 1024, NULL, 1, &loopTaskHandle, CONFIG_ARDUINO_RUNNING_CORE);
	//xTaskCreateUniversal(displayService, "displayService", 2048, NULL, 2, &loopTaskHandle, CONFIG_ARDUINO_RUNNING_CORE);
	
	
}

#endif
