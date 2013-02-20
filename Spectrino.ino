int analogPin = 2; // sensor output connected to Analog Pin 1
double sensorValue = 0; // variable to store the ADC value of the photodiode
int blue = 12; // blue LED
int yellow = 11; // yellow LED
int orange = 10; // orange LED
int red = 9; // red LED
int IR = 8; // IR LED
double output = 0; // output
int switcher = 5; // push button
int val = 0; // Read push button state
int ledon = 0; // Tracks LED states

void setup()
{
  
  Serial.begin(9600); // Setup Data link to Computer; 9600 bps
  
  // Setup Pins to putput to LEDs
  pinMode(blue, OUTPUT); 
  pinMode(yellow, OUTPUT);
  pinMode(orange, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(IR, OUTPUT);
  
  // Setup Push Button
  pinMode(switcher, INPUT);
  
  digitalWrite(blue, HIGH);   // sets the LED on
  ledon = blue; // Tracks which LED is on
  
}

void loop()
{ 
  sensorValue = analogRead(analogPin);
  output = 5000*(sensorValue/1023);
  Serial.println(output);
  delay(1000);
    
}
