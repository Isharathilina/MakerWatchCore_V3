#include <makerDisplay.h>


unsigned long targetTime = 0;
byte red = 31;
byte green = 0;
byte blue = 0;
byte state = 0;
unsigned int colour1 = red << 11;

// clock function
static uint8_t conv2d(const char* p) 
{
  uint8_t v = 0;
  if ('0' <= *p && *p <= '9')
    v = *p - '0';
  return 10 * v + *++p - '0';
}

// get time
uint8_t hh=conv2d(__TIME__), mm=conv2d(__TIME__+3), ss=conv2d(__TIME__+6);  // Get H, M, S from compile time




void setup(void) {
  Serial.begin(9600);
  makerDisplay.init();
  makerDisplay.setRotation(0);
  makerDisplay.fillScreen(BLACK);

  targetTime = millis() + 1000;
}

void loop() {

    if (targetTime < millis()) {
    targetTime = millis() + 1000;

  
  // change time
   ss++;              // Advance second
    if (ss==60) {
      ss=0;
      mm++;            // Advance minute
      if(mm>59) {
        mm=0;
        hh++;          // Advance hour
        if (hh>23) {
          hh=0;
        }
      }
    }
  
   
     String hour = String(hh);
     String minute;
     if(mm<10)
     {
        minute = "0"+String(mm);
      }else{
        minute = String(mm);
        }
     
     String watchTime = hour+"."+minute;

   // makerDisplay.setTextColor(GREEN);
    makerDisplay.setTextColor(GREEN, BLACK); // Do not plot the background colour1
    // The new larger fonts do not use the .setCursor call, coords are embedded
    makerDisplay.drawCentreString("-RTX-", 65, 20, 2); // Draw text centre at position 80, 24 using font 6
    makerDisplay.drawCentreString(watchTime, 50, 45, 6); // Draw text centre at position 80, 24 using font 6
    makerDisplay.drawCentreString("Your Name ;-)", 62, 90, 2); // Draw text centre at position 80, 24 using font 6

    Serial.println(watchTime);

  
  }
}