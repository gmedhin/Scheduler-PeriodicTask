# Scheduler-PeriodicTask

The program uses methods provided by the Scheduler class to add and execute any task (say PeriodicTask) at a specified time interval. The Scheduler provides the following methods:
   - Add PeriodicTask with given time interval, in seconds
   - Remove PeriodicTask so that it will no longer executed periodically
   - Change the time interval of any already exissting PeriodicTask
   
The implementation takes the following additional (non-functional ) requirements into consideration:
   - Adding and removing PeriodicTask must be possible at any time
   - The interface is thread-safe (uses mutex to protect access to shared resources)
   - The logic works with externally provided time, does not relay on system time
   
Directories:
        
    main - contains the main method (driver code)
    lib - contains the library (interface), scheduler 
    util - other utilities
    tst - contains the test file 
    bld - contains build generated files
   
How to build code?

     1. mkdir bld  //-->if it does not already exist
     2. cd bld
     3. cmake ../.  
     4. make
     
Test the code?

      1. cd bld   //--> go to build folder
      2../main/main  //--> to test the the code using the main driver method 
      3. make test  // --> to execute the testcases

Note: You need atleast c++17 compiler support
