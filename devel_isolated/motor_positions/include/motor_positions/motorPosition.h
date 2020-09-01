// Generated by gencpp from file motor_positions/motorPosition.msg
// DO NOT EDIT!


#ifndef MOTOR_POSITIONS_MESSAGE_MOTORPOSITION_H
#define MOTOR_POSITIONS_MESSAGE_MOTORPOSITION_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace motor_positions
{
template <class ContainerAllocator>
struct motorPosition_
{
  typedef motorPosition_<ContainerAllocator> Type;

  motorPosition_()
    : motor_id(0)
    , position(0)  {
    }
  motorPosition_(const ContainerAllocator& _alloc)
    : motor_id(0)
    , position(0)  {
  (void)_alloc;
    }



   typedef uint8_t _motor_id_type;
  _motor_id_type motor_id;

   typedef uint16_t _position_type;
  _position_type position;





  typedef boost::shared_ptr< ::motor_positions::motorPosition_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::motor_positions::motorPosition_<ContainerAllocator> const> ConstPtr;

}; // struct motorPosition_

typedef ::motor_positions::motorPosition_<std::allocator<void> > motorPosition;

typedef boost::shared_ptr< ::motor_positions::motorPosition > motorPositionPtr;
typedef boost::shared_ptr< ::motor_positions::motorPosition const> motorPositionConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::motor_positions::motorPosition_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::motor_positions::motorPosition_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace motor_positions

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'motor_positions': ['/home/charles/devel/ros/scarab/scarab_ros/src/motor_positions/ROS-msgs'], 'std_msgs': ['/home/charles/catkin_ws/install_isolated/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::motor_positions::motorPosition_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::motor_positions::motorPosition_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::motor_positions::motorPosition_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::motor_positions::motorPosition_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::motor_positions::motorPosition_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::motor_positions::motorPosition_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::motor_positions::motorPosition_<ContainerAllocator> >
{
  static const char* value()
  {
    return "791e891bae681c33af37a246f28f5485";
  }

  static const char* value(const ::motor_positions::motorPosition_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x791e891bae681c33ULL;
  static const uint64_t static_value2 = 0xaf37a246f28f5485ULL;
};

template<class ContainerAllocator>
struct DataType< ::motor_positions::motorPosition_<ContainerAllocator> >
{
  static const char* value()
  {
    return "motor_positions/motorPosition";
  }

  static const char* value(const ::motor_positions::motorPosition_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::motor_positions::motorPosition_<ContainerAllocator> >
{
  static const char* value()
  {
    return "uint8  motor_id\n"
"uint16 position\n"
;
  }

  static const char* value(const ::motor_positions::motorPosition_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::motor_positions::motorPosition_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.motor_id);
      stream.next(m.position);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct motorPosition_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::motor_positions::motorPosition_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::motor_positions::motorPosition_<ContainerAllocator>& v)
  {
    s << indent << "motor_id: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.motor_id);
    s << indent << "position: ";
    Printer<uint16_t>::stream(s, indent + "  ", v.position);
  }
};

} // namespace message_operations
} // namespace ros

#endif // MOTOR_POSITIONS_MESSAGE_MOTORPOSITION_H
