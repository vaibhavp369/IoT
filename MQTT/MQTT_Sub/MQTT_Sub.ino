


#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_INA219.h>

// Connect to the WiFi
const char* ssid = "HR";                           //!!!!!!!!!!!!!!!!!!!!!
const char* password = "123123123";                //!!!!!!!!!!!!!!!!!!!!!
const char* mqtt_server = "192.168.43.190";                 //!!!!!!!!!!!!!!!!!!!!!

String str = "";
const byte ledPin = 2; // digital pin 4 on a weMos D1 mini is next to ground so easy to stick a LED in.
WiFiClient espClient;
PubSubClient client(espClient);

void setup()
{
  Serial.begin(9600);
  delay(10);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

//  Serial.println("connecting WiFi ...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
//    Serial.print(".");
  }

 client.setServer(mqtt_server, 1883);
 client.setCallback(callback);

 str.reserve(10);
 pinMode(ledPin,OUTPUT);

}
 

 
void callback(char* topic, byte* payload, unsigned int length) {
 
 Serial.print("Message arrived [");
 Serial.print(topic);
 Serial.print("] ");
 
 for (int i=0;i<length;i++) {
  char receivedChar = (char)payload[i];
  Serial.print(receivedChar);
  }
  delay(500);
  client.publish("akg","ESP1");
  Serial.println();
}
 
 
void reconnect() {
 while (!client.connected()) {

 if (client.connect("ESP8266 Client1")) {
  client.subscribe("set");
 } else {
  
  Serial.print("failed, rc=");
  Serial.print(client.state());
  Serial.println(" try again in 5 seconds");
  //Wait 5 seconds before retrying
  delay(5000);
  }
 }
}

char dum[10]= "working";

void loop()
{
  
 if (!client.connected()) {
   reconnect();
 }
 
 client.loop();
 while(Serial.available()>0){

  char c= (char)Serial.read();
  str += c;
  int len;
  if(str.length()>=3){
    /*str.toCharArray(dum,10);
    client.publish("akg",dum);
    digitalWrite(ledPin,1);
    delay(100);
    digitalWrite(ledPin,0);
    str = "";*/
    
  }

 }
}
