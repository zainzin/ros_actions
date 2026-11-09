//
// Created by Zain Hatim on 10/17/26.
//
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "my_robot_interfaces/action/count_until.hpp"

using CountUntil = my_robot_interfaces::action::CountUntil;
using GoalHandle = rclcpp_action::ServerGoalHandle<CountUntil>;

using namespace std::placeholders;

class CountUntilServer : public rclcpp::Node {
    public:
    CountUntilServer() : Node("count_until_server") {
        count_until_server_ = rclcpp_action::create_server<CountUntil>(
            this,
            "count_until",
            std::bind(&CountUntilServer::goal_callback, this, _1, _2),
            std::bind(&CountUntilServer::cancel_callback, this, _1),
            std::bind(&CountUntilServer::handle_accepeted, this, _1));
        RCLCPP_INFO(this->get_logger(), "Action has been started successfully.");
    }
private:
    rclcpp_action::Server<CountUntil>::SharedPtr count_until_server_;
    rclcpp_action::GoalResponse goal_callback(const rclcpp_action::GoalUUID &uuid, std::shared_ptr<const CountUntil::Goal> goal) {
        (void)uuid;
        return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
    }
    rclcpp_action::CancelResponse cancel_callback(const std::shared_ptr<GoalHandle> goal_handle) {
        (void)goal_handle;
        return rclcpp_action::CancelResponse::ACCEPT;
    }
    void handle_accepeted(const std::shared_ptr<GoalHandle> goal_handle) {
        execute_goal(goal_handle);
    }
    void execute_goal(const std::shared_ptr<GoalHandle> goal_handle) {
        int target_number = goal_handle->get_goal()->target_number;
        double period = goal_handle->get_goal()->period;
        int counter = 0;
        rclcpp::Rate rate(1.0/period);
        for (int i = 0; i < target_number; ++i) {
            counter++;
            RCLCPP_INFO(this->get_logger(), "%d", counter);
            rate.sleep();
        }
        auto result = std::make_shared<CountUntil::Result>();
        result->reached_number = counter;
        goal_handle->succeed(result);

    }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<CountUntilServer>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}