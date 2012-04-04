/*************************************************/
/* ADXL345.cpp -- ADXL345/I2C libary for Arduino */
/*                                               */
/* Author: Mathias Dannesbo <neic@neic.dk> and   */
/*         Carl-Emil Grøn Christensen            */
/* Time-stamp: <2012-04-04 14:28:53 (neic)>      */
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
  writemem(BW_RATE, _rate);
}

bool ADXL345::isRawDataReady()
{
  readmem(INT_SOURCE, 1, &_buff[0]);
  return(_buff[0] >> 7);
}

void ADXL345::readAccRaw(int *_AccX, int *_AccY, int *_AccZ)
{
  readmem(DATAX0, 6, &_buff[0]);
  *_AccX = _buff[1] << 8 | _buff[0];
  *_AccY = _buff[3] << 8 | _buff[2];
  *_AccZ = _buff[5] << 8 | _buff[4];
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
