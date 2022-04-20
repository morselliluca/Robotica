#!/usr/bin/env python3
import rospy
import tf, tf2_ros, geometry_msgs.msg
import numpy as np
import math
import actionlib

from nav_msgs.msg import OccupancyGrid, Odometry
from move_base_msgs.msg import MoveBaseGoal, MoveBaseAction
from std_msgs.msg import String


blackRadius = 7 #radius representing a black tile in the map
foundSomethingRadius = 7 #radius of an event in the map to rpevent multiple block drops
visitedRadius = 5 #radius of a visited tile
goalRadius = 7 #minimun distance to consider a goal reached
goalPointSearchRadius = 20 #minumun distance from the goal to the current position
minimunDistanceFromWallRadius = 7 #minimun distance from the goal an sorrounding walls
blackDistance = 5 #distance from the front of the robot and the new found and placed black tile

squaredBlackRadius = blackRadius**2
squaredFoundSomethingRadius = foundSomethingRadius**2
squaredVisitedRadius = visitedRadius**2
squaredGoalRadius = goalRadius**2
squaredGoalPointSearchRadius = goalPointSearchRadius**2
squaredMinimunDistanceFromWallRadius = minimunDistanceFromWallRadius**2

noGoPoints = []
foundSomethingPoints = []

currentPosition = None
currentRotation = None
goalPoint = None

mapResolution = 0.01
mapDimention = 0
halfMapDimention = 0
visitedMap = None #0 empty space , 100 wall, -1 unknown, -2 visited

mapPub = None
visitedPub = None
goalPub = None
cubePub = None

def occupancyGridToMatrix(occupancyGrid):
    global mapDimention, blackRadius, squaredBlackRadius, noGoPoints
    matrix = np.empty([mapDimention, mapDimention]).astype(np.int8)

    #for i in range(0, mapDimention): #fill the new matrix with the values from the occupancyGrid (which is a 1d array)
    #    for j in range(0, mapDimention):
    #        matrix[i, j] = occupancyGrid[mapDimention * i + j]
    matrix = np.reshape(occupancyGrid, (mapDimention, mapDimention))

    for point in noGoPoints: #fill the new matrix with "artificial" walls where there are black tiles
        for i in range(point[0]-blackRadius, point[0]+blackRadius+1):
            for j in range(point[1]-blackRadius, point[1]+blackRadius+1):
                if (i-point[0])**2 + (j-point[1])**2 <= squaredBlackRadius:
                    matrix[i, j] = 100
    return matrix

def getGoalPoint(matrix):
    global currentPosition, goalPointSearchRadius, squaredGoalPointSearchRadius
    tmpMatrix = matrix.copy() #copy the given matrix (circumvents the reference of the object)

    for i in range(currentPosition[0]-goalPointSearchRadius, currentPosition[0]+goalPointSearchRadius+1): #artificially set a visited area so the robot doest search a goal near him
            for j in range(currentPosition[1]-goalPointSearchRadius, currentPosition[1]+goalPointSearchRadius+1):
                if (i-currentPosition[0])**2 + (j-currentPosition[1])**2 <= squaredGoalPointSearchRadius:
                    tmpMatrix[i, j] = -2
    
    tmpGoal = findGoalPoint(tmpMatrix) #search a goal point that is somewhat far away from the robot
    if tmpGoal is None:
        #tmpGoal = findGoalPoint(matrix)
        #if tmpGoal is None:
        rospy.loginfo("Exploration finisced, returning to base")
        tmpGoal = (0, 0)
    return tmpGoal  

def findGoalPoint(matrix): #finds a new goal point on a given matrix
    global currentPosition, mapDimention
    tmpmatrix = matrix.copy() #copy the given matrix (circumvents the reference of the object)
    pointList1 = set()
    pointList2 = set()

    pointList1.add(currentPosition)

    test = 0
    while True: #find the new goal
        test +=1
        rospy.loginfo("Loop: " + str(test) + " lunghezza: " + str(len(pointList1)) + " Map dim:" + str(mapDimention))
        for pt in pointList1:
            #rospy.loginfo("Loop: " + str(test) + " lunghezza: " + str(len(pointList1)) + " Val:" + str(matrix[pt[0], pt[1]]) + " Map dim:" + str(mapDimention))
            if pt not in pointList2:
                #rospy.loginfo("punto x:" + str(pt[0]) + " y:" + str(pt[1]) + " valore:" + str(matrix[pt[0], pt[1]]))
                tmpmatrix[pt[0], pt[1]] = -1
                if pt[0] + 1 < mapDimention:
                    if tmpmatrix[pt[0] + 1, pt[1]] == 0:
                        rospy.loginfo("New goal found!")
                        return (pt[0] + 1, pt[1])
                    elif tmpmatrix[pt[0] + 1, pt[1]] == -2:
                        if not checkForWalls(tmpmatrix, pt[0] + 1, pt[1]):
                            pointList2.add((pt[0] + 1, pt[1]))
                if pt[1] + 1 < mapDimention:
                    if tmpmatrix[pt[0], pt[1] + 1] == 0:
                        rospy.loginfo("New goal found!")
                        return (pt[0], pt[1] + 1)
                    elif tmpmatrix[pt[0], pt[1] + 1] == -2:
                        if not checkForWalls(tmpmatrix, pt[0], pt[1] + 1):
                            pointList2.add((pt[0], pt[1] + 1))
                if pt[0] - 1 >= 0:
                    if tmpmatrix[pt[0] - 1, pt[1]] == 0:
                        rospy.loginfo("New goal found!")
                        return (pt[0] - 1, pt[1])
                    elif tmpmatrix[pt[0] - 1, pt[1]] == -2:
                        if not checkForWalls(tmpmatrix, pt[0] - 1, pt[1]):
                            pointList2.add((pt[0] - 1, pt[1]))
                if pt[1] - 1 >= 0:
                    if tmpmatrix[pt[0], pt[1] - 1] == 0:
                        rospy.loginfo("New goal found!")
                        return (pt[0], pt[1] - 1)
                    elif tmpmatrix[pt[0], pt[1] - 1] == -2:
                        if not checkForWalls(tmpmatrix, pt[0], pt[1] - 1):
                            pointList2.add((pt[0], pt[1] - 1))
        if len(pointList2) == 0:
            return None
        else:
            pointList1 = pointList2
            pointList2 = set()

def checkForWalls(matrix, x, y):
    #rospy.loginfo("punto x:" + str(x) + " y:" + str(y) + " valore:" + str(matrix[x, y]))
    global minimunDistanceFromWallRadius, squaredMinimunDistanceFromWallRadius
    for i in range(x-minimunDistanceFromWallRadius, x+minimunDistanceFromWallRadius+1): #check that no walls are near a specified point
            for j in range(y-minimunDistanceFromWallRadius, y+minimunDistanceFromWallRadius+1):
                if (i-x)**2 + (j-y)**2 <= squaredMinimunDistanceFromWallRadius and matrix[i, j] == 100:
                    #rospy.loginfo("Wall found [" + str(i) + "," + str(j) + "]")
                    return True
    return False


def isThereAPoint(positionToCheck): #check for a black tile
    global noGoPoints, squaredBlackRadius
    for point in noGoPoints:
        if (positionToCheck[0]-point[0])**2 + (positionToCheck[1]-point[1])**2 <= squaredBlackRadius:
            return True
    return False

def isThereAPoint(positionToCheck, typeToCkeck): #check for an already interacted thing
    global foundSomethingPoints, squaredFoundSomethingRadius
    for point in foundSomethingPoints:
        if point[2] == typeToCkeck and (positionToCheck[0]-point[0])**2 + (positionToCheck[1]-point[1])**2 <= squaredFoundSomethingRadius:
            return True
    return False

def prepareMap(matrix):
    global mapResolution, mapDimention, halfMapDimention
    outMap = OccupancyGrid()
    outMap.info.resolution = mapResolution 
    outMap.info.width = mapDimention
    outMap.info.height = mapDimention
    outMap.info.origin.position.x = -(mapResolution*mapDimention/2 + 0.012) #-25.612
    outMap.info.origin.position.y = -(mapResolution*mapDimention/2 + 0.012) #-25.612
    outMap.info.origin.position.z = 0.0 
    outMap.info.origin.orientation.x = 0.0 
    outMap.info.origin.orientation.y = 0.0 
    outMap.info.origin.orientation.z = 0.0 
    outMap.info.origin.orientation.w = 0.0 
    tmpMatrix = matrix.ravel()
    tmpMatrix[tmpMatrix == -2] = -1
    outMap.data = tmpMatrix.astype(int).tolist()
    return outMap

def prepareGoalPoint():
    global goalPoint, mapResolution, halfMapDimention
    goal = MoveBaseGoal()
    goal.target_pose.header.frame_id = "map"
    goal.target_pose.header.stamp = rospy.Time.now()
    goal.target_pose.pose.position.y = (goalPoint[0]-halfMapDimention)*mapResolution
    goal.target_pose.pose.position.x = (goalPoint[1]-halfMapDimention)*mapResolution
    rospy.loginfo("Goal position: " + str((goalPoint[1]-halfMapDimention)*mapResolution) + "," + str((goalPoint[0]-halfMapDimention)*mapResolution))
    goal.target_pose.pose.orientation.w = 1
    return goal

def mapCallback(data):
    global mapDimention, currentPosition, visitedRadius, squaredVisitedRadius, mapPub, visitedPub, squaredGoalRadius, goalPoint, goalPub, visitedMap
    #rospy.loginfo(rospy.get_caller_id() + "I heard %s", data.data)
    #rospy.loginfo("Current map dimentions: %s,%s", data.info.width, data.info.height)
    #matrix = occupancyGridToMatrix(data.data, data.info.width, data.info.height)
    rospy.loginfo("Got a new map")
    if mapDimention != 0:
        matrix = occupancyGridToMatrix(data.data)
        if visitedMap is None:
            visitedMap = np.zeros([mapDimention, mapDimention])

        for i in range(currentPosition[0]-visitedRadius, currentPosition[0]+visitedRadius+1):
            for j in range(currentPosition[1]-visitedRadius, currentPosition[1]+visitedRadius+1):
                if matrix[i, j] == -1:
                    visitedMap[i, j] = -1
                elif (i-currentPosition[0])**2 + (j-currentPosition[1])**2 <= squaredVisitedRadius:
                    visitedMap[i, j] = -2
        
        if mapPub is not None:
            #print(prepareMap(matrix))
            mapPub.publish(prepareMap(matrix))
            rospy.loginfo("Corrected map published")
            visitedPub.publish(prepareMap(visitedMap))
            rospy.loginfo("Visited map published")
        
        #rospy.loginfo("Sending goal")
        #goalPoint = (2,2)
        #goalPub.send_goal(prepareGoalPoint())
        #wait = goalPub.wait_for_result()
        #if not wait:
        #    rospy.logerr("Action server not available!")

        #rospy.loginfo("Goalpoint published")
        
        if checkForWalls(matrix, currentPosition[0], currentPosition[1]):
            try:
                rospy.loginfo("Recalculating new goalPoint")
                goalPoint = getGoalPoint(visitedMap)
                goalPub.send_goal(prepareGoalPoint())
                rospy.loginfo("Recalculated goalpoint published " + str(goalPoint))
            except:
                rospy.loginfo("An error occured during the recalculated goal publishing ¯\\_(ツ)_/¯")

        #rospy.loginfo("Curpos: [" + str(currentPosition[0]) + "," + str(currentPosition[1]) + "] GoalPos: [" +str(goalPoint[0]) + "," + str(goalPoint[1]) + "]")
        
        if (goalPoint[0]-currentPosition[0])**2 + (goalPoint[1]-currentPosition[1])**2 <= squaredGoalRadius:
            try:
                rospy.loginfo("Calculating new goalPoint")
                goalPoint = getGoalPoint(visitedMap)
                goalPub.send_goal(prepareGoalPoint())
                rospy.loginfo("Goalpoint published " + str(goalPoint))
            except:
                rospy.loginfo("An error occured during the goal publishing ¯\\_(ツ)_/¯")
                


        
def blackTileCallback(data): #https://stackoverflow.com/questions/41379482/how-to-translate-a-point-to-specified-distance-at-a-specified-angle
    global currentPosition, currentRotation, blackDistance
    if data.data == "1" and isThereAPoint(currentPosition):
        noGoPoints.append((currentPosition[0] + blackDistance*math.sin(currentRotation), currentPosition[1]+ blackDistance*math.cos(currentRotation)))

def colorCallback(data):
    global foundSomethingPoints, currentPosition
    if (data.data == "R"):
        if not isThereAPoint(currentPosition, "R"):
            foundSomethingPoints.append((currentPosition[0], currentPosition[1], "R"))
            dropCube(1)
    elif (data.data == "Y"):
        if not isThereAPoint(currentPosition, "Y"):
            foundSomethingPoints.append((currentPosition[0], currentPosition[1], "Y"))
            dropCube(1)
    elif (data.data == "G"):
        if not isThereAPoint(currentPosition, "G"):
            foundSomethingPoints.append((currentPosition[0], currentPosition[1], "G"))
            dropCube(0)
    else:
        rospy.loginfo("BS heat from serial")

def letterCallback(data):
    global foundSomethingPoints, currentPosition
    if (data.data == "H"):
        if not isThereAPoint(currentPosition, "H"):
            foundSomethingPoints.append((currentPosition[0], currentPosition[1], "H"))
            dropCube(3)
    elif (data.data == "S"):
        if not isThereAPoint(currentPosition, "S"):
            foundSomethingPoints.append((currentPosition[0], currentPosition[1], "S"))
            dropCube(2)
    elif (data.data == "U"):
        if not isThereAPoint(currentPosition, "U"):
            foundSomethingPoints.append((currentPosition[0], currentPosition[1], "U"))
            dropCube(0)
    else:
        rospy.loginfo("BS letter from OpenCVNode")

def heatCallBack(data):
    global foundSomethingPoints, currentPosition
    if (data.data == "L" or data.data == "R" or data.data == "F"):
        if not isThereAPoint(currentPosition, "Heat"):
            foundSomethingPoints.append((currentPosition[0], currentPosition[1], "Heat"))
            dropCube(1)

def dropCube(numberOfCubes):
    global cubePub
    cubePub.publish(numberOfCubes)


def listener(): #https://answers.ros.org/question/341062/how-to-get-a-robot-position-xy-in-a-map-instead-of-odometry-in-python/
    global mapResolution, mapDimention, halfMapDimention, mapPub, visitedPub, goalPub, cubePub, currentPosition, currentRotation, goalPoint
    rospy.init_node('GoalFinder', anonymous=True)
    rate = rospy.Rate(3.0)

    rospy.Subscriber("/map", OccupancyGrid, mapCallback)
    rospy.Subscriber("/nero", String, blackTileCallback)
    rospy.Subscriber("/colore", String, colorCallback)
    rospy.Subscriber("/lettera", String, letterCallback)
    rospy.Subscriber("/calore", String, heatCallBack)
    listener = tf.TransformListener()
    
    mapResolution = rospy.get_param("/hector_mapping/map_resolution")
    mapDimention = rospy.get_param("/hector_mapping/map_size")
    halfMapDimention = mapDimention/2

    mapPub = rospy.Publisher('/blackmap', OccupancyGrid, queue_size=3)
    visitedPub = rospy.Publisher('/visited', OccupancyGrid, queue_size=3)
    goalPub = actionlib.SimpleActionClient('move_base',MoveBaseAction)
    cubePub = rospy.Publisher('/cubi', String, queue_size=10)

    #broadcaster = tf2_ros.StaticTransformBroadcaster()
    #static_transformStamped = geometry_msgs.msg.TransformStamped()

    goalPoint = (halfMapDimention, halfMapDimention)
    rospy.loginfo('GoalFinder node started')
    
    while not rospy.is_shutdown():
        try:
            """
            static_transformStamped.header.stamp = rospy.Time.now()
            static_transformStamped.header.frame_id = "goalfinder"
            static_transformStamped.child_frame_id = "map"

            static_transformStamped.transform.translation.x = float(0)
            static_transformStamped.transform.translation.y = float(0)
            static_transformStamped.transform.translation.z = float(0)

            quat = tf.transformations.quaternion_from_euler(float(0),float(0),float(0))
            static_transformStamped.transform.rotation.x = quat[0]
            static_transformStamped.transform.rotation.y = quat[1]
            static_transformStamped.transform.rotation.z = quat[2]
            static_transformStamped.transform.rotation.w = quat[3]

            broadcaster.sendTransform(static_transformStamped)
            """

            (trans,rot) = listener.lookupTransform('/map', '/base_link', rospy.Time(0))
            #rospy.loginfo('Translation: ' + str(trans))
            #rospy.loginfo(type(trans))

            #trans = (0,0,0)
            #rot = (0,0,0)

            #update current position and rotation
            currentPosition = (int(trans[1]/mapResolution+halfMapDimention), int(trans[0]/mapResolution+halfMapDimention))
            #currentPosition = (int(trans[0]*mapResolution), int(trans[1]*mapResolution))
            currentRotation = rot[2] #*57.2957 to get radians to degrees


        except (tf.LookupException, tf.ConnectivityException, tf.ExtrapolationException):
            rospy.logwarn("An error occured ¯\\_(ツ)_/¯")
            continue
        rate.sleep()
    # spin() simply keeps python from exiting until this node is stopped
    #rospy.spin()

if __name__ == '__main__':
    rospy.loginfo("Starting GoalFinder")
    try:     
        listener()
    except: #rospy.ROSInterruptException
        rospy.logfatal("A bigger error occured")
        pass
