const int analog_ip = A0; //Naming analog input pin
const int LED = 0;        //Naming LED Pin
int inputVal  = 0;        //Variable to store analog input values

void setup() {
  pinMode(LED, OUTPUT);  // Defining pin as output
  Serial.begin(9600);    // Initiating Serial communication

}                                                                                                                                                                                                                           
void loop() {
  inputVal = analogRead (analog_ip); // Analog Values 0 to 1023
  Serial.println (inputVal);
  analogWrite(LED, inputVal/4);      // Mapping 0 to 255
  delay(1000);
}
