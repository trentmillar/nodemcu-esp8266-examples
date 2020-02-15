#include <ESP8266WiFi.h>
 
const char* ssid = "SSID";
const char* password = "PASSWORD";
 
int ledPin = 15; // D8 -> GPIO15
int tiltPin = 13; // D7 -> GPIO13

bool is_tilt = false;
bool is_led_switch_on = false;
int tiltState = 0;

WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(ledPin, OUTPUT);
  pinMode(tiltPin, INPUT);
  digitalWrite(ledPin, LOW);
  digitalWrite(tiltPin, HIGH);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void handleTiltLed() {
  if (is_tilt) {
    return digitalWrite(ledPin, LOW);
  }

  return digitalWrite(ledPin, is_led_switch_on ? HIGH : LOW);
}
 
void loop() {
  // HANLDE TILT
  is_tilt = !digitalRead(tiltPin);
  
  Serial.print("is tilted: ");
  Serial.println(is_tilt);
  
  //Serial.print("led switch on: ");
  //Serial.println(is_led_switch_on);

  handleTiltLed();
  delay(100);
  // END TILT
  
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  if (request.indexOf("/LED=ON") != -1)  {
    is_led_switch_on = true;
  }
  if (request.indexOf("/LED=OFF") != -1)  {
    is_led_switch_on = false;
  }
 
// Set ledPin according to the request
//digitalWrite(ledPin, value);
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Led pin is now: ");
 
  if(is_led_switch_on == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("<a href=\"/LED=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/LED=OFF\"\"><button>Turn Off </button></a><br />");  
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
