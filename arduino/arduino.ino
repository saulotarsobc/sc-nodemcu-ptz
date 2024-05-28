#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Servo.h>
#include <ArduinoJson.h>

#ifndef STASSID
#define STASSID "S&S costa"
#define STAPSK "movtelecoM@"
#endif

const char *ssid = STASSID;
const char *password = STAPSK;
Servo servoLR;

int lrVal = 90;
int udVal = 90;
int zVal = 50;

int increment = 1;
int delayBetweenSteps = 3;

ESP8266WebServer server(80);

void handleRoot()
{
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
  String responseJson = "{\"msg\":\"ok\"}";
  server.send(200, "application/json", responseJson);
}

void handleNotFound()
{
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
  String message = "File Not Found\n\n";
  server.send(404, "text/plain", message);
}

int mapPosition(int value, int fromLow, int fromHigh, int toLow, int toHigh)
{
  return (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
}

void setPositionServoLR()
{
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "Content-Type");

  if (server.method() == HTTP_OPTIONS)
  {
    server.send(204);
    return;
  }

  if (server.method() == HTTP_POST)
  {
    String body = server.arg("plain");
    DynamicJsonDocument doc(200);
    deserializeJson(doc, body);

    if (doc.containsKey("position"))
    {
      int targetPosition = doc["position"];

      int mappedPosition = mapPosition(targetPosition, 0, 100, 10, 170);

      int direction = (mappedPosition > lrVal) ? 1 : -1;

      while (lrVal != mappedPosition)
      {
        lrVal += increment * direction;
        servoLR.write(lrVal);
        delay(delayBetweenSteps);
      }

      String responseJson = "{\"lr\":\"" + String(lrVal) + "\"}";
      server.send(200, "application/json", responseJson);
    }
    else
    {
      server.send(400, "text/plain", "Missing 'position' parameter");
    }
  }
  else
  {
    server.send(405, "text/plain", "Method Not Allowed");
  }
}

void setup(void)
{
  servoLR.attach(D1);
  servoLR.write(lrVal);

  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("sc-nodemcu-ptz"))
  {
    Serial.println("MDNS responder started");
  }

  server.on("/", HTTP_GET, handleRoot);
  server.on("/setPositionServoLR", HTTP_POST, setPositionServoLR);
  server.on("/setPositionServoLR", HTTP_OPTIONS, []()
            {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.sendHeader("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
    server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
    server.send(204); });
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void)
{
  server.handleClient();
  MDNS.update();
}
