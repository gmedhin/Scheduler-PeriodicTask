#ifndef _TASKINFO_
#define _TASKINFO_

#include <iostream>
#include <functional>

/**
 * Given two tasks are assumed to be equal if only if they both have the same id. 
 *  i.e., task id is unique and it is used to identify each task. However, more than one task can have equal period or time interval.
 */
struct TaskInfo 
{
   int m_id;
   int m_period;

   explicit TaskInfo(int id, int period = 3): m_id(id), m_period(period) 
   {
   }

   bool operator == (const TaskInfo & other) 
   {
      return m_id == other.m_id;
   }

   friend std::ostream & operator << (std::ostream & os, const TaskInfo & taskId);
};

//Overloading << operator
inline std::ostream & operator << (std::ostream & os, const TaskInfo & taskId) 
{
   os << "Task id: " << taskId.m_id << ", Period: " << taskId.m_period << std::endl;
   return os;
}

//custom hash function
struct hashing_func 
{
   std::size_t operator()(const TaskInfo & taskId) const
   {
      return std::hash < int > ()(taskId.m_id);
   }
};

//Custom comparision function for equality
struct key_equal_fn 
{
   bool operator()(const TaskInfo & id1,
      const TaskInfo & id2) const {
      return id1.m_id == id2.m_id;
   }
};

namespace std 
{

   template < >
      struct hash < TaskInfo > 
      {
         size_t operator()(const TaskInfo & taskId) const 
         {
            // Compute hash values based on id so that task id will be unique (map key)
            return hash < int > ()(taskId.m_id);
         }
      };
}
#endif