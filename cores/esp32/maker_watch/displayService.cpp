
#include "displayService.h"
#include <Arduino.h>
  

#define IWIDTH  128
#define IHEIGHT 128

// create display
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite console = TFT_eSprite(&tft);

    
extern uint8_t ex8bitCount;
extern uint8_t ex16bitCount;

uint8_t lineNum=0;
String str[14];
uint16_t colour[14];

void consoleLog(char *text, uint16_t fontColour)
{

  if(strlen(text)>20)
  {
    String originalStr = text;
    String sub = originalStr.substring(0, 21);
    String exSub = originalStr.substring(20);

    char buf[21];
    char exbuf[60];
    sub.toCharArray(buf, 21);
    exSub.toCharArray(exbuf, 60);
    consoleLog(buf, fontColour);
    consoleLog(exbuf, fontColour);

  }else
  {
	  
	  if(lineNum==14)
	  {
		lineNum=13;
		console.fillSprite(TFT_BLACK);
		
		String tempDataStr[14];
		uint16_t tempDataColour[14];
		
		for(int i=0; i<14; i++)
		  {
			tempDataStr[i] = str[i];
			tempDataColour[i] = colour[i];
		  }
		for(int i=0; i<13; i++)
		  {
			str[i] = tempDataStr[i+1]; 
			colour[i] = tempDataColour[i+1]; 
		  }
	   }


	  str[lineNum] = text;
	  colour[lineNum] = fontColour;
	  lineNum++;
	  console.setTextColor(TFT_BLUE); //console.setTextColor(TFT_GREEN);
	  console.setTextSize(2);
	  console.setCursor(0,0);
	  console.println(" -Console-");

	  console.setTextSize(1);

	  for(int i=0; i<lineNum; i++)
		{
			console.setTextColor(colour[i]); //TFT_GREEN
			console.println(str[i]);
		}
	  console.pushSprite(0, 0);
  
  }

}

// console clear function
void consoleClear()
{
	 console.fillSprite(TFT_BLACK);
	 console.setCursor(0,0);
	 console.setTextColor(TFT_GREEN);
	 console.setTextSize(1);
	 console.pushSprite(0, 0);
	lineNum=0;
}

//invalid pin err display function
void invalidPinConfigErr(uint8_t pin)
{
	char msg[20];
	sprintf(msg, "Pin %d is Invalid!", pin);
	consoleLog(msg, TFT_RED);
	
	char suggestion[60];
	uint8_t pinCount = ex8bitCount*8 + ex16bitCount*16;
	
	if(pinCount<8) // then no attach any IO extender
	{
		sprintf(suggestion, "You haven't attach  any IO Extender, So Please attach it");
	}else
	{
		sprintf(suggestion, "You can use pin 1 to %d only", pinCount);
	}
	consoleLog(suggestion, TFT_LIGHTGREY);
	
}


void invalidSetInterruptErr(uint8_t pin)
{
	char msg[20];
	sprintf(msg, "Pin %d setInterrupt is Invalid!", pin);
	consoleLog(msg, TFT_RED);
	
	char suggestion[80];
	
	uint8_t minimumPinNo = ex8bitCount*8;
	uint8_t maxPinNo = ex16bitCount*16+minimumPinNo;
	
	
	if(ex16bitCount<1) // then no attach any 16  bit IO extender
	{
		sprintf(suggestion, "No attach any 16bit IO Extender, Interrupt only available in 16bit extenders");
	}else
	{
		sprintf(suggestion, "You can use pin %d to %d only for setInterrupt", minimumPinNo+1, maxPinNo);
	}
	consoleLog(suggestion, TFT_LIGHTGREY);
	
}





//invalid analog pin err display function

void invalidAnalogWriteErr(uint8_t pin)
{
	char msg[20];
	sprintf(msg, "Pin %d AnalogWrite is Invalid!", pin);
	consoleLog(msg, TFT_RED);
	
	char suggestion[80];
	uint8_t minimumPinNo = ex8bitCount*8;
	uint8_t maxPinNo = ex16bitCount*16+minimumPinNo;
	
	if(ex16bitCount<1) // then no attach any 16  bit IO extender
	{
		sprintf(suggestion, "No attach any 16bit IO Extender, analogWrite only available in 16bit extenders");
	}else
	{
		sprintf(suggestion, "You can use pin %d to %d only for analogwrite", minimumPinNo+1, maxPinNo);
	}
	consoleLog(suggestion, TFT_LIGHTGREY);
	
}



#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_DISPLAY)
MakerDisplay display(0);

#endif

MakerDisplay::MakerDisplay(int noUse){}


void MakerDisplay::print(char *text)
{
	consoleLog(text, TFT_GREEN);
	
}

void MakerDisplay::print(char *text, int colour)
{
	consoleLog(text, colour);
	
}


void MakerDisplay::print(int text)
{
	char cstr[20];
	itoa(text, cstr, 10);
	consoleLog(cstr, TFT_GREEN);
	
}

void MakerDisplay::print(int text, int colour)
{
	char cstr[20];
	itoa(text, cstr, 10);
	consoleLog(cstr, colour);
	
}


void MakerDisplay::println(char *text)
{
	consoleLog(text, TFT_GREEN);
	
}

void MakerDisplay::println(char *text, int colour)
{
	consoleLog(text, colour);
	
}


void MakerDisplay::println(int text)
{
	char cstr[20];
	itoa(text, cstr, 10);
	consoleLog(cstr, TFT_GREEN);
	
}


void MakerDisplay::println(int text, int colour)
{
	char cstr[20];
	itoa(text, cstr, 10);
	consoleLog(cstr, colour);
	
}


void MakerDisplay::clear()
{
	consoleClear();
	
}