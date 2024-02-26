# 设定名称
workspace_name="dev_ws" # 工作空间
motorlib_name="MotorLib-For-Linux" # MotorLib功能包名
bupt_can_name="bupt_can_node" # MotorLib依赖的bupt_can的包名


echo "setup can"
~/$workspace_name/src/$motorlib_name/third_party/$bupt_can_name/setup_can.sh
echo "开始运行，正在监听话题"
~/$workspace_name/build/claw_control/claw_control
