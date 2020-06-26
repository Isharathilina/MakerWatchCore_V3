#include <Arduino.h>
#include <Wire.h>
#include "G_dualMotor.h"


struct G_MOTOR_STATUS motor_status;


/*

*/
G_MOTOR::G_MOTOR(){
  i2c_address = DEFAULT_G_MOTOR_ADDRESS;
}

/*
@brief
*/
G_MOTOR::G_MOTOR(int address){
  i2c_address = address;
}

/*
@brife

@param


*/
int G_MOTOR::init(int address){
  i2c_address = address;
  //Wire.begin();
  return 0;
}

/*
@brife

@param


*/
int G_MOTOR::setDirection(MTDRV_motor_channel channel, G_MOTOR_DIRECTION_t direction){
  int retValue = 0;

  //send data packet
  Wire.beginTransmission(i2c_address);
  Wire.write(channel);
  Wire.write(DRIVER_CMD_SET_DIRECTION);
  Wire.write(direction);
  retValue = Wire.endTransmission();   
  delay(5); 
  return retValue;
}


/*
@brife

@param


*/
int G_MOTOR::breake(MTDRV_motor_channel channel){
  int retValue = 0;

  //send data packet
  Wire.beginTransmission(i2c_address);
  Wire.write(channel);
  Wire.write(DRIVER_CMD_BREAK_MOTOR);
  retValue = Wire.endTransmission();  
  delay(5); 
  return retValue;
}

/*
@brife

@param


*/
int G_MOTOR::releas(MTDRV_motor_channel channel){
  int retValue = 0;

  //send data packet
  Wire.beginTransmission(i2c_address);
  Wire.write(channel);
  Wire.write(DRIVER_CMD_SET_RELEAS_MOTOR);
  retValue = Wire.endTransmission(); 
  delay(5); 
  return retValue;  
}


/*
@brife

@param


*/
int G_MOTOR::setSpeed(MTDRV_motor_channel channel, int speed){
  int retValue = 0;

  //send data packet
  Wire.beginTransmission(i2c_address);
  Wire.write(channel);
  Wire.write(DRIVER_CMD_SET_SPEED);
  Wire.write(speed);
  retValue = Wire.endTransmission();   
  delay(5);  
  return retValue;
}

/*
@brife

@param


*/
int G_MOTOR::enableChannel(MTDRV_motor_channel channel){
  int retValue = 0;

  //send data packet
  Wire.beginTransmission(i2c_address);
  Wire.write(channel);
  Wire.write(DRIVER_CMD_ENABLE_MOTOR);
  retValue = Wire.endTransmission();
  delay(5);      
  return retValue;
}

/*
@brife

@param


*/
int G_MOTOR::disableChannel(MTDRV_motor_channel channel){
  int retValue = 0;

  //send data packet
  Wire.beginTransmission(i2c_address);
  Wire.write(channel);
  Wire.write(DRIVER_CMD_DISABLE_MOTOR);
  retValue = Wire.endTransmission(); 
  delay(5);  
  return retValue;
}

/*
@brife

@param


*/
struct G_MOTOR_STATUS* G_MOTOR::getStatus(MTDRV_motor_channel channel){
  uint8_t data[6] = {0};
  uint8_t index = 0;

  //send data packet
  Wire.beginTransmission(i2c_address);
  Wire.write(channel);
  Wire.write(DRIVER_CMD_GET_STATUS);
  Wire.endTransmission(); 
  delay(20);
    
  Wire.requestFrom(i2c_address, 6);     // request 6 bytes from the driver
  while (Wire.available()) {            // slave may send less than requested
    data[index++] = Wire.read();        // receive a byte as character
  }

//  for(int i = 0 ; i < sizeof(data); i++){
//    Serial.print(data[i]);
//    Serial.print(", ");
//  }
//  Serial.println("*****************\n");

  //motor_status.isEnable = data[3];
  //motor_status.status = data[4];
  //motor_status.speed = data[5];
  
  return &motor_status; 
}
