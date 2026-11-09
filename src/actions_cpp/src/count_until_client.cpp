//
// Created by Zain Hatim on 10/17/26.
//
#include "rclcpp/rclcpp.hpp"
#include "my_robot_interfaces/action/count_until.hpp"
#include "rclcpp_action/rclcpp_action.hpp"

using CountUntil = my_robot_interfaces::action::CountUntil;
using GoalHandle = rclcpp_action::ClientGoalHandle<CountUntil>;

class CountUntilClient : public rclcpp::Node {
    public:
    CountUntilClient() : Node("count_until_client") {
        action_client_ = rclcpp_action::create_client<CountUntil>(this, "count_until");

    }
    void send_goal(int target_number, double period) {
        this->action_client_->wait_for_action_server();
        auto goal = CountUntil::Goal();
        goal.target_number = target_number;
        goal.period = period;
        RCLCPP_INFO(this->get_logger(), "Sending goal");
        this->action_client_->async_send_goal(goal);
    }
private:
    rclcpp_action::Client<CountUntil>::SharedPtr action_client_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<CountUntilClient>();
    node->send_goal(6, 0.8);
    rclcpp::spin(node);
    // rclcpp::executor::execute_on();
    rclcpp::shutdown();
    return 0;
}