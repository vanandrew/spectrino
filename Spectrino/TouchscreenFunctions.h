#ifndef TOUCHSCREENFUNCTIONS_H
#define TOUCHSCREENFUNCTIONS_H

#include "Arduino.h" // Include Arduino Library
#include "dataaquireprocess.h" // Contains data aquisition and processing functions
#include "display.h"


// Defines touchscreen analog ports
#define xLow  17
#define xHigh 15
#define yLow  16
#define yHigh 14

int ts_coords[2] = {0}; // Creates coordinate array availiable for all
double blank_freq = 0; // Stores frequency of blank

void get_coordinates()
{  
  pinMode(xLow,OUTPUT);
  pinMode(xHigh,OUTPUT);
  digitalWrite(xLow,LOW); // Use analog pin 2 as a GND connection
  digitalWrite(xHigh,HIGH); // Use analog pin 0 as a +3.3V connection
  digitalWrite(yLow,LOW); // Set y to LOW
  digitalWrite(yHigh,LOW); // Set y to LOW
  pinMode(yLow,INPUT);
  pinMode(yHigh,INPUT);
  delay(10); // Wait for voltage to settle
  ts_coords[0] = analogRead(yLow-14); // Read the X value

  pinMode(yLow,OUTPUT);
  pinMode(yHigh,OUTPUT);
  digitalWrite(yLow,LOW); // Use analog pin 2 as a GND connection
  digitalWrite(yHigh,HIGH); // Use analog pin 0 as a +3.3V connection
  digitalWrite(xLow,LOW); // Set y to LOW
  digitalWrite(xHigh,LOW); // Set y to LOW
  pinMode(xLow,INPUT);
  pinMode(xHigh,INPUT);
  delay(10); // Wait for voltage to settle
  ts_coords[1] = analogRead(xLow-14); // Read the X value
}

// Waits for touchscreen input and returns input
char touchscreen_input()
{
  while(1)
  {
    // Update with most recent coordinates
    get_coordinates();
  
    // Blank
    if (ts_coords[0] > 100 && ts_coords[0] < 500)
    {
        blank_freq = calc_frequency();
        return 'b';
    }
    
    // Reset
    else if(ts_coords[0] > 500 && ts_coords[0] < 900)
    {
        blank_freq = 0;
        return 'r';
    }
    
    // Display measurement data
    /*if (blank_freq == 0)
      Serial.println("Reference Needed");
    else{*/
      char temp_arr[4];
      double absorb = absorption(blank_freq);
      
      double thingy = 1.555;
      int whole = thingy;
      int decimal = (thingy-whole)*1000;
      //sprintf(temp_arr, "%1.3f",thingy );
      //String new_string(temp_arr);
      dtostrf(thingy, 4, 3, temp_arr);

      gotoXY(4,1);
      //temp_str.toCharArray(temp_arr, temp_str.length());
      //String whole_s = whole;
      LcdString(temp_arr); //to go to display
    //}
  }
}

#endif
