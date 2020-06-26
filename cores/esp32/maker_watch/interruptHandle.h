
#ifndef interruptHandle_h
#define interruptHandle_h

#ifdef __cplusplus
extern "C" {
#endif

#include "esp32-hal.h"



void setInterruptInC(uint8_t pin, void (*)(void), int mode);
void runPinInterruptInC(uint8_t pin);

void __setInterrupt(uint8_t pin, void (*)(void), int mode);

#ifdef __cplusplus
}
#endif

#endif 
