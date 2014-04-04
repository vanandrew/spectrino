/* 
  This code is for the Spectrino project,
  a world health application of the Arduino board to make a
  spectrophotometer.
  Written by Andrew Van, Jeffrey Smith, and Claire Kalkbrenner
*/

// Includes the touch screen function, which outputs a character
// corresponding to a touchscreen button, also waits until a button is pushed
#include "TouchscreenFunctions.h"
#include "display.h" // Library containing functions for the 5110 Nokia Display

// Initialize Here
void setup()
{
  DDRD = DDRD | B00000000; // Set all  pins(0 to 7) to read mode
	
  // Setup serial connection with 9600 bps baud rate
  // Serial.begin(9600);
  // Serial.println("Begin Stream");
	
  // Initialize the Display
  LcdInitialise();
  LcdClear();
}

void loop()
{
  while(1)
  {
    // Wait for touch screen input
    touchscreen_input();
  }
}
