#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#ifndef APSSID
  #define APSSID "ESP8266 Hotspot"
  #define APPSK "87654321"
#endif

void handleRoot();

const char *SSID = APSSID;
const char *PASSWORD = APPSK;

ESP8266WebServer server(80);

byte acceleration = 1;
byte steering = 1;

void setup(){
  settingConnections();

  server.on("/", handleRoot);

  server.begin();
  Serial.println("HTTP Server started");
}

void loop(){
  server.handleClient();
  delay(100);

  if (server.hasArg("value")) deriveInput(server.arg("value"));    

  

}








String oldValue = "15";
void deriveInput(String value){
  if(oldValue != value){
    if(value != "10"){
      if(value == "1"){
        if(steering > 0)
          steering = steering - 1;
      }else if(value == "2"){
        if(steering < 2)
          steering = steering + 1;
      }else if(value == "3"){
        acceleration = 0;
      }else if(value == "4"){
        acceleration = 1;
      }else if(value == "5"){
        acceleration = 2;
      }
    }
    oldValue = value;
  }
}

void settingConnections(){
  delay(1000);
  Serial.begin(115200);
  Serial.println("\nConfiguring access point...");
  WiFi.softAP(SSID, PASSWORD);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP Address: ");
  Serial.println(myIP);
}

void handleRoot() {
  String html = "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no\">";
  html += "<body style=\"margin: 25px; display: flex; align-items: flex-end; justify-content: space-between;\" onclick='sendValue(10)'>";
  html += "<div style=\"width: 30%; height: 100px; display: flex; justify-content: space-around; align-items: center;\" >";
  html += "<button style=\"height: 80%; width: 40%;\" onclick='sendValue(1)'>L</button>";
  html += "<button style=\"height: 80%; width: 40%;\" onclick='sendValue(2)'>R</button>";
  html += "</div>";
  html += "<div style=\"width: 30%; height: 200px; display: flex; justify-content: space-around; align-items: center;\">";
  html += "<div style=\"width: 30%; height: 90%; display: flex; align-items: flex-end;\">";
  html += "<button style=\"height: 40%; width: 100%;\" onclick='sendValue(5)'>E</button>";
  html += "</div>";
  html += "<div style=\"width: 40%; height: 90%; display: flex; flex-direction: column; justify-content: space-between;\">";
  html += "<button style=\"height: 40%; width: 100%;\" onclick='sendValue(3)'>F</button>";
  html += "<button style=\"height: 40%; width: 100%;\" onclick='sendValue(4)'>B</button>";
  html += "</div>";
  html += "</div>";
  html += "<script>";
  html += "function sendValue(valueToSend) {";
  html += "var xhr = new XMLHttpRequest();";
  html += "xhr.open('POST', '/', true);"; ///
  html += "xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');";   ///
  html += "xhr.send('value=' + valueToSend);";
  html += "}";
  html += "</script>";
  html += "</body>";
  server.send(200, "text/html", html);
}