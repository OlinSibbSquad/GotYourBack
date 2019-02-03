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

const int SIZED = 10;

float movingAverageAx[SIZED];
float movingAverageAy[SIZED];
float movingAverageAz[SIZED];
float moveAvgAx;
float moveAvgAy;
float moveAvgAz;
bool startCalc;
float t;
const float XCONST = 0.50;
const float YCONST = 0.0;
const float ZCONST = 0.0;

int curr_avg;

const int INSTRUCTIONS[4] = {1, 1, 1, 1};
const bool TURNS[4] = {true, true, true, true};

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

curr_avg = 0;
startCalc = false;
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
  t = (currentTime - lastTime); //1000 converts from ms to s
  lastTime = currentTime;
  imu.settings.accel.scale = 1; // Set accel range to +/-1g
  imu.readAccel();
  movingAverageAx[curr_avg] = imu.ax;
  movingAverageAy[curr_avg] = imu.ay;
  movingAverageAz[curr_avg] = imu.az;
  Serial.println(imu.ax);
  Serial.println(imu.ay);
  Serial.println(imu.az);
  curr_avg = curr_avg + 1;

  if(startCalc){
    updateAvgs();
    da_x = imu.calcAccel(moveAvgAx)*9.8 + XCONST;
    
    dv_x = (da_x * t / 1000) + dv_x;
    dx_x = 1/2 * da_x * sq(t / 1000) + dv_x * t / 1000 + dx_x;
    if((curr_avg % 10) == 0){
      printStuff();
    }
    da_y = imu.calcAccel(moveAvgAy)*9.8 + YCONST;
    dv_y = da_y * t / 1000 + dv_y;
    dx_y = 1/2 * da_y * sq(t / 1000) + dv_y * t / 1000 + dx_y;
    da_z = imu.calcAccel(moveAvgAz)*9.8 + ZCONST;
    dv_z = da_z * t / 1000 + dv_z;
    dx_z = 1/2 * da_z * sq(t / 1000) + dv_z * t / 1000 + dx_z;
    
    if(abs(dx_x)>= 3){ //3 = distance to travel
      resetStuff();
      lastTime = currentTime;
      Serial.println("We Reset!!");
      delay(10);
      lastTime = currentTime;
      startCalc = false;
      }
    }
  else {
    if(curr_avg == SIZED){
      startCalc = true;
    }
    
  }

  startCalc = true;
  delay(20);
}

void printStuff(){
    Serial.println("Time to print!");
      Serial.println(t);
      Serial.println(da_x);
      Serial.println(dv_x);
      Serial.println(dx_x);
      Serial.println("Y values:");
      Serial.println(da_y);
      Serial.println(dv_y);
      Serial.println(dx_y);
      Serial.println("Z values:");
      Serial.println(da_z);
      Serial.println(dv_z);
      Serial.println(dx_z);
      Serial.println("Moving averages.");
      Serial.println(moveAvgAx);
      Serial.println(moveAvgAy);
      Serial.println(moveAvgAz);
      
}

void updateAvgs(){
  float tempsumax = 0;
  float tempsumay = 0;
  float tempsumaz = 0;

  for (int i = 0; i < SIZED; i ++){
    tempsumax = tempsumax + movingAverageAx[i];
    tempsumay = tempsumay + movingAverageAy[i];
    tempsumaz = tempsumaz + movingAverageAz[i];
  }
  
  moveAvgAx  = tempsumax / SIZED;
  moveAvgAy  = tempsumay / SIZED;
  moveAvgAz  = tempsumaz / SIZED;
}

void resetStuff(){
    dv_x = 0;
    dx_x = 0;
    dv_y = 0;
    dx_y = 0;
    dv_z = 0;
    dx_z = 0;
}
