cmake_minimum_required ( VERSION 2.6 )
project ( robot-comm )

# Need threads
find_package ( Threads )

# Cereal dependency
set ( CEREAL_INCLUDE_FOLDER "../cereal/include" CACHE FILEPATH "Cereal include folder" )

# Robie library
add_library ( robot-comm SHARED
              ./core/Arduino.cpp
              ./core/BluetoothSocket.cpp
              ./core/Client.cpp
              ./core/IpSocket.cpp
              ./core/Message.cpp
              ./core/Server.cpp

              ./msgs/Command.cpp
              ./msgs/Error.cpp
              ./msgs/Order.cpp
              ./msgs/Update.cpp )
set_property ( TARGET robot-comm PROPERTY CXX_STANDARD 14 )

install ( TARGETS robot-comm LIBRARY DESTINATION /usr/lib )
target_include_directories ( robot-comm PUBLIC ./core ./msgs 
                                               ${CEREAL_INCLUDE_FOLDER} )
target_link_libraries ( robot-comm ${CMAKE_THREAD_LIBS_INIT} bluetooth )
