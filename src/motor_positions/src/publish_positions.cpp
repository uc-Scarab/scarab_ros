#include <boost/thread/pthread/mutex.hpp>
#include <ostream>
#include <string>
#include <iostream>
#include <cstdio>
#include "serial/serial.h"
#include <math.h>

// OS Specific sleep
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <motor_positions/motorPosition.h>
#include <motor_positions/positionArray.h>
#include <motor_positions/controlTable.h>
#include <boost/thread/thread.hpp>

#define UPPER_BYTE(b) (b >> 8) //defines byte structure 
#define LOWER_BYTE(b) (b & 0xff)
#define INT_JOIN_BYTE(u, l) (u << 8) | l

using std::cout;

void my_sleep(unsigned long milliseconds){
        #ifdef _WIN32
            Sleep(milliseconds);
        #else
            usleep(milliseconds*1000);
        #endif
    }


enum ControlTableItem{

  MODEL_NUMBER = 0,

  MODEL_INFORMATION,

  FIRMWARE_VERSION,

  PROTOCOL_VERSION,

  ID,

  SECONDARY_ID,

  BAUD_RATE,

  DRIVE_MODE,

  CONTROL_MODE,

  OPERATING_MODE,

  CW_ANGLE_LIMIT,

  CCW_ANGLE_LIMIT,

  TEMPERATURE_LIMIT,

  MIN_VOLTAGE_LIMIT,

  MAX_VOLTAGE_LIMIT,

  PWM_LIMIT,

  CURRENT_LIMIT,

  VELOCITY_LIMIT,

  MAX_POSITION_LIMIT,

  MIN_POSITION_LIMIT,

  ACCELERATION_LIMIT,

  MAX_TORQUE,

  HOMING_OFFSET,

  MOVING_THRESHOLD,

  MULTI_TURN_OFFSET,

  RESOLUTION_DIVIDER,

  EXTERNAL_PORT_MODE_1,

  EXTERNAL_PORT_MODE_2,

  EXTERNAL_PORT_MODE_3,

  EXTERNAL_PORT_MODE_4,

  STATUS_RETURN_LEVEL,

  RETURN_DELAY_TIME,

  ALARM_LED,

  SHUTDOWN,



  TORQUE_ENABLE,

  LED,

  LED_RED,

  LED_GREEN,

  LED_BLUE,

  REGISTERED_INSTRUCTION,

  HARDWARE_ERROR_STATUS,

  VELOCITY_P_GAIN,

  VELOCITY_I_GAIN,

  POSITION_P_GAIN,

  POSITION_I_GAIN,

  POSITION_D_GAIN,

  FEEDFORWARD_1ST_GAIN,

  FEEDFORWARD_2ND_GAIN,

  P_GAIN,

  I_GAIN,

  D_GAIN,

  CW_COMPLIANCE_MARGIN,

  CCW_COMPLIANCE_MARGIN,

  CW_COMPLIANCE_SLOPE,

  CCW_COMPLIANCE_SLOPE,

  GOAL_PWM,

  GOAL_TORQUE,

  GOAL_CURRENT,

  GOAL_POSITION,

  GOAL_VELOCITY,

  GOAL_ACCELERATION,

  MOVING_SPEED,

  PRESENT_PWM,

  PRESENT_LOAD,

  PRESENT_SPEED,

  PRESENT_CURRENT,

  PRESENT_POSITION,

  PRESENT_VELOCITY,

  PRESENT_VOLTAGE,

  PRESENT_TEMPERATURE,

  TORQUE_LIMIT,

  REGISTERED,

  MOVING,

  LOCK,

  PUNCH,

  CURRENT,

  SENSED_CURRENT,

  REALTIME_TICK,

  TORQUE_CTRL_MODE_ENABLE,

  BUS_WATCHDOG,

  PROFILE_ACCELERATION,

  PROFILE_VELOCITY,

  MOVING_STATUS,

  VELOCITY_TRAJECTORY,

  POSITION_TRAJECTORY,

  PRESENT_INPUT_VOLTAGE,

  EXTERNAL_PORT_DATA_1,

  EXTERNAL_PORT_DATA_2,

  EXTERNAL_PORT_DATA_3,

  EXTERNAL_PORT_DATA_4,



  LAST_DUMMY_ITEM = 0xFF

};

class SerialComs {
        boost::mutex mtx_;
        serial::Serial teensy_serial;
       //serial::Serial read_serial;
        ros::NodeHandle node;
        std::string port;
        int baud = 115200;

    public:
        SerialComs(ros::NodeHandle out_node) {
        node = out_node;
    std::string vid_pid = "2341:0043"; // vid/pid for an Arduino Uno
    std::string teensy = "16c0:0483"; // vid/pid for the Teensy4.0
    std::string diff = "CP2102"; // If the description of the device contains this then it isn't the coms cable.
    std::string port;

    std::vector<serial::PortInfo> devices_found = serial::list_ports();
    std::vector<serial::PortInfo>::iterator iter = devices_found.begin();

    while(iter != devices_found.end()){
        serial::PortInfo device = *iter++;
        std::cout << "id" << device.hardware_id << std::endl;

        if (device.hardware_id != "n/a"){
        std::string ids = device.hardware_id.substr(12, 10);
        if (ids.compare(vid_pid) or ids.compare(teensy) or ids.compare(diff)){
            port = device.port;
            std::cout << "description:" << device.description << std::endl;
        }
        }

    }
     serial::Serial teensy_serial(this->port, this->baud, serial::Timeout::simpleTimeout(1000));
 

    std::cout << "Port:" << port << std::endl;

    if(teensy_serial.isOpen())
        ROS_INFO("serial open");
    else
        ROS_INFO("serial not open");
        }
           
    int position_rpm_to_raw(float theoretical){
        int float_raw = theoretical * (4095 / 6.283);
        int rounded_raw = round(float_raw);
        return rounded_raw;
    }
    

    void controlCallback(motor_positions::controlTable msg){
        boost::lock_guard<boost::mutex> guard(this->mtx_);
     ROS_INFO_STREAM(msg);
     //serial::Serial teensy_serial(this->port, this->baud, serial::Timeout::simpleTimeout(1000));
        std::string port = "/dev/ttyACM0";

    uint8_t control_buffer[8];

    int value;

    value = position_rpm_to_raw(msg.value);
    
    control_buffer[0] = LOWER_BYTE(60000);
    control_buffer[1] = UPPER_BYTE(60000);
    control_buffer[2] = 5;
    control_buffer[3] = msg.motor_id;
    control_buffer[4] = msg.command_id;
    control_buffer[5] = LOWER_BYTE(value);
    control_buffer[6] = UPPER_BYTE(value);
    control_buffer[7] = 244;

    //teensy_serial.write(control_buffer, 8);
    ROS_INFO_STREAM(value);
    my_sleep(100);

    
}

void writeControl(){
     boost::lock_guard<boost::mutex> guard(this->mtx_);
     ros::Subscriber sub = node.subscribe("dynamixel_control", 1000, &SerialComs::controlCallback, this);
     ros::spin();
}

void receivePositions(int baud, std::string port){
   ros::Publisher publisher = node.advertise<motor_positions::positionArray>("publisher_positions", 1);
       serial::Serial teensy_serial(port, baud, serial::Timeout::simpleTimeout(1000));

   while(1){
    boost::lock_guard<boost::mutex> guard(mtx_);

        if(teensy_serial.available() >= 3){
            uint8_t check_buffer[3];
            teensy_serial.read(check_buffer, 3);
            uint16_t check = INT_JOIN_BYTE(check_buffer[1], check_buffer[0]);
                if(check != 60000){
                teensy_serial.flushInput();
                ROS_ERROR_STREAM("front: check:" << check);
                //cout << "flushed" << std::endl;
                
                } else {
                    motor_positions::motorPosition motor;
                    motor_positions::positionArray msg; 
                    int payload = int(check_buffer[2]);
                    uint8_t message_buffer[payload];
                    teensy_serial.read(message_buffer, payload);

                    for(int i=0;i<payload -3;i+=3){
                        //cout << "id:" << int(message_buffer[i]) << std::endl;
                        int int_id = int(message_buffer[i]);
                        ROS_INFO_STREAM("id:" << int_id);
                        motor.motor_id = message_buffer[i];
                        uint16_t full_byte = INT_JOIN_BYTE(message_buffer[i + 2], message_buffer[i + 1]);
                        //cout << "position" << int(full_byte) << std::endl;
                        //cout << "---------" << std::endl;
                        int int_full_byte = int(full_byte);
                        ROS_INFO_STREAM("position:" << int_full_byte);
                        motor.position = full_byte;
                        msg.positions.push_back(motor);
                    
                    publisher.publish(msg);

                    }

                    //if (message_buffer[payload - 1] != 244){
                        //ROS_ERROR_STREAM("back check" << message_buffer[payload - 1]);
                    //teensy_serial.flushInput();
                    //}
        }
                    
                }
          
    }
}



        };



int main(int argc, char**argv){

    ros::init(argc, argv, "publish_positions");
    ros::NodeHandle node;
    SerialComs teensy_serial(node); 
    
    std::string port = "/dev/ttyACM0";
   int baud = 115200;


  

    //boost::thread read(&SerialComs::receivePositions, &teensy_serial, baud, port);
    boost::thread write(&SerialComs::writeControl, &teensy_serial);
    //read.join();
   write.join();
    return 0;
    
}
