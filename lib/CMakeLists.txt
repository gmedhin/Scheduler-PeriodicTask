
set(SOURCE_FILES src/Scheduler.cpp)
add_library(Lib ${SOURCE_FILES})
target_include_directories(Lib PUBLIC include/)
target_link_libraries(Lib PUBLIC Util)
#target_compile_features(Lib PRIVATE cxx_std_17)


