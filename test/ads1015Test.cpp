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
#include "ads1015.h"

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
  LoggerSingleton::getInstance()->setFilename("ads1015Test",true);
  LoggerSingleton::getInstance()->setSeverity(SEVERITY_INFO);

  if(argc != 2)
  {
    LoggerSingleton::getInstance()->writeError("Usage: ads1015Test <analog file>");
    return -1;
  }

  std::string analogFilename(argv[1]);

  ADS1015 analog;
  
  analog.loadConfiguration(analogFilename);
  analog.openADS1015();

  for(int i=0;i<100;i++)
  {
    uint16_t analogValue = analog.readPort(0);
    LoggerSingleton::getInstance()->writeInfo("Port 0 Read ="+std::to_string(analogValue));
    analogValue = analog.readPort(1);
    LoggerSingleton::getInstance()->writeInfo("Port 1 Read ="+std::to_string(analogValue));
    analogValue = analog.readPort(2);
    LoggerSingleton::getInstance()->writeInfo("Port 2 Read ="+std::to_string(analogValue));
    analogValue = analog.readPort(3);
    LoggerSingleton::getInstance()->writeInfo("Port 3 Read ="+std::to_string(analogValue));

    std::this_thread::sleep_for(50ms);
  }
  analog.closeADS1015();
  return rc;
}

