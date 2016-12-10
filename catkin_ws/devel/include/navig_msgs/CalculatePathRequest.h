// Generated by gencpp from file navig_msgs/CalculatePathRequest.msg
// DO NOT EDIT!


#ifndef NAVIG_MSGS_MESSAGE_CALCULATEPATHREQUEST_H
#define NAVIG_MSGS_MESSAGE_CALCULATEPATHREQUEST_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Pose.h>
#include <nav_msgs/OccupancyGrid.h>

namespace navig_msgs
{
template <class ContainerAllocator>
struct CalculatePathRequest_
{
  typedef CalculatePathRequest_<ContainerAllocator> Type;

  CalculatePathRequest_()
    : start_pose()
    , goal_pose()
    , map()  {
    }
  CalculatePathRequest_(const ContainerAllocator& _alloc)
    : start_pose(_alloc)
    , goal_pose(_alloc)
    , map(_alloc)  {
  (void)_alloc;
    }



   typedef  ::geometry_msgs::Pose_<ContainerAllocator>  _start_pose_type;
  _start_pose_type start_pose;

   typedef  ::geometry_msgs::Pose_<ContainerAllocator>  _goal_pose_type;
  _goal_pose_type goal_pose;

   typedef  ::nav_msgs::OccupancyGrid_<ContainerAllocator>  _map_type;
  _map_type map;




  typedef boost::shared_ptr< ::navig_msgs::CalculatePathRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::navig_msgs::CalculatePathRequest_<ContainerAllocator> const> ConstPtr;

}; // struct CalculatePathRequest_

typedef ::navig_msgs::CalculatePathRequest_<std::allocator<void> > CalculatePathRequest;

typedef boost::shared_ptr< ::navig_msgs::CalculatePathRequest > CalculatePathRequestPtr;
typedef boost::shared_ptr< ::navig_msgs::CalculatePathRequest const> CalculatePathRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::navig_msgs::CalculatePathRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::navig_msgs::CalculatePathRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace navig_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'nav_msgs': ['/opt/ros/indigo/share/nav_msgs/cmake/../msg'], 'sensor_msgs': ['/opt/ros/indigo/share/sensor_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/indigo/share/actionlib_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/indigo/share/geometry_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::navig_msgs::CalculatePathRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::navig_msgs::CalculatePathRequest_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::navig_msgs::CalculatePathRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::navig_msgs::CalculatePathRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::navig_msgs::CalculatePathRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::navig_msgs::CalculatePathRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::navig_msgs::CalculatePathRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "2a75d2c32f93ff2373731b21edc31f79";
  }

  static const char* value(const ::navig_msgs::CalculatePathRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x2a75d2c32f93ff23ULL;
  static const uint64_t static_value2 = 0x73731b21edc31f79ULL;
};

template<class ContainerAllocator>
struct DataType< ::navig_msgs::CalculatePathRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "navig_msgs/CalculatePathRequest";
  }

  static const char* value(const ::navig_msgs::CalculatePathRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::navig_msgs::CalculatePathRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "geometry_msgs/Pose start_pose\n\
geometry_msgs/Pose goal_pose\n\
nav_msgs/OccupancyGrid map\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Pose\n\
# A representation of pose in free space, composed of postion and orientation. \n\
Point position\n\
Quaternion orientation\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Point\n\
# This contains the position of a point in free space\n\
float64 x\n\
float64 y\n\
float64 z\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Quaternion\n\
# This represents an orientation in free space in quaternion form.\n\
\n\
float64 x\n\
float64 y\n\
float64 z\n\
float64 w\n\
\n\
================================================================================\n\
MSG: nav_msgs/OccupancyGrid\n\
# This represents a 2-D grid map, in which each cell represents the probability of\n\
# occupancy.\n\
\n\
Header header \n\
\n\
#MetaData for the map\n\
MapMetaData info\n\
\n\
# The map data, in row-major order, starting with (0,0).  Occupancy\n\
# probabilities are in the range [0,100].  Unknown is -1.\n\
int8[] data\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n\
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
\n\
================================================================================\n\
MSG: nav_msgs/MapMetaData\n\
# This hold basic information about the characterists of the OccupancyGrid\n\
\n\
# The time at which the map was loaded\n\
time map_load_time\n\
# The map resolution [m/cell]\n\
float32 resolution\n\
# Map width [cells]\n\
uint32 width\n\
# Map height [cells]\n\
uint32 height\n\
# The origin of the map [m, m, rad].  This is the real-world pose of the\n\
# cell (0,0) in the map.\n\
geometry_msgs/Pose origin\n\
";
  }

  static const char* value(const ::navig_msgs::CalculatePathRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::navig_msgs::CalculatePathRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.start_pose);
      stream.next(m.goal_pose);
      stream.next(m.map);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER;
  }; // struct CalculatePathRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::navig_msgs::CalculatePathRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::navig_msgs::CalculatePathRequest_<ContainerAllocator>& v)
  {
    s << indent << "start_pose: ";
    s << std::endl;
    Printer< ::geometry_msgs::Pose_<ContainerAllocator> >::stream(s, indent + "  ", v.start_pose);
    s << indent << "goal_pose: ";
    s << std::endl;
    Printer< ::geometry_msgs::Pose_<ContainerAllocator> >::stream(s, indent + "  ", v.goal_pose);
    s << indent << "map: ";
    s << std::endl;
    Printer< ::nav_msgs::OccupancyGrid_<ContainerAllocator> >::stream(s, indent + "  ", v.map);
  }
};

} // namespace message_operations
} // namespace ros

#endif // NAVIG_MSGS_MESSAGE_CALCULATEPATHREQUEST_H
