// UNO = INPUT, ESP8266 = INPUT_PULLUP
// 52mm PP Liquid Water Level Sensor Horizontal Float Switch Down
// https://www.aliexpress.com/item/32636496334.html

int waterPin = 13; // D7

int loop_count = 0;
 
void setup() {
  Serial.begin(9600);
  pinMode(waterPin, INPUT_PULLUP);
}
 
void loop() {
  int is_wet = digitalRead(waterPin);
  
  Serial.print("is wet: ");
  Serial.println(is_wet);
  delay(100);
}
