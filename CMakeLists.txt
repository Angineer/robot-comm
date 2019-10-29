cmake_minimum_required ( VERSION 2.6 )
project ( robot-comm )

# Need threads
find_package ( Threads )

# Cereal dependency
set ( CEREAL_INCLUDE_FOLDER "../cereal/include" CACHE FILEPATH "Cereal include folder" )

# Robie library
add_library ( robot-comm SHARED
                           ./src/Arduino.cpp
                           ./src/BluetoothSocket.cpp
                           ./src/Client.cpp
                           ./src/Command.cpp
                           ./src/Error.cpp
                           ./src/IpSocket.cpp
                           ./src/Message.cpp
                           ./src/Order.cpp
                           ./src/Server.cpp
                           ./src/Update.cpp )
set_property ( TARGET robot-comm PROPERTY CXX_STANDARD 11 )

install ( TARGETS robot-comm LIBRARY DESTINATION /usr/lib )
target_include_directories ( robot-comm PUBLIC ./include 
                                               ${CEREAL_INCLUDE_FOLDER} )
target_link_libraries ( robot-comm ${CMAKE_THREAD_LIBS_INIT} bluetooth )
