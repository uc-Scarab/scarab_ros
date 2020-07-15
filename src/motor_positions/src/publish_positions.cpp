#include <boost/thread/pthread/mutex.hpp>
#include <ostream>
#include <string>
#include <iostream>
#include <cstdio>
#include "serial/serial.h"

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
class SerialComs {
        boost::mutex mtx_;
        serial::Serial teensy_serial;
        ros::NodeHandle node;
        std::string port;
        int baud;

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


    std::cout << "Port:" << port << std::endl;

    if(teensy_serial.isOpen())
        ROS_INFO("serial open");
    else
        ROS_INFO("serial not open");
        }
            

    

    void controlCallback(motor_positions::controlTable msg){
        boost::lock_guard<boost::mutex> guard(this->mtx_);
     ROS_INFO_STREAM(msg);
     serial::Serial teensy_serial(this->port, this->baud, serial::Timeout::simpleTimeout(1000));

    uint8_t control_buffer[8];
    
    control_buffer[0] = LOWER_BYTE(60000);
    control_buffer[1] = UPPER_BYTE(60000);
    control_buffer[2] = 5;
    control_buffer[3] = msg.motor_id;
    control_buffer[4] = msg.command_id;
    control_buffer[5] = LOWER_BYTE(msg.value);
    control_buffer[6] = UPPER_BYTE(msg.value);
    control_buffer[7] = 244;

    teensy_serial.write(control_buffer, 8);
    my_sleep(100);

    
}

void writeControl(){
     ros::Subscriber sub = node.subscribe("dynamixel_control", 1000, &SerialComs::controlCallback, this);
     ros::spin();
}

void receivePositions(int baud, std::string port){
   ros::Publisher publisher = node.advertise<motor_positions::positionArray>("publisher_positions", 1);
       serial::Serial teensy_serial(port, baud, serial::Timeout::simpleTimeout(1000));

   while(1){
    boost::lock_guard<boost::mutex> guard(mtx_);
       //std::cout << "open?:" << teensy_serial.isOpen() << std::endl;
        //uint8_t test_buffer[3];
        //teensy_serial.read(test_buffer, 3);
        //std::cout << "available:" << teensy_serial.available() << std::endl;

        if(teensy_serial.available() >= 3){
            uint8_t check_buffer[3];
            teensy_serial.read(check_buffer, 3);
            uint16_t check = INT_JOIN_BYTE(check_buffer[1], check_buffer[0]);
            //uint16_t check = 60000;
                //cout << "check:" << check << std::endl;
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
     //int baud = 115200;
        //serial::Serial teensy_serial(port, baud, serial::Timeout::simpleTimeout(1000));

    //uint8_t control_buffer[3];

    //while(1){

    //control_buffer[0] = LOWER_BYTE(60000); 
    //control_buffer[1] = UPPER_BYTE(60000);
    //control_buffer[2] = 5;
    //teensy_serial.write(control_buffer, 3);
    //std::cout << "sending" << std::endl;
    //my_sleep(2000);
    //}
    //return 0;
    
//}



    ros::init(argc, argv, "publish_positions");
    ros::NodeHandle node;
    SerialComs teensy_serial(node); 
    
    std::string port = "/dev/ttyACM0";
   int baud = 115200;


  

    boost::thread read(&SerialComs::receivePositions, &teensy_serial, baud, port);
    boost::thread write(&SerialComs::writeControl, &teensy_serial);
    read.join();
   write.join();
    return 0;
    
}
