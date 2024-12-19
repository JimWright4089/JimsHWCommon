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

