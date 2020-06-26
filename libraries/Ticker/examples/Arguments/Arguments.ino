#include <Arduino.h>
#include <Ticker.h>

// attach a LED to GPIO 21
#define LED_PIN 21

Ticker tickerSetHigh;
Ticker tickerSetLow;

void setPin(int state) {
  CdigitalWrite(LED_PIN, state);
}

void setup() {
  CpinMode(LED_PIN, OUTPUT);
  CdigitalWrite(1, LOW);
  
  // every 25 ms, call setPin(0) 
  tickerSetLow.attach_ms(25, setPin, 0);
  
  // every 26 ms, call setPin(1)
  tickerSetHigh.attach_ms(26, setPin, 1);
}

void loop() {

}
