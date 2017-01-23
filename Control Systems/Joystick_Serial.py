import serial
import time

new_str = ""
old_str = ""
ser = serial.Serial ('/dev/ttyUSB1', 9600) # Pro-Mini w/integrated FTDI
# ser = serial.Serial ('/dev/ttyACM0', 9600) # Official Arduino Uno

while True:

    new_str = str(ser.readline(), "cp437")

    if (new_str != old_str):
        outFile = open("/var/www/html/WriteLines.txt", "w")
        #print (new_str)
        outFile.write (new_str)
        outFile.close()

        old_str = new_str
        time.sleep(.01)

### EOF

