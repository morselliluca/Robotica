#!/usr/bin/env python
import rospy
import tf

from nav_msgs.msg import OccupancyGrid

blackRadius = 20
foundSomethingRadius = 20

squaredBlackRadius = blackRadius**2
squaredFoundSomethingRadius = foundSomethingRadius**2

noGoPoints = []
foundSomethingPoints = []

currentPosition = None

def occupancyGridToMatrix(occupancyGrid, width, height):
    matrix = []

    for i in range(0, height):
        matrix.append([])
        for j in range(0, width):
            matrix[i].append(occupancyGrid[width * i + j])

    for point in noGoPoints:
        for i in range(point[0]-blackRadius, point[0]+blackRadius+1):
            for j in range(point[1]-blackRadius, point[1]+blackRadius+1):
                if (i-point[0])**2 + (j-point[1])**2 <= squaredBlackRadius:
                    matrix[i][j] = -1

    return matrix

def isThereAPoint(positionToCheck):
    for point in foundSomethingPoints:
        if (positionToCheck[0]-point[0])**2 + (positionToCheck[1]-point[1])**2 <= squaredBlackRadius:
            return True
    return False


def mapCallback(data):
    #rospy.loginfo(rospy.get_caller_id() + "I heard %s", data.data)
    rospy.loginfo("Current map dimentions: %s,%s", data.info.width, data.info.height)
    matrix = occupancyGridToMatrix(data.data, data.info.width, data.info.height)       

def colorCallback(data):
    if (data.data == "A"):
        foundSomethingPoints.append((currentPosition[0], currentPosition[1], "A"))
    elif (data.data == "B"):
        foundSomethingPoints.append((currentPosition[0], currentPosition[1], "B"))
    elif (data.data == "C"):
        foundSomethingPoints.append((currentPosition[0], currentPosition[1], "C"))
    else:
        rospy.loginfo("BS heat from serial")

def cameraCallback(data):
    if (data.data == "H") :
        foundSomethingPoints.append((currentPosition[0], currentPosition[1], "H"))
    elif (data.data == "S"):
        foundSomethingPoints.append((currentPosition[0], currentPosition[1], "S"))
    elif (data.data == "U"):
        foundSomethingPoints.append((currentPosition[0], currentPosition[1], "U"))
    else:
        rospy.loginfo("BS letter from OpenCVNode")

def listener(): #https://answers.ros.org/question/341062/how-to-get-a-robot-position-xy-in-a-map-instead-of-odometry-in-python/
    rospy.init_node('GoalFinder', anonymous=True)
    rate = rospy.Rate(3.0)

    rospy.Subscriber("/map", OccupancyGrid, mapCallback)
    listener = tf.TransformListener()

    rospy.loginfo('GoalFinder node started')
    while not rospy.is_shutdown():
        try:
            
            (trans,rot) = listener.lookupTransform('/map', '/base_link', rospy.Time(0))
            #rospy.loginfo('Translation: ' + str(trans))
            #rospy.loginfo(type(trans))

            #setta la posizione iniziale
            currentPosition = (trans[0], trans[1])
            print(currentPosition)

        except (tf.LookupException, tf.ConnectivityException, tf.ExtrapolationException):
            rospy.loginfo("An error occured ¯\\_(ツ)_/¯")
            continue

        rate.sleep()

    
    
    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':
    print("Starting GoalFinder")
    listener()