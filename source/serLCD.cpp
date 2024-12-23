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
#include "serLCD.h"

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
SerLCD::SerLCD()
{

}

//----------------------------------------------------------------------------
//  Purpose:
//   Destructor
//
//  Notes:
//
//----------------------------------------------------------------------------
SerLCD::~SerLCD()
{

}

//----------------------------------------------------------------------------
//  Purpose:
//   Load the config file
//
//  Notes:
//
//----------------------------------------------------------------------------
void SerLCD::loadConfiguration(std::string filename)
{
  LoggerSingleton::getInstance()->writeDebug("SerLCD::loadConfiguration");

  mI2CDevice.loadConfiguration(filename);
}

//----------------------------------------------------------------------------
//  Purpose:
//   Open Port
//
//  Notes:
//
//----------------------------------------------------------------------------
void SerLCD::openSerLCD()
{
  LoggerSingleton::getInstance()->writeDebug("SerLCD::openSerLCD");

  mI2CDevice.openPort();
}

//----------------------------------------------------------------------------
//  Purpose:
//   Close Port
//
//  Notes:
//
//----------------------------------------------------------------------------
void SerLCD::closeSerLCD()
{
  LoggerSingleton::getInstance()->writeDebug("SerLCD::closeSerLCD");

  mI2CDevice.closePort();
}

//----------------------------------------------------------------------------
//  Purpose:
//   Read and return Temperature in C
//
//  Notes:
//
//----------------------------------------------------------------------------
int SerLCD::writeText(uint8_t* text, int length)
{
  LoggerSingleton::getInstance()->writeDebug("SerLCD::writeText");

  for(int i=0;i<length;i++)
  {
    uint8_t writeBuffer[1];
    uint8_t writeLen = 0;

    if('|' == text[i])
    {
      writeBuffer[0] = '|';
      writeLen = 1;

      int returnValue = mI2CDevice.writeToDevice(writeBuffer, writeLen);

      if(returnValue <= 0)
      {
        LoggerSingleton::getInstance()->writeError("Write Text code:"+std::to_string(returnValue));
        return returnValue;
      }
    }
    writeBuffer[0] = text[i];
    writeLen = 1;

    int returnValue = mI2CDevice.writeToDevice(writeBuffer, writeLen);

    if(returnValue <= 0)
    {
      LoggerSingleton::getInstance()->writeError("Write Text code:"+std::to_string(returnValue));
      return returnValue;
    }
  }

  return length;
}

//----------------------------------------------------------------------------
//  Purpose:
//   Read and return Temperature in C
//
//  Notes:
//
//----------------------------------------------------------------------------
int SerLCD::clearAll()
{
  LoggerSingleton::getInstance()->writeDebug("SerLCD::clearAll");

  uint8_t writeBuffer[3];
  uint8_t writeLen = 0;

  writeBuffer[0] = SETTING_COMMAND;
  writeBuffer[1] = CLEAR_COMMAND;
  writeLen = 2;

  int returnValue = mI2CDevice.writeToDevice(writeBuffer, writeLen);

  if(returnValue <= 0)
  {
    LoggerSingleton::getInstance()->writeError("Clear LCD code:"+std::to_string(returnValue));
  }
  return returnValue;
}

//----------------------------------------------------------------------------
//  Purpose:
//   Read and return Temperature in C
//
//  Notes:
//
//----------------------------------------------------------------------------
int SerLCD::moveCursor(int x, int y)
{
  LoggerSingleton::getInstance()->writeDebug("SerLCD::moveCursor");

  uint8_t writeBuffer[3];
  uint8_t writeLen = 0;

  writeBuffer[0] = SPECIAL_COMMAND;
  writeBuffer[1] = 128 + (64*y) + x;
  writeLen = 2;

  int returnValue = mI2CDevice.writeToDevice(writeBuffer, writeLen);

  if(returnValue <= 0)
  {
    LoggerSingleton::getInstance()->writeError("Set LCD location:"+std::to_string(returnValue));
  }
  return returnValue;
}

//----------------------------------------------------------------------------
//  Purpose:
//   Read and return Temperature in C
//
//  Notes:
//
//----------------------------------------------------------------------------
int SerLCD::setBlacklight(uint8_t red, uint8_t green, uint8_t blue)
{
  LoggerSingleton::getInstance()->writeDebug("SerLCD::setBlacklight");

  uint8_t writeBuffer[7];
  uint8_t writeLen = 6;

  writeBuffer[0] = SETTING_COMMAND;
  writeBuffer[1] = BACKLIGHT_RED + red;
  writeBuffer[2] = SETTING_COMMAND;
  writeBuffer[3] = BACKLIGHT_GREEN + green;
  writeBuffer[4] = SETTING_COMMAND;
  writeBuffer[5] = BACKLIGHT_BLUE + blue;

  int returnValue = mI2CDevice.writeToDevice(writeBuffer, writeLen);

  if(returnValue <= 0)
  {
    LoggerSingleton::getInstance()->writeError("Set LCD Backlight:"+std::to_string(returnValue));
  }
  return returnValue;
}

//----------------------------------------------------------------------------
//  Purpose:
//   Read and return Temperature in C
//
//  Notes:
//
//----------------------------------------------------------------------------
int SerLCD::reset()
{
  LoggerSingleton::getInstance()->writeDebug("SerLCD::reset");

  uint8_t writeBuffer[3];
  uint8_t writeLen = 0;

  writeBuffer[0] = SETTING_COMMAND;
  writeBuffer[1] = RESET_COMMAND;
  writeLen = 2;

  int returnValue = mI2CDevice.writeToDevice(writeBuffer, writeLen);

  if(returnValue <= 0)
  {
    LoggerSingleton::getInstance()->writeError("Reset LCD location:"+std::to_string(returnValue));
  }
  return returnValue;
}

//----------------------------------------------------------------------------
//  Purpose:
//   Read and return Temperature in C
//
//  Notes:
//
//----------------------------------------------------------------------------
int SerLCD::setContrast(uint8_t light)
{
  LoggerSingleton::getInstance()->writeDebug("SerLCD::setContrast");

  uint8_t writeBuffer[3];
  uint8_t writeLen = 0;

  writeBuffer[0] = SETTING_COMMAND;
  writeBuffer[1] = CONTRAST_COMMAND;
  writeBuffer[2] = light;
  writeLen = 3;

  int returnValue = mI2CDevice.writeToDevice(writeBuffer, writeLen);

  if(returnValue <= 0)
  {
    LoggerSingleton::getInstance()->writeError("Set Contrast code::"+std::to_string(returnValue));
  }
  return returnValue;
}

