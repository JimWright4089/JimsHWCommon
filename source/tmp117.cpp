//----------------------------------------------------------------------------
//
//  $Workfile: i2c.cpp$
//
//  Copyright: Jim Wright 2024
//
//  Notes:
//
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//  Includes
//----------------------------------------------------------------------------
#include <iostream>
#include "loggerSingleton.h"
#include "tmp117.h"

//----------------------------------------------------------------------------
//  Global and Static data
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//  Purpose:
//   Constructor
//
//  Notes:
//
//----------------------------------------------------------------------------
TMP117::TMP117()
{

}

//----------------------------------------------------------------------------
//  Purpose:
//   Destructor
//
//  Notes:
//
//----------------------------------------------------------------------------
TMP117::~TMP117()
{

}

//----------------------------------------------------------------------------
//  Purpose:
//   Load the config file
//
//  Notes:
//
//----------------------------------------------------------------------------
void TMP117::loadConfiguration(std::string filename)
{
  LoggerSingleton::getInstance()->writeDebug("TMP117::loadConfiguration");

  mI2CDevice.loadConfiguration(filename);
}

//----------------------------------------------------------------------------
//  Purpose:
//   Open Port
//
//  Notes:
//
//----------------------------------------------------------------------------
void TMP117::openTMP117()
{
  LoggerSingleton::getInstance()->writeDebug("TMP117::openTMP117");

  mI2CDevice.openPort();
}

//----------------------------------------------------------------------------
//  Purpose:
//   Close Port
//
//  Notes:
//
//----------------------------------------------------------------------------
void TMP117::closeTMP117()
{
  LoggerSingleton::getInstance()->writeDebug("TMP117::closeTMP117");

  mI2CDevice.closePort();
}

//----------------------------------------------------------------------------
//  Purpose:
//   Read and return Temperature in C
//
//  Notes:
//
//----------------------------------------------------------------------------
double TMP117::readC()
{
  LoggerSingleton::getInstance()->writeDebug("TMP117::readC");

  uint8_t writeBuffer[1];
  uint8_t writeLen = 0;
  uint8_t readBuffer[2] = {0};
  int readLen = 0;

  writeBuffer[0] = TMP117_TEMP_RESULT;
  writeLen = 1;
  readLen = 2;

  int returnValue = mI2CDevice.writeReadFromDevice(writeBuffer, writeLen, readBuffer,&readLen);

  if(returnValue < 0)
  {
    return 0;
  }

  int16_t temp = readBuffer[0]*0x100 + readBuffer[1];
  return (temp)*TMP117_C_CONVERSION;
}
