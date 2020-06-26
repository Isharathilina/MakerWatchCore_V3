
#include <Wire.h>
#include "G_dualMotor.h"

G_MOTOR motorDriver;

void setup() {

  
  motorDriver.init(0x03);
  
  //Serial.println("enabling motor channels");
 // printCannel_Status(MTDRV_CHANNEL_02);
  delay(100);
  motorDriver.enableChannel(MTDRV_CHANNEL_02);
  //motorDriver.enableChannel(MTDRV_CHANNEL_01);
  //printCannel_Status(MTDRV_CHANNEL_02);
  //printCannel_Status(MTDRV_CHANNEL_01);
  delay(100);
   
}

byte x = 0;

void loop() {
  
  motorDriver.setDirection(MTDRV_CHANNEL_02, GMOTOR_FOWARD);
  for(int i  = 0; i < 256; i++)
  {
    motorDriver.setSpeed(MTDRV_CHANNEL_02,i);
    delay(10);
  }
  printCannel_Status(MTDRV_CHANNEL_02);
  
  for(int i  = 256; i > 0; i--){
    motorDriver.setSpeed(MTDRV_CHANNEL_02,i-1);
    delay(10);
  }

  motorDriver.setDirection(MTDRV_CHANNEL_02, GMOTOR_BACKWARD);
  for(int i  = 0; i < 256; i++){
    motorDriver.setSpeed(MTDRV_CHANNEL_02,i);
    delay(10);
  }
  //printCannel_Status(MTDRV_CHANNEL_02);
  for(int i  = 256; i > 0; i--){
    motorDriver.setSpeed(MTDRV_CHANNEL_02,i-1);
    delay(10);
  }
}



void printCannel_Status(MTDRV_motor_channel channel){
  struct G_MOTOR_STATUS *stat_ptr;
  
  stat_ptr =  motorDriver.getStatus(channel);
  Serial.print("channel ");
  if(channel == MTDRV_CHANNEL_01){
    Serial.print(1);
  }else{
    Serial.print(2);
  }
  Serial.print(" is ");
 
  if(stat_ptr->isEnable){
    Serial.print("ENABLED ");
  }else{
    Serial.print("DISABLED ");
  }

  Serial.print("and ");      
  switch(stat_ptr->status){
    case MTDRV_STATUS_FOWARD:
      Serial.print("moving FOWARD in ");
      Serial.println(stat_ptr->speed);
      break;
    case MTDRV_STATUS_BACKWARD:
      Serial.print("moving BACKWARD in ");
      Serial.println(stat_ptr->speed);
      break;
    case MTDRV_STATUS_BREAK:
      Serial.println("BRAKED");
      break;  
    case MTDRV_STATUS_RELEASE:
      Serial.println("RELEASED");
      break;
    default:
      Serial.println("ERROR");
      break;
  }
 }
