// Generated by gencpp from file motor_positions/trajectory.msg
// DO NOT EDIT!


#ifndef MOTOR_POSITIONS_MESSAGE_TRAJECTORY_H
#define MOTOR_POSITIONS_MESSAGE_TRAJECTORY_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <motor_positions/viaPoints.h>

namespace motor_positions
{
template <class ContainerAllocator>
struct trajectory_
{
  typedef trajectory_<ContainerAllocator> Type;

  trajectory_()
    : q()  {
    }
  trajectory_(const ContainerAllocator& _alloc)
    : q(_alloc)  {
  (void)_alloc;
    }



   typedef std::vector< ::motor_positions::viaPoints_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::motor_positions::viaPoints_<ContainerAllocator> >::other >  _q_type;
  _q_type q;





  typedef boost::shared_ptr< ::motor_positions::trajectory_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::motor_positions::trajectory_<ContainerAllocator> const> ConstPtr;

}; // struct trajectory_

typedef ::motor_positions::trajectory_<std::allocator<void> > trajectory;

typedef boost::shared_ptr< ::motor_positions::trajectory > trajectoryPtr;
typedef boost::shared_ptr< ::motor_positions::trajectory const> trajectoryConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::motor_positions::trajectory_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::motor_positions::trajectory_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace motor_positions

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'motor_positions': ['/home/charles/devel/ros/scarab/scarab_ros/src/motor_positions/ROS-msgs'], 'std_msgs': ['/home/charles/catkin_ws/install_isolated/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::motor_positions::trajectory_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::motor_positions::trajectory_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::motor_positions::trajectory_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::motor_positions::trajectory_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::motor_positions::trajectory_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::motor_positions::trajectory_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::motor_positions::trajectory_<ContainerAllocator> >
{
  static const char* value()
  {
    return "e22957dcc8eb24a0e55afb89801e2607";
  }

  static const char* value(const ::motor_positions::trajectory_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xe22957dcc8eb24a0ULL;
  static const uint64_t static_value2 = 0xe55afb89801e2607ULL;
};

template<class ContainerAllocator>
struct DataType< ::motor_positions::trajectory_<ContainerAllocator> >
{
  static const char* value()
  {
    return "motor_positions/trajectory";
  }

  static const char* value(const ::motor_positions::trajectory_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::motor_positions::trajectory_<ContainerAllocator> >
{
  static const char* value()
  {
    return "viaPoints[] q\n"
"\n"
"================================================================================\n"
"MSG: motor_positions/viaPoints\n"
"uint16 motor_1\n"
"uint16 motor_2\n"
"uint16 motor_3\n"
"uint16 motor_4\n"
;
  }

  static const char* value(const ::motor_positions::trajectory_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::motor_positions::trajectory_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.q);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct trajectory_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::motor_positions::trajectory_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::motor_positions::trajectory_<ContainerAllocator>& v)
  {
    s << indent << "q[]" << std::endl;
    for (size_t i = 0; i < v.q.size(); ++i)
    {
      s << indent << "  q[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::motor_positions::viaPoints_<ContainerAllocator> >::stream(s, indent + "    ", v.q[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // MOTOR_POSITIONS_MESSAGE_TRAJECTORY_H
