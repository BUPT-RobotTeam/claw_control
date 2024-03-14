#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "bupt_can/bupt_can.h"
#include "motor_lib/dji_board.h"
#include <chrono>
#include <thread>
#include <iostream>

const int32_t maxPosVel = 500; //最大转动速度
const int32_t catchPose = 4500; //抓取命令转到的位置
const int32_t dropPose = 0; //松开命令转到的位置

//将board声明为全局变量
std::shared_ptr<Can> can_handle = std::make_shared<Can>("can0");
DJIBoard board(1,can_handle);

class node: public rclcpp::Node
{
private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscriber_;
    void topic_callback(const std_msgs::msg::String::SharedPtr msg)
    {
        // 输出接受到的消息
        // RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg->data.c_str());

        // 执行动作
        if (msg->data == "catch")
        {
            std::cout << "执行catch" << std::endl; //std是C++标准库的命名空间，用std::指明它们位于此命名空间
            board.PosCtrl(1, catchPose); //用MotorLib位置环
        }

        if (msg->data == "drop")
        {
            std::cout << "执行drop" << std::endl;
            board.PosCtrl(1, dropPose);
        }

        if (msg->data == "off")
        {
            std::cout << "motoroff" << std::endl;
            board.MotorOff(1);
        }
    }
public:
    node(std::string st) : Node(st)
    {
        RCLCPP_INFO(this->get_logger(), "爪夹控制节点启动");
        subscriber_ = this->create_subscription<std_msgs::msg::String>(
            "claw_control_topic", 10,
            std::bind(&node::topic_callback, this, std::placeholders::_1));
    }
    ~node()
    {
        RCLCPP_INFO(this->get_logger(), "爪夹控制节点关闭");
    }
};

class ROS_EVENT_LOOP
{
public:
    ROS_EVENT_LOOP(int argc, char *argv[],std::string st)
    {
        rclcpp::init(argc, argv);
        rclcpp::spin(std::make_shared<node>(st));
    }
    ~ROS_EVENT_LOOP()
    {
        rclcpp::shutdown();
    }
};

int main(int argc, char *argv[])
{
    //电机初始化
    can_handle->can_start();
    board.PosCfg(1, maxPosVel);
    board.MotorOn(1);
    ROS_EVENT_LOOP(argc, argv,"claw_control_node");
    return 0;
}