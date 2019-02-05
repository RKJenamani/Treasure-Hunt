#include <bits/stdc++.h>
#include <utility>
#include "blackbox.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include "ros/ros.h"
#include "turtlesim/Spawn.h"
using namespace std;
BlackBox obj;
double dis_threshold =0.1, theta_threshold=0.001;

//turtle 1
ros::Publisher velocity_publisher1;
ros::Subscriber velocity_subscriber1;
turtlesim::Pose turtlesim_pose1;

//turtle2
ros::Publisher velocity_publisher2;
ros::Subscriber velocity_subscriber2;
turtlesim::Pose turtlesim_pose2;

void poseCallback1(const turtlesim::Pose::ConstPtr & pose_message) 
{
	turtlesim_pose1.x = pose_message->x;
	turtlesim_pose1.y = pose_message->y;
	turtlesim_pose1.theta = pose_message->theta;
}

void poseCallback2(const turtlesim::Pose::ConstPtr & pose_message) 
{
	turtlesim_pose2.x = pose_message->x;
	turtlesim_pose2.y = pose_message->y;
	turtlesim_pose2.theta = pose_message->theta;
}
double calcDis(double x1,double y1,double x2,double y2) 
{
	return sqrt(pow(x1-x2,2) + pow(y1-y2,2));
}

double calcTheta(double x1,double y1,double x2,double y2) 
{
	if(x2 != x1)
	  	return atan2((y2-y1),(x2-x1));
	else
	{
		if(y1 > y2) return -1.571;
		else return 1.571;
	}
}
void moveturtle1(double x, double y)
{
	geometry_msgs::Twist vel_msg;
	x=0.5+x*0.714;	//border of 0.5 
	y=0.5+y*0.714;

	cout<<x<<"   "<<y<<endl;
	ros::Rate loop_rate(10);//10 messages per second

	//makes turtle orient in the direction of goal
	while(abs((calcTheta(turtlesim_pose1.x,turtlesim_pose1.y,x,y) - turtlesim_pose1.theta)) > theta_threshold)
	{
		vel_msg.linear.x = 0;
		vel_msg.linear.y = 0;
		vel_msg.linear.z = 0;

		vel_msg.angular.x = 0;
		vel_msg.angular.y = 0;
		vel_msg.angular.z = 1.5 * (calcTheta(turtlesim_pose1.x,turtlesim_pose1.y,x,y) - turtlesim_pose1.theta);
		velocity_publisher1.publish(vel_msg);

		ros::spinOnce();
		loop_rate.sleep();
	}

	vel_msg.angular.z = 0;

	//makes turtle go to goal location 
	while(calcDis(turtlesim_pose1.x,turtlesim_pose1.y,x,y) > dis_threshold) 
	{
		vel_msg.linear.x = 1.5 * calcDis(turtlesim_pose1.x,turtlesim_pose1.y,x,y);
		vel_msg.linear.y = 0;
		vel_msg.linear.z = 0;

		vel_msg.angular.x = 0;
		vel_msg.angular.y = 0;
		vel_msg.angular.z = 0;

		velocity_publisher1.publish(vel_msg);
		ros::spinOnce();
		loop_rate.sleep();
	}

	vel_msg.linear.x = 0;

	velocity_publisher1.publish(vel_msg);
	cout << "working" << endl;
}
void moveturtle2(double x, double y)
{
	geometry_msgs::Twist vel_msg;
	x=0.5+x*0.714;
	y=0.5+y*0.714;
	ros::Rate loop_rate(10);//10 messages per second

	int t = 0;
	//makes turtle orient in the direction of goal
	while(abs((calcTheta(turtlesim_pose2.x,turtlesim_pose2.y,x,y) - turtlesim_pose2.theta)) > theta_threshold)
	{
		vel_msg.linear.x = 0;
		vel_msg.linear.y = 0;
		vel_msg.linear.z = 0;

		vel_msg.angular.x = 0;
		vel_msg.angular.y = 0;
		vel_msg.angular.z = 1.5 * (calcTheta(turtlesim_pose2.x,turtlesim_pose2.y,x,y) - turtlesim_pose2.theta);
		velocity_publisher2.publish(vel_msg);

		ros::spinOnce();
		loop_rate.sleep();
	}

	vel_msg.angular.z = 0;

	//makes turtle go to goal location 
	while(calcDis(turtlesim_pose2.x,turtlesim_pose2.y,x,y) > dis_threshold) 
	{
		vel_msg.linear.x = 1.5 * calcDis(turtlesim_pose2.x,turtlesim_pose2.y,x,y);
		vel_msg.linear.y = 0;
		vel_msg.linear.z = 0;

		vel_msg.angular.x = 0;
		vel_msg.angular.y = 0;
		vel_msg.angular.z = 0;

		velocity_publisher2.publish(vel_msg);
		ros::spinOnce();
		loop_rate.sleep();
	}

	vel_msg.linear.x = 0;

	velocity_publisher1.publish(vel_msg);
	cout << "working" << endl;
}
int rows = obj.get_rows();
int cols = obj.get_cols();
char traversal1,traversal2;
void initialize()
{
	pair<int, int> t1, t2;int i,j;
	t1 = obj.get_turtle_pos1();
	t2 = obj.get_turtle_pos2();
	cout<<"Initial positions of turtles : \n"<<"Turtle 1: X="<<t1.first<<"  Y="<<t1.second<<endl<<"Turtle 2: X="<<t2.first<<"  Y="<<t2.second<<endl;
	traversal1='r';
	traversal2='r';
	moveturtle1(7,7);
	moveturtle2(1,0);
	//sends turtle 2 to 1,0
	while(obj.get_turtle_pos2().first!=1)
	{
		if(obj.get_turtle_pos2().first<1)
			obj.move_2(1);
		else
			obj.move_2(0);
		cout<<obj.get_turtle_pos2().first<<" - ";
	}
	cout<<"worked   "<<obj.get_turtle_pos2().first;
	while(obj.get_turtle_pos2().second!=0)
	{
		obj.move_2(2);
		cout<<obj.get_turtle_pos2().second<<" - ";
	}
	cout<<"worked  "<<obj.get_turtle_pos2().second;

	//sends turtle 1 to (7,7)
	while(obj.get_turtle_pos1().first!=7)
	{
		if(obj.get_turtle_pos1().first<7)
			obj.move_1(1);
		else
			obj.move_1(0);
		cout<<obj.get_turtle_pos1().first<<" - ";
	}
	cout<<"worked   "<<obj.get_turtle_pos1().first;
	while(obj.get_turtle_pos1().second!=7)
	{
		if(obj.get_turtle_pos1().second<7)
			obj.move_1(3);
		else
			obj.move_1(2);
		cout<<obj.get_turtle_pos1().second<<" - ";
	}
	cout<<"worked  "<<obj.get_turtle_pos1().second;
	obj.update_food(); //updates food

}
bool isvalid( int i, int j)
{
	 if(i>=0 && j>=0 && i<rows && j<cols)
		return 1;
	else
		return 0;
}
int checkresource(pair <int,int> position) //checks if resource is present in surrounding
{	
	if(isvalid(position.first,position.second+1) && obj.check_status(position.first,position.second+1)==1)
		return 3;
	else if(isvalid(position.first-1,position.second) && obj.check_status(position.first-1,position.second)==1)
		return 0;
	else if(isvalid(position.first,position.second-1) && obj.check_status(position.first,position.second-1)==1)
		return 2;
	else if(isvalid(position.first+1,position.second) && obj.check_status(position.first+1,position.second)==1)
		return 1;
	else
		return -1;
}

int mturtle1(pair <int,int> posturtle1)
{
	//cout<<"Checkresource "<<checkresource(posturtle1)<<endl;
	if(checkresource(posturtle1)==-1)	//if object not found up 0 down 1 left 2 right 3
	{
		if(obj.get_turtle_pos1().first==13 && obj.get_turtle_pos1().second==14)
			return -10;
		if(traversal1=='l')
		{
			if(isvalid(posturtle1.first,posturtle1.second-1))
			{

				obj.move_1(2);
			}
			else
			{
				obj.move_1(1);
				obj.move_1(1);
				obj.move_1(1);
				traversal1='r';
			}
		}
		else 
		{
			if(isvalid(posturtle1.first,posturtle1.second+1))
			{
				obj.move_1(3);
			}
			else
			{
				obj.move_1(1);
				obj.move_1(1);
				obj.move_1(1);
				traversal1='l';
			}
		}
		moveturtle1(obj.get_turtle_pos1().first,obj.get_turtle_pos1().second);
		return -1;


	}
	else
	{
		switch(checkresource(posturtle1))
		{
			case 0: obj.move_1(0);break;
			case 1: obj.move_1(1);break;
			case 2: obj.move_1(2);break;
			case 3: obj.move_1(3);
		}
		//cout<<"position of turtles : \n"<<"Turtle 1: X="<<obj.get_turtle_pos1().first<<"  Y="<<obj.get_turtle_pos1().second<<"Turtle 2: X="<<obj.get_turtle_pos2().first<<"  Y="<<obj.get_turtle_pos2().second<<endl;
		moveturtle1(obj.get_turtle_pos1().first,obj.get_turtle_pos1().second);
		cout<<"-----------------------------------"<<endl<<" RESOURCE FOUND BY TURTLE 1 AT: X:"<<obj.get_turtle_pos1().first<<" Y:"<<obj.get_turtle_pos1().second<<endl<<"-----------------------------------"<<endl;
		
		return 1;
	}
//	sleep(1000);
}
int mturtle2(pair <int,int> posturtle2)
{
	//cout<<"Checkresource "<<checkresource(posturtle2)<<endl;
	if(checkresource(posturtle2)==-1)	//if object not found up 0 down 1 left 2 right 3
	{
		if(obj.get_turtle_pos2().first==7 && obj.get_turtle_pos2().second==7)
			return -10;
		if(traversal2=='l')
		{
			if(isvalid(posturtle2.first,posturtle2.second-1))
			{
				obj.move_2(2);
			}
			else
			{
				obj.move_2(1);
				obj.move_2(1);
				obj.move_2(1);
				traversal2='r';
			}
		}
		else 
		{
			if(isvalid(posturtle2.first,posturtle2.second+1))
			{
				obj.move_2(3);
			}
			else
			{
				obj.move_2(1);
				obj.move_2(1);
				obj.move_2(1);
				traversal2='l';
			}
		}
		moveturtle2(obj.get_turtle_pos2().first,obj.get_turtle_pos2().second);
		return -1;


	}
	else
	{
		switch(checkresource(posturtle2))
		{
			case 0: obj.move_2(0);break;
			case 1: obj.move_2(1);break;
			case 2: obj.move_2(2);break;
			case 3: obj.move_2(3);
		}
		//cout<<"position of turtles : \n"<<"Turtle 1: X="<<obj.get_turtle_pos1().first<<"  Y="<<obj.get_turtle_pos1().second<<"Turtle 2: X="<<obj.get_turtle_pos2().first<<"  Y="<<obj.get_turtle_pos2().second<<endl;
		moveturtle2(obj.get_turtle_pos2().first,obj.get_turtle_pos2().second);
		cout<<"-----------------------------------"<<endl<<" RESOURCE FOUND BY TURTLE 2 AT: X="<<obj.get_turtle_pos2().first<<" Y :"<<obj.get_turtle_pos2().second<<endl<<"-----------------------------------"<<endl;
		return 1;
	}
//	sleep(1000);
}

int main(int argc,char** argv)
{
	ros::init(argc,argv,"hunt");
	ros::NodeHandle n;
	ros::ServiceClient turt = n.serviceClient<turtlesim::Spawn>("/spawn");
	turtlesim::Spawn loc;
	loc.request.x = 0.5;
	loc.request.y = 0.5;
	loc.request.theta = 0;
	turt.call(loc);

	velocity_publisher1=n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",10);
	velocity_subscriber1=n.subscribe("/turtle1/pose", 10, poseCallback1);

	velocity_publisher2=n.advertise<geometry_msgs::Twist>("/turtle2/cmd_vel",10);
	velocity_subscriber2=n.subscribe("/turtle2/pose", 10, poseCallback2);
	pair<int, int> t1, t2;
	int re1=1,re2=1;
	while(ros::ok())
	{
		//cout<<"loop running   \n";
		if(re1>-1 || re2>-1 || (re1==-10 && re2==-10))
		{
			sleep(1);
			cout<<"INITIALIZATION TAKING PLACE";
			initialize();
		}
		//cout<<"k";
		t1 = obj.get_turtle_pos1();
		t2 = obj.get_turtle_pos2();
		//cout<<"position of turtles : \n"<<"Turtle 1: X="<<t1.first<<"  Y="<<t1.second<<"Turtle 2: X="<<t2.first<<"  Y="<<t2.second<<endl;
		re1=mturtle1(t1);
		re2=mturtle2(t2);
		cout<<re1<<"   "<<re2<<endl;
		
	}
	return 0;
}
/*
int main(int argc, char **argv)
{
	ros::init(argc,argv,"hunt");
	ros::NodeHandle n;
	velocity_publisher1=n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",10);
	velocity_subscriber1=n.subscribe("/turtle1/pose", 10, poseCallback1);

	velocity_publisher2=n.advertise<geometry_msgs::Twist>("/turtle2/cmd_vel",10);
	velocity_subscriber2=n.subscribe("/turtle2/pose", 10, poseCallback2);
	moveturtle1(7,7);
	moveturtle2(1,0);
	ros::spin();
}
*/
/*
int main(int argc, char **argv)
{
	ros::init(argc,argv,"hunt");
	ros::NodeHandle n;
	velocity_publisher1=n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",10);
	velocity_subscriber1=n.subscribe("/turtle1/pose", 10, poseCallback1);

	velocity_publisher2=n.advertise<geometry_msgs::Twist>("/turtle2/cmd_vel",10);
	velocity_subscriber2=n.subscribe("/turtle2/pose", 10, poseCallback2);
	moveturtle1(6,2);
	moveturtle2(4,4);
	ros::spin();

	

}


		case 3:	obj.move_1(3);
				return 3;
		case 0: obj.move_1(0);
				return 0;
		case 2:	obj.move_1(2);
				return 2;
		case 1: obj.move_1(1);
				return 1;
		case -1://traversal
				switch(traversal1)
				{
					case 'd':	if(visited[posturtle1.first+1][posturtle1.second])
								{
									obj.move_1(0); //move up if can't move right
									traversal1='w';
								}
								else
									obj.move_1(3); //move right if unvisited
								break;
					case 'w':	if(visited[posturtle1.first][posturtle1.second+1])
								{
									obj.move_1(2); //move left if cant move up
									traversal1='a';
								}
								else
								{
									obj.move_1(0); //move up if unvisited
								}
								break;
					case 'a':	if(visited[posturtle1.first-1][posturtle1.second])
								{
									obj.move_1(1); //move down if cant move left
									traversal1='s';
								}
								else
								{
									obj.move_1(2); //move left if unvisited
								}
								break;
					case 's':   if(visited[posturtle1.first][posturtle1.second-1])
								{
									obj.move_1(3); //move right if cant move down
									traversal1='d';
								}
								else
								{
									obj.move_1(1); //move down if unvisited
								}
								break;

				}
				sleep(1);
				cout<<"X:  "<<posturtle1.first<<"    Y:  "<<posturtle1.second<<endl;
				return -1;
	}
	
}
int mturtle2(pair <int,int> posturtle2)
{
	switch(checkresource(posturtle2))	//up 0 down 1 left 2 right 3
	{
		case 3:	obj.move_2(3);
				return 3;
		case 0: obj.move_2(0);
				return 0;
		case 2:	obj.move_2(2);
				return 2;
		case 1: obj.move_2(1);
				return 1;
		case -1://traversal
				switch(traversal2)
				{
					case 'd':	if(visited[posturtle2.first][posturtle2.second])
									obj.move_2(3); //move right if can't move down
								else
								{
									obj.move_2(1); //move down if can turn
									traversal2='s';
								}
								break;
					case 'w':	if(visited[posturtle2.first+1][posturtle2.second])
									obj.move_2(0); //move up if cant move right
								else
								{
									obj.move_2(3); //move right if can turn
									traversal2='d';
								}
								break;
					case 's':	if(visited[posturtle2.first-1][posturtle2.second])
									obj.move_2(1); //move down if cant move left
								else
								{
									obj.move_2(2);
									traversal2='a'; //move left if can turn
								}
								break;
					case 'a':   if(visited[posturtle2.first][posturtle2.second+1])
									obj.move_2(2); //move left if can't move up
								else
								{
									obj.move_2(1); //move up if can turn
									traversal2='w';
								}
								break;

				}
				return -1;
	}
}
*/
/*
#include "geometry_msgs/Twist.h"
#include "ros/ros.h"
ros::Publisher velocity_publisher;
using namespace std;
void move(double speed, double distance, bool isForward)
{
	geometry_msgs::Twist vel_msg;
	if(isForward)
		vel_msg.linear.x=abs(speed);
	else
		vel_msg.linear.x=-abs(speed);
	vel_msg.linear.y=0;
	vel_msg.linear.z=0;
	vel_msg.angular.x=0;
	vel_msg.angular.y=0;
	vel_msg.angular.z=0;
	double t0=ros::Time::now().toSec();
	double current_distance=0;
	ros::Rate loop_rate(10);
	do
	{
		velocity_publisher.publish(vel_msg);
		double t1=ros::Time::now().toSec();
		current_distance=speed*(t1-t0);
		ros::spinOnce();
		loop_rate.sleep();
	}while(current_distance<distance);
	vel_msg.linear.x=0;
	velocity_publisher.publish(vel_msg);
}	
	
int main(int argc, char **argv)
{
	ros::init(argc,argv,"robot_cleaner");
	ros::NodeHandle n;
	double speed;
	double distance;
	bool isForward;
	velocity_publisher=n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",10);
	cout<<"enter speed: ";
	cin>>speed;
	cout<<"Enter diatance :";
	cin>>distance;
	cout<<"Forward ?:";
	cin>>isForward;
	move(speed,distance,isForward);
}*/
