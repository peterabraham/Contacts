cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(ContactsClient)


# specify the c++ standard
set(CMAKE_CXX_STANDARD 11)

## load in pkg-config support
find_package(PkgConfig)
## use pkg-config to get hints for 0mq locations
pkg_check_modules(PC_ZeroMQ QUIET zmq)


## use the hint from above to find where 'zmq.hpp' is located
find_path(ZeroMQ_INCLUDE_DIR
        NAMES zmq.hpp
        PATHS ${PC_ZeroMQ_INCLUDE_DIRS}
        )

## use the hint from about to find the location of libzmq
find_library(ZeroMQ_LIBRARY
        NAMES zmq
        PATHS ${PC_ZeroMQ_LIBRARY_DIRS}
        )
       
SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "/usr/local/Cellar/boost/1.78.0_1/include")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "/usr/local/Cellar/boost/1.78.0_1/lib")
FIND_PACKAGE(Boost)
IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()

## Source & header files
add_executable("${PROJECT_NAME}"
"Contact.h"
"CommunicationManager.h"
"ContactsManager.h"
"Queue.h"

"client.cpp"
"CommunicationManager.cpp"
"ContactsManager.cpp")

## add the include directory to our compile directives
target_include_directories(${PROJECT_NAME} PUBLIC ${ZeroMQ_INCLUDE_DIR})

## at the 0mq library to our link directive
target_link_libraries(${PROJECT_NAME} PUBLIC ${ZeroMQ_LIBRARY} ${Boost_PROGRAM_OPTIONS_LIBRARY})

