import rospy, os, subprocess, signal, time

from std_msgs.msg import String

readyPub = None
mapProcess = None
rosProcess = None
serialProcess = None
started = 0
transitioning = 0
ready = 0
localCostmapPath="/home/ubuntu/lidar_ws/src/param/local_costmap_params.yaml"
localCostmapConfigV1 = """update_frequency: 5.0
publish_frequency: 5.0
transform_tolerance: 0.2
static_map: false
rolling_window: true
resolution: 0.01
inflation_radius: 0.05
width: 0.6
height: 0.6

plugins:
  - {name: obstacle_layer, type: "costmap_2d::ObstacleLayer"}

obstacle_layer:
  observation_sources: laser_scan_sensor
  laser_scan_sensor: {sensor_frame: laser, data_type: LaserScan, topic: LiDAR/LD06, marking: true, clearing: true}
"""
localCostmapConfigV2 = """local_costmap:
  update_frequency: 5.0
  publish_frequency: 5.0
  transform_tolerance: 0.2
  static_map: false
  rolling_window: true
  resolution: 0.01
  inflation_radius: 0.02
  width: 0.6
  height: 0.6
  
  plugins:
    - {name: obstacle_layer, type: "costmap_2d::ObstacleLayer"}
  
  obstacle_layer:
    observation_sources: laser_scan_sensor
    laser_scan_sensor: {sensor_frame: laser, data_type: LaserScan, topic: LiDAR/LD06, marking: true, clearing: true}
"""


def checkStart(data):
  global started, ready, mapProcess, transitioning
  if (data.data == "1"):
    started = 1
    if transitioning == 0:
      transitioning = 1
      rospy.loginfo("Starting SLAM+Navigation stack")
      #mapProcess = subprocess.Popen("source /home/ubuntu/lidar_ws/devel/setup.bash && roslaunch /home/ubuntu/test.launch", shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
      #mapProcess = subprocess.Popen("roslaunch /home/ubuntu/test.launch", shell=True)
      #mapProcess = subprocess.Popen("sshpass -p DKVLab321 ssh ubuntu@localhost source /opt/ros/noetic/setup.bash && source /home/ubuntu/lidar_ws/devel/setup.bash --extend && roslaunch /home/ubuntu/test.launch", shell=True)
      #mapProcess = subprocess.Popen("sshpass -p DKVLab321 ssh ubuntu@localhost . /opt/ros/noetic/setup.bash && . /home/ubuntu/lidar_ws/devel/setup.bash --extend && roslaunch /home/ubuntu/test.launch", shell=True)
      #mapProcess = subprocess.Popen("sshpass -p DKVLab321 ssh ubuntu@localhost ls -l `which sh`", shell=True)
      #mapProcess = subprocess.Popen("sshpass -p DKVLab321 ssh ubuntu@localhost script /dev/null && screen -S DKV ./starter.sh", shell=True, preexec_fn=os.setpgrp)
      #mapProcess = subprocess.Popen("sshpass -p DKVLab321 ssh ubuntu@localhost screen -S DKV ./starter.sh", shell=True)
      #mapProcess = subprocess.Popen("sshpass -p DKVLab321 ssh ubuntu@localhost screen -S DKV ./starter.sh", shell=True, stdout=subprocess.PIPE)
      mapProcess = subprocess.Popen("screen -dmS DKV ./starter.sh", shell=True, stdout=subprocess.PIPE)
      #subprocess.call(['sh', './home/ubuntu/starter.sh'])
      #os.system('sh chmod +x starter.sh|./starter.sh')
      #os.system('sshpass -p DKVLab321 ssh ubuntu@localhost screen -S DKV ./starter.sh')
      #sp = subprocess.Popen(["/bin/bash", "-i", "-c", "./starter.sh"])
      time.sleep(12)
      rospy.loginfo("Ready state reached")
      ready = 1
  elif (data.data == "0"):
    started = 0
    ready = 0
    if transitioning == 1:
      transitioning = 0
      rospy.loginfo("Killing SLAM+Navigation stack")
      """
      mapProcess.send_signal(signal.SIGINT)
      mapProcess.send_signal(signal.SIGTERM)
      time.sleep(5)"""
      #tmpProcess = subprocess.Popen("sshpass -p DKVLab321 ssh ubuntu@localhost screen -S DKV -X quit", shell=True, preexec_fn=os.setpgrp)
      #tmpProcess = subprocess.Popen("screen -S DKV -X quit", shell=True, stdout=subprocess.PIPE)
      #tmpProcess.terminate()
      subprocess.run("screen -S DKV -X quit", shell=True)
      #os.killpg(os.getpgid(mapProcess.pid), signal.SIGINT)
      #os.system('pkill -TERM -P {pid}'.format(pid=mapProcess.pid))
      #os.killpg(os.getpgid(mapProcess.pid), signal.SIGTERM)
      mapProcess.terminate()
      rospy.loginfo("Reset complete")


def talker():
    global readyPub, rosProcess, serialProcess, mapProcess, ready, localCostmapPath
    print("Starting Roscore")
    #rosProcess = subprocess.Popen("sudo chmod 666 /dev/i2c* $$ roscore", shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    rosProcess = subprocess.Popen("roscore")
    #print(rosProcess)
    time.sleep(5)
    serialProcess = subprocess.Popen("roslaunch /home/ubuntu/seriale.launch", shell=True)
    rospy.loginfo("Roscore started")

    rospy.loginfo("Fixing Local costmap bug")
    os.remove(localCostmapPath)
    file = open(localCostmapPath,"w")
    file.write(localCostmapConfigV1)
    file.close()
    mapProcess = subprocess.Popen("sshpass -p DKVLab321 ssh ubuntu@localhost . /opt/ros/noetic/setup.bash && roslaunch /home/ubuntu/test.launch", shell=True, preexec_fn=os.setpgrp)
    time.sleep(15)
    rospy.loginfo("Rewriting original file")
    os.killpg(os.getpgid(mapProcess.pid), signal.SIGTERM)
    os.remove(localCostmapPath)
    file = open(localCostmapPath,"w")
    file.write(localCostmapConfigV2)
    file.close()

    readyPub = rospy.Publisher('/ready', String, queue_size=10)
    rospy.Subscriber("/partito", String, checkStart)
    rospy.init_node('starter', anonymous=False)
    rate = rospy.Rate(10)
    rospy.loginfo("Robot Ready")

    while not rospy.is_shutdown():
        readyPub.publish(str(ready))
        rate.sleep()
        
if __name__ == '__main__':
    try:
      talker()
    except rospy.ROSInterruptException:
        pass
