//ADD MOVING AVERAGE BEFORE INTEGRATING WITH WHOLE.

#include <SPI.h> // SPI library included for SparkFunLSM9DS1
#include <Wire.h> // I2C library included for SparkFunLSM9DS1
#include <SparkFunLSM9DS1.h> // SparkFun LSM9DS1 library
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

void setup() {
  // put your setup code here, to run once:
  
// Use the LSM9DS1 class to create an object. [imu] can be
// named anything, we'll refer to that throught the sketch.
imu.settings.device.commInterface = IMU_MODE_SPI; //sets mode to SPI
imu.settings.device.mAddress = 10; //CSM connected to D10
imu.settings.device.agAddress = 9; //CSAG connected to D9
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
check();
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

void loop(){
  unsigned long currentTime = millis();
  float t = (currentTime - lastTime); //1000 converts from ms to s
  lastTime = currentTime;
  imu.settings.accel.scale = 1; // Set accel range to +/-1g
  imu.readAccel();
  Serial.println("Time to print!");
  float a_x = imu.ax;
  float a_y = imu.ay;
  float a_z = imu.az;
  da_x = imu.calcAccel(a_x)*9.8 + 0.51;
  Serial.println(t);
  Serial.println(da_x);
  dv_x = (da_x * t / 1000) + dv_x;
  Serial.println(dv_x);
  dx_x = 1/2 * da_x * sq(t / 1000) + dv_x * t / 1000 + dx_x;
  Serial.println(dx_x);
  da_y = imu.calcAccel(a_y)*9.8;
  dv_y = da_y * t / 1000 + dv_y;
  dx_y = 1/2 * da_y * sq(t / 1000) + dv_y * t / 1000 + dx_y;
  da_z = imu.calcAccel(a_z)*9.8;
  dv_z = da_z * t / 1000 + dv_z;
  dx_z = 1/2 * da_z * sq(t / 1000) + dv_z * t / 1000 + dx_z;
  if(abs(dx_x)>= 3){ 
    resetStuff();
    lastTime = currentTime;
    Serial.println("We Reset!!");
    delay(1000);
    lastTime = currentTime;
    }
   delay(200);
}

void resetStuff(){
    dv_x = 0;
    dx_x = 0;
    dv_y = 0;
    dx_y = 0;
    dv_z = 0;
    dx_z = 0;
}
