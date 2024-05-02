#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int32.hpp"
#include <memory>
#include <chrono>
#include <functional>
//#include <string>
using namespace std::chrono_literals;
void callback(rclcpp::Node::SharedPtr node, rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr pub)
{
    static int count;
    //auto message = std_msgs::msg::String();
    auto cnt = std_msgs::msg::Int32();
    cnt.data = count++;
    //message.data = "Hello world! " + std::to_string(count++);
    RCLCPP_INFO(node->get_logger(), "Publish: %d", cnt.data);
    pub->publish(cnt);
}
int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("node_pub1_2");
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    auto pub = node->create_publisher<std_msgs::msg::Int32>("topic_pub1_2", qos_profile);
    std::function<void()> fn = std::bind(callback, node, pub);
    auto timer = node->create_wall_timer(50ms, fn);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}