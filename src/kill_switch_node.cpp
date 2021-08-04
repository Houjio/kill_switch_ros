#include "ros/ros.h"
#include "std_msgs/Bool.h" 

void killSwitchCallback(const std_msgs::Bool::ConstPtr& kill_switch_bool)
{
  // ROS_INFO("I heard: [%s]", msg->data.c_str());
  ROS_INFO("Caught killswitch");
  if (!kill_switch_bool[0]) {
    ROS_INFO("falsy");
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
