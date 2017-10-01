from DriveRobot import DriveRobot
import kbhit

keyPress = kbhit.KBHit()
robot = DriveRobot()



print "w => forward"
print "z => backward"
print "a => trun left"
print "d => turn right"
print "s => stop robot"
print "t => talk"
print "q => quit"

print "Press desired key"

while True:
	if keyPress.kbhit():
		key = keyPress.getch()
		robot.deciscion(key)
