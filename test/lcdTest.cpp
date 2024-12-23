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
#include "serLCD.h"

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
  LoggerSingleton::getInstance()->setFilename("serLCDTest",true);
  LoggerSingleton::getInstance()->setSeverity(SEVERITY_INFO);

  if(argc != 2)
  {
    LoggerSingleton::getInstance()->writeError("Usage: serLCDTest <lcd file> ");
    return -1;
  }

  std::string lcdFilename(argv[1]);

  SerLCD serLCD;
  
  serLCD.loadConfiguration(lcdFilename);
  serLCD.openSerLCD();

  LoggerSingleton::getInstance()->writeInfo("Reset");
  serLCD.reset();

  LoggerSingleton::getInstance()->writeInfo("Set Contrast");
  serLCD.setContrast(5);

  LoggerSingleton::getInstance()->writeInfo("Set Backlight");
  serLCD.setBlacklight(1,1,1);

  LoggerSingleton::getInstance()->writeInfo("Clear All");
  serLCD.clearAll();

  LoggerSingleton::getInstance()->writeInfo("Set Backlight");
  serLCD.setBlacklight(29,29,29);
  std::this_thread::sleep_for(2000ms);

  LoggerSingleton::getInstance()->writeInfo("Print");
  serLCD.writeText((uint8_t*)"Count:",6);

  for(double i=-40.0;i<40.0;i+=.002)
  {
    char text[10];
    
    // -40.0 to 40.0
    int len = snprintf(text,10,"%5.2f    ",i);

    serLCD.moveCursor(0, 1);
    serLCD.writeText((uint8_t*)text,7);
  }

  serLCD.closeSerLCD();
  return rc;
}

