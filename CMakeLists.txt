cmake_minimum_required(VERSION 3.10)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

find_package( OpenCV REQUIRED )

if (UNIX)
  set (CMAKE_CXX_FLAGS "-Wall -O3")
endif ()

# set the project name
project(ARImageProc)

include_directories (src)

# add the executable
add_executable(ARImageProc src/ARImageProc.cpp)

target_link_libraries(ARImageProc ${OpenCV_LIBS} )
