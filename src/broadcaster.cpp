#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Pose.h"
#include "my_robot_model/frame_transform.h"
#include "tf/transform_broadcaster.h"

using namespace std;

int main (int argc, char **argv){
    ros::init(argc,argv,"my_robot_model_client");
    ros::NodeHandle nh; 
    ros::ServiceClient client =nh.serviceClient<my_robot_model::frame_transform>("frame_transform");
    my_robot_model::frame_transform srv;
    srv.request.frame_a.data = "link_0";
    srv.request.frame_b.data = "link_7";

    ROS_INFO("Waiting for the client server");
    client.waitForExistence();
    ROS_INFO("Client server up now");

    

    tf::TransformBroadcaster br;
    tf::Transform transform;
    tf::Quaternion q;

    ros::Rate rate(100);
    while (ros::ok()){
        
        
        if (!client.call(srv)){
        ROS_ERROR("Error calling the server");
        return 1;    
        }

        cout << "Service output: " <<srv.response.frame_transform << endl;

        transform.setOrigin(
            tf::Vector3(
                srv.response.frame_transform.position.x,
                srv.response.frame_transform.position.y,
                srv.response.frame_transform.position.z
            )
        );

        

        q.setRPY(
            srv.response.frame_transform.orientation.x,
            srv.response.frame_transform.orientation.y,
            srv.response.frame_transform.orientation.z
        );

        transform.setRotation(q);
        br.sendTransform(tf::StampedTransform(transform,ros::Time::now(), "link_0", "dynamic_tf"));

        rate.sleep();


    }

    return 0;

}