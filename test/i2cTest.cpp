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
#include <unistd.h>				//Needed for I2C port
#include <fcntl.h>				//Needed for I2C port
#include <sys/ioctl.h>			//Needed for I2C port
#include <linux/i2c-dev.h>		//Needed for I2C port
#include <unistd.h> 
#include "loggerSingleton.h"
#include "connection.h"
#include "i2c.h"

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
  LoggerSingleton::getInstance()->setFilename("i2cTest",true);
  LoggerSingleton::getInstance()->setSeverity(SEVERITY_DEBUG);

  if(argc != 3)
  {
    LoggerSingleton::getInstance()->writeError("Usage: i2cTest <temp1 file> <temp2 file> ");
    return -1;
  }

  std::string temp1Filename(argv[1]);
  std::string temp2Filename(argv[2]);

  I2C temp1I2C;
  I2C temp2I2C;

  temp1I2C.loadConfiguration(temp1Filename);
  temp1I2C.openPort();
  temp2I2C.loadConfiguration(temp2Filename);
  temp2I2C.openPort();

  const uint8_t TMP117_TEMP_RESULT = 0X00;

  uint8_t writeBuffer[10];
  uint8_t writeLen = 0;
  uint8_t readBuffer[10] = {0};
  int readLen = 0;

  writeBuffer[0] = 0x00;
  writeLen = 1;
  readLen = 2;

  int returnValue = 0;

  for(int i=0;i<100;i++)
  {
    returnValue = temp1I2C.writeReadFromDevice(writeBuffer, writeLen, readBuffer,&readLen);
    int16_t temp = readBuffer[0]*0x100 + readBuffer[1];
    double tempC = (temp)*0.0078;
    LoggerSingleton::getInstance()->writeInfo("Temp 1 Read ="+std::to_string(tempC));

    returnValue = temp2I2C.writeReadFromDevice(writeBuffer, writeLen, readBuffer,&readLen);
    temp = readBuffer[0]*0x100 + readBuffer[1];
    tempC = (temp)*0.0078;
    LoggerSingleton::getInstance()->writeInfo("Temp 2 Read ="+std::to_string(tempC));


//    LoggerSingleton::getInstance()->writeInfo("Read returnValue="+std::to_string(returnValue));
//    LoggerSingleton::getInstance()->writeInfo("Read length="+std::to_string(readLen));
//    LoggerSingleton::getInstance()->writeInfo("Read ="+std::to_string(readBuffer[0])+" "+std::to_string(readBuffer[1]));

    std::this_thread::sleep_for(100ms);
  }
  temp1I2C.closePort();
  temp2I2C.closePort();
  return rc;
}

#ifdef JUNK
int mainx(int argc, char* argv[])
{
	int file_i2c;
	int length;
	unsigned char buffer[60] = {0};

	
	//----- OPEN THE I2C BUS -----
	char *filename = (char*)"/dev/i2c-1";
	if ((file_i2c = open(filename, O_RDWR)) < 0)
	{
		//ERROR HANDLING: you can check errno to see what went wrong
		printf("Failed to open the i2c bus");
		return 0;
	}
	
	int addr = 0x49;          //<<<<<The I2C address of the slave
	if (ioctl(file_i2c, I2C_SLAVE, addr) < 0)
	{
		printf("Failed to acquire bus access and/or talk to slave.\n");
		//ERROR HANDLING; you can check errno to see what went wrong
		return 0;
	}
	

	//----- WRITE BYTES -----
	buffer[0] = 0x00;
//	buffer[1] = 0x02;
	length = 1;			//<<< Number of bytes to write
	if (write(file_i2c, buffer, length) != length)		//write() returns the number of bytes actually written, if it doesn't match then an error occurred (e.g. no response from the device)
	{
		/* ERROR HANDLING: i2c transaction failed */
		printf("Failed to write to the i2c bus.\n");
	}

	//----- READ BYTES -----
	length = 2;			//<<< Number of bytes to read
	if (read(file_i2c, buffer, length) != length)		//read() returns the number of bytes actually read, if it doesn't match then an error occurred (e.g. no response from the device)
	{
		//ERROR HANDLING: i2c transaction failed
		printf("Failed to read from the i2c bus.\n");
	}
	else
	{
		printf("Data read: %d\n", buffer[0]*0x100+buffer[1]);
	}
  return 0;
}
#endif	
