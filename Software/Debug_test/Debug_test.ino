/*************************************************/
/* Debug_test.ino -- Debug software debugger     */
/*                                               */
/* Author: Mathias Dannesbo <neic@neic.dk>       */
/*                                               */
/* Time-stamp: <2012-05-09 21:42:51 (neic)>      */
/* Part of the Swagway project                   */
/* https://github.com/neic/Swagway               */
/*                                               */
/*************************************************/

#include <math.h>


unsigned long sinceLastSend;

double accAngle, gyroAngle, estAngle, zg;

// Kalman filter
const float Q_angle = 0.001; // Process noise covariance for the accelerometer - Sw
const float Q_gyro = 0.003; // Process noise covariance for the gyro - Sw
const float R_angle = 0.03; // Measurement noise covariance - Sv

double angle = 0; // It starts at 0 degrees
double bias = 0;
double P_00 = 0, P_01 = 0, P_10 = 0, P_11 = 0;
double dt, y, S;
double K_0, K_1;

void setup() 
{
  Serial.begin(115200);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
}

void loop() 
{
  if ((micros()-sinceLastSend) > 100000)
    {
      zg = map(analogRead(A0),0,1023,-90,90);
      gyroAngle =+ zg;
      accAngle = map(analogRead(A1),0,1023,-90,90);
      estAngle = kalman(accAngle, zg, micros()-sinceLastSend);
      sendToGraph();
    
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