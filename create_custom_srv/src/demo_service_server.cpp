#include "ros/ros.h"                        // 加入ROS公用程序
#include "create_custom_srv/AddTwoInts.h"  // 加入service header，在此是create_custom_srv下的AddTwoInts.srv

/* service的server端與client端都有request跟response來處理輸入與輸出
   <package_name>::<service_definition>::Request &req
   <package_name>::<service_definition>::Response &res
   不同於topic的subscriber以ConstPtr以指標存取資料(msg->data)，service直接以參照存取資料 (req.a)
*/
bool add(create_custom_srv::AddTwoInts::Request  &req,
         create_custom_srv::AddTwoInts::Response &res)
{
  res.sum = req.a + req.b;
  ROS_INFO("request: x=%ld, y=%ld", (long int)req.a, (long int)req.b);
  ROS_INFO("sending back response: [%ld]", (long int)res.sum);
  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "add_two_ints_server");   //一開始必須先初始化，指定server node名稱為add_two_ints_server

  /* 該node與ROS系統通訊的存取點(handle)，建構子會初始化該node，
     當離開此scope，解構子會關閉該node */
  ros::NodeHandle n;

  /* advertiseService()會將建立topic的資訊告訴master node，回傳一個ServiceServer物件(在此為service)
     service name為add_two_ints，指定的回呼函式名稱為add
  */ 
  ros::ServiceServer service = n.advertiseService("add_two_ints", add);
  ROS_INFO("Ready to add two ints.");

  /* ros::spin()會進入迴圈，然後呼叫所有在此執行緒(in main function)的
     回呼函式 (在此為add)，直到Ctrl-C被輸入或當前的node被master node關掉
  */
  ros::spin();

  return 0;
}
