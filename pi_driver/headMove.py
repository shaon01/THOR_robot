from time import sleep
import serial
import struct
serialCom = serial.Serial('/dev/ttyAMA0', 9600,timeout =0.1) # Establish the connection on a specific port
serialCom.flush()


def moveHead():
	headAngle =  0
	while(headAngle <90):
		serialCom.write(struct.pack('!cc','h',chr(headAngle)))
		headAngle = headAngle + 5
		print 'going from right to left : ', headAngle
		sleep(0.5)

	while(headAngle > 0):
		serialCom.write(struct.pack('!cc','h',chr(headAngle)))
		headAngle = headAngle - 5
		print 'going from right to left : ', headAngle
		sleep(0.5)
	serialCom.write(struct.pack('!cc','h',chr(30)))

def moveBase():
	baseAngle = 0 
	while(baseAngle < 160):
		serialCom.write(struct.pack('!cc','b',chr(baseAngle)))
		baseAngle = baseAngle + 5
		print 'moving base' , baseAngle
		sleep(0.5)
	
	while(baseAngle > 0 ):
		serialCom.write(struct.pack('!cc','b',chr(baseAngle)))
		baseAngle = baseAngle - 5
		sleep(0.5)

	serialCom.write(struct.pack('!cc','b',chr(100)))


if __name__ == "__main__":
	moveHead()
	sleep(0.5)
	print 'now going to move base'
	moveBase()     
    


