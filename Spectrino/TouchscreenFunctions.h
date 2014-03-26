extern int* ts_coord[2] = {0}; // Creates corrdinate array availiable for all

// Waits for touchscreen input and returns input
char touchscreen_input()
{
    while(1)
    // Update with most recent coordinates
    get_coordinates();
        // Blank
        if ()
        {
            return 'b';
        }
        
        // Standard
        else if ()
        {
            return 's';
        }
        
        // Clear
        else if ()
        {
            return 'c';
        }
        
        // Measure
        else if()
        {
            return 'm';
        }
        
        // Reset
        else if()
        {
            blank = 0;
            standard = 0;
            memset(standard_value,0,sizeof(standard_value));
            return 'r';
        }
        
        // Enter
        else if()
        {
            return 'e';
        }
        
        // 0
        else if()
        {
            return '0';
        }
        
        // 1
        else if()
        {
            return '1';
        }
        
        // 2
        else if()
        {
            return '2';
        }
        
        // 3
        else if()
        {
            return '3';
        }
        
        // 4
        else if()
        {
            return '4';
        }
        
        // 5
        else if()
        {
            return '5';
        }
        
        // 6
        else if()
        {
            return '6';
        }
        
        // 7
        else if()
        {
            return '7';
        }
        
        // 8
        else if()
        {
            return '8';
        }
        
        // 9
        else if()
        {
            return '9';
        }
        
        // Period
        else if()
        {
            return '.';
        }
    }
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
