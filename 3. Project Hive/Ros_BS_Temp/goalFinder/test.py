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

listener = tf.TransformListener()

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



def mapCallback(data):
    #rospy.loginfo(rospy.get_caller_id() + "I heard %s", data.data)
    rospy.loginfo("Current map dimentions: %s,%s", data.info.width, data.info.height)
    matrix = occupancyGridToMatrix(data.data, data.info.width, data.info.height)

def tfCallback(data):
    try:
        # listen to transform
        (trans,rot) = listener.lookupTransform('/map', '/base_link', rospy.Time(0))
        # print the transform
        rospy.loginfo('---------')
        rospy.loginfo('Translation: ' + str(trans))
        rospy.loginfo('Rotation: ' + str(rot))
    except (tf.LookupException, tf.ConnectivityException, tf.ExtrapolationException):
        rospy.loginfo("An error occured ¯\\_(ツ)_/¯")

def listener(): #https://answers.ros.org/question/341062/how-to-get-a-robot-position-xy-in-a-map-instead-of-odometry-in-python/

    rospy.init_node('GoalFinder', anonymous=True)
    rospy.Subscriber("/map", OccupancyGrid, mapCallback)
    rospy.Subscriber("/odom", OccupancyGrid, mapCallback)

    #rate = rospy.Rate(20.0)
    rospy.loginfo('GoalFinder node started')
    # spin() simply keeps python from exiting until this node is stopped
    #rospy.spin()

if __name__ == '__main__':
    print("Starting GoalFinder")
    listener()
