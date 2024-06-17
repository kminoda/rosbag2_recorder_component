#include "rosbag2_recorder_component.hpp"

namespace rosbag2_transport
{

RecorderComponent::RecorderComponent(const rclcpp::NodeOptions & options)
: Recorder(
    std::make_shared<rosbag2_cpp::Writer>(),
    rosbag2_storage::StorageOptions(get_storage_options_from_node_options(options)),
    rosbag2_transport::RecordOptions(get_record_options_from_node_options(options)),
    "rosbag2_recorder_transport",
    options)
{
  // print parameter_overrides in options
  RCLCPP_INFO(this->get_logger(), "RecorderComponent initialized with parameter_overrides:");
  for (const auto & parameter : options.parameter_overrides()) {
    RCLCPP_INFO(this->get_logger(), "  %s: %s", parameter.get_name().c_str(), parameter.value_to_string().c_str());
  }
  RCLCPP_INFO(this->get_logger(), this->storage_options_.uri.c_str());

  // output use_sim_time
  RCLCPP_INFO(this->get_logger(), "use_sim_time: %s", this->record_options_.use_sim_time ? "true" : "false");

  // output all topics
  for (const auto & topic : this->record_options_.topics) {
    RCLCPP_INFO(this->get_logger(), "Recording topic: %s", topic.c_str());
  }

  // Start recording
  this->record();
}

rosbag2_storage::StorageOptions RecorderComponent::get_storage_options_from_node_options(const rclcpp::NodeOptions & options)
{
  rosbag2_storage::StorageOptions storage_options;
  for (const auto & parameter : options.parameter_overrides()) {
    if (parameter.get_name() == "output") {
      storage_options.uri = parameter.value_to_string();
    } else if (parameter.get_name() == "storage_id") {
      storage_options.storage_id = parameter.value_to_string();
    }
  }

  return storage_options;
}

rosbag2_transport::RecordOptions RecorderComponent::get_record_options_from_node_options(const rclcpp::NodeOptions & options)
{
  rosbag2_transport::RecordOptions record_options;

  for (const auto & parameter : options.parameter_overrides()) {
    if (parameter.get_name() == "topics") {
      // topics are separated with comma, so split them
      std::string topics = parameter.value_to_string();
      std::istringstream iss(topics);
      std::string topic;
      while (std::getline(iss, topic, ',')) {
        record_options.topics.push_back(topic);
      }
      break;
    } else if (parameter.get_name() == "serialization_format") {
      record_options.rmw_serialization_format = parameter.value_to_string();
    } else if (parameter.get_name() == "use_sim_time") {
      record_options.use_sim_time = parameter.value_to_string() == "true";
    }
  }

  // Ensure that a serialization format is specified
  if (record_options.rmw_serialization_format.empty()) {
    record_options.rmw_serialization_format = rmw_get_serialization_format();
  }

  return record_options;  
}

}  // namespace rosbag2_transport

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(rosbag2_transport::RecorderComponent)
