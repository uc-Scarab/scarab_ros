#! /usr/bin/env python3
import rospy
from motor_positions.msg import controlTable
from roboticstoolbox import mstraj
import numpy as np
from math import pi, ceil
import pdb
from time import sleep
from inv_kine import leg_ikine

# from std_msgs.msg import String

def radstoRaw(rads):
    raw = rads/ 0.00153589
    raw += 2048
    return(int(raw))

rospy.init_node('trajectories', anonymous=True)
pub = rospy.Publisher("dynamixel_control", controlTable, queue_size=60)
rate = rospy.Rate(10) # 10hz
msg = controlTable()
a = [0.62, 0.86, 0.70, 0.61]

test = np.array(leg_ikine(1.5, 0, 0, -pi/2, -1, a))

# zeros = np.array(
        # [0, 0, 0, 0],
        # )

# qz = [0, 0, 0, 0]
# qn = [0, 0.9484, -1.9477, -0.5715]
setup_msg = controlTable()

path = np.array([
        [0, 0.4401, 0.6496, 0.7019],
        [0, 0, 0, 0],
        [0, -0.4401, -0.6496, -0.7019]
        ])



# path = np.row_stack((qz, qn))
out = mstraj(path, dt=0.1, tacc=1, tsegment=[2, 2])
for i in range(10, 14):
    setup_msg.dest = i
    setup_msg.command_id = 2
    setup_msg.value = 500
    rospy.loginfo(setup_msg)
    pub.publish(setup_msg)

    setup_msg.command_id = 5
    rospy.loginfo(setup_msg)
    pub.publish(setup_msg)
    sleep(0.1)

print("finish setup")

pdb.set_trace()
move_msg = controlTable()

for move in out.q:
    for count, via in enumerate(move):
        move_msg.dest = count + 10
        move_msg.command_id = 0
        move_msg.value = ceil(radstoRaw(via))

        rospy.loginfo(move_msg)
        pub.publish(move_msg)
        sleep(0.1)



