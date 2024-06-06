cmake_minimum_required(VERSION 3.15)
project(driver_project)

# 设置路径变量
set(LIBPATH ${PROJECT_SOURCE_DIR}/lib)
set(EXECPATH ${PROJECT_SOURCE_DIR}/bin)
set(HEADPATH ${PROJECT_SOURCE_DIR}/inc)

# 配置查找路径模式
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# 定义选项
option(USE_x86 "Whether to build for x86" OFF)

if (USE_x86)
    # 设置x86编译工具链和系统信息
    set(CMAKE_SYSTEM_NAME Linux)
    set(CMAKE_SYSTEM_PROCESSOR x86_64)
    set(CMAKE_C_COMPILER /usr/bin/gcc)
    set(CMAKE_CXX_COMPILER /usr/bin/g++)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -DDEBUG -ggdb -Wall -Wno-unused -O0 -fPIC")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -DDEBUG -ggdb -Wall -Wno-unused -O0 -fPIC")
else()
    # 设置ARM交叉编译工具链和系统信息
    set(CMAKE_SYSTEM_NAME Linux)
    set(CMAKE_SYSTEM_PROCESSOR arm)
    set(target_arch aarch64-linux-gnu)
    set(CMAKE_C_COMPILER /home/book/100ask_imx6ull-sdk/ToolChain/arm-buildroot-linux-gnueabihf_sdk-buildroot/bin/arm-buildroot-linux-gnueabihf-gcc)
    set(CMAKE_CXX_COMPILER /home/book/100ask_imx6ull-sdk/ToolChain/arm-buildroot-linux-gnueabihf_sdk-buildroot/bin/arm-buildroot-linux-gnueabihf-g++)
    set(CMAKE_LIBRARY_ARCHITECTURE ${target_arch} CACHE STRING "" FORCE)
endif()

# 添加子目录
add_subdirectory(driver)
add_subdirectory(test_app)
