# Claw_Control

基于ROS2开发的控制爪夹的功能包

## 1. 环境与依赖

### 1.1 环境

- Ubuntu 22.04

### 1.2 依赖

- ROS 2 Humble
- [MotorLib-For-Linux](https://github.com/BUPT-RobotTeam/MotorLib-For-Linux)

## 2. 使用方法

1. 将此功能包放入工作空间，修改launch.sh内的路径名称，直接运行此脚本即可
    ```shell
    bash launch.sh
    ```

2. 控制电机请向 /claw_control_topic 话题发送 std_msgs/msg/String 类型的消息： catch 或 drop 或 off

## 3. 内部原理

创建 claw_control 节点\
对外暴露 claw_control_topic 话题，监听字符串类型的消息\
内部调用 MotorLib 库，使用位置环控制电机

