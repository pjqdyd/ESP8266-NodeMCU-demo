const int trigPin = 2;  //D4 GPIO2
const int echoPin = 0;  //D3 GPIO0

// defines variables
float duration;
float distance;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  Serial.print("echoPin: ");
  Serial.print(echoPin);
  // Calculating the distance
  distance= duration*0.034/2.0;
  // Prints the distance on the Serial Monitor
  Serial.print(" ,Distance: ");
  Serial.println(distance);
  delay(500);
}
