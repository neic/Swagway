/*************************************************/
/* ADXL345.cpp -- ADXL345/I2C libary for Arduino */
/*                                               */
/* Author: Mathias Dannesbo <neic@neic.dk> and   */
/*         Carl-Emil Grøn Christensen            */
/* Time-stamp: <2012-04-04 18:04:52 (neic)>      */
/* Part of the Swagway project                   */
/* https://github.com/neic/Swagway               */
/*                                               */
/* Inspired by the ITG3200 Arduino library at    */
/* http://code.google.com/p/itg-3200driver       */
/*************************************************/

#include "ADXL345.h"
#include <Wire.h>

ADXL345::ADXL345()
{
}

void ADXL345::init(unsigned int address)
{
  _dev_address = address;
  setStandbyMode();
  setMeasureMode();

}

void ADXL345::setStandbyMode()
{
  writemem(POWER_CTL, STANDBY_MODE);
}

void ADXL345::setMeasureMode()
{
  writemem(POWER_CTL, MEASURE_MODE);
}

byte ADXL345::getOutputRate()
{
  readmem(BW_RATE, 1, &_buff[0]);
  return(_buff[0]);
}

void ADXL345::setOutputRate(byte _rate)
{
  _rate %= 16; //Prevent overflow
  writemem(BW_RATE, _rate);
}

bool ADXL345::getFullRes()
{
  readmem(DATA_FORMAT, 1, &_buff[0]);
  return(_buff[0] >> 3);
}

void ADXL345::setFullRes(bool _fullRes)
{
  readmem(DATA_FORMAT, 1, &_buff[0]);
  writemem(DATA_FORMAT, ((_buff[0] & ~(1 << 3)) | (_fullRes << 3)));
}

int ADXL345::getRange()
{
  readmem(DATA_FORMAT, 1, &_buff[0]);
  return(_buff[0] & B00000011);
}

void ADXL345::setRange(int range)
{
  range %= 4; //Prevent overflow
  readmem(DATA_FORMAT, 1, &_buff[0]);
  writemem(DATA_FORMAT, ((_buff[0] & ~3) | range));
}


bool ADXL345::isRawDataReady()
{
  readmem(INT_SOURCE, 1, &_buff[0]);
  return(_buff[0] >> 7);
}
void ADXL345::setVoltage(float _voltage)
{
  voltage = _voltage;
  updateScaleFactor();
}

void ADXL345::updateScaleFactor()
{
  int rangeScale=256;
  if (!getFullRes())
    {
      rangeScale = pow(2,(8-getRange()));
    }
  scaleFactor[0] = rangeScale*0.89013671875+rangeScale*0.0439453125*voltage;
  scaleFactor[1] = rangeScale*0.89013671875+rangeScale*0.0439453125*voltage;
  scaleFactor[2] = rangeScale;
}

void ADXL345::readAccRaw(int *_AccX, int *_AccY, int *_AccZ)
{
  readmem(DATAX0, 6, &_buff[0]);
  *_AccX = _buff[1] << 8 | _buff[0];
  *_AccY = _buff[3] << 8 | _buff[2];
  *_AccZ = _buff[5] << 8 | _buff[4];
}

void ADXL345::readAcc(float *_AccX, float *_AccY, float *_AccZ)
{
  int x, y, z;
  readAccRaw(&x,&y,&z);
  *_AccX = x / scaleFactor[0];
  *_AccY = y / scaleFactor[1];
  *_AccZ = z / scaleFactor[2];
}

void ADXL345::writemem(uint8_t _addr, uint8_t _val) {
  Wire.beginTransmission(_dev_address);   // start transmission to device 
  Wire.write(_addr); // send register address
  Wire.write(_val); // send value to write
  Wire.endTransmission(); // end transmission
}

void ADXL345::readmem(uint8_t _addr, uint8_t _nbytes, uint8_t __buff[]) {
  Wire.beginTransmission(_dev_address); // start transmission to device 
  Wire.write(_addr); // sends register address to read from
  Wire.endTransmission(); // end transmission
  
  Wire.beginTransmission(_dev_address); // start transmission to device 
  Wire.requestFrom(_dev_address, _nbytes);// send data n-bytes read
  uint8_t i = 0; 
  while (Wire.available()) {
    __buff[i] = Wire.read(); // receive DATA
    i++;
  }
  Wire.endTransmission(); // end transmission
}
