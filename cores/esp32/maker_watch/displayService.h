#ifndef displayservice_h
#define displayservice_h

#include <inttypes.h>
#include "display/TFT_eSPI.h"



//#define IWIDTH  128
//#define IHEIGHT 128

//TFT_eSPI tft1 = TFT_eSPI();

void consoleLog(char *text, uint16_t fontColour);
void consoleClear();
void invalidPinConfigErr(uint8_t pin);
void invalidAnalogWriteErr(uint8_t pin);
void invalidSetInterruptErr(uint8_t pin);



//#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_SERIAL)
//extern MakerDisplay display;
//#endif
//extern MakerDisplay display;


class MakerDisplay
{


public:

    MakerDisplay(int noUse);
	
	void print(char *text);
	void print(char *text, int colour);
	void print(int text);
	void print(int text, int colour);
	
	
	void println(char *text);
	void println(char *text, int colour);
	void println(int text);
	void println(int text, int colour);
	
	void clear();

};



#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_DISPLAY)

extern MakerDisplay display;

#endif




#endif
