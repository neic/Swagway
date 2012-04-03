#include <Wire.h>
#include <math.h>
#include "ITG3200.h"

unsigned long timeNew = 0;
unsigned long timeOld = 0;

byte buffa[6];
byte buffg[6];

int xa, ya, za;
float xg, yg, zg;

double accAngle = 0;
double gyroAngle = 0;
double gyroRate = 0;
double estAngle = 0;

const int calibrationSamples = 10;

int packageCount = 0;

// Kalman filter
const float Q_angle = 0.001; // Process noise covariance for the accelerometer - Sw
const float Q_gyro = 0.003; // Process noise covariance for the gyro - Sw
const float R_angle = 0.03; // Measurement noise covariance - Sv

double angle = 180; // It starts at 180 degrees
double bias = 0;
double P_00 = 0, P_01 = 0, P_10 = 0, P_11 = 0;
double dt, y, S;
double K_0, K_1;

// acc I2C
const int accaddr = 0x53;
const int accdataregaddr = 0x32;

//gyro I2C
ITG3200 gyro = ITG3200();

void setup() 
{
  Serial.begin(115200);
  Wire.begin();

  //Turning on the acc
  writeTo(accaddr, 0x2D, B00000000); //Resets POWER_CTL
  writeTo(accaddr, 0x2D, B00010000); //Puts the sensor to standby mode
  writeTo(accaddr, 0x2D, B00001000); //Puts the sensor to measure mode

  gyro.init(ITG3200_ADDR_AD0_LOW);
  gyro.zeroCalibrate(2500,2);
}

void loop() 
{
  while (gyro.isRawDataReady()) {
    /* 
    // Reads uncalibrated raw values from the sensor 
    gyro.readGyroRaw(&ix,&iy,&iz); 
    Serial.print("X1:"); 
    Serial.print(ix); 
    Serial.print("  Y:"); 
    Serial.print(iy); 
    Serial.print("  Z:"); 
    Serial.println(iz); 
    */ 
     
    /* 
    // Reads calibrated raw values from the sensor 
    gyro.readGyroRawCal(&ix,&iy,&iz); 
    Serial.print("X2:"); 
    Serial.print(ix); 
    Serial.print("  Y:"); 
    Serial.print(iy); 
    Serial.print("  Z:"); 
    Serial.println(iz); 
    */ 
     
    // Reads calibrated values in deg/sec    
    gyro.readGyro(&xg,&yg,&zg); 
    Serial.print("X3:"); 
    Serial.print(xg); 
    Serial.print("  Y:"); 
    Serial.print(yg); 
    Serial.print("  Z:"); 
    Serial.println(zg);
  } 
  /* if (millis()-timeNew >= 10) */
  /*   { */
  /*     timeNew = millis(); */
  /*     reciveAndClean(); //Recives xa, ya, za, xg, yg, zg. */

  /*     accAngle = atan2(float(xa),float(ya))*180/3.1415; // calcutalte the X-Y-angle */
  /*     gyroRate = zg*10/2/gyroSens; */
  /*     gyroAngle += gyroRate; // Integral to the abs angle. */
      
  /*     estAngle = kalman(accAngle, gyroRate, millis()-timeOld); */

  /*     //estAngle = (0.98)*(estAngle+gyroAngle)+(0.02)*(); */
  /*     //SerialDebugRaw(); */
  /*     //SerialDebugAngle(); */
  /*     serialGraph(); */

  /*     timeOld = millis(); */
  /*   } */
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
}

void gyroCalibration()
{
  double accAngleBuf = 0;
  
  //Serial.println("Gyro calibration started");
  for (int i = 0; i < calibrationSamples; ++i)
    {
      reciveAndClean();
      accAngleBuf +=  accAngle;
      delay(10);
    }
  gyroAngle = accAngleBuf/calibrationSamples;
  
  //Serial.print("Done. zgErr=");
  //Serial.println(zgErr, 10);
}



double kalman(double newAngle, double newRate, double dtime) {
    // KasBot V2 - Kalman filter module - http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1284738418 - http://www.x-firm.com/?page_id=145
    // with slightly modifications by Kristian Lauszus
    // See http://academic.csuohio.edu/simond/courses/eec644/kalman.pdf and http://www.cs.unc.edu/~welch/media/pdf/kalman_intro.pdf for more information
    dt = dtime / 1000; // Convert from milliseconds to seconds
    
    // Discrete Kalman filter time update equations - Time Update ("Predict")
    // Update xhat - Project the state ahead
    angle += dt * (newRate - bias);
    
    // Update estimation error covariance - Project the error covariance ahead
    P_00 += -dt * (P_10 + P_01) + Q_angle * dt;
    P_01 += -dt * P_11;
    P_10 += -dt * P_11;
    P_11 += +Q_gyro * dt;
    
    // Discrete Kalman filter measurement update equations - Measurement Update ("Correct")
    // Calculate Kalman gain - Compute the Kalman gain
    S = P_00 + R_angle;
    K_0 = P_00 / S;
    K_1 = P_10 / S;
    
    // Calculate angle and resting rate - Update estimate with measurement zk
    y = newAngle - angle;
    angle += K_0 * y;
    bias += K_1 * y;
    
    // Calculate estimation error covariance - Update the error covariance
    P_00 -= K_0 * P_00;
    P_01 -= K_0 * P_01;
    P_10 -= K_1 * P_00;
    P_11 -= K_1 * P_01;
    
    return angle;
}

float floatmap(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
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
  Serial.print(gyroAngle); //0
  Serial.print(",");
  Serial.print(accAngle); //1
  Serial.print(",");
  Serial.println(estAngle); //2
}


