#include <fstream>
#include <string>
#include <sstream>

#include "ros/ros.h"
#include "std_msgs/Bool.h"

using namespace std;

void killSwitchCallback(const std_msgs::Bool::ConstPtr& kill_switch_bool)
{
  bool killswitch_pin_default_value;
  int killswitch_pin;

  ros::param::get("/killswitch_pin_default_value", killswitch_pin_default_value);
  ros::param::get("/killswitch_pin", killswitch_pin);
  
  std::stringstream dirss;
  dirss << "/sys/class/gpio" << killswitch_pin << "/value";
  std::string dir = dirss.str();

  ofstream file ( dir );

  if (kill_switch_bool->data) {
    ROS_INFO("Caught killswitch true");
    if (killswitch_pin_default_value) {
      file<<"1";
    } else {
      file<<"0";
    }
  } else {
    ROS_INFO("Caught killswitch false");
    if (killswitch_pin_default_value) {
      file<<"0";
    } else {
      file<<"1";
    }
  }

  file.close();
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
