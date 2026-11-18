#include <ESP8266WiFi.h>
#include <KiwisIoT.h>

// WiFi credentials
const char* ssid = "Name";
const char* pass = "Password;

// KiwisIoT Topic ID
const char* topic = "TopicID";

// Pin configuration
#define LDR_PIN A0
#define LED_PIN D1

// Create KiwisIoT object
KiwisIoT kiwisiot(ssid, pass, topic);

void setup() {

  Serial.begin(115200);

  Serial.println();
  Serial.println("Smart Street Light Monitoring");

  pinMode(LED_PIN, OUTPUT);

  kiwisiot.begin();

  Serial.println("KiwisIoT Initialized");
}

void loop(){
  kiwisiot.run();

  int ldrValue = analogRead(LDR_PIN);

  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  if (ldrValue> 500) {
    digitalWrite(LED_PIN, HIGH);

    kiwisiot.send("0", "ON");  // LED ON
    kiwisiot.send("1","DARK");  // Room DARK

    Serial.println("LED Status: ON");
    Serial.println("Room Status: DARK");
  }
  else {
    digitalWrite(LED_PIN, LOW);

    kiwisiot.send("0", "OFF");  // LED OFF
    kiwisiot.send("1", "BRIGHT");  // Room BRIGHT

    Serial.println("LED Status: OFF");
    Serial.println("Room Status: BRIGHT");
  }

  kiwisiot.send("2", ldrValue);  // LDR Value

  delay(3000);
}
