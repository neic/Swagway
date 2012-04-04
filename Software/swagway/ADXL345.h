/*************************************************/
/* ADXL345.h -- ADXL345/I2C libary for Arduino   */
/*                                               */
/* Author: Mathias Dannesbo <neic@neic.dk> and   */
/*         Carl-Emil Grøn Christensen            */
/* Time-stamp: <2012-04-04 17:37:05 (neic)>      */
/* Part of the Swagway project                   */
/* https://github.com/neic/Swagway               */
/*                                               */
/* Inspired by the ITG3200 Arduino library at    */
/* http://code.google.com/p/itg-3200driver       */
/*************************************************/

#ifndef ADXL345_h
#define ADXL345_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define ADXL345_ADDR_SD0_HIGH 0x1D
#define ADXL345_ADDR_SD0_LOW 0x53

// Registers
#define BW_RATE        0x2C // RW SETUP: Output rate and low power mode
#define POWER_CTL      0x2D // RW SETUP: Power control
#define INT_SOURCE     0x30 // R  INTERRUPT: Status
#define DATA_FORMAT    0x31 // RW SETUP: Self-test and data format
#define DATAX0         0x32 // R  SENSOR: Data

// Bitmaps
#define STANDBY_MODE   0x00 // 0000 0000
#define MEASURE_MODE   0x08 // 0000 1000

class ADXL345
{
 public:
  float scaleFactor[3];
  float voltage;
  
  ADXL345();

  void init(unsigned int address);

  // SETUP: Mode
  void setStandbyMode();
  void setMeasureMode();

  // SETUP: Output Rate
  byte getOutputRate();
  void setOutputRate(byte _SampleRate);

  // SETUP: Data format
  bool getFullRes();
  void setFullRes(bool fullRes);
  int getRange();
  void setRange(int range);
  
  // INTERRUPT
  bool isRawDataReady();

  // SETUP: Data processing
  void setVoltage(float _voltage);
  void updateScaleFactor();
  
  // SENSOR: Read
  void readAccRaw(int *_AccX, int *_AccY, int *_AccZ);
  void readAcc(float *_AccX, float *_AccY, float *_AccZ);

  void writemem(uint8_t _addr, uint8_t _val);
  void readmem(uint8_t _addr, uint8_t _nbytes, uint8_t __buff[]);
  
 private:
  uint8_t _dev_address;
  uint8_t _buff[6];
};

#endif /* ADXL345_h */


