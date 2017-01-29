 #include <Servo.h>
 
  // global variables
  // position:  
int vPos = 0, hPos = 0;
  // pulse Width
int theTurn = 0, LPW = 0, RPW = 0;
  // joystick values
int JSv = 500, JSh = 500; //Neutral: 517 (v), 528 (h)

Servo front_right, front_left, back_right, back_left;

#define s_Speed 9600

//#define DEBUG

void setup ()
{
  Serial.begin(s_Speed);
  //pinMode (3, OUTPUT);  // Left  Sabertooth, channel A
  //pinMode (4, OUTPUT);  // Left  Sabertooth, channel B
  //pinMode (5, OUTPUT);  // Right Sabertooth, channel A
  //pinMode (6, OUTPUT);  // Right Sabertooth, channel B
  //pinMode (7, OUTPUT);
  
  front_right.attach(4); //Neutral at 94
  back_right.attach(3); //Neutral at 93
  front_left.attach(5); 
  back_left.attach(6);
  
}

void loop ()
{
  // read the serial input
  readSerial(); 
  
  motorControl_Servo();
  //motorControl_PWM();
}

  // readSerial function
  
void readSerial()
{
  #ifdef DEBUG
  Serial.println ("readSerial");
  #endif
  
  int i = 0;
  while (!Serial.available());
  
  while (Serial.available() )
  {
    #ifdef DEBUG
    Serial.println ("x");
    #endif
    
    do
    {
      i = Serial.read();
    } while (i != 'x');     // end do-while
    
    JSv = Serial.parseInt();
    JSh = Serial.parseInt();
  
  /*  
    if (JSv < 600)
{
  digitalWrite (7, HIGH);
}
else
{
  digitalWrite (7, LOW);
} 
*/
    
    if (Serial.read() == '\n')
    {
      return;
    } // end if newline
    
    // Serial.end();
    
  } // end while loop
  
  if (Serial.available () < 0)
  {
    Serial.end();
    Serial.begin(s_Speed);
  } // end if Serial.available is not available, reset it

} //end readSerial function

void motorControl_Servo()
{ 
    // use these to calculate our pulsewidth:
    // pulsewidth varies by 1000 units, analog read is 1024 units, 1000 / 1024 = ~0.977
    
  vPos = (JSv * 0.977);
  hPos = (JSh * 0.977);

    // determine the amount of turn:
    // take the horizontal deviation from center and divide by two,
    // then decrease one direction by half of our difference and 
    // increase the right side by half of our difference
    
  theTurn = ((hPos - 500) / 2);
  
    // calculate our left and right pulse widths using all of our available data
    // pulse width needs to be complementary for each motor as they are horizontally opposed
    
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
