int LDR = A0;
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include<FirebaseArduino.h>
#define FIREBASE_HOST "gothic-depth-208719.firebaseio.com"
#define FIREBASE_AUTH "8TYkeHdRI4jfIYsm1oWKq46RkG9gVtxhBn46tIDZ"
#define WIFI_SSID "Robot"
#define WIFI_PASSWORD "121121121"

#define Relay1 12 //D6
#define DEBUG true
int val1;
FirebaseArduino FirebaseStream;
void setup()
{

pinMode(Relay1,OUTPUT);

Serial.begin(9600);

// connect to wifi.
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
Serial.print("connecting");
while (WiFi.status() != WL_CONNECTED) {
Serial.print(".");
delay(500);
}
Serial.println();
Serial.print("connected: ");
Serial.println(WiFi.localIP());

Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
FirebaseStream.begin(FIREBASE_HOST, FIREBASE_AUTH);
FirebaseStream.stream("/data");
}

int n = 0;
void loop() {
// Serial.println("loop");
//Firebase.setInt("S1", n++);
if (Firebase.failed()) {
Serial.println(Firebase.error());
}
int data = Firebase.getInt("S1");
int MES = analogRead(A0);
Firebase.setInt("MES", MES);

switch (data) {
case 0:

break;
case 1:
digitalWrite(Relay1,HIGH);
Serial.println("light 1 ON");

break;
 case 2:

digitalWrite(Relay1,LOW);
Serial.println("light 1 OFF");

break;
if (Firebase.failed()) {
Serial.println(Firebase.error());
}
Serial.print("data: ");
Serial.println(data);
Serial.print("heap: ");
if (FirebaseStream.available()) {
FirebaseObject event = FirebaseStream.readEvent();
Serial.print("event: ");
Serial.println(event.getString("event"));
Serial.print("path: ");
Serial.println(event.getString("path"));
Serial.print("data: ");
Serial.println(event.getInt("data"));
}
Serial.println(ESP.getFreeHeap());
delay(1000);
}
}
