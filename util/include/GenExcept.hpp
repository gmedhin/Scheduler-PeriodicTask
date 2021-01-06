/**
 *  File Name: GenExcept.hpp
 *  Description: Custom exception handler class
 */
//-------------------------------------------------------------------------------------------------------------//

#ifndef _GENEXCEPT_
#define _GENEXCEPT_

#include <exception>
#include <string>

class GenExcept: virtual public std::exception {
	
protected:
    std::string m_error_message;  ///< Error message
	//TODO: make sure error number is unique
    int m_error_number;           ///< Error number  

public:

   /** 
    *  Constructor (C++ STL string, int, int).
    *  @param msg The error message
    *  @param err_num Error number
    */
   explicit GenExcept(const std::string& msg, int err_num):
               m_error_message(msg),
               m_error_number(err_num)
               {}
			  
   /** 
    *  Destructor.
    *  Virtual to allow for subclassing.
    */
   virtual ~GenExcept() throw (){}

   /** 
    *  Returns a pointer to  error description.
    *
    *  @return A pointer to a const char*. The underlying memory
    *  is in possession of the Except object. Callers must
    *  not attempt to free the memory.
    */
   virtual const char* what() const throw () 
   {
      return m_error_message.c_str();
   }
    
   /**
    *  Returns error number.
    *
    *  @return #error_number
    */
   virtual int getErrorNumber() const throw() 
   {
      return m_error_number;
   }	   	   
};
#endif
