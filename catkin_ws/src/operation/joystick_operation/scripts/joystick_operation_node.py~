#!/usr/bin/env python
import math
import rospy
from sensor_msgs.msg import Joy
from std_msgs.msg import Float32MultiArray
from std_msgs.msg import Empty

def callbackJoy(msg):
    global leftSpeed
    global rightSpeed
    global b_Button
    ### Read of b_button for stop the mobile base
    b_Button = msg.buttons[1]
    
    ### Control of mobile base with right Stick
    #rightStickX = msg.axes[3]
    rightStickX = msg.axes[0]
    rightStickY = msg.axes[4]
    rightTrigger = msg.axes[5]
    magnitudRight = math.sqrt(rightStickX*rightStickX + rightStickY*rightStickY)
    if magnitudRight > 0.1:
        turboFactor = 0.5 + (-rightTrigger + 1.0)/4.0
        leftSpeed = turboFactor*(rightStickY - 0.5*rightStickX)
        rightSpeed = turboFactor*(rightStickY + 0.5*rightStickX)
    else:
        leftSpeed = 0
        rightSpeed = 0
    
def main():
    global leftSpeed
    global rightSpeed
    global b_Button
    
    print "Initializing joystick operation node..."
    rospy.init_node("joystick_operation")
    
    rospy.Subscriber("/hardware/joy", Joy, callbackJoy)
    pubSpeeds = rospy.Publisher("/hardware/mobile_base/speeds", Float32MultiArray, queue_size=1)
    pubStop = rospy.Publisher("/hardware/robot_state/stop", Empty, queue_size = 1)

    loop = rospy.Rate(10)

    leftSpeed = 0
    rightSpeed = 0
    b_Button = 0
    msgSpeeds = Float32MultiArray()
    msgHeadPos = Float32MultiArray()
    msgStop = Empty()

    while not rospy.is_shutdown():
        if math.fabs(leftSpeed) > 0 or math.fabs(rightSpeed) > 0:
            msgSpeeds.data = [leftSpeed, rightSpeed]
            pubSpeeds.publish(msgSpeeds)

        if b_Button == 1:
            pubStop.publish(msgStop)


        loop.sleep()

if __name__ == '__main__':
    try:
        main()
    except rospy.ROSInterruptException:
        pass
