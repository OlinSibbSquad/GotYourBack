#define ledPin 7
int state = 0;

#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // RX | TX

void setup() {
//  pinMode(ledPin, OUTPUT);
pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(9600); // Default communication rate of the Bluetooth module
  BTSerial.begin(38400);
  
  delay(2000);
}
void loop() {
  if(Serial.available() > 0){ // Checks whether data is comming from the serial port
    state = Serial.read(); // Reads the data from the serial port

    // say what you got:
//    Serial.print("I received: ");
//    Serial.println(state, DEC);
 }
// else {
//  delay(100);
//  Serial.println("It no go.");
// }
 if (state == '0') {
  digitalWrite(LED_BUILTIN, LOW); // Turn LED OFF
//  Serial.println("LED: OFF"); // Send back, to the phone, the String "LED: ON"
  state = 0;
 }
 else if (state == '1') {
  digitalWrite(LED_BUILTIN, HIGH);
//  Serial.println("LED: ON");;
//  state = 0;
  delay(2000);
 } 
 delay(100);
}
