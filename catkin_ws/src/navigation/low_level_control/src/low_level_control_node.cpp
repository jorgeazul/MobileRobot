#include <iostream>
#include "ros/ros.h"
#include "std_msgs/Float32MultiArray.h"
#include "std_msgs/Empty.h"
#include "tf/transform_listener.h"
#include "nav_msgs/Path.h"
#include "Controls.h"

nav_msgs::Path goalPath;
bool achiveGoal = false; 

void callback_path(const nav_msgs::Path::ConstPtr& msg)
{
    goalPath = *msg;
    //std::cout << "Size of path: " << goalPath.poses.size() << std::endl;
    //std::cout << "Size of path: " << msg->poses.size() << std::endl;
}

void callback_start(const std_msgs::Empty::ConstPtr& msg)
{
    std::cout << "Empty message received" << std::endl;
    std::cout << "Size of path: " << goalPath.poses.size() << std::endl;
    //std::cout << "Last Path X: " << goalPath.poses[goalPath.poses.size() - 1].pose.position.x << std::endl;
    achiveGoal = true;
}



int main(int argc, char** argv)
{
    std::cout << "Initializing low level control node..." << std::endl;
    ros::init(argc, argv, "low_level_control");
    ros::NodeHandle n;
    ros::Publisher pubSp = n.advertise<std_msgs::Float32MultiArray>("/hardware/mobile_base/speeds", 1);
    ros::Subscriber subGoalPath = n.subscribe("/navigation/a_star_path",1, callback_path);
    ros::Subscriber subStart = n.subscribe("/navigation/start_path",1, callback_start);
    
    ros::Rate loop(10);
    tf::TransformListener tf;
    tf::StampedTransform t;
    tf.waitForTransform("map", "base_link", ros::Time(0), ros::Duration(5.0));
    float robotX, robotY, robotTheta;
    float goalX = 0.0;
    float goalY = 0.0;
    float error = 0.0, tolerance = 0.3;
    int pointOfPath = 0;
    std_msgs::Float32MultiArray msgSpeeds;
    while(ros::ok())
    {
        tf.lookupTransform("map", "base_link", ros::Time(0), t);
        robotX = t.getOrigin().x();
        robotY = t.getOrigin().y();
        tf::Quaternion q = t.getRotation();
        robotTheta = atan2((float)q.z(), (float)q.w()) * 2;
	if(achiveGoal)
	{
	 //
	 do
	 {
	  goalX = goalPath.poses[pointOfPath].pose.position.x;
	  goalY = goalPath.poses[pointOfPath].pose.position.y;
	  error = sqrt((goalX - robotX)*(goalX - robotX) + (goalY - robotY)*(goalY - robotY));
	  //std::cout << "Point of path: " << pointOfPath << std::endl;
	  //std::cout << "Error: " << error << "\tSize of path: " << goalPath.poses.size() << std::endl;
	  //pointOfPath++;
	 }while((error < tolerance) && (++pointOfPath < goalPath.poses.size()));
	 //
	 if(pointOfPath == goalPath.poses.size())
	 {
	  std::cout << "\tGoal has been achieved..."  << std::endl;
	  std::cout << "Point of path: " << pointOfPath << std::endl;
	  std::cout << "Last X: "  << goalX << "\tLast Y: "  << goalY << std::endl;
	  msgSpeeds.data[0] = 0.0;
	  msgSpeeds.data[0] = 0.0;
	  pubSp.publish(msgSpeeds);
	  pointOfPath = 0;
	  achiveGoal = false;
	 }
	 else
	 {
	  //std::cout << "Robot X: " << robotX << "\tRobot Y: " << robotY << std::endl;
	  //std::cout << "Goal X: " << goalX << "\tGoal Y: " << goalY << std::endl;
	  msgSpeeds.data = Controls::CalculateSpeeds(robotX, robotY, robotTheta, goalX,  goalY, 1);
	  //std::cout << "Robot X: " << robotX << "\tRobot Y: " << robotY << "\tRobot Th: " << robotTheta  << std::endl;
	  //std::cout << "Speed R: " << msgSpeeds.data[0] << "\tSpeed L: " << msgSpeeds.data[1] << std::endl;
          pubSp.publish(msgSpeeds);
	 }
	}
        ros::spinOnce();
        loop.sleep();
    }
    return 0;
}
