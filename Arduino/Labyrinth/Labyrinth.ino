// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 

#include <math.h>

#include "Wire.h"
#include "WiiChuck.h"
#include "nunchuck_funcs.h"

Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 
 
WiiChuck chuck = WiiChuck(); 

void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  nunchuck_setpowerpins();
  
  Serial.begin(115200);
  
  chuck.begin();
  chuck.update();
  
} 
 
 
void loop() 
{ 
  chuck.update(); 
  
  int valtot =0;
  int val=0;
  int i;
  int n = 25;
  int readings[n];
  
  //gather readings over period of time
  for(i=0; i<n; i++)
  {
    chuck.update(); 
    readings[i] = chuck.readJoyX();
      //delay(20); 
  }
  
  //create average
  for(i=0; i<n; i++)
  {
    valtot = valtot+readings[i];
  }
  val = valtot/i;
  
  // map joystick value to degrees  
  pos = map(val, -130, 130, 70, 110);
  if( ((val > 0) && (val <= 2)) || ((val >= -2) && (val < 0)) )
  {
    pos = 90;
    Serial.print("Correction");
  }
  else
    Serial.print("          ");
  
  myservo.write(pos);              // tell servo to go to position in variable 'pos' 
  //delay(15);                       // waits 15ms for the servo to reach the position 
  
  Serial.print("   Joy: ");
  Serial.print(val);
  Serial.print(" \t\t Pos: ");
  Serial.println(pos);
 
} 
