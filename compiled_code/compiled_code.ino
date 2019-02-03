//NOTE: NEED TO INCLUDE SHIRIN FIXED

#include <SPI.h> // SPI library included for SparkFunLSM9DS1
#include <Wire.h> // I2C library included for SparkFunLSM9DS1
#include <SparkFunLSM9DS1.h> // SparkFun LSM9DS1 library
#include "pitches.h"
LSM9DS1 imu;
unsigned long initialTime; 
unsigned long lastTime;

float da_x;
float dv_x;
float dx_x;
float da_y;
float dv_y;
float dx_y;
float da_z;
float dv_z;
float dx_z;
int note = NOTE_F6;

#include <SoftwareSerial.h>

SoftwareSerial BTSerial(5, 6); // RX | TX
int imumAddr = 10;
int imuagaddr = 9;
// digital pin 2 has an IR attached to it. Give it a name:
int irSensor = 2;
int leftBuzz = 3;
int rightBuzz = 4;
int speaker = 5;



// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the irSensor's pin an input:
  pinMode(irSensor, INPUT);
  pinMode(leftBuzz, OUTPUT);
  pinMode(rightBuzz, OUTPUT);
  
  // Use the LSM9DS1 class to create an object. [imu] can be
  // named anything, we'll refer to that throught the sketch.
  imu.settings.device.commInterface = IMU_MODE_SPI; //sets mode to SPI
  imu.settings.device.mAddress = imumAddr; //CSM connected to D10
  imu.settings.device.agAddress = imuagaddr; //CSAG connected to D9
  initialTime = 0;
  lastTime = 0;
  da_x=0;
  dv_x=0;
  dx_x=0;
  da_y=0;
  dv_y=0;
  dx_y=0;
  da_z=0;
  dv_z=0;
  dx_z=0;
  Serial.begin(9600);
//  check();
}

void irUpdate(){
  Serial.println("Get the heckers away from me!");
  bleep();
}


// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int buttonState = digitalRead(irSensor);
  
  // print out the state of the button:
  Serial.println(buttonState);

  if(buttonState == LOW){
    buzzWriteHigh();
    bleep();
  }
  else {
    buzzWriteLow();
  }
 delay(100);        // delay in between reads for stability
}

void buzzWriteHigh(){
  digitalWrite(leftBuzz, HIGH);
  digitalWrite(rightBuzz, HIGH); 
}

void buzzWriteLow(){
  digitalWrite(leftBuzz, LOW);
  digitalWrite(rightBuzz, LOW);
}

void bleep(){
  int noteDuration = 1000 / 2;
  tone(speaker, note, noteDuration);
}

int check(){
  imu.begin();
  if (!imu.begin())
  {
      Serial.println("Failed to communicate with LSM9DS1.");
      Serial.println("Looping to infinity.");
      while (1);
  }
}
