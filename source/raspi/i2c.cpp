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
#include <stdio.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include "loggerSingleton.h"
#include "i2c.h"

using namespace std::chrono_literals;

//----------------------------------------------------------------------------
//  Global and Static data
//----------------------------------------------------------------------------
std::mutex I2C::mI2CMutex;

//----------------------------------------------------------------------------
//  Purpose:
//   Constructor
//
//  Notes:
//
//----------------------------------------------------------------------------
I2C::I2C() :
  mDeviceFilePointer(BAD_I2C_PORT),
  mAddress(0)
{

}

//----------------------------------------------------------------------------
//  Purpose:
//   destructor
//
//  Notes:
//
//----------------------------------------------------------------------------
I2C::~I2C()
{
}

//----------------------------------------------------------------------------
//  Purpose:
//   load configuration from file
//
//  Notes:
//
//----------------------------------------------------------------------------
void I2C::loadConfiguration(std::string fileName)
{
  LoggerSingleton::getInstance()->writeDebug("I2C::loadConfiguration");

  if(false == mConnection.loadFromFile(fileName))
  {
    LoggerSingleton::getInstance()->writeError("The connection is blank");
  }

  mConnection.print();  
}

//----------------------------------------------------------------------------
//  Purpose:
//   Open the port
//
//  Notes:
//
//----------------------------------------------------------------------------
void I2C::openPort()
{
  LoggerSingleton::getInstance()->writeDebug("I2C::openPort");

  if(BAD_I2C_PORT != mDeviceFilePointer)
  {
    closePort();
  }

  LoggerSingleton::getInstance()->writeInfo("opening " + mConnection.getDevice());

  //----- OPEN THE I2C BUS -----
  mDeviceFilePointer = open(mConnection.getDevice().c_str(), O_RDWR);
  if (mDeviceFilePointer <= BAD_I2C_PORT)
  {
    LoggerSingleton::getInstance()->writeError("Failed to open " + 
      mConnection.getDevice() + " for I2C code:" + std::to_string(mDeviceFilePointer));
    mDeviceFilePointer = BAD_I2C_PORT;
    return;
  }

  mAddress = mConnection.getPort();

  int returnValue = setAddress(mAddress);

  returnValue = ioctl(mDeviceFilePointer, I2C_TIMEOUT, 10);
  std::this_thread::sleep_for(50ms);
}

//----------------------------------------------------------------------------
//  Purpose:
//   Open the port
//
//  Notes:
//
//----------------------------------------------------------------------------
void I2C::closePort()
{
  LoggerSingleton::getInstance()->writeDebug("I2C::closePort");

  LoggerSingleton::getInstance()->writeInfo("closing " + mConnection.getDevice());
  close(mDeviceFilePointer);
  mDeviceFilePointer = BAD_I2C_PORT;
}


//----------------------------------------------------------------------------
//  Purpose:
//   Open the port
//
//  Notes:
//
//----------------------------------------------------------------------------
int I2C::writeReadFromDevice(
      uint8_t *dataToWrite, int lengthToWrite, 
      uint8_t *dataRead, int *lengthRead)
{
  LoggerSingleton::getInstance()->writeDebug("I2C::writeReadToDevice");

  if(BAD_I2C_PORT == mDeviceFilePointer)
  {
    return BAD_I2C_PORT;
  }

  std::lock_guard<std::mutex> guard(mI2CMutex);

  int returnValue = rawWrite(dataToWrite, lengthToWrite);
  if(returnValue < 0)
  {
    return returnValue;
  }

  return rawRead(dataRead, lengthRead);
}

//----------------------------------------------------------------------------
//  Purpose:
//   Open the port
//
//  Notes:
//
//----------------------------------------------------------------------------
int I2C::readFromDevice(uint8_t *dataRead, int *lengthRead)
{
  LoggerSingleton::getInstance()->writeDebug("I2C::readFromDevice");

  if(BAD_I2C_PORT == mDeviceFilePointer)
  {
    return BAD_I2C_PORT;
  }

  std::lock_guard<std::mutex> guard(mI2CMutex);

  return rawRead(dataRead, lengthRead);
}

//----------------------------------------------------------------------------
//  Purpose:
//   Open the port
//
//  Notes:
//
//----------------------------------------------------------------------------
int I2C::writeToDevice(uint8_t *data, int length)
{
  LoggerSingleton::getInstance()->writeDebug("I2C::writeFromDevice");

  if(BAD_I2C_PORT == mDeviceFilePointer)
  {
    return BAD_I2C_PORT;
  }

  std::lock_guard<std::mutex> guard(mI2CMutex);

  return rawWrite(data, length);
}

//----------------------------------------------------------------------------
//  Purpose:
//   Open the port
//
//  Notes:
//
//----------------------------------------------------------------------------
int I2C::rawRead(uint8_t *dataRead, int *lengthRead)
{
  LoggerSingleton::getInstance()->writeDebug("I2C::rawRead");

  int length = read(mDeviceFilePointer, dataRead, (size_t)*lengthRead);
  //----- READ BYTES -----
  if (*lengthRead != length)
  {
    printf("Failed to read from the i2c bus.\n");
    return length;
  }

  std::this_thread::sleep_for(10ms);
  *lengthRead != length;
  return length;
}

//----------------------------------------------------------------------------
//  Purpose:
//   Open the port
//
//  Notes:
//
//----------------------------------------------------------------------------
int I2C::rawWrite(uint8_t *data, int length)
{
  LoggerSingleton::getInstance()->writeDebug("I2C::rawWrite");

  //----- WRITE BYTES -----
  int returnValue = write(mDeviceFilePointer, data, length);
  if (returnValue != length)
  {
    LoggerSingleton::getInstance()->writeError("Failed to write data " + 
      mConnection.getDevice() + " command:" + std::to_string(data[0]));
  }
  std::this_thread::sleep_for(10ms);
  return returnValue;
}

//----------------------------------------------------------------------------
//  Purpose:
//   Open the port
//
//  Notes:
//
//----------------------------------------------------------------------------
int I2C::setAddress(uint8_t address)
{
  LoggerSingleton::getInstance()->writeDebug("I2C::setAddress");

  int returnValue = ioctl(mDeviceFilePointer, I2C_SLAVE, address);

  if (returnValue < 0)
  {
    LoggerSingleton::getInstance()->writeError("Failed to set address " + 
      mConnection.getDevice() + " to:" + std::to_string(address) + 
      " code:" + std::to_string(returnValue));
  }
  std::this_thread::sleep_for(100ms);
  return returnValue;
}

//----------------------------------------------------------------------------
//  Purpose:
//   Open the port
//
//  Notes:
//
//----------------------------------------------------------------------------
uint16_t I2C::read16Register(uint8_t reg)
{
  LoggerSingleton::getInstance()->writeDebug("I2C::read16Register");

  uint8_t writeBuffer[1];
  uint8_t writeLen = 1;
  uint8_t readBuffer[2] = {0};
  int readLen = 2;

  writeBuffer[0] = reg;

  int returnValue = writeReadFromDevice(writeBuffer, writeLen, readBuffer,&readLen);

  if(returnValue < 0)
  {
    return I2C_UINT16_BAD_VALUE;
  }

  return (readBuffer[0]*0x100)+readBuffer[1];
}

//----------------------------------------------------------------------------
//  Purpose:
//   Open the port
//
//  Notes:
//
//----------------------------------------------------------------------------
int I2C::writeCommand(uint8_t command)
{
  LoggerSingleton::getInstance()->writeDebug("I2C::writeCommand");

  uint8_t writeBuffer[1];
  uint8_t writeLen = 1;
  writeBuffer[0] = command;

  return writeToDevice(writeBuffer, writeLen);
}

//----------------------------------------------------------------------------
//  Purpose:
//   Open the port
//
//  Notes:
//
//----------------------------------------------------------------------------
int I2C::writeCommandByteValue(uint8_t command, uint8_t value)
{
  LoggerSingleton::getInstance()->writeDebug("I2C::writeCommandByteValue");

  uint8_t writeBuffer[2];
  uint8_t writeLen = 2;
  writeBuffer[0] = command;
  writeBuffer[0] = value;

  return writeToDevice(writeBuffer, writeLen);
}
