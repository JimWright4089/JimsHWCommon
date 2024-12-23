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
#include <chrono>
#include <thread>
#include "loggerSingleton.h"
#include "ads1015.h"

using namespace std::chrono_literals;

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
ADS1015::ADS1015()
{

}

//----------------------------------------------------------------------------
//  Purpose:
//   Destructor
//
//  Notes:
//
//----------------------------------------------------------------------------
ADS1015::~ADS1015()
{

}

//----------------------------------------------------------------------------
//  Purpose:
//   Load the config file
//
//  Notes:
//
//----------------------------------------------------------------------------
void ADS1015::loadConfiguration(std::string filename)
{
  LoggerSingleton::getInstance()->writeDebug("ADS1015::loadConfiguration");

  mI2CDevice.loadConfiguration(filename);
}

//----------------------------------------------------------------------------
//  Purpose:
//   Open Port
//
//  Notes:
//
//----------------------------------------------------------------------------
void ADS1015::openADS1015()
{
  LoggerSingleton::getInstance()->writeDebug("ADS1015::openADS1015");

  mI2CDevice.openPort();
}

//----------------------------------------------------------------------------
//  Purpose:
//   Close Port
//
//  Notes:
//
//----------------------------------------------------------------------------
void ADS1015::closeADS1015()
{
  LoggerSingleton::getInstance()->writeDebug("ADS1015::closeADS1015");

  mI2CDevice.closePort();
}

//----------------------------------------------------------------------------
//  Purpose:
//   Read and return Temperature in C
//
//  Notes:
//
//----------------------------------------------------------------------------
uint16_t ADS1015::readPort(uint8_t port)
{
  LoggerSingleton::getInstance()->writeDebug("ADS1015::readPort");

  uint8_t writeBuffer[3];
  uint8_t writeLen = 0;
  uint8_t readBuffer[2] = {0};
  int readLen = 0;

  if (port > 3)
  {
    return ADS1015_BAD_VALUE;
  }

  uint16_t config = ADS1015_CONFIG_OS_SINGLE |
                    ADS1015_CONFIG_CQUE_NONE |
                    ADS1015_CONFIG_RATE_250HZ;

  config |= ADS1015_CONFIG_MODE_SINGLE;

  switch (port)
  {
  case (0):
    config |= ADS1015_CONFIG_MUX_SINGLE_0;
    break;
  case (1):
    config |= ADS1015_CONFIG_MUX_SINGLE_1;
    break;
  case (2):
    config |= ADS1015_CONFIG_MUX_SINGLE_2;
    break;
  case (3):
    config |= ADS1015_CONFIG_MUX_SINGLE_3;
    break;
  }

  writeBuffer[0] = ADS1015_POINTER_CONFIG;
  writeBuffer[1] = (config>>8)&0xFF;
  writeBuffer[2] = (config)&0xFF;;
  writeLen = 3;

  mI2CDevice.writeToDevice(writeBuffer, writeLen);

  uint8_t timeoutCount = 0;

  while (!available())
  {
    LoggerSingleton::getInstance()->writeInfo("Wait for data available count:"+
      std::to_string(timeoutCount));
    timeoutCount++;
    if(timeoutCount > TIMEOUT_COUNT)
    {
      return ADS1015_TIMEOUT;
    }
    std::this_thread::sleep_for(10ms);
  }

  uint16_t value = mI2CDevice.read16Register(ADS1015_POINTER_CONVERT);
  if(I2C::I2C_UINT16_BAD_VALUE == value)
  {
    return false;
  }

  value = value >> 4;
  return value;
}

//----------------------------------------------------------------------------
//  Purpose:
//   Read and return Temperature in C
//
//  Notes:
//
//----------------------------------------------------------------------------
bool ADS1015::available()
{
  LoggerSingleton::getInstance()->writeDebug("ADS1015::available");

  uint16_t value = mI2CDevice.read16Register(ADS1015_POINTER_CONFIG);
  if(I2C::I2C_UINT16_BAD_VALUE == value)
  {
    return false;
  }

  return ((value & ADS1015_CONFIG_OS_READY) > 0); // If the OS bit is 1 : the device is not currently performing a conversion (i.e. data is available)
}
