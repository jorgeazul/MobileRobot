#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include <math.h>
#include "visualization_msgs/Marker.h"
#include "geometry_msgs/Point.h"
//#include "tf/TransformListener.h"
#include "tf/transform_listener.h"
#include "std_msgs/Float32MultiArray.h"
//Launch path tracking nl

float d0 = 6.0, eta = 7.0, robotTheta = 0.0, sum_x = 0.0, sum_y = 0.0;
float robotX, robotY;
float rejectionX, rejectionY;
float attractionX, attractionY, gama = 7.0;
float goalPoseX = 0.0, goalPoseY = 4.0;

std::vector<float> calculate_rejection(const sensor_msgs::LaserScan::ConstPtr& msg)
{
  std::cout << msg->ranges.size() << " " << msg->angle_min << " " << msg->angle_increment << std::endl;
  for(int i=0; i < msg->ranges.size(); i++)
  {
    float dist = msg->ranges[i];
    float angle = msg->angle_min + msg->angle_increment * i;
    float mag = dist < d0 ? sqrt(1.0/dist -1.0/d0)*eta : 0;
    float rej_x = -cos(angle + robotTheta) * mag;
    float rej_y = -sin(angle + robotTheta) * mag;
    sum_x += rej_x;
    sum_y += rej_y;
  }
  sum_x /= msg->ranges.size();
  sum_y /= msg->ranges.size();
  std::cout << "Sum x: " <<  sum_x  << "      Sum y: " <<  sum_y << std::endl;
}

void callback_Goal_Pose(const std_msgs::Float32MultiArray::ConstPtr& msg)
{
  goalPoseX = msg->data[0];
  goalPoseY = msg->data[1];
  /*attractionX = (msg->data[0] - robotX);
  attractionY = (msg->data[1] - robotY);
  float magnitud = sqrt(attractionX*attractionX + attractionY*attractionY);
  attractionX = gama * attractionX / magnitud;
  attractionY = gama * attractionY / magnitud;*/
}

void callback_Scan(const sensor_msgs::LaserScan::ConstPtr& msg)
{
  std::cout << "Receiving data callback_Scan..." << std::endl;

  std::cout << msg->ranges.size() << " " << msg->angle_min << " " << msg->angle_increment << std::endl;
  for(int i=0; i < msg->ranges.size(); i++)
  {
    float dist = msg->ranges[i];
    float angle = msg->angle_min + msg->angle_increment * i;
    float mag = dist < d0 ? sqrt(1.0/dist -1.0/d0)*eta : 0;
    float rej_x = -cos(angle + robotTheta) * mag;
    float rej_y = -sin(angle + robotTheta) * mag;
    sum_x += rej_x;
    sum_y += rej_y;
  }
  sum_x /= msg->ranges.size();
  sum_y /= msg->ranges.size();
  std::cout << "Sum x: " <<  sum_x  << "      Sum y: " <<  sum_y << std::endl;
  rejectionX = sum_x;
  rejectionY = sum_y;
}
//Transform listener, transform stamp, wait for transform

//Cuaternion posision del robot


int main(int argc, char **argv)
{
  std::cout << "Initializing potential fields node..." << std::endl;
  ros::init(argc, argv, "potential_fields");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("/hardware/scan", 1, callback_Scan);
  ros::Subscriber subGoalPose = n.subscribe("/navigation/goal_pose", 1, callback_Goal_Pose);
  ros::Publisher pubRej = n.advertise<visualization_msgs::Marker>("/hri/visualization_marker", 1);
  visualization_msgs::Marker pubMsgRej;


  geometry_msgs::Point startRej;
  geometry_msgs::Point endRej;

  endRej.x = 1.0;
  endRej.y = 1.0;

  pubMsgRej.id = 0;
  pubMsgRej.header.frame_id = "map";
  pubMsgRej.type = visualization_msgs::Marker::ARROW;
  pubMsgRej.ns = "potential_fields";
  pubMsgRej.action = visualization_msgs::Marker::ADD;
  pubMsgRej.lifetime = ros::Duration();
  pubMsgRej.points.push_back(startRej);
  pubMsgRej.points.push_back(endRej);
  pubMsgRej.color.r = 1.0;
  pubMsgRej.color.g = 0.0;
  pubMsgRej.color.b = 0.0;
  pubMsgRej.color.a = 1.0;
  pubMsgRej.scale.x = 0.05;
  pubMsgRej.scale.y = 0.05;
  pubMsgRej.scale.z = 0.0;

  visualization_msgs::Marker pubMsgAttraction;
  pubMsgAttraction = pubMsgRej;

  pubMsgAttraction.id = 1;
  pubMsgAttraction.color.r = 0.0;
  pubMsgAttraction.color.g = 1.0;
  pubMsgAttraction.color.b = 1.0;

  visualization_msgs::Marker pubMsgResult;
  pubMsgResult = pubMsgRej;

  pubMsgResult.id = 2;
  pubMsgResult.color.r = 0.0;
  pubMsgResult.color.g = 0.0;
  pubMsgResult.color.b = 1.0;
  
  tf::TransformListener tf;
  tf::StampedTransform t;
  tf.waitForTransform("map", "base_link", ros::Time(0), ros::Duration(5.0));


  ros::Rate loop_rate(10);

  int count = 0;
  while (ros::ok())
  {
    tf.lookupTransform("map", "base_link", ros::Time(0), t);
    robotX = t.getOrigin().x();
    robotY = t.getOrigin().y();
    tf::Quaternion q = t.getRotation();
    robotTheta = atan2((float)q.z(), (float)q.w()) * 2;

    attractionX = (goalPoseX - robotX);
    attractionY = (goalPoseY - robotY);
    float magnitud = sqrt(attractionX*attractionX + attractionY*attractionY);
    attractionX = gama * attractionX / magnitud;
    attractionY = gama * attractionY / magnitud;

    pubMsgRej.points[0].x = robotX;
    pubMsgRej.points[0].y = robotY;
    pubMsgRej.points[1].x = robotX + rejectionX;
    pubMsgRej.points[1].y = robotY + rejectionY;

    pubMsgAttraction.points[0].x = robotX;
    pubMsgAttraction.points[0].y = robotY;
    pubMsgAttraction.points[1].x = robotX + attractionX;
    pubMsgAttraction.points[1].y = robotY + attractionY;

    pubMsgResult.points[0].x = robotX;
    pubMsgResult.points[0].y = robotY;
    pubMsgResult.points[1].x = robotX + rejectionX + attractionX;
    pubMsgResult.points[1].y = robotY + rejectionY + attractionY;

    pubRej.publish(pubMsgRej);//Rojo
    pubRej.publish(pubMsgAttraction);//Verde
    pubRej.publish(pubMsgResult);//Azul
    ros::spinOnce();

    loop_rate.sleep();
    //++count;
  }


  return 0;
}
