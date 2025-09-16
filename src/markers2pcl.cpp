#include <ros/ros.h>
#include <vicon_bridge/Markers.h>
#include <vicon_bridge/Marker.h>
#include <sensor_msgs/PointCloud.h>
#include <geometry_msgs/Point32.h>

#define QUEUE_SIZE 1
#define MM2M 0.001

class ViconToPointCloud
{
    public:
        ViconToPointCloud()
        {
            ros::NodeHandle nh;
            sub_ = nh.subscribe("/vicon/markers", QUEUE_SIZE, &ViconToPointCloud::callback, this);
            pub_ = nh.advertise<sensor_msgs::PointCloud>("/vicon/markers_pcl", QUEUE_SIZE);
        }

    private:
        ros::Subscriber sub_;
        ros::Publisher pub_;

        void callback(const vicon_bridge::Markers::ConstPtr& msg)
        {
            sensor_msgs::PointCloud cloud;
            cloud.header = msg->header;
            cloud.header.frame_id = "vicon/world";

            for (const auto& marker : msg->markers)
            {
                geometry_msgs::Point32 pt;
                pt.x = MM2M*marker.translation.x;
                pt.y = MM2M*marker.translation.y;
                pt.z = MM2M*marker.translation.z;
                cloud.points.push_back(pt);    
            }

            pub_.publish(cloud);
        }
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "vicon_to_pointcloud");
    ViconToPointCloud node;
    ros::spin();
    return 0;
}