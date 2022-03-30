import RPi.GPIO as gp
import os
import cv2
import time

gp.cleanup()

gp.setwarnings(True)
gp.setmode(gp.BOARD)

gp.setup(7, gp.OUT)
gp.setup(11, gp.OUT)
gp.setup(12, gp.OUT)

camera = 1
counter = 10000

i2c = "i2cset -y 1 0x70 0x00 0x05"
os.system(i2c)
gp.output(7, True)
gp.output(11, False)
gp.output(12, True)

cap = cv2.VideoCapture("/dev/video0", cv2.CAP_V4L)


def switchCam(camera):
	global counter
	if camera == 1:
		i2c = "i2cset -y 1 0x70 0x00 0x04"
		os.system(i2c)
		#gp.cleanup()
		gp.output(7, False)
		gp.output(11, False)
		gp.output(12, True)
		if counter == 0:
			counter = 10000
			return 0
		else:
			counter -= 1
	else:
		i2c = "i2cset -y 1 0x70 0x00 0x05"
		os.system(i2c)
		#gp.cleanup()
		gp.output(7, True)
		gp.output(11, False)
		gp.output(12, True)
		if counter == 0:
			counter = 10000
			return 1
		else:
			counter -= 1

while True:
    #camera = switchCam(camera)
    #print(counter)
    #time.sleep(0.1)
    ret, frame = cap.read()
    cv2.imshow('frame',frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
gp.cleanup()
