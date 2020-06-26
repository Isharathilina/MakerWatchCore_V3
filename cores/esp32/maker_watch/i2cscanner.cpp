#include "i2cscanner.h"
#include "Arduino.h"
#include "Wire.h"  // for scan i2c bus
//#include "ioExtender.h"
//#include "pinhandle.h" // for runinterrupt

#define DEBUG

uint8_t ex8bitAddresses[4];
uint8_t ex8bitCount;
uint8_t ex16bitAddresses[4];
uint8_t ex16bitCount;

uint8_t deviceTable[20];
uint8_t numberOfDevices;

void i2cscanservice()
{
	
  numberOfDevices = 0;	
  byte error, address;
#ifdef DEBUG     
   Serial.println("Scanning...");
#endif
  

  for(address = 1; address < 127; address++ ) 
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
		
#ifdef DEBUG     
   Serial.print("I2C device found at address ");

      //if (address<16) 
       // Serial.print("0");
  
      Serial.print(address);
      Serial.println("  !");
#endif
     



	  deviceTable[numberOfDevices] = address;
      numberOfDevices++;
    }
    else if (error==4) 
    {
#ifdef DEBUG     
      Serial.print("Unknow error at address 0x");
    
      if (address<16)   
      Serial.print("0");
      Serial.println(address); //Serial.println(address,HEX);
#endif		  
        
    }    
  }
  if (numberOfDevices == 0)
  {
#ifdef DEBUG     
		Serial.println("No I2C devices found\n");
#endif
    
  }else{
#ifdef DEBUG     
		Serial.print("numberOfDevices :-"); Serial.println(numberOfDevices);
		
		Serial.println("done\n"); //numberOfDevices
#endif
  }

		 
}




void selectDevice()
{
	
	ex8bitCount = 0;
	ex16bitCount = 0;


				
	for(int i=0; i<numberOfDevices; i++)
	{	
#ifdef DEBUG 
		Serial.print("Detected device :- "); //numberOfDevices
		Serial.println(deviceTable[i]); //numberOfDevices
		
#endif	
		
		switch (deviceTable[i])// connected device address for IO extender
		{ 
		
		   case 24: //48 for test
		   case 25: 
		   case 26:
		   case 27: 
		     ex8bitAddresses[ex8bitCount]=deviceTable[i];
			 ex8bitCount++;
				   break; 
			
		   case 88: 
		   case 89: 
		   case 90:
		   case 91: 
		    ex16bitAddresses[ex16bitCount]=deviceTable[i];
			 ex16bitCount++;
				   break; 
		     
	   } 
			
		
	}
	
	
}


