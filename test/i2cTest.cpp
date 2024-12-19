//----------------------------------------------------------------------------
//
//  Workfile: i2cTest.cpp
//
//  Copyright: Jim Wright 2024
//
//  Notes:
//     This is the test of the I2C class
//
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//  Includes
//----------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <iostream> 
#include <unistd.h> 
#include "loggerSingleton.h"
#include "connection.h"
#include "i2c.h"

//----------------------------------------------------------------------------
//  Global and Static data
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//  Purpose:
//   Entry point
//
//  Notes:
//
//----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
  int rc = 0;
  LoggerSingleton::getInstance()->setFilename("i2cTest",true);
  LoggerSingleton::getInstance()->setSeverity(SEVERITY_DEBUG);

  if(argc != 2)
  {
    LoggerSingleton::getInstance()->writeError("Usage: i2cTest <connection file> ");
    return -1;
  }

  std::string sqlFilename(argv[1]);

  I2C testI2C;

  testI2C.loadConfiguration(sqlFilename);
  testI2C.openPort();

  testI2C.closePort();
  return rc;
}
