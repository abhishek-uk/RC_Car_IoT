/* This is a script to control a rc car
 * using nodeMCU 8266
 * using a toy car with 6v dc motor for rear and a servo for front tilt
 */

#include <ESP8266WiFi.h>
#include <Servo.h>


#ifndef STASSID
#define STASSID "OnePlus 9RT 5G"
#define STAPSK "34567890"
#endif

#define DEBUG   // Uncomment to enable debugging 

const char* SSID = STASSID;
const char* PASSWORD = STAPSK;
Servo myServo;

void connectWifi();
void leftTurn();
void rightTurn();
void straightTurn();

void setup() {
  Serial.begin(9600);  // open a serial connection to your computer
  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);
  connectWifi();
  myServo.attach(D1);   // attaches the servo on pin D1 to the servo object
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void loop() {
  // check if wifi disconnected 
  if(WiFi.status() != WL_CONNECTED){     
    #ifdef DEBUG // only for when connect with computer 
      Serial.println("WiFi Disconnectd");
    #endif
    connectWifi();
  }

}





// Useful funciton starts 

void connectWifi(){    
  // function to connect with WiFi
  while(WiFi.status() != WL_CONNECTED){
    #ifdef DEBUG // only for when connect with computer 
      Serial.print(". ");
    #endif
    delay(400);
  }
  #ifdef DEBUG // only for when connect with computer 
    Serial.println("WiFi Connected");
  #endif
}

void leftTurn(){
  // Function to turn the car to the left
  const byte MAX_LEFT_ANGLE = 40; // max left angle; Default:  40
  myServo.write(MAX_LEFT_ANGLE);
}
void rightTurn(){
  // Function to turn the car to the right
  const byte MAX_RIGHT_ANGLE = 140; // max right angle; Default: 140
  myServo.write(MAX_RIGHT_ANGLE);
}
void straightTurn(){
  // Function to set the car to the center position
  const byte STRAIGHT_ANGLE = 88; // center angle of servo;   Perfect: 88
  myServo.write(STRAIGHT_ANGLE);
}

// Useful function ends 