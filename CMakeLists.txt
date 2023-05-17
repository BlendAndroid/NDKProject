# CMake的最低版本为3.10
cmake_minimum_required(VERSION 3.10)
# get_filename_component 获取包含完整路径的其中一部分，例如文件名称（不包含）后缀，或者其所在的文件夹的绝对路径

# get_filename_component(<VAR> <FileName> <COMP> [CACHE])

# CMAKE_CURRENT_SOURCE_DIR C:/Project/NDKProject

# COMP可选择以下关键字：
# DIRECTORY 所在文件夹的绝对路径
# NAME 文件名（包含后缀）
# EXT 文件后缀
# NAME_WE 文件名（不包含后缀）
# ABSOLUTE 绝对路径，一般用于使用相对路径生成绝对路径
# REALPATH 链接指向的绝对路径

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})

# 项目名称
project(${ProjectId} C)

set(CMAKE_C_STANDARD 11)

file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/c_demo/*.c")

foreach(file ${files})
    get_filename_component(name ${file} NAME)
    # 使用add_executable命令将文件添加到我们的项目中
    add_executable(${name} ${file})
endforeach()


# 下面这个是一个项目完整的配置

# 配置头文件
INCLUDE_DIRECTORIES("c_demo/header/include/")

# 添加源文件目录
AUX_SOURCE_DIRECTORY(c_demo/header HEADER)

# 设置变量
SET(TEST_HEADER ${HEADER})

ADD_EXECUTABLE("factorial_main" ${TEST_HEADER})