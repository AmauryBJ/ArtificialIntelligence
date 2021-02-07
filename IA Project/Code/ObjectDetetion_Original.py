#For Robot
from jetbot import Robot
robot = Robot()
robotSpeed = 0.4
robot.stop()

import jetson.inference
import jetson.utils

net = jetson.inference.detectNet("ssd-mobilenet-v2", threshold=0.5)
#camera = jetson.utils.videoSource("csi://0")      # '/dev/video0' for V4L2
camera = jetson.utils.videoSource("/dev/video1")      # '/dev/video0' for V4L2
display = jetson.utils.videoOutput("display://0") # 'my_video.mp4' for file
#display = jetson.utils.videoOutput("rtp://192.168.1.169:1234") # 'my_video.mp4' for file

index = 0
width = 0
location = 0



while display.IsStreaming():
	img = camera.Capture()
	detections = net.Detect(img)
	display.Render(img)
	display.SetStatus("Object Detection | Network {:.0f} FPS".format(net.GetNetworkFPS()))

	for detection in detections:
		index = detections[0].ClassID
		width = (detections[0].Width)
		location = (detections[0].Center[0])

	#print("detection:")
	#print(index)
	#print(width)
	#print(location)


	if(index == 1):
		if(location > 800):
			print("Right")
			robot.right(robotSpeed)
		elif(location < 400):
			print("Left")
			robot.left(robotSpeed)
		else:
			print("Stop")
			robot.stop()
	else:
		print("Stop")	
		robot.stop()
	
	# reset 
	index = 0
	width = 0
	location = 0


