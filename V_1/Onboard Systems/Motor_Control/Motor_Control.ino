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
int JSv = 500, JSh = 500; //Neutral: 517 (v), 528 (h)  //Joystick values

Servo front_right, front_left, middle_right, middle_left, back_right, back_left;

#define s_Speed 9600

//#define DEBUG

// Run Program **************************************************************************

void setup()
{
  Serial.begin(s_Speed);

  //Attach servo motors
  front_right.attach(2);  //Neutral at 94
  front_left.attach(3);
  middle_right.attach(4);
  middle_left.attach(5);
  back_right.attach(6);   //Neutral at 93
  back_left.attach(7);
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
    Serial.println ("In readSerial()");
    #endif
    
    /*do
    {
      i = Serial.read();
    } while (i != 'x');
    */
    
    JSv = Serial.parseInt();
    JSh = Serial.parseInt();
    
    if(Serial.read() == '\n')
      return;
  }
  
  if(Serial.available() < 0)
  {
    Serial.end();
    Serial.begin(s_Speed);
  }
}

void motorControl_Servo()
{ 
  //Use these to calculate our pulsewidth
  //Pulsewidth varies by 1000 units, analog read is 1024 units, 1000 / 1024 = ~0.977 
  double vPos = (JSv * 0.977);
  double hPos = (JSh * 0.977);

  //Determine the amount of turn
  //Take the horizontal deviation from center and divide by two,
  //  then decrease one direction by half of our difference and 
  //  increase the right side by half of our difference  
  double theTurn = ((hPos - 500) / 2);
  
  // Calculate our left and right pulse widths using all of our available data
  // pulse width needs to be complementary for each motor as they are horizontally opposed 
  // Since we are using servo.write, we need to translate the PWM to degrees
  // PWM values are from 1000-2000
  // servo angles are from 0-180
  // so, take the Pulse Width value (LPW or RPW), subtract 1000, 
  // divide that number by a factor of 5.5 (1000/180)
  // and this should be the correct angle to correspond to our desired motor speed and direction
  
  double LPW = ((1000 + vPos + theTurn)-1000)/5.5;
  double RPW = ((2000 - vPos + theTurn)-1000)/5.5;

  //Assign the pulsewidth values to the motors
  front_right.write(RPW);
  front_left.write(LPW);
  middle_right.write(RPW);
  middle_left.write(LPW);
  back_right.write(RPW);
  back_left.write(LPW);
  
  /*
  front_right.writeMicroseconds(RPW);
  front_left.writeMicroseconds(LPW);
  middle_right.writeMicroseconds(RPW);
  middle_left.writeMicroseconds(LPW);
  back_right.writeMicroseconds(RPW);
  back_left.writeMicroseconds(LPW);
  */
  
  #ifdef DEBUG
    Serial.print(RPW);
    Serial.print(" : ");
    Serial.println(LPW);
  #endif
}
