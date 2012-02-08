#include <Wire.h>
#include <math.h>

unsigned long timeNew = 0;
unsigned long timeOld = 0;

byte buffa[6];
byte buffg[6];

int xa, ya, za, xg, yg, zg;

double accAngle = 0;

float zgErr = 0;
double zgDeg = 0;
volatile double gyroAngle = 0;

double estAngle = 0;

const int calibrationSamples = 10;

// acc I2C
const int accaddr = 0x53;
const int accdataregaddr = 0x32;

//gyro I2C
const int gyroregaddr = 0x68;
const int gyrodataregaddr = 0x1D;

const float gyroSens = 14375; //LSB per deg/sec

void setup() 
{
  Serial.begin(19200);
  Wire.begin();

  //Turning on the acc
  writeTo(accaddr, 0x2D, B00000000); //Resets POWER_CTL
  writeTo(accaddr, 0x2D, B00010000); //Puts the sensor to standby mode
  writeTo(accaddr, 0x2D, B00001000); //Puts the sensor to measure mode

  //Turning on the gyro
  writeTo(gyroregaddr, 0x16, B00010011); //Set DLPF register to FS_SEL = 3 and DLPF_cfg = 3 (LPF=42Hz, internal sample rate = 1kHz)
  writeTo(gyroregaddr, 0x15, 9); //Sets sample rate to (internal sample rate)/(9 + 1) (1kHz/(9+1)=100Hz <=> 10ms)

  gyroCalibration();
}

void loop() 
{
  if (micros()-timeNew >= 10000)
    {
      timeNew = micros();
      reciveAndClean(); //Recives xa, ya, za, xg, yg, zg and calulates accAngle

      zgDeg = (zg-zgErr)/gyroSens; // Calculate the angle change since last sample
      gyroAngle += zgDeg*10; // Int to the abs angle. 
      estAngle = kalmanCalculate(gyroAngle, zgDeg, (micros()-timeOld)/1000);

      //SerialDebugRaw();
      //SerialDebugAngle();
      serialGraph();
      timeOld = micros();
    }
}


void writeTo(int device, byte address, byte val)
{
  Wire.beginTransmission(device);
  Wire.write(address);
  Wire.write(val);
  Wire.endTransmission();
}

void readFrom(int device, byte address, int num, byte buff[])
{
  Wire.beginTransmission(device); //start transmission to device
  Wire.write(address); //sends address to read from
  Wire.endTransmission(); //ends transmission

  Wire.beginTransmission(device); //start transmission to device (initiate again)
  Wire.requestFrom(device, num); //request 6 num bytes from device

  int i=0;

  while(Wire.available()) //device may send less than requested (abnormal)
  {
    buff[i]=Wire.read(); //receive a num byte
    i++;
  }
  
  Wire.endTransmission(); //end transmission
}

void reciveAndClean()
{
  //Accel calculations
  readFrom(accaddr, accdataregaddr, 6, buffa); // read the data from the acc

  xa=(((int)buffa[1])<<8) | buffa[0]; // cleanup the data and put it in variables
  ya=(((int)buffa[3])<<8) | buffa[2];
  za=(((int)buffa[5])<<8) | buffa[4];

  float xaf=xa; // convert to float to do calculations
  float yaf=ya;

  accAngle = atan2(xaf,yaf)*180/3.14159; // calcutalte the X-Y-angle


  //Gyro calculations
  readFrom(gyroregaddr, gyrodataregaddr, 6, buffg); // read the data from gyro

  xg=(((int)buffg[0])<<8) | buffg[1]; // cleanup the data and put it in variables
  yg=(((int)buffg[2])<<8) | buffg[3];
  zg=(((int)buffg[4])<<8) | buffg[5];
}

void gyroCalibration()
{
  double accAngleBuf = 0;
  
  //Serial.println("Gyro calibration started");
  for (int i = 0; i < calibrationSamples; ++i)
    {
      reciveAndClean();
      accAngleBuf +=  accAngle;
      zgErr += zg;
      if (0 == i%(calibrationSamples/10))
        {
          //Serial.print(100*i/calibrationSamples);
          //Serial.println(" %");
        }
      delay(10);
    }
  gyroAngle = accAngleBuf/calibrationSamples;
  zgErr = zgErr/calibrationSamples;
  
  //Serial.print("Done. zgErr=");
  //Serial.println(zgErr, 10);
}


const float Q_angle  =  1; //0.001
const float Q_gyro   =  3;  //0.003
const float R_angle  =  30;  //0.03

float x_angle = 0;
float x_bias = 0;
float P_00 = 0, P_01 = 0, P_10 = 0, P_11 = 0;
float dt, y, S;
float K_0, K_1;

float kalmanCalculate(float newAngle, float newRate,int looptime) {
  dt = float(looptime)/1000;                                    
  x_angle += dt * (newRate - x_bias);
  P_00 +=  - dt * (P_10 + P_01) + Q_angle * dt;
  P_01 +=  - dt * P_11;
  P_10 +=  - dt * P_11;
  P_11 +=  + Q_gyro * dt;
    
  y = newAngle - x_angle;
  S = P_00 + R_angle;
  K_0 = P_00 / S;
  K_1 = P_10 / S;
  
  x_angle +=  K_0 * y;
  x_bias  +=  K_1 * y;
  P_00 -= K_0 * P_00;
  P_01 -= K_0 * P_01;
  P_10 -= K_1 * P_00;
  P_11 -= K_1 * P_01;
  
  return x_angle;
}

/* Serial communication */

void SerialDebugRaw()
{
  Serial.print("xa: ");
  Serial.print(xa);
  Serial.print(" ");
  Serial.print("ya: ");
  Serial.print(ya);
  Serial.print(" ");
  Serial.print("za: ");
  Serial.print(za);
  Serial.print(" ");
  Serial.print("xg: ");
  Serial.print(xg);
  Serial.print(" ");
  Serial.print("yg: ");
  Serial.print(yg);
  Serial.print(" ");
  Serial.print("zg: ");
  Serial.println(zg); 
  Serial.println(" ");
}

void SerialDebugAngle()
{
  Serial.print("estAngle ");
  //Serial.print(estAngle);
  Serial.print(" gyroAngle= ");
  Serial.print(gyroAngle);
  Serial.print(" accAngle= ");
  Serial.println(accAngle);
}

void serialGraph()
{
  Serial.print(gyroAngle);
  Serial.print(",");
  Serial.print(accAngle);
  Serial.print(",");
  Serial.print(estAngle);
  Serial.print(",");
  Serial.print((micros()-timeNew)/1000);
  Serial.print(",");
  Serial.println((micros()-timeOld)/1000);
}