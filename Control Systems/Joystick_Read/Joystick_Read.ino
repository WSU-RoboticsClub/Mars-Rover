  // global variables
  
const int JSy_neutral = 517, JSx_neutral = 528;

  // joystick values

int JSy = 0, JSx = 0, JSy_old = 0, JSx_old = 0;

void setup ()
{
  Serial.begin(9600);
}

void loop ()
{

    // read the joystick positions:

  JSy = filterSignal(analogRead(0), 0);

  JSx = filterSignal(analogRead(1), 1);

    // print the joystick values to the serial stream

  if(checkForUpdate())
  {
    //Print the updated commands
    Serial.print(JSy);
    Serial.print(",");
    Serial.print(JSx);
    Serial.print(",");
    Serial.print("x");
    Serial.print("\n");
    
    JSy_old = JSy;
    JSx_old = JSx;
  }
  else
  {
    //Print the old commands
    Serial.print(JSy_old);
    Serial.print(",");
    Serial.print(JSx_old);
    Serial.print(",");
    Serial.print("x");
    Serial.print("\n");
  }
  
}

int filterSignal(int JS_value, int JS_type)
{
  switch(JS_type)
  {
    case 0: //JSy
      
      return ((abs(JS_value-JSy_neutral)>10) ? (JS_value) : (JSy_neutral));
      break;
    case 1: //JSh
    
      return ((abs(JS_value-JSx_neutral)>10) ? (JS_value) : (JSx_neutral));
      break;
  }
}

bool checkForUpdate()
{
  if(abs(JSy-JSy_old)>5 || abs(JSx-JSx_old)>5)
    return true;
  else
    return false;
}
