#ifndef pinhandle_h
#define pinhandle_h

#include <inttypes.h>

//#include "maker_watch/globle.h"
//#include "maker_watch/displayService.h"


// update pin err flag and pin for access in main 
//void invalidPinConfigErrHandle(uint16_t pin);
 // load all 8 bit and 16 bit instence EX8_1, EX16_1





void pinMap(uint8_t pin);

void pinMode(uint8_t pin, uint8_t mode);

void digitalWrite(uint8_t pin, uint8_t val);

bool digitalRead(uint8_t pin);

//uint16_t analogRead(uint8_t pin);

void analogWrite(uint8_t pin, uint8_t val);

void setInterrupt(uint8_t pin, void (*)(void), int mode);

void runPinInterrupt(uint8_t pin, int8_t edge);

void interruptPinDrive();


// void testfun2();
// void setInterrupt1(uint8_t pin, void (*)(void), int mode);
// void attachInterruptArg1(uint8_t pin, void (*)(void*), void * arg, int mode);
// //void setInterrupt(int pin, void (*name)(void));
// // void my_int_func();



#endif
