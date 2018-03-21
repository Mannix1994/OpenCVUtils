# required cmake version
cmake_minimum_required(VERSION 2.8)
# CMakeLists.txt for G4CU project
project(OpenCVUtils)

set(CMAKE_CXX_COMPILER clang++)
#set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-std=c++11")

# packages
#set(OpenCV_DIR "/usr/local/include") 	    #修改这一句，指定opencv的版本
#set(OpenCV_DIR "/usr/local/opencv331share/OpenCV")
find_package(OpenCV REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../run)	#这一句指定可执行文件的位置

include_directories(${OPENCV_INCLUDE_DIRS})
include_directories(lib)

file(GLOB CURRENT_HEADERS  *.h lib/*.h)
file(GLOB CURRENT_SOURCES  *.cpp lib/*.cpp)


add_executable(${PROJECT_NAME} ${CURRENT_HEADERS} ${CURRENT_SOURCES})

target_link_libraries(${PROJECT_NAME}
        ${OpenCV_LIBS}
        )