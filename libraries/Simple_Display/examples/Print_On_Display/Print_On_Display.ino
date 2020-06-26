/*
Maker watch colour list

 BLACK       NAVY        
 DARKGREEN   DARKCYAN    
 MAROON      PURPLE     
 OLIVE       LIGHTGREY   
 DARKGREY    BLUE       
 GREEN       CYAN        
 RED         MAGENTA     
 YELLOW      WHITE       
 ORANGE      GREENYELLOW 
 PINK        

*/

void setup() {
  // put your setup code here, to run once:
display.print("helo Maker watch");
display.println("This is default font");
delay(2000);
display.println("Colour font1", ORANGE);
display.println("Colour font2", YELLOW);
delay(2000);
display.clear();
display.print("Cleared..1");
delay(1000);
}

int num =0;
void loop() {
  display.print("This is display test");
  display.print("Hey, this is display clour test", MAGENTA);
  display.print(num);
  num++;
  delay(1000);
 

}