/* 
  This code is for the Spectrino project, a world health application of the arduino board to make a spectrophotometer
  Written by Andrew Van, Jeffrey Smith, and Claire Kalkbrenner
*/

#include <FHT.h> // Include Fast Hartley Transform Library

uint16_t freq;

void setup()
{
  DDRD = DDRD | B00000000; //Set all  pins(0 to 7) to read mode
  Serial.begin(9600); // Setup serial connection with 9600 bps baud rate
  Serial.println("Begin Stream");
}

void loop()
{
  while(1) // Create indefinite while loop for stable loop
  {
    delay(1000);
    for(int i = 0; i < FHT_N; i++) // Read in signal; 256 sample window
    {
      fht_input[i] = ((int) bitRead(PIND,2))*255; // Stores an int value in the fht array    
      delayMicroseconds(10); // Sample every 10 microseconds
    }
    
    for(int m= 0; m < (FHT_N); m++)
    {
      Serial.print(fht_input[m]);
      Serial.print(",");
    }
    Serial.println();
    
    fht_reorder(); // Reorder data for fht
    fht_run(); // Run the fht on data
    fht_mag_lin(); // Find magnitude of data
   
    for(int n = 0; n < (FHT_N/2); n++)
    {
      Serial.print((float) fht_lin_out[n]);
      Serial.print(",");
    }
    Serial.println();
    
    freq = max_of_array(fht_lin_out)*100000/FHT_N;
    
    Serial.println(freq);
  }
}

// Finds max of windowed array
uint16_t max_of_array(uint16_t a[])
{
  uint16_t temp_max = a[1];
  uint16_t k;
  
  for(uint16_t i = 1; i<(FHT_N/2);i++)
  {
    if(temp_max < a[i])
      uint16_t k = i;
  }
  
  if(temp_max==0)
    k = 0;
  
  Serial.println(k);
    
  return k;
}
