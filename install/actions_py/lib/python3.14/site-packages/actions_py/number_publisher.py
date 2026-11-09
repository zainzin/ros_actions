import rclpy
from rclpy.node import Node
from rclpy.executors import MultiThreadedExecutor
from rclpy.callback_groups import ReentrantCallbackGroup
from std_msgs.msg import Int32

class NumberPublisherNode(Node):
    def __init__(self):
        super().__init__('number_publisher')
        self.counter = 0
        self.publisher = self.create_publisher(Int32,
                                               "number_publisher",
                                               10,
                                               callback_group=ReentrantCallbackGroup())
        self.timer = self.create_timer(1, self.publish)

    def publish(self):
        msg = Int32()
        msg.data = self.counter
        self.publisher.publish(msg)
        self.counter += 1

def main(args=None):
    rclpy.init(args=args)
    node = NumberPublisherNode()
    executor = MultiThreadedExecutor()
    executor.add_node(node)
    executor.spin()
    node.destroy_node()
    rclpy.shutdown()