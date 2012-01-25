#include <Wire.h>
#include <math.h> 

int xa, ya, za, xg, yg, zg;
double zgDeg = 0;
double zgDegOld = 0;
long timeOld = 0;
double gyroAngle = 0;
double accAngle = 0;
byte buffa[6];
byte buffg[6];

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
  Wire.begin(); //join i2c bus (address optional for master)

  //turning on the ADXL345
  writeTo(accaddr, 0x2D, B00000000); //Resets POWER_CTL
  writeTo(accaddr, 0x2D, B00010000); //Puts the sensor to standby mode
  writeTo(accaddr, 0x2D, B00001000); //Puts the sensor to measure mode

  //gyro
  writeTo(gyroregaddr, 0x16, B00010011); //Set DLPF register to FS_SEL = 3 and DLPF_cfg = 3 (LPF=42Hz, internal sample rate = 1kHz)
  writeTo(gyroregaddr, 0x15, 9); //Sets sample rate to (internal sample rate)/(9 + 1) (1kHz/(9+1)=100Hz <=> 10ms)
}

void loop() 
{//Gyro scale 14375 LSB/deg/sec
  unsigned long timeNow = millis();

  //Accel calculations
  readFrom(accaddr, accdataregaddr, 6, buffa); //read the acceleration data from the ADXL345

  xa=(((int)buffa[1])<<8) | buffa[0];
  ya=(((int)buffa[3])<<8) | buffa[2];
  za=(((int)buffa[5])<<8) | buffa[4];

  float xaf=xa;
  float yaf=ya;

  accAngle = atan(xaf/yaf)*180/3.14;

  if (yaf > 0)
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
  readFrom(gyroregaddr, gyrodataregaddr, 6, buffg); //read the gyro data from ITG3200

  xg=(((int)buffg[0])<<8) | buffg[1];
  yg=(((int)buffg[2])<<8) | buffg[3];
  zg=(((int)buffg[4])<<8) | buffg[5];

  zgDeg = zg / gyroSens;
  gyroAngle = gyroAngle+(zgDeg *(timeNow-timeOld)); //bugged, showing twice the angle
  zgDegOld = zgDeg;

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
  /*Serial.print("gyroAngle= ");
   Serial.println(gyroAngle);
  /* Serial.print("zgDeg= ");
   Serial.println(zgDeg);*/
  Serial.print("accAngle= ");
  Serial.println(accAngle);
  Serial.print("xa: ");
  Serial.print(xa);
  Serial.print(" ");
  Serial.print("ya: ");
  Serial.print(ya);
}

