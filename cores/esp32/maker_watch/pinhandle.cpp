
#include "pinhandle.h"
#include "i2cscanner.h"
#include "displayService.h"
#include "ioExtender.h"
#include "interruptHandle.h" //interrupt pin drive



extern uint8_t ex8bit[4];
extern uint8_t ex8bitCount;
extern uint8_t ex16bit[4];
extern uint8_t ex16bitCount;


uint8_t mappedPinNo;
uint8_t mappedExpander;  //EX8_1 = 81, EX8_2 = 82, EX16_1 = 161




// load all 8 bit and 16 bit instence EX8_1, EX16_1

void pinMap(uint8_t pin)
{
	
//------------------- -----------start 0----------

	if(ex8bitCount==0 && ex16bitCount==0)
	{
		//give display err no connected gpio extender
		//invalidPinConfigErrHandle(pin);
		invalidPinConfigErr(pin);

	}
	

	if(ex8bitCount==0 && ex16bitCount==1)
	{
		if(pin<17)
		{
			//EX16_1.pinMode(pin, mode);
			mappedPinNo = pin;
			mappedExpander = 161;
			
		}else
		{
			//give err
			invalidPinConfigErr(pin);
		}
	}
	

	if(ex8bitCount==0 && ex16bitCount==2)
	{
		if(pin<17)
		{
			//EX16_1.pinMode(pin, mode);
			mappedPinNo = pin;
			mappedExpander = 161;
			
		}else if(pin<33)
		{
			//EX16_2.pinMode(pin-8, mode);
			mappedPinNo = pin-16;
			mappedExpander = 162;
		
		}else
		{
			//give err
			invalidPinConfigErr(pin);

		}
		
	}
	

	if(ex8bitCount==0 && ex16bitCount==3)
	{
		if(pin<17)
		{
			//EX16_1.pinMode(pin, mode);
			mappedPinNo = pin;
			mappedExpander = 161;
			
		}else if(pin<33)
		{
			//EX16_2.pinMode(pin-16, mode);	
			mappedPinNo = pin-16;
			mappedExpander = 162;
			
		}else if(pin<49)
		{
			//EX16_3.pinMode(pin-32, mode);
			mappedPinNo = pin-32;
			mappedExpander = 163;

		}else
		{
			//give err
			invalidPinConfigErr(pin);
		}

		
	}
	
  
  
  	if(ex8bitCount==0 && ex16bitCount==4)
	{
		if(pin<17)
		{
			//EX16_1.pinMode(pin, mode);
			mappedPinNo = pin;
			mappedExpander = 161;
			
		}else if(pin<33)
		{
			//EX16_2.pinMode(pin-16, mode);
			mappedPinNo = pin-16;
			mappedExpander = 162;
			
		}else if(pin<49)
		{
			//EX16_3.pinMode(pin-32, mode);	
			mappedPinNo = pin-32;
			mappedExpander = 163;

		}else if(pin<65)
		{
			//EX16_4.pinMode(pin-48, mode);			
			mappedPinNo = pin-48;
			mappedExpander = 164;

		}else
		{
			//give err
			invalidPinConfigErr(pin);
		}

		
	}
	
  

//----------------------end 0 -----------start 1


	if(ex8bitCount==1 && ex16bitCount==0)
	{
		if(pin<9)
		{
			//EX8_1.pinMode(pin, mode);
			mappedPinNo = pin;
			mappedExpander = 81;
			
		}else
		{
			//give display err invalid pin
			invalidPinConfigErr(pin);
		}
	}
	

	if(ex8bitCount==2 && ex16bitCount==0)
	{
		if(pin<9)
		{
			//EX8_1.pinMode(pin, mode);
			mappedPinNo = pin;
			mappedExpander = 81;
			
			//Serial.println("trigger 81");
			
		}else if(pin<17)
		{
			//EX8_2.pinMode(pin-8, mode);	
			mappedPinNo = pin-8;
			mappedExpander = 82;
			
			// Serial.println("trigger 82");
			// Serial.print("pin ;- ");
			// Serial.println(mappedPinNo);

			
		}else
		{
			//give err
			invalidPinConfigErr(pin);
			Serial.println("trigger err");
		}
	}
	

	if(ex8bitCount==3 && ex16bitCount==0)
	{
		if(pin<9)
		{
			//EX8_1.pinMode(pin, mode);
			mappedPinNo = pin;
			mappedExpander = 81;
			
		}else if(pin<17)
		{
			//EX8_2.pinMode(pin-8, mode);	
			mappedPinNo = pin-8;
			mappedExpander = 82;
			
		}else if(pin<25)
		{
			//EX8_3.pinMode(pin-16, mode);	
			mappedPinNo = pin-16;
			mappedExpander = 83;
		}else
		{
			//give err
			invalidPinConfigErr(pin);
		}
		
	}
	

	if(ex8bitCount==4 && ex16bitCount==0)
	{
		if(pin<9)
		{
			//EX8_1.pinMode(pin, mode);
			mappedPinNo = pin;
			mappedExpander = 81;
			
		}else if(pin<17)
		{
			//EX8_2.pinMode(pin-8, mode);
			mappedPinNo = pin-8;
			mappedExpander = 82;
			
		}else if(pin<25)
		{
			//EX8_3.pinMode(pin-16, mode);
			mappedPinNo = pin-16;
			mappedExpander = 83;
			
		}else if(pin<33)
		{
			//EX8_4.pinMode(pin-24, mode);	
			mappedPinNo = pin-24;
			mappedExpander = 84;
			
		}else
		{
			//give err
			invalidPinConfigErr(pin);
		}

		
	}
	
  	
	
//----------------------end 1 -----------start 2

	if(ex8bitCount==1 && ex16bitCount==1)
	{
		if(pin<9)
		{
			//EX8_1.pinMode(pin, mode);
			mappedPinNo = pin;
			mappedExpander = 81;
			
		}else if(pin<25)
		{
			//EX16_1.pinMode(pin-8, mode);
			mappedPinNo = pin-8;
			mappedExpander = 161;
			
		}else
		{
			//give err
			invalidPinConfigErr(pin);
		}
		
	}
	

	if(ex8bitCount==2 && ex16bitCount==1)
	{
		if(pin<9)
		{
			//EX8_1.pinMode(pin, mode);
			mappedPinNo = pin;
			mappedExpander = 81;
			
		}else if(pin<17)
		{
			//EX8_2.pinMode(pin-8, mode);	
			mappedPinNo = pin-8;
			mappedExpander = 82;
			
		}else if(pin<33)
		{
			//EX16_1.pinMode(pin-16, mode);
			mappedPinNo = pin-16;
			mappedExpander = 161;
			
		}else
		{
			//give err
			invalidPinConfigErr(pin);
		}
	}
	

	if(ex8bitCount==3 && ex16bitCount==1)
	{
		if(pin<9)
		{
			//EX8_1.pinMode(pin, mode);
			mappedPinNo = pin;
			mappedExpander = 81;
			
		}else if(pin<17)
		{
			//EX8_2.pinMode(pin-8, mode);
			mappedPinNo = pin-8;
			mappedExpander = 82;
			
		}else if(pin<25)
		{
			//EX8_3.pinMode(pin-16, mode);	
			mappedPinNo = pin-16;
			mappedExpander = 83;
			
		}else if(pin<41)
		{
			//EX16_1.pinMode(pin-24, mode);	
			mappedPinNo = pin-24;
			mappedExpander = 161;
			
		}else
		{
			//give err
			invalidPinConfigErr(pin);
		}
		
	}
	

	if(ex8bitCount==4 && ex16bitCount==1)
	{
		if(pin<9)
		{
			//EX8_1.pinMode(pin, mode);
			mappedPinNo = pin;
			mappedExpander = 81;
			
		}else if(pin<17)
		{
			//EX8_2.pinMode(pin-8, mode);
			mappedPinNo = pin-8;
			mappedExpander = 82;
			
		}else if(pin<25)
		{
			//EX8_3.pinMode(pin-16, mode);	
			mappedPinNo = pin-16;
			mappedExpander = 83;
			
		}else if(pin<33)
		{
			//EX8_4.pinMode(pin-24, mode);	
			mappedPinNo = pin-24;
			mappedExpander = 84;
			
		}else if(pin<49)
		{
			//EX16_1.pinMode(pin-32, mode);	
			mappedPinNo = pin-32;
			mappedExpander = 161;
			
		}else
		{
			//give err
			invalidPinConfigErr(pin);
		}

		
	}
	


//----------------------end 2 -----------start3


	if(ex8bitCount==1 && ex16bitCount==2)
	{
		if(pin<9)
		{
			//EX8_1.pinMode(pin, mode);
			mappedPinNo = pin;
			mappedExpander = 81;
			
		}else if(pin<25)
		{
			//EX16_1.pinMode(pin-8, mode);
			mappedPinNo = pin-8;
			mappedExpander = 161;
			
		}else if(pin<41)
		{
			//EX16_2.pinMode(pin-24, mode);			
			mappedPinNo = pin-24;
			mappedExpander = 162;
			
		}else
		{
			//give err
			invalidPinConfigErr(pin);
		}
		
	}
	

	if(ex8bitCount==2 && ex16bitCount==2)
	{
		if(pin<9)
		{
			//EX8_1.pinMode(pin, mode);
			mappedPinNo = pin;
			mappedExpander = 81;
			
		}else if(pin<17)
		{
			//EX8_2.pinMode(pin-8, mode);
			mappedPinNo = pin-8;
			mappedExpander = 82;
			
		}else if(pin<33)
		{
			//EX16_1.pinMode(pin-16, mode);			
			mappedPinNo = pin-16;
			mappedExpander = 161;
			
		}else if(pin<49)
		{
			//EX16_2.pinMode(pin-32, mode);	
			mappedPinNo = pin-32;
			mappedExpander = 162;
			
		}else
		{
			//give err
			invalidPinConfigErr(pin);
		}
	}
	

	if(ex8bitCount==3 && ex16bitCount==2)
	{
		if(pin<9)
		{
			//EX8_1.pinMode(pin, mode);
			mappedPinNo = pin;
			mappedExpander = 81;
			
		}else if(pin<17)
		{
			//EX8_2.pinMode(pin-8, mode);	
			mappedPinNo = pin-8;
			mappedExpander = 82;
			
		}else if(pin<25)
		{
			//EX8_3.pinMode(pin-16, mode);			
			mappedPinNo = pin-16;
			mappedExpander = 83;
			
		}else if(pin<41)
		{
			//EX16_1.pinMode(pin-24, mode);		
			mappedPinNo = pin-24;
			mappedExpander = 161;
			
		}else if(pin<57)
		{
			//EX16_2.pinMode(pin-40, mode);	
			mappedPinNo = pin-40;
			mappedExpander = 162;
			
		}else
		{
			//give err
			invalidPinConfigErr(pin);
		}
		
	}
	

	if(ex8bitCount==4 && ex16bitCount==2)
	{
		if(pin<9)
		{
			//EX8_1.pinMode(pin, mode);
			mappedPinNo = pin;
			mappedExpander = 81;
			
		}else if(pin<17)
		{
			//EX8_2.pinMode(pin-8, mode);	
			mappedPinNo = pin-8;
			mappedExpander = 82;
			
		}else if(pin<25)
		{
			//EX8_3.pinMode(pin-16, mode);	
			mappedPinNo = pin-16;
			mappedExpander = 83;
			
		}else if(pin<33)
		{
			//EX8_4.pinMode(pin-24, mode);		
			mappedPinNo = pin-24;
			mappedExpander = 84;
			
		}else if(pin<49)
		{
			//EX16_1.pinMode(pin-32, mode);	
			mappedPinNo = pin-32;
			mappedExpander = 161;
			
		}else if(pin<65)
		{
			//EX16_2.pinMode(pin-48, mode);			
			mappedPinNo = pin-48;
			mappedExpander = 162;
			
		}else 
		{
			//give err
			invalidPinConfigErr(pin);
		}

		
	}
	

//----------------------end 3 -----------start4


	if(ex8bitCount==1 && ex16bitCount==3)
	{
		if(pin<9)
		{
			//EX8_1.pinMode(pin, mode);
			mappedPinNo = pin;
			mappedExpander = 81;
			
		}else if(pin<25)
		{
			//EX16_1.pinMode(pin-8, mode);	
			mappedPinNo = pin-8;
			mappedExpander = 161;
			
		}else if(pin<41)
		{
			//EX16_2.pinMode(pin-24, mode);	
			mappedPinNo = pin-24;
			mappedExpander = 162;
			
		}else if(pin<57)
		{
			//EX16_3.pinMode(pin-40, mode);		
			mappedPinNo = pin-40;
			mappedExpander = 163;
			
		}else
		{
			//give err
			invalidPinConfigErr(pin);
		}
		
	}
	

	if(ex8bitCount==2 && ex16bitCount==3)
	{
		if(pin<9)
		{
			//EX8_1.pinMode(pin, mode);
			mappedPinNo = pin;
			mappedExpander = 81;
			
		}else if(pin<17)
		{
			//EX8_2.pinMode(pin-8, mode);	
			mappedPinNo = pin-8;
			mappedExpander = 82;
			
		}else if(pin<33)
		{
			//EX16_1.pinMode(pin-16, mode);			
			mappedPinNo = pin-16;
			mappedExpander = 161;
			
		}else if(pin<49)
		{
			//EX16_2.pinMode(pin-32, mode);	
			mappedPinNo = pin-32;
			mappedExpander = 162;
			
		}else if(pin<65)
		{
			//EX16_3.pinMode(pin-48, mode);		
			mappedPinNo = pin-48;
			mappedExpander = 163;
			
		}else
		{
			//give err
			invalidPinConfigErr(pin);
		}
	}
	

	if(ex8bitCount==3 && ex16bitCount==3)
	{
		if(pin<9)
		{
			//EX8_1.pinMode(pin, mode);
			mappedPinNo = pin;
			mappedExpander = 81;
			
		}else if(pin<17)
		{
			//EX8_2.pinMode(pin-8, mode);
			mappedPinNo = pin-8;
			mappedExpander = 82;
			
		}else if(pin<25)
		{
			//EX8_3.pinMode(pin-16, mode);		
			mappedPinNo = pin-16;
			mappedExpander = 83;
			
		}else if(pin<41)
		{
			//EX16_1.pinMode(pin-24, mode);	
			mappedPinNo = pin-24;
			mappedExpander = 161;
			
		}else if(pin<57)
		{
			//EX16_2.pinMode(pin-40, mode);	
			mappedPinNo = pin-40;
			mappedExpander = 162;
			
		}else if(pin<73)
		{
			//EX16_3.pinMode(pin-56, mode);	
			mappedPinNo = pin-56;
			mappedExpander = 163;
			
		}else
		{
			//give err
			invalidPinConfigErr(pin);
		}
		
	}
	

	if(ex8bitCount==4 && ex16bitCount==3)
	{
		if(pin<9)
		{
			//EX8_1.pinMode(pin, mode);
			mappedPinNo = pin;
			mappedExpander = 81;
			
		}else if(pin<17)
		{
			//EX8_2.pinMode(pin-8, mode);			
			mappedPinNo = pin-8;
			mappedExpander = 82;
			
		}else if(pin<25)
		{
			//EX8_3.pinMode(pin-16, mode);	
			mappedPinNo = pin-16;
			mappedExpander = 83;
			
		}else if(pin<33)
		{
			//EX8_4.pinMode(pin-24, mode);			
			mappedPinNo = pin-24;
			mappedExpander = 84;
			
		}else if(pin<49)
		{
			//EX16_1.pinMode(pin-32, mode);		
			mappedPinNo = pin-32;
			mappedExpander = 161;
			
		}else if(pin<65)
		{
			//EX16_2.pinMode(pin-48, mode);			
			mappedPinNo = pin-48;
			mappedExpander = 162;
			
		}else if(pin<81)
		{
			//EX16_3.pinMode(pin-64, mode);		
			mappedPinNo = pin-64;
			mappedExpander = 163;
			
		}else
		{
			//give err
			invalidPinConfigErr(pin);
		}

		
	}
	
//----------------------end 4 -----------start 5


	if(ex8bitCount==1 && ex16bitCount==4)
	{
		if(pin<9)
		{
			//EX8_1.pinMode(pin, mode);
			mappedPinNo = pin;
			mappedExpander = 81;
			
		}else if(pin<25)
		{
			//EX16_1.pinMode(pin-8, mode);	
			mappedPinNo = pin-8;
			mappedExpander = 161;
			
		}else if(pin<41)
		{
			//EX16_2.pinMode(pin-24, mode);	
			mappedPinNo = pin-24;
			mappedExpander = 162;
			
		}else if(pin<57)
		{
			//EX16_3.pinMode(pin-40, mode);			
			mappedPinNo = pin-40;
			mappedExpander = 163;
			
		}else if(pin<73)
		{
			//EX16_4.pinMode(pin-56, mode);	
			mappedPinNo = pin-56;
			mappedExpander = 164;
			
		}else
		{
			//give err
			invalidPinConfigErr(pin);
		}
		
	}
	

	if(ex8bitCount==2 && ex16bitCount==4)
	{
		if(pin<9)
		{
			//EX8_1.pinMode(pin, mode);
			mappedPinNo = pin;
			mappedExpander = 81;
			
		}else if(pin<17)
		{
			//EX8_2.pinMode(pin-8, mode);	
			mappedPinNo = pin-8;
			mappedExpander = 82;
			
		}else if(pin<33)
		{
			//EX16_1.pinMode(pin-16, mode);	
			mappedPinNo = pin-16;
			mappedExpander = 161;
			
		}else if(pin<49)
		{
			//EX16_2.pinMode(pin-32, mode);	
			mappedPinNo = pin-32;
			mappedExpander = 162;
			
		}else if(pin<65)
		{
			//EX16_3.pinMode(pin-48, mode);			
			mappedPinNo = pin-48;
			mappedExpander = 163;
			
		}else if(pin<81)
		{
			//EX16_4.pinMode(pin-64, mode);		
			mappedPinNo = pin-64;
			mappedExpander = 164;
			
		}else
		{
			//give err
			invalidPinConfigErr(pin);
		}
	}
	

	if(ex8bitCount==3 && ex16bitCount==4)
	{
		if(pin<9)
		{
			//EX8_1.pinMode(pin, mode);
			mappedPinNo = pin;
			mappedExpander = 81;
			
		}else if(pin<17)
		{
			//EX8_2.pinMode(pin-8, mode);			
			mappedPinNo = pin-8;
			mappedExpander = 82;
			
		}else if(pin<25)
		{
			//EX8_3.pinMode(pin-16, mode);
			mappedPinNo = pin-16;
			mappedExpander = 83;
			
		}else if(pin<41)
		{
			//EX16_1.pinMode(pin-24, mode);	
			mappedPinNo = pin-24;
			mappedExpander = 161;
			
		}else if(pin<57)
		{
			//EX16_2.pinMode(pin-40, mode);	
			mappedPinNo = pin-40;
			mappedExpander = 162;
			
		}else if(pin<73)
		{
			//EX16_3.pinMode(pin-56, mode);		
			mappedPinNo = pin-56;
			mappedExpander = 163;
			
		}else if(pin<89)
		{
			//EX16_3.pinMode(pin-72, mode);			
			mappedPinNo = pin-2;
			mappedExpander = 163;
			
		}else
		{
			//give err
			invalidPinConfigErr(pin);
		}
		
	}
	

	if(ex8bitCount==4 && ex16bitCount==4)
	{
		if(pin<9)
		{
			//EX8_1.pinMode(pin, mode);
			mappedPinNo = pin;
			mappedExpander = 81;
			
		}else if(pin<17)
		{
			//EX8_2.pinMode(pin-8, mode);
			mappedPinNo = pin-8;
			mappedExpander = 82;
			
		}else if(pin<25)
		{
			//EX8_3.pinMode(pin-16, mode);		
			mappedPinNo = pin-16;
			mappedExpander = 83;
			
		}else if(pin<33)
		{
			//EX8_4.pinMode(pin-24, mode);		
			mappedPinNo = pin-24;
			mappedExpander = 84;
			
		}else if(pin<49)
		{
			//EX16_1.pinMode(pin-32, mode);	
			mappedPinNo = pin-32;
			mappedExpander = 161;
			
		}else if(pin<65)
		{
			//EX16_2.pinMode(pin-48, mode);	
			mappedPinNo = pin-48;
			mappedExpander = 162;
			
		}else if(pin<81)
		{
			//EX16_3.pinMode(pin-64, mode);	
			mappedPinNo = pin-64;
			mappedExpander = 163;
			
		}else if(pin<97)
		{
			//EX16_4.pinMode(pin-80, mode);			
			mappedPinNo = pin-80;
			mappedExpander = 164;
			
		}else
		{
			//give err
			invalidPinConfigErr(pin);
		}

		
	}
	

//----------------------end 4 -----------
		 
}


void pinMode(uint8_t pin, uint8_t mode)
{
	pinMap(pin);
	// mappedPinNo mappedExpander
	switch (mappedExpander)// connected device address
		{ 
		
		   case 81:
				
				EX8_1.pinMode(mappedPinNo, mode);
				//Serial.println("trigger pinmode 81");

				break;
		   case 82:
				EX8_2.pinMode(mappedPinNo, mode);
				//Serial.println("trigger pinmode 82");
				break;
		   case 83:
				EX8_3.pinMode(mappedPinNo, mode);
				break;
		   case 84: 
				EX8_4.pinMode(mappedPinNo, mode);
				break;
		   case 161: 
				EX16_1.pinMode(mappedPinNo, mode);
				//Serial.println("trigger pinmode 81");
				break;
		   case 162: 
				EX16_2.pinMode(mappedPinNo, mode);
				//Serial.println("trigger pinmode 82");
				break;
		   case 163:
				EX16_3.pinMode(mappedPinNo, mode);
				break;
		   case 164: 
				EX16_4.pinMode(mappedPinNo, mode);
				break;
		     
	   }	
}





void digitalWrite(uint8_t pin, uint8_t val)
{
	pinMap(pin);
	// mappedPinNo mappedExpander
	switch (mappedExpander)// connected device address
		{ 
		
		   case 81:
				
				EX8_1.digitalWrite(mappedPinNo, val);
				break;
		   case 82:
				EX8_2.digitalWrite(mappedPinNo, val);
				
				 //Serial.print("addr of 82 - ");
				// Serial.println(EX8_2.i2cAddress);
				break;
		   case 83:
				EX8_3.digitalWrite(mappedPinNo, val);
				break;
		   case 84: 
				EX8_4.digitalWrite(mappedPinNo, val);
				break;
		   case 161: 
				EX16_1.digitalWrite(mappedPinNo, val);
				break;
		   case 162: 
				EX16_2.digitalWrite(mappedPinNo, val);
				break;
		   case 163:
				EX16_3.digitalWrite(mappedPinNo, val);
				break;
		   case 164: 
				EX16_4.digitalWrite(mappedPinNo, val);
				break;
		     
	   }	
}


bool digitalRead(uint8_t pin)
{
	pinMap(pin);
	// mappedPinNo mappedExpander
	switch (mappedExpander)// connected device address
		{ 
		
		   case 81:
				//return 0; // for test
				return EX8_1.digitalRead(mappedPinNo);
				break;
		   case 82:
				return EX8_2.digitalRead(mappedPinNo);
				break;
		   case 83:
				return EX8_3.digitalRead(mappedPinNo);
				break;
		   case 84: 
				return EX8_4.digitalRead(mappedPinNo);
				break;
		   case 161: 
				return EX16_1.digitalRead(mappedPinNo);
				break;
		   case 162: 
				return EX16_2.digitalRead(mappedPinNo);
				break;
		   case 163:
				return EX16_3.digitalRead(mappedPinNo);
				break;
		   case 164: 
				return EX16_4.digitalRead(mappedPinNo);
				break;
		   default :
				return 0;
	  
	   }	
}


// uint16_t analogRead(uint8_t pin)
// {
	// pinMap(pin);
	// // mappedPinNo mappedExpander
	// switch (mappedExpander)// connected device address
		// { 
		
		   // case 81:
				// //return 1280; // for test
				// return EX8_1.analogRead(mappedPinNo);
				// break;
		   // case 82:
				// return EX8_2.analogRead(mappedPinNo);
				// break;
		   // case 83:
				// return EX8_3.analogRead(mappedPinNo);
				// break;
		   // case 84: 
				// return EX8_4.analogRead(mappedPinNo);
				// break;
		   // case 161: 
				// return EX16_1.analogRead(mappedPinNo);
				// break;
		   // case 162: 
				// return EX16_2.analogRead(mappedPinNo);
				// break;
		   // case 163:
				// return EX16_3.analogRead(mappedPinNo);
				// break;
		   // case 164: 
				// return EX16_4.analogRead(mappedPinNo);
				// break;
		     
	   // }	
// }


void analogWrite(uint8_t pin, uint8_t val)
{			

	pinMap(pin);
	// mappedPinNo mappedExpander
	switch (mappedExpander)// connected device address
		{ 
		
		   case 81:
				
				//EX8_1.analogWrite(mappedPinNo, val);
				//break;
		   case 82:
				//EX8_2.analogWrite(mappedPinNo, val);
				//break;
		   case 83:
				//EX8_3.analogWrite(mappedPinNo, val);
				//break;
		   case 84: 
				//EX8_4.analogWrite(mappedPinNo, val);
				//break;
				invalidAnalogWriteErr(pin);
				break;
				
		   case 161: 
				EX16_1.analogWrite(mappedPinNo, val);
				break;
		   case 162: 
				EX16_2.analogWrite(mappedPinNo, val);
				break;
		   case 163:
				EX16_3.analogWrite(mappedPinNo, val);
				break;
		   case 164: 
				EX16_4.analogWrite(mappedPinNo, val);
				break;
		     
	   }	
}


 
typedef void (*voidFuncPtr2)(void);
uint8_t configerdInterruptPinList[65] = {0,};
uint8_t configerdInterrupEdgeList[96] = {0,};
uint8_t interruptIndex = 0;

void setInterrupt(uint8_t pin, voidFuncPtr2 userFunc, int intr_type)
{
	pinMap(pin);
	if(ex16bitCount>0)
	{
		int minimumPinNo = ex8bitCount*8;
		int maxPinNo = ex16bitCount*16+minimumPinNo;
		
		if(pin>minimumPinNo && pin<maxPinNo)
		{
			  setInterruptInC(pin, userFunc, intr_type);  // in inerruptHandler.c // set interrupt
			  configerdInterruptPinList[interruptIndex++] = pin; // update configered pin table
			  configerdInterrupEdgeList[pin] = intr_type;
			  
			  switch (mappedExpander)// connected device address
				{ 
						
				   case 161: 
						EX16_1.interruptConfig(mappedPinNo, 1); // 1 for interrupt interrupt enable
						
						//Serial.print("set interrupt :-");
						//Serial.println(mappedPinNo); //testing
						break;
				   case 162: 
						EX16_2.interruptConfig(mappedPinNo, 1);
						break;
				   case 163:
						EX16_3.interruptConfig(mappedPinNo, 1);
						break;
				   case 164: 
						EX16_4.interruptConfig(mappedPinNo, 1);
						break;
					 
			   }	
		}else
		{
			// please enter valid pin no
			invalidSetInterruptErr(pin);
		}
		
		
	}else
	{
		// print err no 16 bit io
		invalidSetInterruptErr(pin);
	}
	
}




void runPinInterrupt(uint8_t pin, int8_t edge)
{
	uint8_t index = 0;
	//Serial.println(" loop in");
	while(configerdInterruptPinList[index]!=0)
	{
		if(configerdInterruptPinList[index]==pin) // if have pre configered pin
		{	
			if(configerdInterrupEdgeList[pin]==1 && edge==1) // risin edge
			{
				runPinInterruptInC(pin);
				
			}else if( ((configerdInterrupEdgeList[pin]==2)||(configerdInterrupEdgeList[pin]==0)) && edge==-1) // faling edge
			{
				runPinInterruptInC(pin);
				
			}else if(configerdInterrupEdgeList[pin]==3) // change
			{
				runPinInterruptInC(pin);
			}
			  
			 // Serial.println("have it");
			  break;
			  	
		}
		index++;
	}
	//Serial.println("exit loop");
}





//pin 5 hardcorded
void interruptPinDrive()
{
	uint8_t pin=0;
	uint8_t pinAjustVal_Ex8bit=0;
	
	switch (ex8bitCount)// connected device address
		{ 
		   case 1:
				pinAjustVal_Ex8bit = 8;
				break;
		   case 2:
				pinAjustVal_Ex8bit = 16;
				break;
		   case 3: 
				pinAjustVal_Ex8bit = 24;
				break;
		   case 4: 
				pinAjustVal_Ex8bit = 32;
				break;
		   default:
				pinAjustVal_Ex8bit = 0;
				
		}			
				
	
	if(ex16bitCount) // have 16 bit extender 
	{
				
				if(ex16bitCount==1)
				{
					
					pin = EX16_1.getInterruptedPin();  // noice interrupt genarate 	
					//pin = 5;
					//Serial.print("pin value");
					//Serial.println(pin);
					if(pin!=0) // if return 0, it havent detect interrupt
					{
						for(byte st=0;st<65; st++)
						{
							if(configerdInterruptPinList[st]==pin) // check configer interrupt for this pin
							{						
								runPinInterrupt((pin+pinAjustVal_Ex8bit), EX16_1.getInterruptEdge()); //EX16_1.getInterruptEdge()
								Serial.print("edge ");
								Serial.println(EX16_1.getInterruptEdge());
								break;
							}
						}
						
						// if configered pin;  EX16_1.getInterruptEdge()
						// then, run
						
						//Serial.println(pin+pinAjustVal_Ex8bit);
					}
				}else if(ex16bitCount==2)
				{
					pin = EX16_1.getInterruptedPin();
					if(pin!=0)
					{
						// if configered pin;
						// then, run
						for(byte st=0;st<65; st++)
						{
							if(configerdInterruptPinList[st]==pin) // check configer interrupt for this pin
							{
								runPinInterrupt((pin+pinAjustVal_Ex8bit), EX16_1.getInterruptEdge());
								break;
							}
						}
						
					}
					
					pin = EX16_2.getInterruptedPin();
					if(pin!=0)
					{
						// if configered pin;
						// then, run
						for(byte st=0;st<65; st++)
						{
							if(configerdInterruptPinList[st]==pin) // check configer interrupt for this pin
							{
								runPinInterrupt((pin+16+pinAjustVal_Ex8bit), EX16_2.getInterruptEdge());
								break;
							}
						}
						
					}
					
				}else if(ex16bitCount==3)
				{
					pin = EX16_1.getInterruptedPin();
					if(pin!=0)
					{
						// if configered pin;
						// then, run
						for(byte st=0;st<65; st++)
						{
							if(configerdInterruptPinList[st]==pin) // check configer interrupt for this pin
							{
								runPinInterrupt((pin+pinAjustVal_Ex8bit), EX16_1.getInterruptEdge());
								break;
							}
						}
						
					}
					
					pin = EX16_2.getInterruptedPin();
					if(pin!=0)
					{
						// if configered pin;
						// then, run
						for(byte st=0;st<65; st++)
						{
							if(configerdInterruptPinList[st]==pin) // check configer interrupt for this pin
							{
								runPinInterrupt((pin+16+pinAjustVal_Ex8bit), EX16_2.getInterruptEdge());
								break;
							}
						}
						
					}
					
					pin = EX16_3.getInterruptedPin();
					if(pin!=0)
					{
						// if configered pin;
						// then, run
						for(byte st=0;st<65; st++)
						{
							if(configerdInterruptPinList[st]==pin) // check configer interrupt for this pin
							{
								runPinInterrupt((pin+32+pinAjustVal_Ex8bit), EX16_3.getInterruptEdge());
								break;
							}
						}
						
					}
					
				}else if(ex16bitCount==4)
				{
					pin = EX16_1.getInterruptedPin();
					if(pin!=0)
					{
						// if configered pin;
						// then, run
						for(byte st=0;st<65; st++)
						{
							if(configerdInterruptPinList[st]==pin) // check configer interrupt for this pin
							{
								runPinInterrupt((pin+pinAjustVal_Ex8bit), EX16_1.getInterruptEdge());
								break;
							}
						}
						
					}
					
					pin = EX16_2.getInterruptedPin();
					if(pin!=0)
					{
						// if configered pin;
						// then, run
						for(byte st=0;st<65; st++)
						{
							if(configerdInterruptPinList[st]==pin) // check configer interrupt for this pin
							{
								runPinInterrupt((pin+16+pinAjustVal_Ex8bit), EX16_2.getInterruptEdge());
								break;
							}
						}
						
					}
					
					pin = EX16_3.getInterruptedPin();
					if(pin!=0)
					{
						// if configered pin;
						// then, run
						for(byte st=0;st<65; st++)
						{
							if(configerdInterruptPinList[st]==pin) // check configer interrupt for this pin
							{
								runPinInterrupt((pin+32+pinAjustVal_Ex8bit), EX16_3.getInterruptEdge());
								break;
							}
						}
						
					}
					
					pin = EX16_4.getInterruptedPin();
					if(pin!=0)
					{
						// if configered pin;
						// then, run
						for(byte st=0;st<65; st++)
						{
							if(configerdInterruptPinList[st]==pin) // check configer interrupt for this pin
							{
								runPinInterrupt((pin+48+pinAjustVal_Ex8bit), EX16_4.getInterruptEdge());
								break;
							}
						}
					}
				}
				
				
				
	}
			
			
}



