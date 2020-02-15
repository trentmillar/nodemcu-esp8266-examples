// Use on UNO
// https://www.instructables.com/id/liquid-level-sensor-tutorial/

int waterPin = A0;
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(waterPin, INPUT);
}
 
void loop() {
  int is_wet = analogRead(waterPin);
  
  Serial.print("is wet: ");
  Serial.println(is_wet);
  delay(100);
}
