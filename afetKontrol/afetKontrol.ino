// Import required libraries
#include "deneyap.h"
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include "lsm6dsm.h"

LSM6DSM IMU;

// Replace with your network credentials
const char* ssid = "TTNET_ZyXEL_X7W4";
const char* password = "nflpycpp0962";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String readAccelerometerXAxis() {
  
  if (IMU.readFloatAccelX()<0.10 & IMU.readFloatAccelX()>-0.10)
  {
    return String(0);
  }
  else if (IMU.readFloatAccelX()>0.10)
  {
    return String(10);
  }
  
  else if (IMU.readFloatAccelX()<-0.10)
  {
    return String(-10);
  }
  return String(0);
}


void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  IMU.begin();                                  // IMU ayarlari konfigure edildi

  
  // Initialize SPIFFS
  if(!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }


  // Print Deneyap_Kart Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html");
  });
  server.on("/accelerometer", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readAccelerometerXAxis().c_str());
  });

  server.on("/highcharts.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/highcharts.js", "text/javascript");
  });
  
  // Start server
  server.begin();
}void loop(){}
