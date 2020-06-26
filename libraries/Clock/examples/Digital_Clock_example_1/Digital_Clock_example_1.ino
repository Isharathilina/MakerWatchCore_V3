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

    // colour1 changing state machine
    for (int i = 0; i < 160; i++) {
      makerDisplay.drawFastVLine(i, 0, makerDisplay.height(), colour1);
      switch (state) {
        case 0:
          green += 2;
          if (green == 64) {
            green = 63;
            state = 1;
          }
          break;
        case 1:
          red--;
          if (red == 255) {
            red = 0;
            state = 2;
          }
          break;
        case 2:
          blue ++;
          if (blue == 32) {
            blue = 31;
            state = 3;
          }
          break;
        case 3:
          green -= 2;
          if (green == 255) {
            green = 0;
            state = 4;
          }
          break;
        case 4:
          red ++;
          if (red == 32) {
            red = 31;
            state = 5;
          }
          break;
        case 5:
          blue --;
          if (blue == 255) {
            blue = 0;
            state = 0;
          }
          break;
      }
      colour1 = red << 11 | green << 5 | blue;
    }
  
  
  
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

    // The standard ADAFruit font still works as before
    makerDisplay.setTextColor(BLACK);
    //tft.setCursor (12, 5);
  
    // The new larger fonts do not use the .setCursor call, coords are embedded
    makerDisplay.setTextColor(BLACK, BLACK); // Do not plot the background colour1
    makerDisplay.drawCentreString("-RTX-", 65, 20, 2); // Draw text centre at position 80, 24 using font 6
    makerDisplay.drawCentreString(watchTime, 50, 45, 6); // Draw text centre at position 80, 24 using font 6
    makerDisplay.drawCentreString("Your Name ;-)", 62, 90, 2); // Draw text centre at position 80, 24 using font 6

    Serial.println(watchTime);

  
  }
}