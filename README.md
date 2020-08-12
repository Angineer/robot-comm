# robot-comm

Communication tools for my service robot:
- Generic client and server objects for communicating via IP or bluetooth
- Variety of message types for different tasks
- Arduino utilities
  - Objects that encapsulate serial communication
  - Scripts for uploading sketches

Dependencies:
* Cereal (https://github.com/USCiLab/cereal)

To install, clone this repo and the cereal repo so they are in the same directory. Then, build with CMake:

`cd robot-comm`\
`mkdir build && cd build`\
`cmake ..`\
`make`\
`sudo make install`

See https://www.adtme.com/projects/Robot.html for more info about the overall project.
