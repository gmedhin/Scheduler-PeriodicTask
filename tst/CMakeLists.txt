
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package (Threads REQUIRED)
find_package (Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

include_directories("${PROJECT_SOURCE_DIR}")

#Google Test
add_executable(mainTest schedulerUT/main.cpp)
target_link_libraries(mainTest gtest)

add_executable(simpleTest schedulerUT/SimpleTest.cpp)
target_link_libraries(simpleTest gtest gmock_main Lib Util Threads::Threads)
add_test(NAME simple_test COMMAND simpleTest)




