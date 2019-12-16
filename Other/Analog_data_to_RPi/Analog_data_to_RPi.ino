#include <Arduino_JSON.h>

#include "ESP8266WiFi.h"
#include <ESP8266HTTPClient.h>

const char* ssid = "HR"; //Enter SSID
const char* password = "123123123"; //Enter Password
const int analog_ip = A0; //Naming analog input pin
int CS=0;
int PS=0;
int inputVal  = 0;        //Variable to store analog input values

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
 if(WiFi.status()== WL_CONNECTED){   
 
   HTTPClient http; 

   http.begin("http://192.168.43.190:8000/vedam"); 
   http.addHeader("Content-Type", "text/plain");  
   inputVal = analogRead (analog_ip);
   CS= inputVal;
   if(abs(CS-PS)>30)
   { 
   Serial.println (inputVal);
   JSONVar myObject;
   myObject["val"] = inputVal;
  // JSON.stringify(myVar) can be used to convert the json var to a String
  String data = JSON.stringify(myObject);
  Serial.print(data);
   //String AnalogData = String(inputVal);
   //Serial.print(AnalogData);
   int httpCode = http.POST(data);   //Send the request
   String payload = http.getString();                  //Get the response payload
   //Serial.println(httpCode);   //Print HTTP return code
   Serial.println(payload);    //Print request response payload
   http.end();  //Close connection
   }
   PS=CS;
 }else{
 
    Serial.println("Error in WiFi connection");   
 
 }
 
  delay(250);  //Send a request every 30 seconds
 }
