/**
 *  File Name: PeriodicTask.hpp
 *  Description: Periodic task sample implementation
 */
//-------------------------------------------------------------------------------------------------------------//
#ifndef _PERIODICTASK_
#define _PERIODICTASK_

#include <iostream>
#include <mutex>
#include <sstream>
#include <chrono>

static void PrintMessage(const std::string_view message)
{
   static std::mutex mutexPrint;    //access to cout is mutually exclusive
   std::lock_guard<std::mutex> guard(mutexPrint);
   std::cout<<message<<std::endl<<std::flush;
}

 template <typename IdType_t>
 void PeriodicTask(IdType_t taskId)
{
    std::stringstream ssMessage;
    ssMessage<<"Executing Periodic task, Task Info: "<<taskId<<std::endl<<std::flush;
    PrintMessage(ssMessage.str());
		   
    using namespace std::chrono_literals;
    using namespace std::this_thread;
    sleep_for(3s);
}	 

 #endif
