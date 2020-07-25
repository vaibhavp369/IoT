/*
 Author : - VAIBHAV PATIL
 DATE : - 16th JUNE 2019
 TIME COMPLETED :-  8:58 PM
 TIME REQUIRED TO COMPLETE : - 10Hr+
 GUIDENCE : - VEDAM LABS
 Abstract :-  This code is used to control pins using ESP. The input is given through app in Json format to Raspberry pi. The Raspberry pi publish
              data to subscribed ESP and receive its aknowledgement
              Subscribed Topic :- "LED"
              Publish Topic :- "LED"
               
*/


#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_INA219.h>
char temp[17];
const char* ssid = "HR";                      
const char* password = "123123123";                
const char* mqtt_server = "192.168.43.190"; // mqtt broker IP
const byte led = D0; 
WiFiClient espClient;
PubSubClient client(espClient);

void setup()
{
  Serial.begin(115200);
  delay(10);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);

  }

 client.setServer(mqtt_server, 1883);
 client.setCallback(callback);
 pinMode(led,OUTPUT);
 digitalWrite(led,HIGH);

}
 
void callback(char* topic, byte* payload, unsigned int length) 
{
 
 Serial.print("Message arrived [");
 Serial.print(topic);
 Serial.print("] ");
 
 for (int i=0;i<length;i++) 
 {
     char receivedChar = (char)payload[i];
     Serial.print(receivedChar);
     temp[i] = receivedChar;
  }
 Serial.println();
 String q = String(temp);
 if( q == "{u'val': u'on'}}")
    {
      client.publish("LED","ESP1: LED_ON");
      //Serial.println("akg LED_ON");
      digitalWrite(led,LOW);
    }
  else if( q == "{u'val': u'off'}")
    {
      client.publish("LED","ESP1:LED_OFF");
      //Serial.println("akg LED_OFF");
      digitalWrite(led,HIGH);
    }
}
 
 
void reconnect() 
{
 while (!client.connected()) 
  {
 if (client.connect("ESP8266 Client1"))   // here the mqtt_subscriber_client_name is ESP8266 Client 1 IT SHOULD BE DIFFERENT FOR DIFFERENT subscriber subscribing to similar topic
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

void loop()
  {
  
      if (!client.connected())
          {
            reconnect();
          }
 
      client.loop();

    
  }

 
