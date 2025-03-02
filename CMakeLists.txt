cmake_minimum_required(VERSION 3.10)

project(JimsHWCommon)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
find_package(jsoncpp REQUIRED)

# Find Boost libs.


SET(Boost_USE_STATIC_LIBS ON)
FIND_PACKAGE( Boost 1.74.0 COMPONENTS program_options REQUIRED )
FIND_PACKAGE( Boost 1.74.0 COMPONENTS thread log log_setup REQUIRED )
find_package(Threads)
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
INCLUDE_DIRECTORIES( ../JimsCommon/include )
INCLUDE_DIRECTORIES( ./include )

add_executable(i2cTest
../JimsCommon/source/randomSingleton.cpp
../JimsCommon/source/connection.cpp
../JimsCommon/source/logger.cpp
../JimsCommon/source/loggerSingleton.cpp
./source/raspi/i2c.cpp
./test/i2cTest.cpp
)
target_link_libraries(i2cTest jsoncpp ${Boost_LIBRARIES})

add_executable(tmp117Test
../JimsCommon/source/randomSingleton.cpp
../JimsCommon/source/connection.cpp
../JimsCommon/source/logger.cpp
../JimsCommon/source/loggerSingleton.cpp
./source/raspi/i2c.cpp
./source/tmp117.cpp
./test/tmp117Test.cpp
)
target_link_libraries(tmp117Test jsoncpp ${Boost_LIBRARIES})

add_executable(ads1015Test
../JimsCommon/source/randomSingleton.cpp
../JimsCommon/source/connection.cpp
../JimsCommon/source/logger.cpp
../JimsCommon/source/loggerSingleton.cpp
./source/raspi/i2c.cpp
./source/ads1015.cpp
./test/ads1015Test.cpp
)
target_link_libraries(ads1015Test jsoncpp ${Boost_LIBRARIES})

add_executable(lcdTest
../JimsCommon/source/randomSingleton.cpp
../JimsCommon/source/connection.cpp
../JimsCommon/source/logger.cpp
../JimsCommon/source/loggerSingleton.cpp
./source/raspi/i2c.cpp
./source/serLCD.cpp
./test/lcdTest.cpp
)
target_link_libraries(lcdTest jsoncpp ${Boost_LIBRARIES})


