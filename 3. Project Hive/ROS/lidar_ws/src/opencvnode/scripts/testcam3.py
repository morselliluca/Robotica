import RPi.GPIO as gp
import os
import cv2
import numpy as np
import time
from datetime import datetime

gp.cleanup()

gp.setwarnings(True)
gp.setmode(gp.BOARD)

gp.setup(7, gp.OUT)
gp.setup(11, gp.OUT)
gp.setup(12, gp.OUT)

i2c = "i2cset -y 1 0x70 0x00 0x05"
os.system(i2c)
gp.output(7, True)
gp.output(11, False)
gp.output(12, True)

DIM=(640, 480)
K=np.array([[317.99935415233875, 0.0, 289.6473668885689], [0.0, 319.67904906766756, 222.11549412102065], [0.0, 0.0, 1.0]])
D=np.array([[0.02328041011239981], [-0.13779629253390122], [0.16897171168971936], [-0.06494475775342826]])

currcam = 1
cap = cv2.VideoCapture("/dev/video0", cv2.CAP_V4L)


def switchCam(camera):
    global currcam
    if currcam != camera:
        currcam = camera
        if camera == 1:
            i2c = "i2cset -y 1 0x70 0x00 0x04"
            os.system(i2c)
            #gp.cleanup()
            gp.output(7, False)
            gp.output(11, False)
            gp.output(12, True)
        elif camera == 2:
            i2c = "i2cset -y 1 0x70 0x00 0x05"
            os.system(i2c)
            #gp.cleanup()
            gp.output(7, True)
            gp.output(11, False)
            gp.output(12, True)
        elif camera == 3:
            i2c = "i2cset -y 1 0x70 0x00 0x06"
            os.system(i2c)
            #gp.cleanup()
            gp.output(7, False)
            gp.output(11, True)
            gp.output(12, False)
        elif camera == 4:
            i2c = "i2cset -y 1 0x70 0x00 0x07"
            os.system(i2c)
            #gp.cleanup()
            gp.output(7, True)
            gp.output(11, True)
            gp.output(12, False)

switchCam(1)
while True:
    ret, img = cap.read()
    h,w = img.shape[:2]    
    map1, map2 = cv2.fisheye.initUndistortRectifyMap(K, D, np.eye(3), K, DIM, cv2.CV_16SC2)
    undistorted_img = cv2.remap(img, map1, map2, interpolation=cv2.INTER_LINEAR, borderMode=cv2.BORDER_CONSTANT)    
    cv2.imshow('frame',undistorted_img)
    k = cv2.waitKey(33)
    if k == 49:
        switchCam(1)
    elif k == 50:
        switchCam(2)
    elif k == 51:
        switchCam(3)
    elif k == 52:
        switchCam(4)
    elif k == 115:
        cv2.imwrite("savedimages/" + str(datetime.now()) + ".jpg", frame)


cap.release()
cv2.destroyAllWindows()
gp.cleanup()
