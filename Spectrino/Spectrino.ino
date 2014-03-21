/* 
  This code is for the Spectrino project,
  a world health application of the Arduino board to make a
  spectrophotometer.
  Written by Andrew Van, Jeffrey Smith, and Claire Kalkbrenner
*/

// Variables
boolean temp_bool;
boolean data[1024];
int index1 = -1;
int index2 = -1;
int index3 = -1;
float frequency;
double samp_period;
double freq_reading_count = 0;
double period_sum = 0;
double freq;
int* ts_coord[2] = {0};




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
  
  freq = calc_frequency();
  //Temporary until display is implemented
  Serial.print("This is freq_avg: ");
  Serial.println(freq);

  // Reset variables for next loop
  freq_reading_count = 0; 
  period_sum = 0;
}
}


double calc_frequency()
{
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
        
	return (double)(freq_reading_count/period_sum)*500;
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
