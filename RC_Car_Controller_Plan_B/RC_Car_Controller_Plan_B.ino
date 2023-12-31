#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

#ifndef APSSID
  #define APSSID "ESP8266 Hotspot"
  #define APPSK "87654321"
#endif

#define DEBUG   // Uncomment to enable debugging 

void handleRoot();

const char *SSID = APSSID;
const char *PASSWORD = APPSK;

ESP8266WebServer server(80);

Servo myServo;

void setup(){
  settingConnections();

  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP Server started");
  
  myServo.attach(D1); 
}

void loop(){
  server.handleClient();
  delay(100);

  if (server.hasArg("value")) {
    String value = server.arg("value");
    Serial.println(value);
    vehicleController(value);
  }
}

String oldValue = "15";
void vehicleController(String value){
  if(oldValue != value){
    if(value == "1"){
      straightTurn();
    }else if (value == "2"){
      leftTurn();
    }else if (value == "3"){
      rightTurn();
    }else if (value == "4"){
      Serial.println("Breaking...");
    }else if (value == "5"){
      Serial.println("Forwarding");
    }else if (value == "6"){
      Serial.println("Reverseing");
    }
    oldValue = value;
    Serial.println("on fdsjflsd");
  }
}






void leftTurn(){                    // Function to turn the car to the left
  const byte MAX_LEFT_ANGLE = 40;   // max left angle; Default:  40
  myServo.write(MAX_LEFT_ANGLE);
}
void straightTurn(){                // Function to set the car to the center position
  const byte STRAIGHT_ANGLE = 88;   // center angle of servo;   Perfect: 88
  myServo.write(STRAIGHT_ANGLE);
}
void rightTurn(){                   // Function to turn the car to the right
  const byte MAX_RIGHT_ANGLE = 140; // max right angle; Default: 140
  myServo.write(MAX_RIGHT_ANGLE);
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
  html +="<body style=\"margin: 25px; display: flex; align-items: flex-end; justify-content: space-between;\">";
  html +="<div style=\"width: 30%; height: 200px; \">";
  html +="<div style=\"width: 100%; height: 100px; display: flex; align-items: top; justify-content: center;\">";
  html +="<button style=\"width: 40%; height: 80%;\" onclick='sendValue(1)'>S</button>";
  html +="</div>";
  html +="<div style=\"width: 100%; height: 100px; display: flex; justify-content: space-around; align-items: center;\" >";
  html +="<button style=\"height: 80%; width: 40%;\" onclick='sendValue(2)'>L</button>";
  html +="<button style=\"height: 80%; width: 40%;\" onclick='sendValue(3)'>R</button>";
  html +="</div>";
  html +="</div>";
  html +="<div style=\"width: 30%; height: 200px; display: flex; justify-content: space-around; align-items: center;\">";
  html +="<div style=\"width: 30%; height: 90%; display: flex; align-items: flex-end;\">";
  html +="<button style=\"height: 40%; width: 100%;\" onclick='sendValue(4)'>E</button>";
  html +="</div>";
  html +="<div style=\"width: 40%; height: 90%; display: flex; flex-direction: column; justify-content: space-between;\">";
  html +="<button style=\"height: 40%; width: 100%;\" onclick='sendValue(5)'>F</button>";
  html +="<button style=\"height: 40%; width: 100%;\" onclick='sendValue(6)'>B</button>";
  html +="</div>";
  html +="</div>";
  html += "<script>";
  html += "function sendValue(valueToSend) {";
  html += "var xhr = new XMLHttpRequest();";
  html += "xhr.open('POST', '/', true);"; ///
  html += "xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');";   ///
  html += "xhr.send('value=' + valueToSend);";
  html += "}";
  html += "</script>";
  html +="</body>";
  server.send(200, "text/html", html);
}
