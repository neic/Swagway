#include <Wire.h>
#include <math.h>
#include "ITG3200.h"
#include "ADXL345.h"

// IMU
ADXL345 acc = ADXL345();
float accSampleRate;
ITG3200 gyro = ITG3200();
float gyroSampleRate;

// General
int xa, ya, za;
float xg, yg, zg;

unsigned long sinceLastSend;

bool newAccData, newGyroData;

double accAngle, gyroAngle, estAngle;

// Kalman filter
const float Q_angle = 0.001; // Process noise covariance for the accelerometer - Sw
const float Q_gyro = 0.003; // Process noise covariance for the gyro - Sw
const float R_angle = 0.03; // Measurement noise covariance - Sv

double angle = 0; // It starts at 0 degrees
double bias = 0;
double P_00 = 0, P_01 = 0, P_10 = 0, P_11 = 0;
double dt, y, S;
double K_0, K_1;

// Motor

const int directionPinLeft = 7; //HIGH when forward
const int forwardPinLeft = 9;
const int backwardPinLeft = 6;

const int directionPinRight = 8; //HIGH when forward
const int forwardPinRight = 10;
const int backwardPinRight = 5;

// PID

const int targetAngle = 0;
const float Ex = 2.6;
const float Kp = 2;

void setup() 
{
  Serial.begin(115200);
  Wire.begin();

  //Init the acc
  acc.init(ADXL345_ADDR_SD0_LOW);
  acc.setFullRes(true);
  acc.setRange(3);
  acc.setVoltage(3.3);
  acc.setOutputRate(10); //25Hz*2^(10-8)=100Hz. See table 7 in ADXL345 datasheet

  //Calculate the accSampleRate
  accSampleRate = 25*pow(2,(acc.getOutputRate()-8)); //See table 7 in ADXL345 datasheet

  //Init the gyro
  gyro.init(ITG3200_ADDR_AD0_LOW);
  gyro.setSampleRateDiv(79); //Set the sample rate to 8000Hz/(79+1)=100Hz

  //Calculate the gyroSampleRate
  if (gyro.getFilterBW() == BW256_SR8)
  {
    gyroSampleRate = 8000 / (gyro.getSampleRateDiv()+1);
  }
  else
  {
    gyroSampleRate = 1000 / (gyro.getSampleRateDiv()+1);
  }

  pinMode(directionPinLeft, OUTPUT);
  pinMode(forwardPinLeft, OUTPUT);
  pinMode(backwardPinLeft, OUTPUT);
  pinMode(directionPinRight, OUTPUT);
  pinMode(forwardPinRight, OUTPUT);
  pinMode(backwardPinRight, OUTPUT);
  //Calibration
  gyro.zeroCalibrate(250,2);

  //Dump settings
  dumpIMUsettings();
}

void loop() 
{
  if (acc.isRawDataReady())
  {
    acc.readAccRaw(&xa,&ya,&za);
    accAngle = atan2(xa,ya)*180/3.1415; // calcutalte the X-Y-angle
    newAccData = true;
  }

  if (gyro.isRawDataReady())
  {
    gyro.readGyro(&xg,&yg,&zg);
    gyroAngle += zg/gyroSampleRate;
    newGyroData = true;
  }

  if (newAccData && newGyroData)
  {
    estAngle = kalman(accAngle, zg, micros()-sinceLastSend);
    //      sendToGraph();
    newAccData = newGyroData = false;
    float pwm = pid(estAngle);
    motorControl(pwm,pwm);
    Serial.print(estAngle);
    Serial.println(pwm);

    sinceLastSend = micros();
  }
}

  double kalman(double newAngle, double newRate, double dtime) {
    // KasBot V2 - Kalman filter module - http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1284738418 - http://www.x-firm.com/?page_id=145
    // with slightly modifications by Kristian Lauszus
    // See http://academic.csuohio.edu/simond/courses/eec644/kalman.pdf and http://www.cs.unc.edu/~welch/media/pdf/kalman_intro.pdf for more information
      dt = dtime / 1000000; // Convert from microseconds to seconds

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

float pid(float input)
{
  float output;
  if (input>0)
  {
   output = pow(input,Ex) + Kp*input;
  }
  else
  {
    output = -pow(-input,Ex) + Kp*input;
  }
  return constrain(output, -255, 255);
}

void motorControl(int left, int right)
{
  if (left < 0)
  {
    digitalWrite(directionPinLeft, HIGH);
    digitalWrite(backwardPinLeft, LOW);
    analogWrite(forwardPinLeft, -left);
  }
  else
  {
    digitalWrite(directionPinLeft, LOW);
    digitalWrite(forwardPinLeft, LOW);
    analogWrite(backwardPinLeft, left);
  }
  if (right < 0)
  {
    digitalWrite(directionPinRight, HIGH);
    digitalWrite(backwardPinRight, LOW);
    analogWrite(forwardPinRight, -right);
  }
  else
  {
    digitalWrite(directionPinRight, LOW);
    digitalWrite(forwardPinRight, LOW);
    analogWrite(backwardPinRight, right);
  }
}
/* Serial communication */

void sendToGraph()
{
  Serial.print("<");
  Serial.print(gyroAngle); //0
  Serial.print(",");
  Serial.print(accAngle); //1
  Serial.print(",");
  Serial.print(estAngle); //2
  Serial.print(",");
  Serial.print(micros()-sinceLastSend); //3
  Serial.println(">");
}

void dumpIMUsettings()
{
  Serial.println();
  Serial.println("========================================");
  Serial.println("==============IMU Settings==============");
  Serial.println();
  Serial.println("              ---Gyro---                ");
  Serial.print("Sample rate                  (Hz) = ");
  Serial.println(gyroSampleRate,0);
  Serial.println();
  Serial.println("               ---Acc---                ");
  Serial.print("Sample rate                  (Hz) = ");
  Serial.println(accSampleRate,0);
  Serial.print("Full resolution                   = ");
  Serial.println(acc.getFullRes());
  Serial.print("Range                         (g) = ");
  Serial.println(pow(2,(1+acc.getRange())),0);
  Serial.print("Scale factor X            (LBS/g) = ");
  Serial.println(acc.scaleFactor[0],0);
  Serial.print("Scale factor Y            (LBS/g) = ");
  Serial.println(acc.scaleFactor[1],0);
  Serial.print("Scale factor Z            (LBS/g) = ");
  Serial.println(acc.scaleFactor[2],0);
  Serial.println();
  Serial.println("============end IMU Settings============");
  Serial.println("========================================");
  Serial.println();
}

