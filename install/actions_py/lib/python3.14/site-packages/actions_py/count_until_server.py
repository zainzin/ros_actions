import rclpy
from rclpy.node import Node
from rclpy.action import ActionServer

class CountUntilServer(Node):
    def __init__(self):
        super().__init__('count_until_server_node')
        self.count_until_server = ActionServer()
