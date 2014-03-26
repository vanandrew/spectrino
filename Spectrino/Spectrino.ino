/* 
  This code is for the Spectrino project,
  a world health application of the Arduino board to make a
  spectrophotometer.
  Written by Andrew Van, Jeffrey Smith, and Claire Kalkbrenner
*/

//includes the touch screen function, which outputs a character corresponding to a touchscreen button, also waits until a button is pushed
#include "TouchscreenFunctions.h"

// Global Variables
int* ts_coord[2] = {0};
double blank_conc = 0;
double standard = 0;
int sd_conc = 0;
char standard_value[5] = 0;
int char_count = 0;

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
  reset = false;
  while(!read_blank()) {;}
  while(!read_standard()) {;}
  while(out_measurement()) {;}   
}
}



boolean read_standard()
{
    
    if(touchscreen_input(/*   */)
    { 
       // Stores the frequency of the standard
       standard_freq = calc_frequency();
       ts_coord[2] = {0}; // Clear coordinates for next touchscreen input
       sd_conc = 0; // Reset Standard Concentration value to 0
       int curr_digit = 0;
       while(get_digit(curr_value)) // Watch for enter key press
       {
        curr_digit++;
       }

    }
    else
      return false;
}

double out_measurement(){
  //returns concentration of the sample
  return get_frequency() * standard/(sd_freq - blank_freq);
}

boolean enter()
{
  if(/*coordinates of enter*/)
    return true;
  else
    return false;


// This function returns the digit called
char get_digit(int curr_value)
{
  boolean digit_found = false;
  char digit = touchscreen_input();
      
  
  standard_value[curr_value] = digit;
  return true;
}

double calc_frequency()
{

double freq_output; // Stores output frequency  
boolean data[1024]; // Array to store data
// Indexes to track waveform
int index1 = -1;
int index2 = -1;
int index3 = -1;
double samp_period = 0; // Stores Sampling Period
double freq_reading_count = 0; // Stores nnumber of frequencies read
double period_sum = 0; // Stores the sum of the sampling periods
boolean temp_bool; // Tracks current value of data in array

for(int i=0; i<1024;i++)
	{
	delayMicroseconds(1);
	data[i] = bitRead(PIND,2);
	} 
  
	temp_bool = data[0];
	for(int i = 0; i<1024;i++)
	{
		// Compares current index with past stored index; Store value is opposite
		if(temp_bool != data[i])
		{
		  // Stores the first index if not already stored
		  if(index1 == -1){
			index1 = i;
			temp_bool = data[i];
		  }
		  // Stores the second index if not already stored
		  else if(index2 == -1){
			 index2 = i;
			 temp_bool = data[i];
		  }
                  // Stores the third index if not already stored
		  else if(index3 == -1){
			 index3 = i;
			 temp_bool = data[i];
		  }
		  
		}   
    
		//Calculate frequency based on index locations
		if(index1 != -1 && index2 != -1 && index3 != -1)
		{
			freq_reading_count++;
                        //Stores the current period in microseconds
			samp_period = (double)(index3-index1);
			/*Serial.print("This is index3: ");
			Serial.println(index3);
			Serial.print("This is index1: ");
			Serial.println(index1);*/
			//period sum is the sum in microseconds
			period_sum+=samp_period;
			index1 = -1;
			index2 = -1;
			index3 = -1;
		}
  
	}//end of for loop 
  
	// Wait 1 second
	delay(10);
        index1 = -1;
	index2 = -1;
	index3 = -1;
	
        // Calculate the average frequency of the signal
        freq_output = (double)(freq_reading_count/period_sum)*500;
        
        return freq_output;
}

//Pass by reference an array of two values
void get_coordinates(){
  
  pinMode( 15, INPUT ); // Analog pin 1 
  pinMode( 17, INPUT ); // Analog pin 3 
  pinMode( 14, OUTPUT ); // Analog pin 0 
  digitalWrite( 14, LOW ); // Use analog pin 0 as a GND connection 
  pinMode( 16, OUTPUT ); // Analog pin 2 
  digitalWrite( 16, HIGH ); // Use analog pin 2 as a +5V connection 
  delay(2); // Wait for voltage to settle 
  ts_coord[0] = analogRead( 1 );
  
  pinMode( 14, INPUT ); // Analog pin 0 
  pinMode( 16, INPUT ); // Analog pin 2 
  pinMode( 15, OUTPUT ); // Analog pin 1 
  digitalWrite( 15, LOW ); // Use analog pin 1 as a GND connection 
  pinMode( 17, OUTPUT ); // Analog pin 3 
  digitalWrite( 17, HIGH ); // Use analog pin 3 as a +5V connection 
  delay(2); // Wait for voltage to settle 
  ts_coord[1] = analogRead( 0 ); // Read the Y value
}

boolean reset()
{
        // Clear Variables
        blank = 0;
        standard = 0;
        reset = true;
        memset(standard_value,0,sizeof(standard_value));

        get_coordinates();
        if(/*touchscreen coordinates for reset*/)
          return true;
        else
          return false;
}

boolean read_blank()
{
    get_coordinates(); // Update most recent coordinates pushed
    if(/*touchscreen dimensions for blank */)
    { 
       // Stores the frequency of the blank
       blank_freq = calc_frequency();
       ts_coord[2] = {0}; // Clear coordinates for next touchscreen input
       return true;
    }
    else
      return false;
}
