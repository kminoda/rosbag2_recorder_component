#ifndef ROSBAG2_RECORDER_COMPONENT__ROSBAG2_RECORDER_COMPONENT_HPP_
#define ROSBAG2_RECORDER_COMPONENT__ROSBAG2_RECORDER_COMPONENT_HPP_

#include "rclcpp/rclcpp.hpp"
#include "rosbag2_transport/recorder.hpp"
#include "rclcpp_components/register_node_macro.hpp"
#include "rosbag2_cpp/writer.hpp"
#include "rosbag2_storage/storage_options.hpp"
#include "rosbag2_transport/record_options.hpp"

namespace rosbag2_transport
{

class RecorderComponent : public Recorder
{
public:
  explicit RecorderComponent(const rclcpp::NodeOptions & options);

private:
  rosbag2_storage::StorageOptions get_storage_options_from_node_options(const rclcpp::NodeOptions & options);
  rosbag2_transport::RecordOptions get_record_options_from_node_options(const rclcpp::NodeOptions & options);
};

}  // namespace rosbag2_transport

#endif  // ROSBAG2_RECORDER_COMPONENT__ROSBAG2_RECORDER_COMPONENT_HPP_

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(rosbag2_transport::RecorderComponent)
