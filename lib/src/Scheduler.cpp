/** 
 *  File name: Scheduler.cpp
 *  Author: Gebremedhin Abreha
 *  Date: 20 July, 2019
 *  Description: Class implementation that allows a given piece of code (called periodic task ) 
 *               to be executed periodically
 *
 *  History, Date
 *---------------
 *  2019/08/20: Creation
 */
//<--------------------------------------------------------------------------------------------->//

#include <thread>
#include <sstream>
#include <algorithm>
#include <functional>
#include "GenExcept.hpp"
#include "Scheduler.hpp"
#include "PeriodicTask.hpp"

using namespace std;

namespace TaskScheduler 
{

   template < typename Task_t, typename TaskId_t >
      void Scheduler < Task_t, TaskId_t > ::addPeriodicTask(TaskId_t taskId, Task_t task) 
	  {
         
		 std::lock_guard < std::mutex > guard(m_mutex);

         if (auto[pos, done] = m_taskIdToTaskMap.insert({taskId, task}); !done) {
            auto[taskId, task] = * pos;
            stringstream ssMessage;
            ssMessage << "Adding task failed: You cannot add same task more than once. Task Info: " << taskId << endl;
            int errorCode = -13;
            throw GenExcept(ssMessage.str(), errorCode);
         }
      }

   template < typename Task_t, typename TaskId_t >
      void Scheduler < Task_t, TaskId_t > ::onNewTimeSec(timeval currentTime) const 
	  {
		  
         std::lock_guard < std::mutex > guard(m_mutex);
		 
         auto isIntervalEqualToElapsedTime {false};
		 
         for (auto[taskId, task]: m_taskIdToTaskMap) {
            isIntervalEqualToElapsedTime = (0 == currentTime.tv_sec % taskId.m_period);

            if (isIntervalEqualToElapsedTime) {
               thread handler(task, taskId);
               handler.detach(); //continue, do not wait for the thread to finish
            }
         }
      }

   template < typename Task_t, typename TaskId_t >
      void Scheduler < Task_t, TaskId_t > ::removePeriodicTask(TaskId_t taskId) 
	  {
		  
         std::lock_guard < std::mutex > guard(m_mutex);

         if (auto itr = m_taskIdToTaskMap.find(taskId); itr != m_taskIdToTaskMap.end()) {
			 m_taskIdToTaskMap.erase(itr);
         } else {
            stringstream ssMessage;
            ssMessage << "Cannot remove periodic task: Task not found. Task info: " << taskId << endl;
            int errorCode = -12;
            throw GenExcept(ssMessage.str(), errorCode);
         }
      }

   template < typename Task_t, typename TaskId_t >
      void Scheduler < Task_t, TaskId_t > ::changeTimeInterval(TaskId_t taskId, int newTimeIntervalSec) 
	  {
		  
         std::lock_guard < std::mutex > guard(m_mutex);
		 
         if (auto itr = m_taskIdToTaskMap.find(taskId); itr != m_taskIdToTaskMap.end()) {
            auto nodeHandle = m_taskIdToTaskMap.extract(taskId);
            nodeHandle.key().m_period = newTimeIntervalSec;
            m_taskIdToTaskMap.insert(std::move(nodeHandle));
         } else {
            stringstream ssMessage;
            ssMessage << "Cannot change time interval: Task not found. Task info: " << taskId << endl;
            int errorCode = -11;
            throw GenExcept(ssMessage.str(), errorCode);
         }
      }

   template < typename Task_t, typename TaskId_t >
      void Scheduler < Task_t, TaskId_t > ::changeTaskId(TaskId_t oldId, TaskId_t newId) 
	  {
		  
         std::lock_guard < std::mutex > guard(m_mutex);
		 
         if (auto itr = m_taskIdToTaskMap.find(oldId); itr != m_taskIdToTaskMap.end()) {
            auto nodeHandle = m_taskIdToTaskMap.extract(oldId);
            nodeHandle.key() = newId;
            m_taskIdToTaskMap.insert(std::move(nodeHandle));
         } else {
            stringstream ssMessage;
            ssMessage << "Cannot change task Id: Task not found. Task info: " << oldId << endl;
            int errorCode = -10;
            throw GenExcept(ssMessage.str(), errorCode);
         }
      }

   template < typename Task_t, typename TaskId_t >
      int Scheduler < Task_t, TaskId_t > ::getNumOfTasks() const 
	  {
		  
         std::lock_guard < std::mutex > guard(m_mutex);
		 
         return m_taskIdToTaskMap.size();
      }

   template < typename Task_t, typename TaskId_t >
      int Scheduler < Task_t, TaskId_t > ::getTimeIntervalSec(TaskId_t taskId) const 
	  {
		  
         std::lock_guard < std::mutex > guard(m_mutex);
		 
         if (const auto itr = m_taskIdToTaskMap.find(taskId); itr != m_taskIdToTaskMap.end()) {
            auto[taskId, task] = * itr;
            return taskId.m_period;
         } else {
            stringstream ssMessage;
            ssMessage << "Cannot retrieve time interval: Task not found. Task info" << taskId << endl;
            int errorCode = -10;
            throw GenExcept(ssMessage.str(), errorCode);
         }
      }

   using Task_t = std:: function < void(TaskInfo) > ;
   template class Scheduler < Task_t, TaskInfo > ;
}