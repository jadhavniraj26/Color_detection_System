/***
  Rui Santos
  Complete project details at http://randomnerdtutorials.com  
***/

// TCS230 or TCS3200 pins wiring to Arduino
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

// Stores frequency read by the photodiodes
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;

// Stores the red, green, and blue colors
int redColor = 0;
int greenColor = 0;
int blueColor = 0;

// RGB LED pins
#define redLED 9
#define greenLED 10
#define blueLED 11

void setup() {
  // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);
  
  // Setting frequency scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  
  // RGB LED pins as outputs
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  
  // Begins serial communication
  Serial.begin(9600);
}

void loop() {
  // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  
  // Reading the output frequency
  redFrequency = pulseIn(sensorOut, LOW);
  // Remapping the value of the RED (R) frequency from 0 to 255
  redColor = map(redFrequency, 160, 225, 255, 0);
  
  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  
  // Reading the output frequency
  greenFrequency = pulseIn(sensorOut, LOW);
  // Remapping the value of the GREEN (G) frequency from 0 to 255
  greenColor = map(greenFrequency, 188, 300, 255, 0);
 
  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  
  // Reading the output frequency
  blueFrequency = pulseIn(sensorOut, LOW);
  // Remapping the value of the BLUE (B) frequency from 0 to 255
  blueColor = map(blueFrequency, 143, 159, 255, 0);

  // Turn off all LEDs initially
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);

  // Checks the current detected color and turns on the respective LED
  if (redColor > greenColor && redColor > blueColor) {
    Serial.println(" - RED detected!");
    analogWrite(redLED, HIGH);
    // analogWrite(greenLED, LOW);
    // analogWrite(blueLED, LOW);
  }
  else if (greenColor > redColor && greenColor > blueColor) {
    Serial.println(" - GREEN detected!");
    // analogWrite(redLED, LOW);   // Turn off red LED
    analogWrite(greenLED, HIGH); // Turn on green LED
    // analogWrite(blueLED, LOW);  // Turn off blue LED
}
  else if (blueColor > redColor && blueColor > greenColor) {
    Serial.println(" - BLUE detected!");
    // analogWrite(redLED, LOW);
    // analogWrite(greenLED, LOW);
    analogWrite(blueLED, HIGH);
  }

  // Delay to stabilize the reading and avoid rapid toggling
  delay(1000);
}