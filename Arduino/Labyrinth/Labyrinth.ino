// Labyrinth Mini Golf
// Arduino Controller by Matt Gray
// http://www.mattg.co.uk/projects/golf


#include <Servo.h> 

#include <math.h>

#include "Wire.h"
#include "WiiChuck.h"
#include "nunchuck_funcs.h"

Servo Xservo, Yservo;  // objects to control the two servos

WiiChuck chuck = WiiChuck(); 

void setup() 
{ 
  Xservo.attach(9);  // stick one servo on pin 9
  Yservo.attach(10); // and another on pin 10
  nunchuck_setpowerpins();	// lets the Wiichuck adapter work on the analog pins
  
  Serial.begin(115200);		// start serial for debug info
  
  chuck.begin();
  chuck.update();
  
} 
 
 
void loop() 
{ 
  chuck.update(); 
  int Xpos=0;
  int Ypos=0; 
  int Xvaltot =0;
  int Yvaltot =0;
  int Xval=0;
  int Yval =0;
  int i;
  int n = 25;
  int Xreadings[n];
  int Yreadings[n];
  
  //gather n readings
  for(i=0; i<n; i++)
  {
    chuck.update(); 
    Xreadings[i] = chuck.readJoyX();
    Yreadings[i] = chuck.readJoyY();
      //delay(20); 
  }
  
  //create average
  for(i=0; i<n; i++)
  {
    Xvaltot = Xvaltot+Xreadings[i];
    Yvaltot = Yvaltot+Yreadings[i];
  }
  Xval = Xvaltot/i;
  Yval = Yvaltot/i;
  
  // map joystick value to degrees  
  Xpos = map(Xval, -130, 130, 70, 110);
  //correct for noise around 0 to help keep flat
  if( ((Xval > 0) && (Xval <= 2)) || ((Xval >= -2) && (Xval < 0)) )
  {
    Xpos = 90;
    Serial.print("X Correction");
  }
  else
    Serial.print("          ");
    
  // map joystick value to degrees  
  Ypos = map(Yval, -130, 130, 70, 110);
  // correct for noise around 0 to help keep flat
  if( ((Yval > 0) && (Yval <= 2)) || ((Yval >= -2) && (Yval < 0)) )
  {
    Ypos = 90;
    Serial.print("Y Correction");
  }
  else
    Serial.print("          ");
  
  Xservo.write(Xpos);              // tell servo to go to position in variable 'pos' 
  Yservo.write(Ypos);
  //delay(15);                       // waits for the servo to reach the position 
  
  //print debug shizz.
  Serial.print("   XJoy: ");
  Serial.print(Xval);
  Serial.print(" \t\t XPos: ");
  Serial.println(Xpos);
  
  Serial.print(" \t\tYJoy: ");
  Serial.print(Yval);
  Serial.print(" \t\t YPos: ");
  Serial.println(Ypos);
 
} 
