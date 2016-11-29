#!/usr/bin/env python
import sys, math, time
import rospy
from std_msgs.msg import String
from std_msgs.msg import Int16
from std_msgs.msg import Float32MultiArray
from nav_msgs.msg import Odometry
import tf
from geometry_msgs.msg import TransformStamped
import serial
#import RPi.GPIO as GPIO
from time import sleep

#Begining of settings
def settings():
        global Tx_MODE
        global Rx_MODE
        global Direction_Pin
        GPIO.setmode(GPIO.BCM)
        Tx_MODE = GPIO.HIGH
        Rx_MODE = GPIO.LOW
        Direction_Pin = 18
        GPIO.setup(Direction_Pin, GPIO.OUT)
        print "> GPIO Configuration"
#end of settings

def constants():
        global TX_DELAY_TIME
        global START
        global WRITE_DATA
        global READ_DATA
        global BULK_READ
        global BROADCASTING
        global SYNC_WRITE
        global SPEED_LENGHT
        global GOAL_SPEED_L
        global LEFT
        global RIGHT
        global POS_LENGTH
        global PRESENT_POSITION_L
        global LENGTH_READ_POS
        TX_DELAY_TIME = 0.0004
        START = chr(0xFF)
        WRITE_DATA = chr(3)
        READ_DATA = chr(2)
        BROADCASTING = chr(0xFE)
        SYNC_WRITE = chr(0x83)
        SPEED_LENGHT = chr(5)
        GOAL_SPEED_L = chr(32)
        LEFT = 0
        RIGHT = 1
        POS_LENGTH = chr(4)
        PRESENT_POSITION_L = chr(36)
        LENGTH_READ_POS = chr(2)
        BULK_READ = chr(0x92)
        print "> Defining constants"

def readPositions_SW(IDS):
        global Motors
        global START
        global BROADCASTING
        global BULK_READ
        global PRESENT_POSITION_L
        global Tx_MODE
        global Rx_MODE
        global Direction_Pin
        global TX_DELAY_TIME
        Positions = []
        
        Number_Motors = len(IDS)
        Length_Data = 2
        Length = 3 * Number_Motors + 3
        Param1 = chr(0x00)
        checkSum = ord(BROADCASTING) + Length + ord(BULK_READ)
        for n in range(0, Number_Motors):
                Positions.append(-1)
                checkSum += Length_Data + IDS[n] + ord(PRESENT_POSITION_L)
                IDS[n] = chr(IDS[n])
        checkSum = (~(checkSum)) & 0xFF
        checkSum = chr(checkSum)
        Length = chr(Length)
        Length_Data = chr(Length_Data)
        
        GPIO.output(Direction_Pin, Tx_MODE)
        Motors.write(START)
        Motors.write(START)
        Motors.write(BROADCASTING)
        Motors.write(Length)
        Motors.write(BULK_READ)
        Motors.write(Param1)
        for n in range(0, Number_Motors):
                Motors.write(Length_Data)
                Motors.write(IDS[n])
                Motors.write(PRESENT_POSITION_L)
        Motors.write(checkSum)
        sleep(TX_DELAY_TIME)
        GPIO.output(Direction_Pin, Rx_MODE)

        Time_Counter = 0
        word = 0x00
        while((Motors.inWaiting() < 32) and (Time_Counter < 1000)):
                Time_Counter = Time_Counter + 1
                sleep(0.00001)

        attempts = 0
        for n in range(0, Number_Motors):
                word = 0x00
                while(Motors.inWaiting() > 0):
                        Incoming_Byte = ord(Motors.read(size=1))
                        word = ((word << 8) | Incoming_Byte) & 0xFFFF
                        attempts += 1
                        if(word == 0xFFFF):
                                attempts = 0
                                ID_Motor = Motors.read(size=1) #ID
                                Length = ord(Motors.read(size=1)) #Length
                                Error_Byte = ord(Motors.read(size=1)) #Error
                                Position_LOW = ord(Motors.read(size=1)) & 0xFF
                                Position_HIGH = ord(Motors.read(size=1)) & 0xFF
                                check_sum = ord(Motors.read(size=1)) & 0xFF
                                Local_checkSum = (~(ord(IDS[n]) + 4 + Position_LOW + Position_HIGH)) & 0xFF
                                if(check_sum == Local_checkSum):
                                        Positions[n] = ((Position_HIGH << 8) | Position_LOW) & 0xFFFF
                                break
                        elif(attempts > 4):
                                attempts = 0
                                break
        Motors.flushInput()
        return Positions

def turn_SW(IDS, SIDES, Speeds):
        global Motors
        global START
        global BROADCASTING
        global SYNC_WRITE
        global SPEED_LENGHT
        global GOAL_SPEED_L
        global Tx_MODE
        global Rx_MODE
        global Direction_Pin
        Speeds_LOW = []
        Speeds_HIGH = []
        Number_Motors = len(IDS)
        Length_Data = 2
        Length = (Length_Data + 1) * Number_Motors + 4 
        checkSum = ord(BROADCASTING) + Length + ord(SYNC_WRITE) + ord(GOAL_SPEED_L) + Length_Data
        for n in range(0, Number_Motors):
                if SIDES[n] == 0:
                        Speed_H = (Speeds[n] >> 8) & 0xFF
                        Speed_L = (Speeds[n] >> 0) & 0xFF
                else:
                        Speed_H = ((Speeds[n] >> 8) & 0xFF) + 4
                        Speed_L = (Speeds[n] >> 0) & 0xFF
                checkSum += IDS[n] + Speed_L + Speed_H
                IDS[n] = chr(IDS[n])
                Speeds_LOW.append(chr(Speed_L))
                Speeds_HIGH.append(chr(Speed_H))
        checkSum = (~(checkSum)) & 0xFF
        checkSum = chr(checkSum)
        Length = chr(Length)
        Length_Data = chr(Length_Data)
        
        GPIO.output(Direction_Pin, Tx_MODE)
        Motors.write(START)
        Motors.write(START)
        Motors.write(BROADCASTING)
        Motors.write(Length)
        Motors.write(SYNC_WRITE)
        Motors.write(GOAL_SPEED_L)
        Motors.write(Length_Data)
        for n in range(0, Number_Motors):
                Motors.write(IDS[n])
                Motors.write(Speeds_LOW[n])
                Motors.write(Speeds_HIGH[n])
        Motors.write(checkSum)
        sleep(TX_DELAY_TIME)
        GPIO.output(Direction_Pin, Rx_MODE)

def callbackSpeeds(msg):
    global leftSpeed
    global rightSpeed
    global newSpeedData
    #Speeds are assumed to come in float in [-1,1] for each tire. The values need to be transformed to values in [0,127]
    #A float value of -1, indicates the maximum speed backwards
    #Similar for +1
    leftSpeed = msg.data[0]
    rightSpeed = msg.data[1]
    if leftSpeed > 1:
        leftSpeed = 1
    elif leftSpeed < -1:
        leftSpeed = -1
    if rightSpeed > 1:
        rightSpeed = 1
    elif rightSpeed < -1:
        rightSpeed = -1
    newSpeedData = True

def calculateOdometry(currentPos, leftEnc, rightEnc): #Encoder measurements are assumed to be in ticks
    leftEnc = leftEnc * 0.39/4095 #From ticks to meters
    rightEnc = rightEnc * 0.39/4095
    deltaTheta = (rightEnc - leftEnc)/0.23 #0.23 is the robot diameter
    if math.fabs(deltaTheta) >= 0.0001:
        rg = (leftEnc + rightEnc)/(2*deltaTheta)
        deltaX = rg*math.sin(deltaTheta)
        deltaY = rg*(1-math.cos(deltaTheta))
    else:
        deltaX = (leftEnc + rightEnc)/2
        deltaY = 0
    currentPos[0] += deltaX * math.cos(currentPos[2]) - deltaY * math.sin(currentPos[2])
    currentPos[1] += deltaX * math.sin(currentPos[2]) + deltaY * math.cos(currentPos[2])
    currentPos[2] += deltaTheta
    return currentPos
    
def main(portName, portBaud, simulated):
    print "Initializing mobile base node..."
    ###ROS configuration
    rospy.init_node("mobile_base")
    pubOdometry = rospy.Publisher("/hardware/mobile_base/odometry", Odometry, queue_size = 1)
    subSpeeds = rospy.Subscriber("/hardware/mobile_base/speeds", Float32MultiArray, callbackSpeeds)
    pubEncoderM1 = rospy.Publisher("/hardware/robot_state/enc_motor_1", Int16, queue_size = 1)
    pubEncoderM2 = rospy.Publisher("/hardware/robot_state/enc_motor_2", Int16, queue_size = 1)
    pubEncoderM3 = rospy.Publisher("/hardware/robot_state/enc_motor_3", Int16, queue_size = 1)
    pubEncoderM4 = rospy.Publisher("/hardware/robot_state/enc_motor_4", Int16, queue_size = 1)
    br = tf.TransformBroadcaster()
    rate = rospy.Rate(20) # 20hz
    ###Communication with the Dynamixel
    if not simulated:
            global Motors
            global LEFT
            global RIGHT
            settings()
            constants()
            ID_Motors = [1, 2, 3, 4]
            Sides_Motors = [RIGHT, RIGHT, RIGHT, RIGHT]
            Speeds_Motors = [0, 0, 0, 0]
            Motors = serial.Serial(portName, portBaud, timeout = 0.0005)    
            sleep(1)
    ####Variables for setting speeds
    global leftSpeed
    global rightSpeed
    global newSpeedData
    leftSpeed = 0
    rightSpeed = 0
    newSpeedData = False
    speedCounter = 5
    
    ###Variables for Encoders
    if not simulated:
            msgEncoderM1 = Int16()
            msgEncoderM2 = Int16()
            msgEncoderM3 = Int16()
            msgEncoderM4 = Int16()
    ###Variables for odometry
    robotPos = [0, 0, 0]
    while not rospy.is_shutdown():
        if newSpeedData:
            newSpeedData = False
            speedCounter = 5
            if not simulated:
                    leftSpeed = int(leftSpeed*200)
                    rightSpeed = int(rightSpeed*200)
                    if leftSpeed >= 0:
                            Sides_Motors[1] = LEFT
                            Sides_Motors[3] = LEFT
                            Speeds_Motors[1] = leftSpeed
                            Speeds_Motors[3] = leftSpeed
                    else:
                            Sides_Motors[1] = RIGHT
                            Sides_Motors[3] = RIGHT
                            Speeds_Motors[1] = -leftSpeed
                            Speeds_Motors[3] = -leftSpeed
                    if rightSpeed >= 0:
                            Sides_Motors[0] = RIGHT
                            Sides_Motors[2] = RIGHT
                            Speeds_Motors[0] = rightSpeed
                            Speeds_Motors[2] = rightSpeed
                    else:
                            Sides_Motors[0] = LEFT
                            Sides_Motors[2] = LEFT
                            Speeds_Motors[0] = -rightSpeed
                            Speeds_Motors[2] = -rightSpeed
                    turn_SW(*[[1, 2, 3, 4], Sides_Motors, Speeds_Motors])
        else:
            speedCounter -= 1
            if speedCounter == 0:
                    if not simulated:
                            turn_SW(*[[1, 2, 3, 4], Sides_Motors, [0, 0, 0, 0]])
                    else:
                            leftSpeed = 0
                            rightSpeed = 0
            if speedCounter < -1:
                speedCounter = -1
        if not simulated:
                pos = readPositions_SW([1, 2, 3, 4])
                msgEncoderM1.data = pos[0]
                msgEncoderM2.data = pos[1]
                msgEncoderM3.data = pos[2]
                msgEncoderM4.data = pos[3]
                if((msgEncoderM1.data != -1) and (msgEncoderM2.data != -1) and (msgEncoderM3.data != -1) and (msgEncoderM4.data != -1)):
                        pubEncoderM1.publish(msgEncoderM1)
                        pubEncoderM2.publish(msgEncoderM2)
                        pubEncoderM3.publish(msgEncoderM3)
                        pubEncoderM4.publish(msgEncoderM4)
        else:
                encoderLeft = leftSpeed * 0.05 * 4095 / 0.39
                encoderRight = rightSpeed * 0.05 * 4095 / 0.39
        #Calculate odometry
        ###Odometry calculation
        robotPos = calculateOdometry(robotPos, encoderLeft, encoderRight)
        ts = TransformStamped()
        ts.header.stamp = rospy.Time.now()
        ts.header.frame_id = "odom"
        ts.child_frame_id = "base_link"
        ts.transform.translation.x = robotPos[0]
        ts.transform.translation.y = robotPos[1]
        ts.transform.translation.z = 0
        ts.transform.rotation = tf.transformations.quaternion_from_euler(0, 0, robotPos[2])
        br.sendTransform((robotPos[0], robotPos[1], 0), ts.transform.rotation, rospy.Time.now(), ts.child_frame_id, ts.header.frame_id)
        msgOdom = Odometry()
        msgOdom.header.stamp = rospy.Time.now()
        msgOdom.pose.pose.position.x = robotPos[0]
        msgOdom.pose.pose.position.y = robotPos[1]
        msgOdom.pose.pose.position.z = 0
        msgOdom.pose.pose.orientation.x = 0
        msgOdom.pose.pose.orientation.y = 0
        msgOdom.pose.pose.orientation.z = math.sin(robotPos[2]/2)
        msgOdom.pose.pose.orientation.w = math.cos(robotPos[2]/2)
        pubOdometry.publish(msgOdom)
        rate.sleep()
    if not simulated:
        if Motors.isOpen():
                Motors.close()
                print '\nConnection with /dev/ttyAMA0 is closed'
        GPIO.cleanup()
        print "Cleaning GPIO"
    
    

if __name__ == '__main__':
    try:
        portName = "/dev/ttyAMA0"
	portBaud = 1000000
	simulated = False
	if "--simul" in sys.argv:
                simulated = True
        main(portName, portBaud, simulated)
    except rospy.ROSInterruptException:
        pass
