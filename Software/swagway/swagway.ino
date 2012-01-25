#include <Wire.h>
#include <math.h>

unsigned long timeNow = 0;
unsigned long timeOld = 0;

byte buffa[6];
byte buffg[6];

int xa, ya, za, xg, yg, zg;

double gyroAngle = 0;
double accAngle = 0;

double zgDeg = 0;

// acc I2C
const int accaddr = 0x53;
const int accdataregaddr = 0x32;

//gyro I2C
const int gyroregaddr = 0x68;
const int gyrodataregaddr = 0x1D;

const float gyroSens = 14375; //LSB per deg/sec

void setup() 
{
  Serial.begin(9600);
  Wire.begin();

  //Turning on the acc
  writeTo(accaddr, 0x2D, B00000000); //Resets POWER_CTL
  writeTo(accaddr, 0x2D, B00010000); //Puts the sensor to standby mode
  writeTo(accaddr, 0x2D, B00001000); //Puts the sensor to measure mode

  //Turning on the gyro
  writeTo(gyroregaddr, 0x16, B00010011); //Set DLPF register to FS_SEL = 3 and DLPF_cfg = 3 (LPF=42Hz, internal sample rate = 1kHz)
  writeTo(gyroregaddr, 0x15, 9); //Sets sample rate to (internal sample rate)/(9 + 1) (1kHz/(9+1)=100Hz <=> 10ms)
}

void loop() 
{
  timeNow = millis();

  //Accel calculations
  readFrom(accaddr, accdataregaddr, 6, buffa); // read the data from the acc

  xa=(((int)buffa[1])<<8) | buffa[0]; // cleanup the data and put it in variables
  ya=(((int)buffa[3])<<8) | buffa[2];
  za=(((int)buffa[5])<<8) | buffa[4];

  float xaf=xa; // convert to float to do calculations
  float yaf=ya;

  accAngle = atan(xaf/yaf)*180/3.14; // calcutalte the X-Y-angle

  if (yaf > 0) // ignore angles ±90 deg
  {    
    if (xaf < 0)
    {
      accAngle = 90;
    }
    else
    {
      accAngle = -90;
    }
  }

  //Gyro calculations
  readFrom(gyroregaddr, gyrodataregaddr, 6, buffg); // read the data from gyro

  xg=(((int)buffg[0])<<8) | buffg[1]; // cleanup the data and put it in variables
  yg=(((int)buffg[2])<<8) | buffg[3];
  zg=(((int)buffg[4])<<8) | buffg[5];

  zgDeg = zg / gyroSens; // calculate the angle change in this sample
  gyroAngle = gyroAngle+(zgDeg *(timeNow-timeOld)/2); // Intergrate to get the absolute angle. (Why shoud this be divided by two?)

  //SerialDebugRaw();
  SerialDebugAngle();
  delay(10);
  timeOld = timeNow;
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
  Serial.print("gyroAngle= ");
  Serial.print(gyroAngle);
  Serial.print(" zgDeg= ");
  Serial.print(zgDeg);
  Serial.print(" accAngle= ");
  Serial.println(accAngle);
}