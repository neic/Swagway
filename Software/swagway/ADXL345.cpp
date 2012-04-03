/*************************************************/
/* ADXL345.cpp -- ADXL345/I2C libary for Arduino */
/*                                               */
/* Author: Mathias Dannesbo <neic@neic.dk> and   */
/*         Carl-Emil Grøn Christensen            */
/* Time-stamp: <2012-04-03 20:43:45 (neic)>      */
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
