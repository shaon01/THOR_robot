import time
import struct
import serial

serialCom = serial.Serial("/dev/ttyAMA0",9600,timeout=1)
serialCom.isOpen()

while 1:
	print"\n Head = h, Base = b, Quit = q "
	servo = (raw_input("\n what do you want..."))
	
	if servo == 'h':

		degRee = int(raw_input('\n How much head to turn: '))
		
		serialCom.write(struct.pack('!cc',servo,chr(degRee)))
		
		print '\n servo => head = ',servo,'degree = ',degRee
	elif servo == 'b':

		degRee = int(raw_input('\n How much base to turn: '))
		
		serialCom.write(struct.pack('!cc',servo,chr(degRee)))

		print '\n servo => base = ',servo,'degree = ',degRee
	elif servo == 'q':

		print '\n exiting program.'
		break
	else:
		print'\n Not a head or base.'
	
	print '\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~'
	
			
