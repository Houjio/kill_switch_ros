#include "ros/ros.h"
#include "std_msgs/Bool.h" 

void killSwitchCallback(const std_msgs::Bool::ConstPtr& kill_switch_bool)
{
  if (!kill_switch_bool->data) {
    ROS_INFO("Caught killswitch");
    // TODO When a message is received, the value of the GPIO pin with id killswitch_pin must be set to the value contained 
    //      in killswitch_pin_default if the value of the message is false.
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");

  ros::NodeHandle nh;

  // TODO PIN AND DEFAULT VALUE MUST BE CHANGED
  nh.setParam("/killswitch_pin", 8);
  nh.setParam("/killswitch_pin_default_value", true);

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("killswitch_state", 1000, killSwitchCallback);

  ros::spin();

  return 0;
}
