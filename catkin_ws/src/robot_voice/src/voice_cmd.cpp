#include<ros/ros.h>
#include<geometry_msgs/Twist.h>
#include<std_msgs/String.h>
#include<pthread.h>
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<string>

using namespace std;
ros::Publisher pub;
geometry_msgs::Twist vel_cmd;
pthread_t pth_[5];


void* vel_ctr(void* arg)
{
    while(true)
    {

        pub.publish(vel_cmd);
        ros::spinOnce();
        sleep(1);
    }
    return 0;
}

void callback(const std_msgs::String::ConstPtr& msg)
{
    cout<<"Msg："<<msg->data.c_str()<<endl;
    string str1 = msg->data.c_str();
    string str2 = "go forward.";
    string str3 = "go back.";
    string str4 = "turn left.";
    string str5 = "turn right.";
    string str6 = "stop.";
    if(!(strcasecmp(str1.c_str(),str2.c_str())))
    {
        vel_cmd.linear.x = 0.1;
        vel_cmd.angular.z = 0;
        pthread_create(&pth_[0],NULL,vel_ctr,NULL);
    }
    if(!(strcasecmp(str1.c_str(),str3.c_str())))
    {
        vel_cmd.linear.x = -0.1;
        vel_cmd.angular.z = 0;
        pthread_create(&pth_[1],NULL,vel_ctr,NULL);
    }
    if(!(strcasecmp(str1.c_str(),str4.c_str())))
    {
        vel_cmd.linear.x = 0;
        vel_cmd.angular.z = 0.3;
        pthread_create(&pth_[2],NULL,vel_ctr,NULL);
    }
    if(!(strcasecmp(str1.c_str(),str5.c_str())))
    {
        vel_cmd.linear.x = 0;
        vel_cmd.angular.z = -0.3;
        pthread_create(&pth_[3],NULL,vel_ctr,NULL);
    }
    if(!(strcasecmp(str1.c_str(),str6.c_str())))
    {
        vel_cmd.linear.x = 0;
        vel_cmd.angular.z = 0;
        pthread_create(&pth_[0],NULL,vel_ctr,NULL);
    }    
}

int main(int argc, char** argv)
{

    ros::init(argc, argv, "sub_word");
    ros::NodeHandle n;
    
    pub = n.advertise<geometry_msgs::Twist>("/cmd_vel",10);
    ros::Subscriber sub = n.subscribe("voiceWords",10,callback);
    cout<<"--------------------"<<endl;
	cout<<"Voice control begins"<<endl;

    ros::spin();
}
