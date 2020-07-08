#include <arduino.h>

#include "ioExtender.h"
#include "Wire.h"


// aw9523 data register from datasheet 16bit  
// all port swaped, becouse po 1 = pin 9 on IO expender
#define inputPort1 0x00
#define inputPort0 0x01

#define outputPort1 0x02
#define outputPort0 0x03

#define configPort1 0x04
#define configPort0 0x05

#define configPort0Globle 0x11 // register for set push-pull mode p0

#define interruptConfigPort1 0x06
#define interruptConfigPort0 0x07

#define gpioLedSelectReg1 0x12 // register for select gpio/Led mode
#define gpioLedSelectReg0 0x13

#define sofwareResetReg 0x7f

// pca9557 registers from data sheet 8bit
#define inverseReg 0x02
#define configReg 0x03
#define inputReg 0x00
#define outputReg 0x01


#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_IOEXPANDER)

EX16 EX16_1(0,0);
EX16 EX16_2(0,1);
EX16 EX16_3(1,0);
EX16 EX16_4(1,1);

EX8 EX8_1(0,0);
EX8 EX8_2(0,1);
EX8 EX8_3(1,0);
EX8 EX8_4(1,1);

#endif


EX16::EX16(bool AD1, bool AD0)
{
	// init io extender
	// 1 for input , 0 for output
      if(AD1==1 and AD0==1)
		{
          i2cAddress = 0x5B; // 11	91
          
        }else if(AD1==1 and AD0==0)
		{
          i2cAddress = 0x5A; // 10	90
          
        }else if(AD1==0 and AD0==1)
		{
          i2cAddress = 0x59; // 01	89
          
        }else if(AD1==0 and AD0==0)
		{
          i2cAddress = 0x58; // 00	88         
		}  
        
		
		
		// reset device
		Wire.beginTransmission(i2cAddress); // transmit to device 
		Wire.write(sofwareResetReg);        // reset reg
		Wire.write(0);        // data 0 out 1in
		Wire.endTransmission();    // stop transmitting
			
		
		

        // config config_port registers for all pins as input in initilize mode
        /*
        04h config p1
        05 config p2
        */
		
        Wire.beginTransmission(i2cAddress); // transmit to device 
        Wire.write(configPort0);        // config register p0
        Wire.write(pinModeP0);        // data , all pin as input
        Wire.endTransmission();    // stop transmitting

        Wire.beginTransmission(i2cAddress); // transmit to device 
        Wire.write(configPort1);        // config register p1
        Wire.write(pinModeP1);        // data , all pin as input
        Wire.endTransmission();    // stop transmitting

		//disable all interruppt
		Wire.beginTransmission(i2cAddress); // transmit to device 
        Wire.write(interruptConfigPort0);        // config register p0
        Wire.write(interruptPinModeP0);        // data , all pin as disable
        Wire.endTransmission();    // stop transmitting

        Wire.beginTransmission(i2cAddress); // transmit to device 
        Wire.write(interruptConfigPort1);        // config register p1
        Wire.write(interruptPinModeP1);        // data , all pin as disable
        Wire.endTransmission();    // stop transmitting
		
		// set all pin as GPIO pin
		Wire.beginTransmission(i2cAddress); // transmit to device 
        Wire.write(gpioLedSelectReg0);        // config register p0
        Wire.write(gpioLedModeData0);        // data , all pin as gpio
        Wire.endTransmission();    // stop transmitting

        Wire.beginTransmission(i2cAddress); // transmit to device 
        Wire.write(gpioLedSelectReg1);        // config register p1
        Wire.write(gpioLedModeData1);        // data , all pin as gpio
        Wire.endTransmission();    // stop transmitting
		
			// // p0 port set to push-pull mode
		// Wire.beginTransmission(i2cAddress); // transmit to device 
		// Wire.write(configPort0Globle);        // config register p0
		// Wire.write(pushPullData0);        // data
		// Wire.endTransmission();    // stop transmitting
		
		
		
		//set gpio mode
		Wire.beginTransmission(i2cAddress); // transmit to device 
		Wire.write(gpioLedSelectReg0);        // config register p0
		Wire.write(255);        // set all as gpio
		Wire.endTransmission();    // stop transmitting
		
		Wire.beginTransmission(i2cAddress); // transmit to device 
		Wire.write(gpioLedSelectReg1);        // config register p0
		Wire.write(255);        //  set all as gpio
		Wire.endTransmission();    // stop transmitting
		
	
	
}

int EX16::modifyBit(int currentByte, int BitPosition, int bitData) // bitData field, change position, change value
{ 
        int mask = 1 << (BitPosition-1); 
        return (currentByte & ~mask) | ((bitData << (BitPosition-1)) & mask); 
}


int EX16::readBit(uint8_t data, uint8_t pin)
{
	return  (data >> (pin-1)) & 1;
}


void EX16::pinMode(uint8_t pin, uint8_t mode)
{
	bool pinModeVal;
	if(mode==1)
	{
		pinModeVal=1;
	}else
	{
		pinModeVal=0;
	}
	
	if(pin<9){
	
		
      pinModeP0 = modifyBit(pinModeP0, pin, pinModeVal); // change relavent bit in pin mode

      Wire.beginTransmission(i2cAddress); // transmit to device 
      Wire.write(configPort0);        // config register p0
      Wire.write(pinModeP0);        // data
      Wire.endTransmission();    // stop transmitting
	  


    }else
    {
      pinModeP1 = modifyBit(pinModeP1, pin-8, pinModeVal); // change relavent bit in pin mode

      Wire.beginTransmission(i2cAddress); // transmit to device 
      Wire.write(configPort1);        // config register p1
      Wire.write(pinModeP1);        // data 
      Wire.endTransmission();    // stop transmitting
	  
	  
    }
	
}


void EX16::interruptConfig(uint8_t pin, uint8_t mode) // mode 1 for enable
{
		
		
	if(pin<8)
	{	
      interruptPinModeP0 = modifyBit(interruptPinModeP0, pin, !mode); // change relavent bit in pin mode
	  
      Wire.beginTransmission(i2cAddress); // transmit to device 
      Wire.write(interruptConfigPort0);        // config register p0
      Wire.write(interruptPinModeP0);        // data
      Wire.endTransmission();    // stop transmitting
	  
	  
	  //Serial.print("set interrupt data my :-");
	 // Serial.println(interruptPinModeP0); //testing
	 // Serial.println(pin); //testing
	  //pushPullData0 = modifyBit(pushPullData0, pin, !mode);

    }else
    {
      interruptPinModeP1 = modifyBit(interruptPinModeP1, pin-8, !mode); // change relavent bit in pin mode

      Wire.beginTransmission(i2cAddress); // transmit to device 
      Wire.write(interruptConfigPort1);        // config register p1
      Wire.write(interruptPinModeP1);        // data 
      Wire.endTransmission();    // stop transmitting
    }
	
	//Serial.print("set interrupt data :-");
	//Serial.println(interruptPinModeP0); //testing
	//Serial.println(pin); //testing
}


void EX16::digitalWrite(uint8_t pin, uint8_t mode)
{
	
    if(pin<9){  // for 02H register
      pinDataP0 = modifyBit(pinDataP0, pin, mode); // change relavent bit in pin mode

      Wire.beginTransmission(i2cAddress); // transmit to device 
      Wire.write(outputPort0);        // config register p0
      Wire.write(pinDataP0);        // data
      Wire.endTransmission();    // stop transmitting

    }else
    {
	// for 03H register
    pinModeP1 = modifyBit(pinModeP1, pin-8, mode); // change relavent bit in pin mode
	
	// p0 port set to push-pull mode
	Wire.beginTransmission(i2cAddress); // transmit to device 
	Wire.write(configPort0Globle);        // config register p0
	Wire.write(pinModeP1);        // set relavent pin as push pull mode
	Wire.endTransmission();    // stop transmitting

	// write data
    Wire.beginTransmission(i2cAddress); // transmit to device 
    Wire.write(outputPort1);        // config register p1
    Wire.write(pinModeP1);        // data 
    Wire.endTransmission();    // stop transmitting
	
    }
	
}

void EX16::analogWrite(uint8_t pin, uint8_t value)
{
	
	if(pin<9){  // for 12H register
      gpioLedModeData0 = modifyBit(gpioLedModeData0, pin, 0); // change relavent bit to 0 for led mode

      Wire.beginTransmission(i2cAddress); // transmit to device 
      Wire.write(gpioLedSelectReg0);        // config register p0
      Wire.write(gpioLedModeData0);        // data
      Wire.endTransmission();    // stop transmitting

    }else
    {  // for 13H register
      gpioLedModeData1 = modifyBit(gpioLedModeData1, pin-8, 0); // change relavent bit in pin mode

      Wire.beginTransmission(i2cAddress); // transmit to device 
      Wire.write(gpioLedSelectReg1);        // config register p1
      Wire.write(gpioLedModeData1);        // data 
      Wire.endTransmission();    // stop transmitting
    }
	
	
	
	// pin map for extender's order
	uint8_t analogRegister=0;
	if(pin<5)
	{
		analogRegister= pin+31;   
	}else if(pin<9)
	{
		analogRegister= pin+39;   
	}else if(pin<17)
	{
		analogRegister= pin+27;   
	}

    Wire.beginTransmission(i2cAddress); // transmit to device 
    Wire.write(analogRegister);        // config register 
    Wire.write(value);          // data 
    Wire.endTransmission();    // stop transmitting
	

}

uint8_t EX16::digitalRead(uint8_t pin)
{
	   if(pin<9)
      {  //00h reg

        Wire.beginTransmission(i2cAddress); // transmit to device 
        Wire.write(inputPort0);        // config input register 
        Wire.endTransmission();    // stop transmitting

        Wire.beginTransmission(i2cAddress); // transmit to device for read
		Wire.requestFrom(i2cAddress, 1);   // read 1 byte
        uint8_t ReadDataP0 = Wire.read(); // receive byte 
		Wire.endTransmission(); // end transmission
		
		 //Serial.print("port1 value");
		 //Serial.println(ReadDataP0);	


        return  (ReadDataP0 >> (pin-1)) & 1;


      }else
      { // 01h reg

        Wire.beginTransmission(i2cAddress); // transmit to device 
        Wire.write(inputPort1);        // config input register 
        Wire.endTransmission();    // stop transmitting

        Wire.beginTransmission(i2cAddress); // transmit to device for read
		Wire.requestFrom(i2cAddress, 1);   // read 1 byte
        uint8_t ReadDataP1 = Wire.read(); // receive byte 
		Wire.endTransmission(); // end transmission
		
		//Serial.print("port value");
		//Serial.println(ReadDataP0);	



        return  (ReadDataP1 >> (pin-9)) & 1;

      }

}


uint8_t EX16::getInterruptedPin()
{
        //00h reg
        Wire.beginTransmission(i2cAddress); // transmit to device 
        Wire.write(inputPort0);        // config input register 
        Wire.endTransmission();    // stop transmitting

        Wire.beginTransmission(i2cAddress); // transmit to device for read
		Wire.requestFrom(i2cAddress, 1);   // read 1 byte
        uint8_t interruptPinDataP0New = Wire.read(); // receive byte 
		Wire.endTransmission(); // end transmission

       // return  (ReadDataP0 >> pin) & 1;
      
       // 01h reg
        Wire.beginTransmission(i2cAddress); // transmit to device 
        Wire.write(inputPort1);        // config input register 
        Wire.endTransmission();    // stop transmitting

        Wire.beginTransmission(i2cAddress); // transmit to device for read
		Wire.requestFrom(i2cAddress, 1);   // read 1 byte
        uint8_t interruptPinDataP1New = Wire.read(); // receive byte 
		Wire.endTransmission(); // end transmission

        //return  (ReadDataP1 >> pin-8) & 1;
		
    
		int changeValue = interruptPinDataP0^interruptPinDataP0New; //compare status ang get change value 
		int pin=0;
    
		while(changeValue>0)
		{
			changeValue=changeValue>>1;
			pin++;
		}
		
		interruptEdge = readBit(interruptPinDataP0,pin) - readBit(interruptPinDataP0New,pin); // identify ricing or faling egg
		
		if(pin!=0) // detect interrupt
		{	
			interruptPinDataP0=interruptPinDataP0New;			// set new value for previous status
			//Serial.print("interrupted pin");
			//Serial.println(pin);
			return pin;
		}else // if pin ==0 then p0 havent interruppt, so check p1
		{
			 changeValue = interruptPinDataP1^interruptPinDataP1New; //compare status ang get change value 
			 pin=0;
			 
			 while(changeValue>0)
			{
				changeValue=changeValue>>1;
				pin++;
			}
			
			
			
			if(pin!=0)
			{
				interruptPinDataP1=interruptPinDataP1New;  // set new value for previous status
				//Serial.print("interrupted pin");
				//Serial.println(pin);
				return pin+8;
				
			}else
			{
				//Serial.println("no interrupt");
				return 0;
			}
			
			// if return 0, cant identify interruppt
		}
}


int EX16::getInterruptEdge()
{
	return interruptEdge;
}






// 8bit io expander

EX8::EX8(bool AD1, bool AD0)
{
	// init io extender
	delay(6);
	// deive addr 0011 a2 a1 a0  
	// a2 =0
	 // 1 for input , 0 for output
      if(AD1==1 and AD0==1)
		{
          i2cAddress = 0x1B; //0011011  27
          
        }else if(AD1==1 and AD0==0)
		{
          i2cAddress = 0x1A; //0011010	26
          
        }else if(AD1==0 and AD0==1)	
		{
          i2cAddress = 0x19; //0011001	25
		  //Serial.println(" addr 25 called");
          
        }else if(AD1==0 and AD0==0)
		{
          i2cAddress = 0x18; //0011000	24
          
        }  
       

        // config config_port registers for all pins as input in initilize mode
        /*
        04h config p1
        05 config p2
        */
        Wire.beginTransmission(i2cAddress); // transmit to device 
        Wire.write(configReg);        // config register p0
        Wire.write(pinModeP0);        // data , all pin as input
        Wire.endTransmission();    // stop transmitting
		
}

int EX8::modifyBit(int currentByte, int BitPosition, int bitData) // bit field, change BitPosition, change value
      { 
        int mask = 1 << (BitPosition-1); 
        return (currentByte & ~mask) | ((bitData << (BitPosition-1)) & mask); 
      }

// pin , CpinMode  INPUT == 0
void EX8::pinMode(uint8_t pin, uint8_t mode)
{
	bool pinModeVal;
	if(mode==1)
	{
		pinModeVal=1;
	}else
	{
		pinModeVal=0;
	}
	
      pinModeP0 = modifyBit(pinModeP0, pin, pinModeVal); // change relavent bit in pin mode (!mode use for match with arduino mode)

      Wire.beginTransmission(i2cAddress); // transmit to device 
      Wire.write(configReg);        // config register p0
      Wire.write(pinModeP0);        // data
      Wire.endTransmission();    // stop transmitting
	  
	  // config inverse reg
	  Wire.beginTransmission(i2cAddress); // transmit to device 
      Wire.write(inverseReg);        // config invers reg register p0
      Wire.write(0);        // all pin not inverse
      Wire.endTransmission();    // stop transmitting

}

// HIGH ==1 
void EX8::digitalWrite(uint8_t pin, uint8_t mode)
{
	pinDataP0 = modifyBit(pinDataP0, pin, mode); // change relavent bit in pin data

      Wire.beginTransmission(i2cAddress); // transmit to device 
      Wire.write(outputReg);        // config register p0
      Wire.write(pinDataP0);        // data
      Wire.endTransmission();    // stop transmitting
	  
	  //Serial.println(" digital write called");
	  

}


uint8_t EX8::digitalRead(uint8_t pin)
{
	
        Wire.beginTransmission(i2cAddress); // transmit to device 
        Wire.write(inputReg);        // config input register 
        Wire.endTransmission();    // stop transmitting
		//delay(200);

        Wire.beginTransmission(i2cAddress); // transmit to device for read
		Wire.requestFrom(i2cAddress, 1);   // read 1 byte
        uint8_t ReadDataP0 = Wire.read(); // receive byte 
		Wire.endTransmission(); // end transmission
		
		//Serial.println(ReadDataP0);
		//delay(200);

        return  (ReadDataP0 >> (pin-1)) & 1;

}

