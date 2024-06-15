# rosbag2_recorder_component

A rosbag2 recorder component for ROS 2. This can be loaded to a component to minimize the IPC overhead of recording rosbags.

## Installation

```bash
git clone https://github.com/kminoda/rosbag2_recorder_component.git
cd rosbag2_recorder_component
colcon build --symlink-install --cmake-args -DCMAKE_BUILD_TYPE=Release
```

## Usage

```bash
ros2 component load /YOUR_COMPONENT_CONTAINER_NAME rosbag2_recorder_component rosbag2_transport::RecorderComponent --param output:=/PATH/TO/OUTPUT --param topics:=/sensing/top/lidar/pandar_packets --param storage_id:=mcap
```

## Supported parameters

- `output` (string): The path to the output directory.
- `topics` (string): The topics to record. You can specify multiple topics by separating them with a comma. If not specified, all topics will be recorded.
- `storage_id` (string): The storage ID to use. The default is `sqlite3`.
