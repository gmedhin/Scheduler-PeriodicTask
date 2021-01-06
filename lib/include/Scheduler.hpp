/** 
 * File name: Scheduler.hpp
 *  Author: Gebremedhin Abreha
 *  Description: Class that allows a given piece of code (called periodic task) to be executed periodically
 *
 *  History, Date
 *----------------
 *  2019/08/20: Creation
 */
//<------------------------------------------------------------------------------------------------------------->//

#ifndef _SCHEDULER_
#define _SCHEDULER_

#include <unordered_map>

#include <mutex>

#include "TaskInfo.hpp"

namespace TaskScheduler 
{
   ///<  Class for storing and schedulling/starting periodic tasks based on given time interval/period
   template < typename Task_t, typename TaskId_t >
      class Scheduler 
	  {
         public:
         Scheduler() =
            default; ///<  Default constructor
         ~Scheduler() =
            default; ///< Default destructor
         /**
          *  Add periodic task to a table of periodic tasks
          *
          *  @param taskId Id of periodic task 
          *  @param task Name of periodic task to be added/stored in a table of periodic tasks
          */
         void addPeriodicTask(TaskId_t taskId, Task_t task);

         /**
          *  Execute the correct peiodic task by checking the time interval of each peiodic 
          *  tasks in the table, triggering a new thread for each task.
          *  This method can called every new time(e.g., every second) from the client
          *
          *  @param currentTime Current time value (in seconds)
          */
         void onNewTimeSec(timeval currentTimeSec) const;

         /**
          *  Remove a given  periodic task from the table of periodic tasks
          *
          *  @param task Name of periodic task to be added/stored in a table of periodic tasks
          *  @note  may throw exception  
          */
         void removePeriodicTask(TaskId_t taskId);

         /**
          *  Change time interval of a given task with a given new time interval
          *
          *  @param task Name of periodic task to be added/stored in a table of periodic tasks
          *  @param newTimeIntervalSec New time interval value (in secs) for the task 
          *  @note may throw exception
          */
         void changeTimeInterval(TaskId_t taskId, int newTimeIntervalSec);

         /**
          *  Change task id of a given task
          *  @param oldId  Old task id
          *  @param newId  New task id
          */
         void changeTaskId(TaskId_t oldId, TaskId_t newId);
         /**
          *  Retrieve number of available periodic tasks stored in the table
          *
          *  @return Number of periodic tasks
          */
         int getNumOfTasks() const;

         /**
          *  Retrieve time interval/period of a specific task
          *
          * @param task Name of periodic task
          * @return Time interval for periodic task 
          * @note may throw exception
          */
         int getTimeIntervalSec(TaskId_t taskId) const;

         private:

         mutable std::mutex m_mutex;
         std::unordered_map < TaskId_t, Task_t, hashing_func, key_equal_fn > m_taskIdToTaskMap;
      };
}
#endif