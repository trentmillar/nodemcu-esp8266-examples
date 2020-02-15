//KY018 Photo resistor module

/*
 * Range of sensor readings
 * 0 - 1024
 * 
 * 0 - bright as the sun
 * 1024 - pitch black
 */
 
int sensorPin = A0; // select the input pin for the potentiometer
int sensorValue = 0; // variable to store the value coming from the sensor

void setup() {
  Serial.begin(9600);
}
void loop() {
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue, DEC);
}
