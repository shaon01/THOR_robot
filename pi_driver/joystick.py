
import time
import kbhit
import struct
import serial


ser = serial.Serial("/dev/ttyAMA0",9600,timeout=1)
ser.isOpen()

kb = kbhit.KBHit()

# This is the address we setup in the Arduino Program
#address = 0x04
sped = 50
last_key = 's'

def writeNumber(cmnd,val):
    #bus.write_i2c_block_data(address,cmnd,[val])# bus.write_byte_data(address, 0, value)
    #bus.write_byte(address,val)
    ser.write(cmnd)
    ser.write(chr(val))
    return -1

def readNumber():
    #number = bus.read_byte(address)
    #number = bus.read_byte_data(address, 1)
    #number = bus.read_i2c_block_data(address,0)
    number = ser.readline()
    print chr(number)
    '''
    for i in range(0, 4):
        bytes = bus.read_byte(address)
        print struct.unpack('f', "".join(map(chr, bytes)))[0]
    
    print int(''.join(map(str,number)))
    '''
   
 




while 1:
    if kb.kbhit():
        key = kb.getch()

        if key != '=' and key != '-' and key !='e' and key != 'h' and key != 'b':     
            writeNumber(key,sped)
            last_key = key
        elif key == 'h':
		print "enter degree :"
		val = int(raw_input('value for head:'))
		writeNumber(key,val)
		last_key = key
		print 'head value :',val
	elif key == 'b':
		print "enter degree :"
		val = int(raw_input('value for base:'))
		writeNumber(key,val)
		#writeNumber(val)
		last_key = key
		print 'base value :',val
	                
        elif key == '=':
            sped = min(200,sped +10)
            writeNumber(ord(last_key),sped)
            
        elif key == '-':
            sped = max(0,sped - 10)
            writeNumber(ord(last_key),sped)
            
        elif key == 'e':
            print 'encoder :'
            #readNumber()
             
            
        print 'key pressed :',key
        #print 'current direction :',last_key
        #print 'current speed :',sped
        print '~~~~~~~~~~~~~~~~~~~~~'
            
            



