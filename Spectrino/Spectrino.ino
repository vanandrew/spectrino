int analogPin = 2; // sensor output connected to analog pin 2
double sensorValue = 0; // variable to store the ADC value of the photodiode
int output = 0; // output
int digit1 = 0; // first digit to display
int digit2 = 0; // second digit to display
int digit3 = 0; // third digit to display
int digit4 = 0; // fourth digit to display
int clock = 111; // clock for shift registers
int datapin1 = 111; // datapin for shift register 1
int datapin2 = 111; // datapin for shift register 2
int datapin3 = 111; // datapin for shift register 3
int datapin4 = 111; // datapin for shift register 4

void setup()
{
  Serial.begin(9600); // Setup Data link to Computer; 9600 bps
  
  // Output to each shift register + clock
  pinMode(datapin1, OUTPUT);
  pinMode(datapin2, OUTPUT);
  pinMode(datapin3, OUTPUT);
  pinMode(datapin4, OUTPUT);
  pinMode(clock, OUTPUT);
}

void loop()
{ 
  sensorValue = analogRead(analogPin); // Read voltage at analog pin 2
  output = floor(5000*(sensorValue/1023)); // convert value to mV
  Serial.println(output); // Outputs voltage to console
  
  // Get each digit value
  digit1 = floor((output % 10000)/1000);
  digit2 = floor((output % 1000)/100);
  digit3 = floor((output % 100)/10);
  digit4 = output % 10;
  
  // Print each digit (FOR DEBUG ONLY)
  /*
  Serial.println(digit1);
  Serial.println(digit2);
  Serial.println(digit3);
  Serial.println(digit4);
  */
  
  // Display each digit; output to shift registers
  shiftOut(datapin1, clock, MSBFIRST, digit28bit(digit1, 0));
  shiftOut(datapin2, clock, MSBFIRST, digit28bit(digit2, 0));
  shiftOut(datapin3, clock, MSBFIRST, digit28bit(digit3, 0));
  shiftOut(datapin4, clock, MSBFIRST, digit28bit(digit4, 0));
  
  // Wait for 1000 ms
  delay(1000);
}


/*
USAGE
digit - is the digit to be convert to 8 bit value; can be 0 - 9
decimal - displays decimal; can be 0(off) - 1(on)
*/  
int digit28bit(int digit, int decimal)
{
  // Return Value
  int eightbit = 0;
  
  switch (digit)
  {
    // Digits 0 - 9
    case 0:
      eightbit = 255;
      break;
    case 1:
      eightbit = 255;
      break;
    case 2:
      eightbit = 255;
      break;
    case 3:
      eightbit = 255;
      break;
    case 4:
      eightbit = 255;
      break;
    case 5:
      eightbit = 255;
      break;
    case 6:
      eightbit = 255;
      break;
    case 7:
      eightbit = 255;
      break;
    case 8:
      eightbit = 255;
      break;
    case 9:
      eightbit = 255;
      break;
    // Blank
    default:
      eightbit = 127;
  }
  
  // Does decimal need to be on?
  if (decimal != 1)
  {
    eightbit = digit + 128; // turns decimal off
  }
  
  return eightbit;
}
