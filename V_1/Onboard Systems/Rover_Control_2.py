##############################################################################
#   WSU Mars Rover -- Joystick_Serial
#
#   Takes input from the Arduino via the serial stream and uploads the
#   command string to the online .txt file
#
#   This is for Python 2.7, not 3.4!!!
#   - ser.write doesn't handle strings the same way in 3.4
#   - changes from 3.4:
#       urllib.request is just urllib. don't parse the data from the read.
#       Comment out the html.split line and instead of printing the first 
#       element, print the whole thing so "html[0]" becomes just "html".
#
#   Written by Marcus Blaisdell and Jensen Reitz of WSU Robotics Club
#   - leveraging off of code written by Heidi Lyons and Conner Cole
#       for the Internet controlled RC Car for the Hardware Hackathon
##############################################################################

import urllib
import time
import serial

# Setup **********************************************************************

x = 0

# Custom Functions ***********************************************************

print ("Pi Home server running!")

def funct():
    try:
        response=urllib.urlopen('http://192.168.1.3/WriteLines.txt')
        html=str(response.read())[2:-1]
        print (html)
        ser.write(html)
        time.sleep(.1)
    except:
        time.sleep(.1)

# Run Program ****************************************************************        

ser = serial.Serial('/dev/ttyACM0', 115200)

while x < 10:
    # x=x+1 # uncomment if you only want it to run a limited number of times
    funct()
    
ser.close()
