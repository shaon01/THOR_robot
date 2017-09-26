import time
import struct
import serial

#create a class for driving robot where all the direction and everything is predefinied

class DriveRobot:
	
	def __init__(self): #setting up all the serial settings
		self.serl = serial.Serial("/dev/ttyAMA0",9600,timeout = 1)
		self.serl.isOpen()
	
	#call this to move forward 
	def moveForward(self): 
		self.serl.write('w')
		print "moving forward"
	
	#call this to move backward
	def moveBackward(self):
		self.serl.write('z')
		print "moving backward"

	#call this to stop the robot
	def stopRobot(self):
		self.serl.write('s')
		print "stopping the robot"
	
	#call this to turn left
	def turnLeft(self):
		self.serl.write('a')

	#call this to trun right
	def turnRight(self):
		self.serl.write('d')
	
	#<TODO> : implement a way to talking for robot
	def nowTalk(self):
		print "now in talking mode....."


	def deciscion(self,val):
		
		dicTable = {
			'w':self.moveForward,
			'z':self.moveBackward,
			'd':self.turnRight,
			'a':self.turnLeft,
			't':self.nowTalk,
			's':self.stopRobot,
			'q':exit,
			}
				
		dicTable.get(val,self.dicError)()
	
	#this is to catch error when wrong key is pressed
	def dicError(self):
		print "invalid input.........\n\n enter   w => go forward\n      z=> go backward\n       t=> to talk"
		


	

robot = DriveRobot()

if __name__=="__main__":
	
	while True:
		
		dir = raw_input('\nGive direction :')			
		robot.deciscion(dir)

		

