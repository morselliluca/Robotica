#!/usr/bin/env python
import rospy, cv2, os, pytesseract, argparse, time
from std_msgs.msg import String
import numpy as np
import RPi.GPIO as gp
from datetime import datetime
from pytesseract import Output
from imutils.object_detection import non_max_suppression
import numpy as np

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

colorRanges = [
    ([0, 5, 110], [110, 120, 255]), #red
    ([0, 120, 125], [120, 250, 255]), #yellow
    ([0, 65, 10], [90, 255, 115]) #green
]
colorNames = ["R", "Y", "G"]
lettersToFind = ["H", "S", "U"]
colorThreshold = 2500
resizedResolution = (200, 160)
#frame cut at prepare4OCR function

#parameters to overcome camera distorsion
DIM=(640, 480)
K=np.array([[317.99935415233875, 0.0, 289.6473668885689], [0.0, 319.67904906766756, 222.11549412102065], [0.0, 0.0, 1.0]])
D=np.array([[0.02328041011239981], [-0.13779629253390122], [0.16897171168971936], [-0.06494475775342826]])

#current camera being used (from 1 to 4)
currcam = 1
cap = cv2.VideoCapture("/dev/video0", cv2.CAP_V4L)

#the bonefire has been lit, but for the camera
def adjust_gamma(image, gamma=2.0):
   invGamma = 1.0 / gamma
   table = np.array([((i / 255.0) ** invGamma) * 255
      for i in np.arange(0, 256)]).astype("uint8")

   return cv2.LUT(image, table)

#switches the camera sending i2c things and setting up the gpio accordingly 
def switchCam(camera):
    global currcam
    #print("test1: " + str(camera) + " " + str(currcam))
    if currcam != camera:
        currcam = camera
        #print("test2: " + str(camera) + " " + str(currcam))
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

#get the frame, undistorts it and resizes ir
def getFrame():
    global resizedResolution, K, D, DIM
    ret, img = cap.read()
    map1, map2 = cv2.fisheye.initUndistortRectifyMap(K, D, np.eye(3), K, DIM, cv2.CV_16SC2)
    undistorted_img = cv2.remap(img, map1, map2, interpolation=cv2.INTER_LINEAR, borderMode=cv2.BORDER_CONSTANT)   
    return cv2.resize(undistorted_img, resizedResolution, interpolation= cv2.INTER_LINEAR)

#grayscale the image and add more gamma/luminance
def prepare4OCR(image):
    return adjust_gamma(cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)[40:120, 0:160])

#makes all the characters uppercase

#get all the text in theimage
def runOCR(image):
    global lettersToFind
    threshold_img = cv2.threshold(image, 0, 255, cv2.THRESH_BINARY | cv2.THRESH_OTSU)[1]
    #cv2.imshow("Letter", threshold_img)
    #cv2.waitKey(33)
    custom_config = r'--oem 3 --psm 6'
    thingsFound = pytesseract.image_to_string(threshold_img, output_type=Output.DICT, config=custom_config, lang="eng")
    thingsFound = thingsFound["text"].upper()
    if thingsFound.find(lettersToFind[0]) != -1:
        return lettersToFind[0]
    elif thingsFound.find(lettersToFind[1]) != -1:
        return lettersToFind[1]
    elif thingsFound.find(lettersToFind[2]) != -1:
        return lettersToFind[2]
    else:
        return ""

#get the color currently present in the image (creates 3 masks using the ranges and checks the number of non black pixels)
def getColor(image):
    global colorThreshold, colorNames, colorRanges
    for item in enumerate(colorRanges):
        lower = np.array(item[1][0], dtype = "uint8")
        upper = np.array(item[1][1], dtype = "uint8")
        mask = cv2.inRange(image, lower, upper)
        output = cv2.bitwise_and(image, image, mask = mask)
        #cv2.imshow("color", output)
        #cv2.waitKey(33)
        if output.shape[0]*output.shape[1]-int(np.sum(output == 0)/3) >= colorThreshold:
            #print("Color (" + str(output.shape[0]*output.shape[1]-int(np.sum(output == 0)/3)) + "): " + colorNames[item[0]])
            return colorNames[item[0]]
    return ""

def publisher():
    pubLetter = rospy.Publisher('/lettera', String, queue_size=10)
    pubColor = rospy.Publisher('/colore', String, queue_size=10)
    rospy.init_node('OpenCVNode', anonymous=True)
    rate = rospy.Rate(1)
    rospy.loginfo('OpenCVNode started')

    tmpReturn = ""
    while not rospy.is_shutdown():
        try:
            for i in range(1, 4):
                switchCam(i)
                time.sleep(0.3)
                frame = getFrame()
                #cv2.imshow("frame", frame)
                #cv2.waitKey(33)
                tmpReturn = runOCR(prepare4OCR(frame))
                if (tmpReturn != ""):
                    rospy.loginfo("Saw letter [" + tmpReturn + "]")
                    pubLetter.publish(tmpReturn)
                tmpReturn = getColor(frame)
                if (tmpReturn != ""):
                    rospy.loginfo("Saw color [" + tmpReturn + "]")
                    pubColor.publish(tmpReturn)
            rate.sleep()
        except:
            rospy.logwarn("An error occured ¯\\_(ツ)_/¯")
            continue

if __name__ == '__main__':
    try:       
        publisher()
    except: #rospy.ROSInterruptException
        rospy.logfatal("A bigger error occured")
        pass