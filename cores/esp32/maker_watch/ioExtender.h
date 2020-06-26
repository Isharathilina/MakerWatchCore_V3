
#ifndef ioextender_h
#define ioextender_h

#include <inttypes.h>

// 16 bit io expander
class EX16
{
	
    
    uint8_t i2cAddress;
	
    uint8_t pinModeP0 = 0xff; // all as input (1= input)
    uint8_t pinModeP1 = 0xff; // all as input (1= input)
	
    uint8_t pinDataP0 = 0x00; // all as 0 default
    uint8_t pinDataP1 = 0x00; // all as 0 default
	
	uint8_t gpioLedModeData0 = 0xff; // all as 1 default for gpio mode
    uint8_t gpioLedModeData1 = 0xff; // all as 1 default for gpio mode

	uint8_t pushPullData0 = 0xff; // all as 1 default for port0 push pull mode
	
	uint8_t interruptPinModeP0 = 0xff; // all as 1 default, dissable, for interrupt
    uint8_t interruptPinModeP1 = 0xff; // all as 1 default, dissable for interrupt
	
	uint8_t interruptPinDataP0 = 0x00; // all as 0 default, 
    uint8_t interruptPinDataP1 = 0x00; // all as 0 default,
	
	int interruptEdge=0;
	
	

private:
    int modifyBit(int currentByte, int position, int bit);	
	int readBit(uint8_t data, uint8_t pin);
	
public:
    EX16(bool AD1, bool AD0);
	void pinMode(uint8_t pin, uint8_t mode);
	void digitalWrite(uint8_t pin, uint8_t mode);
	uint8_t digitalRead(uint8_t pin);
	void analogWrite(uint8_t pin, uint8_t value);
	
	void interruptConfig(uint8_t pin, uint8_t value);
	uint8_t getInterruptedPin();
	int getInterruptEdge();
	
	
};






// 8bit io expander

class EX8
{

    uint8_t i2cAddress;
    uint8_t pinModeP0 = 0xff; // all as input (1= input)
    uint8_t pinDataP0 = 0x00; // all as 0 default
	
private:
    int modifyBit(int currentByte, int position, int bit);	
	
public:
	//uint8_t i2cAddress;
    EX8(bool AD1, bool AD0);
	
	void pinMode(uint8_t pin, uint8_t mode);
	void digitalWrite(uint8_t pin, uint8_t mode);
	uint8_t digitalRead(uint8_t pin);
	
};






#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_IOEXPANDER)

extern EX16 EX16_1;
extern EX16 EX16_2;
extern EX16 EX16_3;
extern EX16 EX16_4;

extern EX8 EX8_1;
extern EX8 EX8_2;
extern EX8 EX8_3;
extern EX8 EX8_4;



#endif


#endif
