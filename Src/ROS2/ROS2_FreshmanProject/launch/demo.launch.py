# 导入库
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    """launch内容描述函数，由ros2 launch 扫描调用"""
    action_01 = Node(
        package="ROS2_FreshmanProject",
        executable="serial_node"
    )
    action_02 = Node(
        package="ROS2_FreshmanProject",
        executable="tf2_node"
    )
    action_03 = Node(
        package="ROS2_FreshmanProject",
        executable="control_node"
    )
    # 创建LaunchDescription对象launch_description,用于描述launch文件
    launch_description = LaunchDescription(
        [action_01, action_02, action_03])
    # 返回让ROS2根据launch描述执行节点
    return launch_description
