/**
 *  File name: main.cpp
 *  Author: Gebremedhin Abreha
 *  Description: main program for testing the periodic task scheduler 
 *
 *  History, Date
 *---------------
 *  2019/08/20: Creation
 */
//<------------------------------------------------------------------------->//

#include <iostream>
#include <vector>
#include <sstream>
#include <thread>
#include <chrono>
#include "Scheduler.hpp"
#include "GenExcept.hpp"
#include "PeriodicTask.hpp"
#include "TaskInfo.hpp"

//<------------------------------------------------------------------------->//
///<  Helper methods 
//<--------------------------------------------------------------------------->//	

/**
 *   Execute periodic tasks 
 *
 *  @param taskScheduler scheduler object 
 *  @param maMaximum time duration 
 */
template < typename Task_t, typename TaskId_t >
   static void executePeriodicTasks(const TaskScheduler::Scheduler < Task_t, TaskId_t > & taskScheduler, int maxTime) 
   {
      timeval currentTime;
      for (int i = 1; i <= maxTime; i++) {
         using namespace std::this_thread;
         using namespace std::chrono_literals;
         sleep_for(1s);

         currentTime.tv_sec = i;
         taskScheduler.onNewTimeSec(currentTime);
      }
   }

//<------------------------------------------------------------------------------------------------------>//
/** 
 *  Driver main code/ client program
 */
int main() 
{
   using Task_t = std:: function < void(TaskInfo) > ;
   TaskScheduler::Scheduler < Task_t, TaskInfo > schedulerObj;

   TaskInfo taskId1(1);
   TaskInfo taskId2(2, 5);
   TaskInfo taskId3(3);
   TaskInfo taskId4(2);
   TaskInfo taskId5(5);

   std::vector < TaskInfo > taskIdVec = {
      taskId1,
      taskId2,
      taskId3,
      taskId4
   };

   for (auto taskId: taskIdVec) {
      try {
         schedulerObj.addPeriodicTask(taskId, PeriodicTask<TaskInfo>);
      } catch (const GenExcept & e) {
         std::stringstream ssMessage;
         ssMessage << e.what() << " Error code: " << e.getErrorNumber() << std::endl;
         PrintMessage(ssMessage.str());
      }
   }

   const int maxTime = 18;
   executePeriodicTasks(schedulerObj, maxTime);

   try {
      int timeInterval_2 = 2; //new time interval
      int timeInterval_1 = 7; //new time interval
      int timeInterval_3 = 10; //new time interval

      schedulerObj.changeTimeInterval(taskId1, timeInterval_1);
      schedulerObj.changeTimeInterval(taskId2, timeInterval_2);
      schedulerObj.changeTimeInterval(taskId4, timeInterval_3);
      schedulerObj.changeTimeInterval(taskId5, timeInterval_3);
   } catch (const GenExcept & e) {
      std::stringstream ssMessage;
      ssMessage << e.what() << " Error code: " << e.getErrorNumber() << std::endl;
      PrintMessage(ssMessage.str());
   }
   executePeriodicTasks(schedulerObj, maxTime);

   try {
      schedulerObj.removePeriodicTask(taskId4);
      std::stringstream ssMessage;
      ssMessage << "Removed Task: Task info: " << taskId4 << std::endl;
      PrintMessage(ssMessage.str());
   } catch (const GenExcept & e) {
      std::stringstream ssMessage;
      ssMessage << e.what() << " Error code: " << e.getErrorNumber() << std::endl;
      PrintMessage(ssMessage.str());
   }
   executePeriodicTasks(schedulerObj, maxTime);
}

//end