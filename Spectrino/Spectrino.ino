/* 
  This code is for the Spectrino project, a world health application of the arduino board to make a spectrophotometer
*/

int analogPin = 2; // sensor output connected to analog pin 2
double sensorValue = 0; // variable to store the ADC value of the photodiode
int output = 0; //processed output
int rawoutput = 0; // raw output
int digit1 = 0; // first digit to display
int digit2 = 0; // second digit to display
int digit3 = 0; // third digit to display
int digit4 = 0; // fourth digit to display
int datapin = 5; // datapin for shift registers
int strclock = 9; // clock for storage registers
int clock1 = 10; // clock for shift register 1
int clock2 = 11; // clock for shift register 2
int clock3 = 12; // clock for shift register 3
int clock4 = 13; // clock for shift register 4
int clrclock = 6; // clear clock

void setup()
{
  // (FOR DEBUG ONLY)
  // Serial.begin(9600); // Setup Data link to Computer; 9600 bps
  
  // Output to each shift register + clocks
  pinMode(datapin, OUTPUT);
  pinMode(clock1, OUTPUT);
  pinMode(clock2, OUTPUT);
  pinMode(clock3, OUTPUT);
  pinMode(clock4, OUTPUT);
  pinMode(strclock, OUTPUT);
  pinMode(clrclock, OUTPUT);
  
  // Clear Registers
  digitalWrite(clrclock, LOW);
  digitalWrite(clrclock, HIGH);
}

void loop()
{ 
  sensorValue = analogRead(analogPin); // Read voltage at analog pin 2
  rawoutput = floor(5000*(sensorValue/1023)); // convert value to mV
  // Some Signal Processing to change for 5 - 3 V to 0 - 5 V
  output = (((-1*rawoutput) + 5000)*2.5);
  Serial.println(output); // Outputs voltage to console
  
  // Get each digit value
  digit1 = getdigit(output, 1);
  digit2 = getdigit(output, 2);
  digit3 = getdigit(output, 3);
  digit4 = getdigit(output, 4);
  
  // Print each digit (FOR DEBUG ONLY)
  // Serial.println(digit1);
  // Serial.println(digit2);
  // Serial.println(digit3);
  // Serial.println(digit4);
   
  // Print convert digit to console (FOR DEBUG ONLY)
  // Serial.println(digit28bit(digit1, 0));
  // Serial.println(digit28bit(digit2, 0));
  // Serial.println(digit28bit(digit3, 0));
  // Serial.println(digit28bit(digit4, 0));  
  
  // Display each digit; output to shift registers
  digitalWrite(strclock, LOW);
  shiftOut(datapin, clock1, MSBFIRST, digit28bit(digit1, 0));
  shiftOut(datapin, clock2, MSBFIRST, digit28bit(digit2, 0));
  shiftOut(datapin, clock3, MSBFIRST, digit28bit(digit3, 0));
  shiftOut(datapin, clock4, MSBFIRST, digit28bit(digit4, 0));
  digitalWrite(strclock, HIGH);
  
  // Wait for 1000 ms
  delay(1000);
}

// Obtain digit from value; digit can be (1 - 4)
int getdigit(int value, int digit)
{
  int returndigit;

  switch(digit)
  {
    case 1:
      returndigit = floor((value % 10000)/1000);
      break;
    case 2:
      returndigit = floor((value % 1000)/100);
      break;
    case 3:
      returndigit = floor((value % 100)/10);
      break;
    case 4:
      returndigit = value % 10;
      break;
    default:
      returndigit = 0;
  }

  return returndigit;
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
      eightbit = 1;
      break;
    case 1:
      eightbit = 55;
      break;
    case 2:
      eightbit = 66;
      break;
    case 3:
      eightbit = 18;
      break;
    case 4:
      eightbit = 52;
      break;
    case 5:
      eightbit = 24;
      break;
    case 6:
      eightbit = 8;
      break;
    case 7:
      eightbit = 51;
      break;
    case 8:
      eightbit = 0;
      break;
    case 9:
      eightbit = 48;
      break;
    // Blank
    default:
      eightbit = 127;
  }
  
  // Does decimal need to be off?
  if (decimal != 1)
  {
    eightbit = eightbit + 128; // turns decimal off
  }
  
  return eightbit;
}
