//----------------------------------------------------------------------------
//
//  Workfile: i2c.h
//
//  Copyright: Jim Wright 2024
//
//  Notes:
//     This is the I2C interface header
//     Include the correct hardware source file
//
//----------------------------------------------------------------------------
#ifndef I2C_H
#define I2C_H

//----------------------------------------------------------------------------
//  Includes
//----------------------------------------------------------------------------
#include <string>
#include <mutex>
#include "connection.h"

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
class I2C
{
  public:
    //----------------------------------------------------------------------------
    //  Class constants
    //----------------------------------------------------------------------------
    static const uint16_t I2C_UINT16_BAD_VALUE = 65535;

    //----------------------------------------------------------------------------
    //  Class Methods
    //----------------------------------------------------------------------------
    I2C();  
    ~I2C();
    void loadConfiguration(std::string fileName);
    void openPort();
    void closePort();
    uint16_t read16Register(uint8_t reg);
    int writeCommand(uint8_t command);
    int writeCommandByteValue(uint8_t command, uint8_t value);
    int writeReadFromDevice(uint8_t *dataToWrite, int lengthToWrite, uint8_t *dataRead, int *lengthRead);
    int readFromDevice(uint8_t *dataRead, int *lengthRead);
    int writeToDevice(uint8_t *data, int length);

  protected:
    //----------------------------------------------------------------------------
    //  Class constants
    //----------------------------------------------------------------------------
    const int BAD_I2C_PORT = -1;

    //----------------------------------------------------------------------------
    //  Class Atributes
    //----------------------------------------------------------------------------
    Connection mConnection;
    static std::mutex mI2CMutex;
    int mDeviceFilePointer;
    int mAddress;

    //----------------------------------------------------------------------------
    //  Class Methods
    //----------------------------------------------------------------------------
    int rawRead(uint8_t *dataRead, int *lengthRead);
    int rawWrite(uint8_t *data, int length);
    int setAddress(uint8_t address);
};
#endif
