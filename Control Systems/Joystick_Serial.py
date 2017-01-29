##############################################################################
#   WSU Mars Rover -- Joystick_Serial
#
#   Takes input from the Arduino via the serial stream and uploads the
#   command string to the online .txt file
#
#   Written by Marcus Blaisdell and Jensen Reitz of WSU Robotics Club
##############################################################################

import serial
import time

# Setup **********************************************************************

new_str = ""
old_str = ""
#ser = serial.Serial ('/dev/ttyUSB1', 9600) # Pro-Mini w/integrated FTDI
ser = serial.Serial ('/dev/ttyACM0', 9600) # Official Arduino Uno

# Run Program ****************************************************************

while True:

    new_str = str(ser.readline(), "cp437")

    #If the new string is not similar to the old string
    #   (i.e. the commands are not the same), then print the
    #   new commands to the .txt file
    if (new_str != old_str):
        try:
            outFile = open("/var/www/html/WriteLines.txt", "w")
            #print (new_str)
            outFile.write (new_str)
            outFile.close()
    
            old_str = new_str
            time.sleep(.01)
        except:
            time.sleep(.01)
