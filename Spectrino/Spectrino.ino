/* 
  This code is for the Spectrino project,
  a world health application of the Arduino board to make a
  spectrophotometer.
  Written by Andrew Van, Jeffrey Smith, and Claire Kalkbrenner
*/

//includes the touch screen function, which outputs a character corresponding to a touchscreen button, also waits until a button is pushed
#include "TouchscreenFunctions.h"

// Global Variables
boolean reset_flag = false; // flag for resetting device measurement process

// Initialize Here
void setup()
{
	DDRD = DDRD | B00000000; //Set all  pins(0 to 7) to read mode
	Serial.begin(9600); // Setup serial connection with 9600 bps baud rate
	Serial.println("Begin Stream");
}

void loop()
{
  while(1)
  {
    // Wait for touch screen input
    touchscreen_input();
  }
}
