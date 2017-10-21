#!/usr/bin/python
'''
	Author: Guido Diepen <gdiepen@deloitte.nl>
'''

#Import the OpenCV library
import cv2

#importing PI camera stuff

from picamera.array import PiRGBArray
from picamera import PiCamera
import time
from DriveRobot import DriveRobot

#Initialize a face cascade using the frontal face haar cascade provided with
#the OpenCV library
faceCascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')

# initialize the camera and grab a reference to the raw camera capture
camera = PiCamera()
camera.resolution = (640, 480)
camera.framerate = 32
rawCapture = PiRGBArray(camera, size=(640, 480))
 
# allow the camera to warmup
time.sleep(0.1)

#The deisred output width and height
OUTPUT_SIZE_WIDTH = 320
OUTPUT_SIZE_HEIGHT = 280

robot2 = DriveRobot()



def detectLargestFace():
	#Open the first webcame device
	
	
	
	#Create two opencv named windows
	cv2.namedWindow("base-image", cv2.WINDOW_AUTOSIZE)
	cv2.namedWindow("result-image", cv2.WINDOW_AUTOSIZE)

	#Position the windows next to eachother
	#cv2.moveWindow("base-image",0,100)
	#cv2.moveWindow("result-image",400,100)

	#Start the window thread for the two windows we are using
	#cv2.startWindowThread()

	rectangleColor = (0,165,255)

	try:
		for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):
			#Retrieve the latest image from the webcam
			fullSizeBaseImage = frame.array

			#Resize the image to 320x240
			baseImage = cv2.resize( fullSizeBaseImage, ( 320, 240))


			#Check if a key was pressed and if it was Q, then destroy all
			#opencv windows and exit the application
			pressedKey = cv2.waitKey(2)
			if pressedKey == ord('Q'):
				cv2.destroyAllWindows()
				exit(0)



			#Result image is the image we will show the user, which is a
			#combination of the original image from the webcam and the
			#overlayed rectangle for the largest face	
			resultImage = baseImage.copy()


			#For the face detection, we need to make use of a gray colored
			#image so we will convert the baseImage to a gray-based image
			gray = cv2.cvtColor(baseImage, cv2.COLOR_BGR2GRAY)
			#Now use the haar cascade detector to find all faces in the
			#image
			faces = faceCascade.detectMultiScale(gray, 1.3, 5)


			#For now, we are only interested in the 'largest' face, and we
			#determine this based on the largest area of the found
			#rectangle. First initialize the required variables to 0
			maxArea = 0
			x = 0
			y = 0
			w = 0
			h = 0


			#Loop over all faces and check if the area for this face is
			#the largest so far
			for (_x,_y,_w,_h) in faces:
				if  _w*_h > maxArea:
						x = _x
						y = _y
						w = _w
						h = _h
						maxArea = w*h

				#If one or more faces are found, draw a rectangle around the
				#largest face present in the picture
				
			print "maxArea : ",maxArea
			if maxArea > 0 :
				cv2.rectangle(resultImage,  (x-10, y-20),(x + w+10 , y + h+20),rectangleColor,2)
				
			else :
				robot2.moveBase()



			

			#Finally, we want to show the images on the screen
			cv2.imshow("base-image", baseImage)
			cv2.imshow("result-image", resultImage)
			
			
			key = cv2.waitKey(1) & 0xFF
			rawCapture.truncate(0)
			if key == ord("q"):
				break

	#To ensure we can also deal with the user pressing Ctrl-C in the console
	#we have to check for the KeyboardInterrupt exception and destroy
	#all opencv windows and exit the application
	except KeyboardInterrupt as e:
		cv2.destroyAllWindows()
		exit(0)


if __name__ == '__main__':
	detectLargestFace()
