#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#include <geometry_msgs/Point.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "location_markers");
  ros::NodeHandle n;
  ros::Rate loop_rate(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("/hri/rviz/visualization_marker", 1);
  std::cout << "Initializing location markers node..." << std::endl;
  uint32_t shape = visualization_msgs::Marker::POINTS;

  geometry_msgs::Point point;
  visualization_msgs::Marker marker;
  // Set the frame ID and timestamp.  See the TF tutorials for information on these.
  marker.header.frame_id = "map";
  marker.header.stamp = ros::Time::now();

  // Set the namespace and id for this marker.  This serves to create a unique ID
  // Any marker sent with the same namespace and id will overwrite the old one
  marker.ns = "locations";
  

  // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
  //marker.type = visualization_msgs::Marker::CUBE;
  marker.type = shape;


  // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
  marker.action = visualization_msgs::Marker::ADD;

  // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header

  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = 1.0;

  // Set the scale of the marker -- 1x1x1 here means 1m on a side
  marker.scale.x = 0.7;
  marker.scale.y = 0.7;
  marker.scale.z = 0.7;//0.1

  // Set the color -- be sure to set alpha to something non-zero!
  marker.color.r = 0.0f;
  marker.color.g = 1.0f;
  marker.color.b = 0.0f;
  marker.color.a = 1.0;

  marker.lifetime = ros::Duration();

  marker.id = 0;
  point.x = 1;
  point.y = 1;
  point.z = 0.075;
  marker.points.push_back(point);

  marker.id = 1;
  point.x = 2;
  point.y = 2;
  point.z = 0.075;
  marker.points.push_back(point);

  while (ros::ok())
  {
    /*marker.id = 0;
    marker.pose.position.x = 0;
    marker.pose.position.y = 0;
    marker.pose.position.z = 0;*/
    //marker.header.stamp = ros::Time::now();
    marker.type = shape;
    marker_pub.publish(marker);
    ros::spinOnce();

    /*switch (shape)
    {
    case visualization_msgs::Marker::SPHERE_LIST:
      shape = visualization_msgs::Marker::POINTS;
      break;
    case visualization_msgs::Marker::TRIANGLE_LIST:
      shape = visualization_msgs::Marker::POINTS;
      break;
    case visualization_msgs::Marker::POINTS:
      shape = visualization_msgs::Marker::CUBE_LIST;
      break;
    case visualization_msgs::Marker::CUBE_LIST:
      shape = visualization_msgs::Marker::SPHERE_LIST;
      break;
    }*/
    //std::cout << "Publishing..." << std::endl;
    loop_rate.sleep();
  }
}
