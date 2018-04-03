# required cmake version
cmake_minimum_required(VERSION 2.8)
# 项目名
project(MergePicture)
# 编译器
set(CMAKE_CXX_COMPILER g++)
# 编译类型
#set(CMAKE_BUILD_TYPE "Release")
# C++标准
set(CMAKE_CXX_FLAGS "-std=c++11")
# 指定opencv的路径
#set(OpenCV_DIR "/usr/local/include")
# 寻找OpenCV库
find_package(OpenCV REQUIRED)
#指定可执行文件的位置
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY /home/creator/Projects/C++/REN/run/数据)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../run)
# 包含OpenCV头文件目录
include_directories(${OPENCV_INCLUDE_DIRS})
# 包含freetype的头文件目录
include_directories("/usr/local/include/freetype2")
# 包含当前项目的头文件项目路径
include_directories(lib)

file(GLOB CURRENT_HEADERS  *.h lib/*.h)
file(GLOB CURRENT_SOURCES  *.cpp lib/*.cpp)

add_executable(${PROJECT_NAME} ${CURRENT_HEADERS} ${CURRENT_SOURCES})

target_link_libraries(${PROJECT_NAME}
        ${OpenCV_LIBS}  # 添加OpenCV库
        freetype        # 添加freetype库
        )