/*
Author:- VAIBHAV PATIL

Description : - Print_The_String_From_Postman

*/

#include "ESP8266WiFi.h"
#include <ESP8266HTTPClient.h>

const char* ssid = "HR"; //Enter SSID
const char* password = "123123123"; //Enter Password
//String st = String(p);
void setup(void)
{ 
  Serial.begin(115200);
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
     delay(500);
     Serial.print("*");
  }
  
  Serial.println("");
  Serial.println("WiFi connection Successful");
  Serial.print("The IP Address of ESP8266 Module is: ");
  Serial.print(WiFi.localIP());// Print the IP address

}

void loop() 
{
  // EMPTY
  HTTPClient http;

    Serial.print("[HTTP] begin...\n");
 if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
 
   HTTPClient http;    //Declare object of class HTTPClient
    for(int i=0;i<=9;i++)
   {
     String st = String(i);
   http.begin("http://192.168.43.190:8000/vedam");      //Specify request destination
   http.addHeader("Content-Type", "text/plain");  //Specify content-type header

   
   int httpCode = http.POST(st);   //Send the request
   String payload = http.getString();                  //Get the response payload
   delay(1000);
   
   //Serial.println(httpCode);   //Print HTTP return code
   Serial.println(payload);    //Print request response payload
   }
   http.end();  //Close connection
   
 }else{
 
    Serial.println("Error in WiFi connection");   
 
 }
 
  delay(30000);  //Send a request every 30 seconds
 }
