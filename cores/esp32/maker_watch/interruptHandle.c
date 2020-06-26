

#include "interruptHandle.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "rom/ets_sys.h"
#include "esp_attr.h"
#include "esp_intr.h"
#include "rom/gpio.h"
#include "soc/gpio_reg.h"
#include "soc/io_mux_reg.h"
#include "soc/gpio_struct.h"
#include "soc/rtc_io_reg.h"

//for interrupt
//#include "maker_watch/pinhandle.h"


typedef void (*voidFuncPtr)(void);
typedef void (*voidFuncPtrArg)(void*);

typedef struct {
    voidFuncPtr fn;
    void* arg;
    bool functional;
} InterruptHandle_t;

static InterruptHandle_t __pinInterruptHandlers[GPIO_PIN_COUNT] = {0,};

// for setInterrupt function
typedef void (*voidFuncPtr1)(void);
typedef void (*voidFuncPtrArg1)(void*);

typedef struct {
    voidFuncPtr1 fn;
    void* arg;
    bool functional;
} InterruptHandle_t1;

static InterruptHandle_t1 __pinInterruptHandlers1[97] = {0,}; // consider all 96 pin table



#include "driver/rtc_io.h"




static intr_handle_t gpio_intr_handle = NULL;

static void IRAM_ATTR __onPinInterrupt1()
{
    uint32_t gpio_intr_status_l=0;
    uint32_t gpio_intr_status_h=0;

    gpio_intr_status_l = GPIO.status;
    gpio_intr_status_h = GPIO.status1.val;
    GPIO.status_w1tc = gpio_intr_status_l;//Clear intr for gpio0-gpio31
    GPIO.status1_w1tc.val = gpio_intr_status_h;//Clear intr for gpio32-39

    uint8_t pin=0;
    if(gpio_intr_status_l) {
        do {
            if(gpio_intr_status_l & ((uint32_t)1 << pin)) {
                if(__pinInterruptHandlers[pin].fn) {
                    if(__pinInterruptHandlers[pin].arg){
                        ((voidFuncPtrArg)__pinInterruptHandlers[pin].fn)(__pinInterruptHandlers[pin].arg);
                    } else {
                        __pinInterruptHandlers[pin].fn();
                    }
                }
            }
        } while(++pin<32);
    }
    if(gpio_intr_status_h) {
        pin=32;
        do {
            if(gpio_intr_status_h & ((uint32_t)1 << (pin - 32))) {
                if(__pinInterruptHandlers[pin].fn) {
                    if(__pinInterruptHandlers[pin].arg){
                        ((voidFuncPtrArg)__pinInterruptHandlers[pin].fn)(__pinInterruptHandlers[pin].arg);
                    } else {
                        __pinInterruptHandlers[pin].fn();
                    }
                }
            }
        } while(++pin<GPIO_PIN_COUNT);
    }
}



extern void cleanupFunctional(void* arg);


// for setInterrupt function

extern void __attachInterruptFunctionalArg1(uint8_t pin, voidFuncPtrArg1 userFunc, void * arg, int intr_type, bool functional)
{
    static bool interrupt_initialized = false;

    if(!interrupt_initialized) 
	{
        interrupt_initialized = true;
        esp_intr_alloc(ETS_GPIO_INTR_SOURCE, (int)ESP_INTR_FLAG_IRAM, __onPinInterrupt1, NULL, &gpio_intr_handle);
    }

    // if new attach without detach remove old info
    if (__pinInterruptHandlers1[pin].functional && __pinInterruptHandlers1[pin].arg)
    {
    	cleanupFunctional(__pinInterruptHandlers1[pin].arg);
    }
    __pinInterruptHandlers1[pin].fn = (voidFuncPtr1)userFunc;
    __pinInterruptHandlers1[pin].arg = arg;
    __pinInterruptHandlers1[pin].functional = functional;

    // esp_intr_disable(gpio_intr_handle);
    // if(esp_intr_get_cpu(gpio_intr_handle)) 
	// { //APP_CPU
        // GPIO.pin[pin].int_ena = 1;
    // } else { //PRO_CPU
        // GPIO.pin[pin].int_ena = 4;
    // }
    // GPIO.pin[pin].int_type = intr_type;
    // esp_intr_enable(gpio_intr_handle);
}




extern void __setInterrupt(uint8_t pin, voidFuncPtr1 userFunc, int intr_type) 
{
    __attachInterruptFunctionalArg1(pin, (voidFuncPtrArg1)userFunc, NULL, intr_type, false);
	
	
}

void runPinInterruptInC(uint8_t pin)
{
	if(pin!=0)
	{
			__pinInterruptHandlers1[pin].fn();
	}
	
	
}




extern void setInterruptInC(uint8_t pin, voidFuncPtr1 handler, int mode) __attribute__ ((weak, alias("__setInterrupt")));

