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
#include <chrono>
#include <thread>
#include <unistd.h> 
#include "loggerSingleton.h"
#include "connection.h"
#include "tmp117.h"

using namespace std::chrono_literals;

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
  LoggerSingleton::getInstance()->setFilename("tmp117Test",true);
  LoggerSingleton::getInstance()->setSeverity(SEVERITY_DEBUG);

  if(argc != 3)
  {
    LoggerSingleton::getInstance()->writeError("Usage: tmp117Test <temp1 file> <temp2 file> ");
    return -1;
  }

  std::string temp1Filename(argv[1]);
  std::string temp2Filename(argv[2]);

  TMP117 temp1;
  TMP117 temp2;
  
  temp1.loadConfiguration(temp1Filename);
  temp1.openTMP117();
  temp2.loadConfiguration(temp2Filename);
  temp2.openTMP117();

  for(int i=0;i<100;i++)
  {
    double tempC = temp1.readC();
    LoggerSingleton::getInstance()->writeInfo("Temp 1 Read ="+std::to_string(tempC));

    tempC = temp2.readC();
    LoggerSingleton::getInstance()->writeInfo("Temp 2 Read ="+std::to_string(tempC));

    std::this_thread::sleep_for(50ms);
  }
  temp1.closeTMP117();
  temp2.closeTMP117();
  return rc;
}

