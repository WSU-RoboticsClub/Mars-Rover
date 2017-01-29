/*
 *  WSU Mars Rover - Motor_Control
 *  
 *  Takes input via the serial stream in order to know what commands to give to the motor
 *  controllers. Implements the arduino servo library in order to control the motors speed
 *  and direction
 *  
 *  Written by Marcus Blaisdell and Jensen Reitz of WSU Robotics Club
 */

#include <Servo.h>

// Setup *******************************************************************************

// Global Variables ---------------------------------------------------------------------
int vPos = 0, hPos = 0;
int theTurn = 0, LPW = 0, RPW = 0;   //Pulse Width
int JSv = 500, JSh = 500; //Neutral: 517 (v), 528 (h)  //Joystick values

Servo front_right, front_left, back_right, back_left;

#define s_Speed 9600

//#define DEBUG

// Run Program **************************************************************************

void setup()
{
  Serial.begin(s_Speed);
  
  front_right.attach(4); //Neutral at 94
  back_right.attach(3); //Neutral at 93
  front_left.attach(5); 
  back_left.attach(6);
}

void loop()
{
  //Read the serial input
  readSerial(); 
  
  motorControl_Servo();
}

// Custom Functions **********************************************************************

void readSerial()
{
  #ifdef DEBUG
  Serial.println ("Reading Serial");
  #endif
  
  int i = 0;
  
  while(!Serial.available())
  {
  }
  
  while(Serial.available())
  {
    #ifdef DEBUG
    Serial.println ("x");
    #endif
    
    do
    {
      i = Serial.read();
    } while (i != 'x');
    
    JSv = Serial.parseInt();
    JSh = Serial.parseInt();
    
    if(Serial.read() == '\n')
      return;
  }
  
  if(Serial.available () < 0)
  {
    Serial.end();
    Serial.begin(s_Speed);
  }
}

void motorControl_Servo()
{ 
  //Use these to calculate our pulsewidth
  //Pulsewidth varies by 1000 units, analog read is 1024 units, 1000 / 1024 = ~0.977 
  vPos = (JSv * 0.977);
  hPos = (JSh * 0.977);

  //Determine the amount of turn
  //Take the horizontal deviation from center and divide by two,
  //  then decrease one direction by half of our difference and 
  //  increase the right side by half of our difference  
  theTurn = ((hPos - 500) / 2);
  
  //Calculate our left and right pulse widths using all of our available data
  //  pulse width needs to be complementary for each motor as they are horizontally opposed  
  LPW = 1000 + vPos + theTurn;
  RPW = 2000 - vPos + theTurn;
  
  front_right.writeMicroseconds(RPW);
  front_left.writeMicroseconds(LPW);
  back_right.writeMicroseconds(RPW);
  back_left.writeMicroseconds(LPW);
  
  #ifdef DEBUG
    Serial.print(RPW);
    Serial.print(" : ");
    Serial.println(LPW);
  #endif
}
