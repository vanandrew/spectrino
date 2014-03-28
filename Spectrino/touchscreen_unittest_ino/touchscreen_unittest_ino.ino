
#define xLow  17
#define xHigh 15
#define yLow  16
#define yHigh 14

int ts_coords[2] = {0};
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
  get_coordinates();
  Serial.print("X:");
  Serial.print(ts_coords[0]);
  Serial.print(", Y:");
  Serial.println(ts_coords[1]);
  delay(200);
}
}

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
