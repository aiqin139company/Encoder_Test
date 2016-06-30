import sys
import serial
import struct

#ser_write method
def ser_write(data):
	writeData = data
	writeBuff = struct.pack('l', writeData)
	ser.write(writeBuff)

if len(sys.argv) != 2:
	print 'Invalid usage, format is: ' 
	print '\t %s "COMx"' % (sys.argv[0])
	sys.exit()
else:
	portName = sys.argv[1]
	
ser = serial.Serial()
ser.baudrate = 230400
ser.port = portName
ser.timeout = 10.0

print "Opening serial port: " + portName
ser.open()

if not ser.is_open:
	print "Count not open serial port '%s'" % portName
else:	
	
	motorSpeed = 15
	
	#Setting motor speed
	ser_write(0xAAAA)
	print "Setting the motor speed!"
	ser_write(motorSpeed)
	
	#Starting 
	ser_write(0xA0A0)
	print "Starting the motor!"
	print "Testting encoder, please waiting 10s!"
	
	#Getting the period of speed
	sciData = ser.read(4)
	dat = (struct.unpack(">l", sciData))[0]
	dat /= 60.0
	print "The period of speed: %f us" % (dat)
	
	#waiting for read faild msg!
	sciData = ser.read(4)
	
	#timeout or faild
	if 0 == ser.inWaiting():
		print "The encoder test ok!"
	else :
		dat = (struct.unpack(">l", sciData))[0]
		if 0xFFFF == dat :
			print "The encoder test faild!"
	
	#Stopping the motor
	ser_write(0x0A0A)	
	print "Stopping the motor!"
	