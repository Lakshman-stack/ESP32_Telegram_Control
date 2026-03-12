#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "MitronTech_5G";
const char* password = "Mitron&123";

String serverName = "http://192.168.29.71:5000/device/data";

int ledPin = 2;

unsigned long previousMillis = 0;
const long interval = 10000;

void connectWiFi()
{
  Serial.print("Connecting WiFi");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void sendData()
{
  if(WiFi.status()==WL_CONNECTED)
  {

    HTTPClient http;

    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    StaticJsonDocument<200> doc;

    doc["device_id"] = "ESP32_01";
    doc["firmware"] = "1.0";
    doc["wifi_rssi"] = WiFi.RSSI();
    doc["uptime"] = millis()/1000;

    String requestBody;
    serializeJson(doc, requestBody);

    Serial.println("Sending Data:");
    Serial.println(requestBody);

    int httpResponseCode = http.POST(requestBody);

    if(httpResponseCode > 0)
    {
      String response = http.getString();

      Serial.println("Server Response:");
      Serial.println(response);

      parseResponse(response);
    }
    else
    {
      Serial.print("Error Code: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  }
}

void parseResponse(String response)
{
  StaticJsonDocument<200> doc;

  DeserializationError error = deserializeJson(doc, response);

  if(error)
  {
    Serial.println("JSON parse failed");
    return;
  }

  const char* command = doc["command"];

  Serial.print("Command: ");
  Serial.println(command);

  if(String(command) == "LED_ON")
  {
    digitalWrite(ledPin, HIGH);
    Serial.println("LED ON");
  }

  if(String(command) == "LED_OFF")
  {
    digitalWrite(ledPin, LOW);
    Serial.println("LED OFF");
  }
}

void setup()
{
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);

  connectWiFi();
}

void loop()
{

  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;

    sendData();
  }

}