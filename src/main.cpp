#include <WiFi.h>
#include <TelnetStream.h>

#include <credentials.h>

#define HallSensor 22

int val; 
int HallSensorResult = 0;

unsigned long Time;

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
const char ssid[] = SECRET_SSID;    // your network SSID (name)
const char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)

void setup() {
  Serial.begin(115200);

  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  delay(1);
  WiFi.setHostname("Hall-effect_sensor_ESP32_Node");
  delay(1);
  Serial.println(WiFi.getHostname());
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Failed to connect.");
    while (1) {
      delay(10);
    }
  }

  IPAddress ip = WiFi.localIP();
  Serial.println();
  Serial.println("Connected to WiFi network.");
  Serial.print("Connect with Telnet client to ");
  Serial.println(ip);

  TelnetStream.begin();
}

void loop() {

  Time = millis();

  switch (TelnetStream.read()) {
    case 'R':
    TelnetStream.stop();
    delay(100);
    ESP.restart();
      break;
    case 'C':
      TelnetStream.println("bye bye");
      TelnetStream.flush();
      TelnetStream.stop();
      break;
  }

  val = digitalRead (HallSensor);
  if (val == LOW)
  {
    HallSensorResult = 1;
    TelnetStream.print(Time);
    Serial.print(Time);
    TelnetStream.print(",");
    Serial.print(";");
    TelnetStream.println(HallSensorResult);
    Serial.print(HallSensorResult);
  }
  else
  {
  }
}
