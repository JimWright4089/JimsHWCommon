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
#ifndef ADS1015_H
#define ADS1015_H

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
class ADS1015
{
  public:

    const uint16_t ADS1015_BAD_VALUE = 65535;
    const uint16_t ADS1015_TIMEOUT   = 65534;
    //----------------------------------------------------------------------------
    //  Class Methods
    //----------------------------------------------------------------------------
    ADS1015();  
    ~ADS1015();
    void loadConfiguration(std::string filename);
    void openADS1015();
    void closeADS1015();
    uint16_t readPort(uint8_t port);

  protected:
    //----------------------------------------------------------------------------
    //  Class constants
    //----------------------------------------------------------------------------

    const uint16_t ADS1015_CONFIG_OS_SINGLE = 0x8000;	// 1 : Start a single conversion (when in power-down state)
    const uint16_t ADS1015_CONFIG_CQUE_NONE = 0x0003;	 // Disable the comparator and put ALERT/RDY in high state (default)
    const uint16_t ADS1015_CONFIG_MUX_SINGLE_0 = 0x4000;
    const uint16_t ADS1015_CONFIG_MUX_SINGLE_1 = 0x5000;
    const uint16_t ADS1015_CONFIG_MUX_SINGLE_2 = 0x6000;
    const uint16_t ADS1015_CONFIG_MUX_SINGLE_3 = 0x7000;
    const uint16_t ADS1015_POINTER_CONFIG = 0x01;
    const uint16_t ADS1015_POINTER_CONVERT = 0x00;
    const uint16_t ADS1015_CONFIG_OS_NO = 0x0000;
    const uint16_t ADS1015_CONFIG_OS_NOTREADY = 0x0000; // 0 : Device is currently performing a conversion
    const uint16_t ADS1015_CONFIG_OS_READY = 0x8000;	// 1 : Device is not currently performing a conversion
    const uint16_t ADS1015_CONFIG_RATE_250HZ = 0x0020;
    const uint16_t ADS1015_CONFIG_MODE_SINGLE = 0x0100;
    const uint16_t TIMEOUT_COUNT = 5;

#ifdef JUNK
#define ADS1015_POINTER_LOWTHRESH (0x02)
#define ADS1015_POINTER_HITHRESH (0x03)

#define ADS1015_CONFIG_OS_NO (0x0000)
#define ADS1015_CONFIG_OS_NOTREADY (0x0000) // 0 : Device is currently performing a conversion
#define ADS1015_CONFIG_OS_READY (0x8000)	// 1 : Device is not currently performing a conversion

#define ADS1015_CONFIG_MODE_CONT (0x0000)

#define ADS1015_CONFIG_MUX_DIFF_P0_N1 (0x0000)
#define ADS1015_CONFIG_MUX_DIFF_P0_N3 (0x1000)
#define ADS1015_CONFIG_MUX_DIFF_P1_N3 (0x2000)
#define ADS1015_CONFIG_MUX_DIFF_P2_N3 (0x3000)

#define ADS1015_CONFIG_RATE_MASK (0x00E0)
#define ADS1015_CONFIG_RATE_128HZ (0x0000)
#define ADS1015_CONFIG_RATE_490HZ (0x0040)
#define ADS1015_CONFIG_RATE_920HZ (0x0060)
#define ADS1015_CONFIG_RATE_1600HZ (0x0080)
#define ADS1015_CONFIG_RATE_2400HZ (0x00A0)
#define ADS1015_CONFIG_RATE_3300HZ (0x00C0)

#define ADS1015_CONFIG_PGA_MASK (0X0E00)
#define ADS1015_CONFIG_PGA_TWOTHIRDS (0X0000) // +/- 6.144v
#define ADS1015_CONFIG_PGA_1 (0X0200)		  // +/- 4.096v
#define ADS1015_CONFIG_PGA_2 (0X0400)		  // +/- 2.048v
#define ADS1015_CONFIG_PGA_4 (0X0600)		  // +/- 1.024v
#define ADS1015_CONFIG_PGA_8 (0X0800)		  // +/- 0.512v
#define ADS1015_CONFIG_PGA_16 (0X0A00)		  // +/- 0.256v

#define ADS1015_CONFIG_CMODE_TRAD (0x0000)	 // Traditional comparator with hysteresis (default)
#define ADS1015_CONFIG_CMODE_WINDOW (0x0010) // Window comparator
#define ADS1015_CONFIG_CPOL_ACTVLOW (0x0000) // ALERT/RDY pin is low when active (default)
#define ADS1015_CONFIG_CPOL_ACTVHI (0x0008)	 // ALERT/RDY pin is high when active
#define ADS1015_CONFIG_CLAT_NONLAT (0x0000)	 // Non-latching comparator (default)
#define ADS1015_CONFIG_CLAT_LATCH (0x0004)	 // Latching comparator
#define ADS1015_CONFIG_CQUE_1CONV (0x0000)	 // Assert ALERT/RDY after one conversions
#define ADS1015_CONFIG_CQUE_2CONV (0x0001)	 // Assert ALERT/RDY after two conversions
#define ADS1015_CONFIG_CQUE_4CONV (0x0002)	 // Assert ALERT/RDY after four conversions
#endif


    //----------------------------------------------------------------------------
    //  Class Atributes
    //----------------------------------------------------------------------------
    I2C mI2CDevice;

    //----------------------------------------------------------------------------
    //  Class Methods
    //----------------------------------------------------------------------------
    bool available();
};
#endif
