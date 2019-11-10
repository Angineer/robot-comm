import serial
import time

port = serial.Serial ( '/dev/ttyACM0', 9600 )

print ( "Starting" )
time.sleep ( 2 )

print ( "Writing to port" )
port.write ( bytearray([100]) )

print ( "Reading response" )
data = port.read ( 1 )
print ( data )
