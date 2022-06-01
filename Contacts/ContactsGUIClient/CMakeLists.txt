cmake_minimum_required(VERSION 3.1.0)

project(Contacts VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#set(CMAKE_PREFIX_PATH "/Users/peter/Qt/6.2.4/macos/lib/cmake")

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt6 COMPONENTS Widgets REQUIRED)

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

#SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "/usr/local/Cellar/boost/1.78.0_1/include")
#SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "/usr/local/Cellar/boost/1.78.0_1/lib")
FIND_PACKAGE(Boost)
IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()


add_executable(Contacts
    MainDialog.ui
    ContactDialog.ui

    MainDialog.h
    ContactDialog.h
    CommunicationManager.h
    ContactsManager.h
    ResponseManager.h
    Queue.h
    Contact.h

    Main.cpp
    MainDialog.cpp
    ContactDialog.cpp
    CommunicationManager.cpp  
    ContactsManager.cpp
    ResponseManager.cpp

    #resources.qrc
)

## add the include directory to our compile directives
target_include_directories(${PROJECT_NAME} PUBLIC ${ZeroMQ_INCLUDE_DIR})

## at the 0mq library to our link directive
target_link_libraries(${PROJECT_NAME} PUBLIC ${ZeroMQ_LIBRARY} ${Boost_PROGRAM_OPTIONS_LIBRARY} Qt6::Widgets)

#target_link_libraries(Contacts Qt6::Widgets)
