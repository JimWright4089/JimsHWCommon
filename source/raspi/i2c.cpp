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
#include <fcntl.h>
#include <iostream>
#include <fstream>
#include "loggerSingleton.h"
#include "i2c.h"

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
  mDeviceFilePointer(BAD_I2C_PORT)
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
  }
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
  LoggerSingleton::getInstance()->writeInfo("closing " + mConnection.getDevice());
  close(mDeviceFilePointer);
  mDeviceFilePointer = BAD_I2C_PORT;
}
