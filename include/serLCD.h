//----------------------------------------------------------------------------
//
//  Workfile: tmp117.h
//
//  Copyright: Jim Wright 2024
//
//  Notes:
//     This is the interface to the TMP117
//
//----------------------------------------------------------------------------
#ifndef SERLCD_H
#define SERLCD_H

//----------------------------------------------------------------------------
//  Includes
//----------------------------------------------------------------------------
#include <string>
#include <mutex>
#include "connection.h"
#include "i2c.h"

//----------------------------------------------------------------------------
//  Class Declarations
//----------------------------------------------------------------------------
//
// Class Name: I2C
// 
// Purpose:
//      Handle the I2C protocol
//
//----------------------------------------------------------------------------
class SerLCD
{
  public:
    //----------------------------------------------------------------------------
    //  Class Methods
    //----------------------------------------------------------------------------
    SerLCD();  
    ~SerLCD();
    void loadConfiguration(std::string filename);
    void openSerLCD();
    void closeSerLCD();
    int writeText(uint8_t* text, int length);
    int reset();
    int clearAll();
    int moveCursor(int x, int y);
    int setBlacklight(uint8_t red, uint8_t green, uint8_t blue);
    int setContrast(uint8_t light);

  protected:
    //----------------------------------------------------------------------------
    //  Class constants
    //----------------------------------------------------------------------------
    const uint8_t CLEAR_COMMAND = 0x2D;
    const uint8_t SPECIAL_COMMAND = 254;
    const uint8_t SETTING_COMMAND = 0x7C;  
    const uint8_t CONTRAST_COMMAND = 0x18;
    const uint8_t LCD_DISPLAYCONTROL = 0x08;
    const uint8_t LCD_DISPLAYON = 0x04;
    const uint8_t LCD_DISPLAYOFF = 0x00;
    const uint8_t RESET_COMMAND = 0x08;
    const uint8_t SET_RGB_COMMAND = 0x2B;
    const uint8_t BACKLIGHT_RED = 128;
    const uint8_t BACKLIGHT_GREEN = 158;
    const uint8_t BACKLIGHT_BLUE = 188;

    //----------------------------------------------------------------------------
    //  Class Atributes
    //----------------------------------------------------------------------------
    I2C mI2CDevice;

    //----------------------------------------------------------------------------
    //  Class Methods
    //----------------------------------------------------------------------------
};
#endif
