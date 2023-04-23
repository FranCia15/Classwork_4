#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Pose.h"
#include "my_robot_model/frame_transform.h"
#include "tf/transform_listener.h"

using namespace std;

bool service_callback( my_robot_model::frame_transform::Request & req, my_robot_model::frame_transform::Response &res){
    
    cout<<"Frame transformation received:" << endl;
    cout<<"Frame a: "<<req.frame_a.data<< endl;
    cout<<"Frame b: "<<req.frame_b.data<<endl;

    tf::TransformListener listener;
    tf::StampedTransform transform;

    try{

        // Without these function the lookupTransform starts before link info are received 
        listener.waitForTransform(req.frame_a.data,req.frame_b.data,ros::Time(0),ros::Duration(1.0));

        listener.lookupTransform(req.frame_a.data,req.frame_b.data,ros::Time(0),transform);
    }
    catch(tf::TransformException ex){
        ROS_ERROR("%s",ex.what());
        ros::Duration(1.0).sleep();

    }

    ROS_INFO_STREAM("Transform: " <<
        transform.getOrigin().x()<<","<<
        transform.getOrigin().y()<<","<<
        transform.getOrigin().z()<<","<<
        transform.getRotation().x()<<","<<
        transform.getRotation().y()<<","<<
        transform.getRotation().z()
    );

    res.frame_transform.position.x=transform.getOrigin().x();
    res.frame_transform.position.y=transform.getOrigin().y();
    res.frame_transform.position.z=transform.getOrigin().z();
    res.frame_transform.orientation.x=transform.getRotation().x();
    res.frame_transform.orientation.y=transform.getRotation().y();
    res.frame_transform.orientation.z=transform.getRotation().z();

    return true; 
    
}

int main (int argc, char **argv){
    ros::init(argc,argv,"my_robot_model_transform");
    ros::NodeHandle nh; 
    ros::ServiceServer service =nh.advertiseService("frame_transform", service_callback);
    ros::spin();
}


