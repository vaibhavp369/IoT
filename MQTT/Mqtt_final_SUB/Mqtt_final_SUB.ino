#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_INA219.h>
#include <Arduino_JSON.h>
String r ="HELLO";
// Connect to the WiFi
const char* ssid = "HR";  
const char* password = "123123123";
const char* mqtt_server = "192.168.43.190";  


const byte ledPin = 2;
WiFiClient espClient;
PubSubClient client(espClient);

void setup()
{
  Serial.begin(9600);
  delay(10);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
 client.setServer(mqtt_server, 1883);
 client.setCallback(callback);
 //str.reserve(10);
 pinMode(ledPin,OUTPUT);
   String p ="HELLO";
}
void callback(char* topic, byte* payload, unsigned int length) {
 char temp[20];
 Serial.print("Message arrived [");
 Serial.print(topic);
 Serial.print("] ");
// Serial.println(payload);
 for (int i=0;i<length;i++) {
  char receivedChar = (char)payload[i];
   temp[i] = receivedChar;
  Serial.print(receivedChar);
  
  }
  client.publish("akg","ESP 1 RECEIVED");
 /* for(int j=0; j<=25; j++)
  {
  String m = String(j);
  String s= "ESP1 :" + m;
        JSONVar myObject;
  myObject["val"] = s;
  String data = JSON.stringify(myObject);
client.publish("LED",data.c_str());
  delay(500);}
  */
   /*String m = String(temp);
  String s= "ESP1 :" + m;
        JSONVar myObject;
  myObject["val"] = s;
  String data = JSON.stringify(myObject);
client.publish("LED",data.c_str()); */
  Serial.println();
}
 
 
void reconnect() {
 while (!client.connected()) {

 if (client.connect("ESP8266 Client1")) {
  client.subscribe("LED");
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

  /*char c= (char)Serial.read();
  str += c;
  int len;
  if(str.length()>=3){*/
    /*str.toCharArray(dum,10);
    client.publish("akg",dum);
    digitalWrite(ledPin,1);
    delay(100);
    digitalWrite(ledPin,0);
    str = "";*/
    
  }

 }
