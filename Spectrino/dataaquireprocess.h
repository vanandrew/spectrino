#include "Arduino.h" // Include Arduino Library

// Aquires and calculates the frequency from the sensor
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
        
        // Return the frequency of the acquired signal
        return freq_output;
}

double absorption(double blank_freq)
{
  return (-log(calc_frequency()/blank_freq)); 
}
