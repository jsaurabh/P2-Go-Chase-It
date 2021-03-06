#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>
#include <math.h>

ros::ServiceClient client;

void drive_robot(float lin_x, float ang_z){
    ROS_INFO("Received drive velocities - linear: %1.2f, -angular:%1.2f", lin_x, ang_z);

    ball_chaser::DriveToTarget velocity;
    velocity.request.linear_x = lin_x;
    velocity.request.angular_z = ang_z;
	
    if (!client.call(velocity))
        ROS_ERROR("Failed to call drive_robot node with given velocity");
    else
        ROS_INFO("drive_robot node called with given velocity");
}

void process_image_callback(const sensor_msgs::Image img){
    
    int white_pixel = 255;
    int left_limit = img.width/3;
    int middle_limit = 2 * img.width/3;

    int l = 0;
    int r = 0;
    int m = 0;
	
    for (int i=0; i < img.height * img.step; i+= 3){
      if (img.data[i] == white_pixel && img.data[i+1] == white_pixel && img.data[i+2] == white_pixel){
        int row_position_idx = i % (img.width * 3) / 3;
	
        if(row_position_idx <= left_limit)
          l+= 1;                
        else if(row_position_idx > left_limit && row_position_idx <= middle_limit) 
		      m+= 1;               
        else 
		      r+= 1;                
        }
    }
		
    int max_pos = std::max(std::max(l, r), m);

    if (max_pos == 0)
        drive_robot(0.0, 0.0); 
    else if (max_pos == l)
	      drive_robot(0.0, 0.4);  
    else if (max_pos == m)
        drive_robot(0.4, 0.0);
    else
        drive_robot(0.0, -0.4); 
    }

int main(int argc, char** argv){

    ros::init(argc, argv, "process_image");
    ros::NodeHandle nodeHandler;

    client = nodeHandler.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");
    ros::Subscriber subscriber = nodeHandler.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    ros::spin();
    return 0;
}