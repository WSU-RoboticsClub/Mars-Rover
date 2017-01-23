# Mars Rover python control for Raspberry Pi
# Code 1
# leveraging off of code written by Heidi Lyons and Conner Cole
# for the Internet controlled RC Car for the Hardware Hackathon

# 6/2/16

###############################################################
# 5/15/16:
#
# This is for Python 2.7, not 3.4!!!
# ser.write doesn't handle strings the same way in 3.4
#
# changes from 3.4:
#    urllib.request is just urllib.
#    don't parse the data from the read,
#       comment out the html.split line and
#       instead of printing the first element,
#       print the whole thing so "html[0]" becomes just "html"
###############################################################

#receive the data

#!/usr/bin/env/python

import urllib
import time
import serial
from   time import sleep



x = 0

print ("Pi Home server running!")

def funct():
    try:
        response=urllib.urlopen('http://192.168.1.3/WriteLines.txt')
        html=str(response.read())[2:-1]
        print (html)
        ser.write(html)
        sleep(.1)

    except:
        sleep(.1)

ser = serial.Serial('/dev/ttyACM0', 115200)

while x < 10:
    # x=x+1 # uncomment if you only want it to run a limited number of times
    funct()
    
ser.close()
