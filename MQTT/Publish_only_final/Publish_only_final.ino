#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_INA219.h>
#include <Arduino_JSON.h>
const char* ssid = "HR";  
const char* password = "123123123";
const char* mqtt_server = "192.168.43.190"; 
//const char* mqtt_server = "172.31.19.109:"; 
WiFiClient espClient;
PubSubClient client(espClient);

void setup()
{
    Serial.begin(9600);
    delay(10);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) 
        {
            delay(500);
         }
 client.setServer(mqtt_server, 1883);
// client.setCallback(callback);

 }
/*
 void callback(char* topic, byte* payload, unsigned int length) 
 {
    char temp[20];
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
     for (int i=0;i<length;i++) 
      {
        char receivedChar = (char)payload[i];
        temp[i] = receivedChar;
         Serial.print(receivedChar);
      }

  
  Serial.println();
}
 
 */
void loop()
{
  if (!client.connected())
    {
        reconnect();
    }
 client.loop();
 senddata();
 delay(1000);
}

void reconnect() {
 while (!client.connected()) {

    if (client.connect("ESP8266 Client1")) 
        {
          client.subscribe("LED");
        }
     else 
        {
  
          Serial.print("failed, rc=");
          Serial.print(client.state());
          Serial.println(" try again in 5 seconds");
          delay(5000);
        }
    }
}

void senddata()
{
 
    for(int j=0; j<=10; j++)
      {
        int k = random(10,1024);
        String m = String(k);
        Serial.println(k);
        //String s= "ESP1 :" + m;
        JSONVar myObject;
        myObject["name"] = "ESP1_SEN1";
        myObject["val"] = m;
        String data = JSON.stringify(myObject);
         client.publish("akg",data.c_str());
        //client.publish("akg",m.c_str());  //final
         delay(3000);
      }
}
