#include "ros/ros.h"                        // 加入ROS公用程序
#include "create_custom_srv/AddTwoInts.h"  // 加入service header，在此是beginner_tutorials package下的AddTwoInts.srv
#include <cstdlib>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "add_two_ints_client");  //一開始必須先初始化，指定client node名稱為add_two_ints_client
  if (argc != 3)
  {
    ROS_INFO("usage: add_two_ints_client X Y");
    return 1;
  }

  /* 該node與ROS系統通訊的存取點(handle)，建構子會初始化該node，
     當離開此scope，解構子會關閉該node */
  ros::NodeHandle n;
  
  /* serviceClient()會將建立service資訊告訴master node，回傳一個ServiceClient物件(在此為client)
     指定的回呼函式名稱為add_two_ints，
  */ 
  ros::ServiceClient client = n.serviceClient<create_custom_srv::AddTwoInts>("add_two_ints");

  /* 創建暫存的srv，藉以設定request
     由以其中的request成員存取srv的欄位資料a, b
  */
  create_custom_srv::AddTwoInts srv;
  srv.request.a = atoll(argv[1]);
  srv.request.b = atoll(argv[2]);
  
  // 將存有request資料的暫存變數srv，用ServiceClient的call()呼叫service
  if (client.call(srv))                             
  {
    ROS_INFO("Sum: %ld", (long int)srv.response.sum);     //暫存變數的response成員會取得server處理後的結果
  }
  else
  {
    ROS_ERROR("Failed to call service add_two_ints");
    return 1;
  }

  return 0;
}
