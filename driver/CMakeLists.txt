set(KERNEL_DIR /home/book/100ask_imx6ull-sdk/Linux-4.9.88)

# 设置当前目录
set(CRU_DIR ${CMAKE_CURRENT_SOURCE_DIR})
# 设置NFS目录
set(NFS_DIR /home/book/remote/mnt_imx6ull)

# 将当前目录添加到头文件路径中
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# 添加可执行文件输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# 搜索当前目录下的源文件并将其保存到变量中
aux_source_directory(. SRC_FILE)

# 添加模块目标
add_library(hello_drv MODULE ${SRC_FILE})

# 设置模块的输出名称
set_target_properties(hello_drv PROPERTIES PREFIX "")

# 添加编译模块的命令
add_custom_target(build_module
    COMMAND make -C ${KERNEL_DIR} M=${CRU_DIR} modules
    COMMENT "Building kernel module..."
)

# 添加清理模块的命令
add_custom_target(clean_module
    COMMAND make -C ${KERNEL_DIR} M=${CRU_DIR} clean
    COMMENT "Cleaning kernel module build..."
)

# 添加安装模块到NFS目录的命令
add_custom_target(install_module
    COMMAND cp -rf ${CRU_DIR}/*.ko ${NFS_DIR}
    COMMENT "Installing kernel module..."
)

# 确保在构建模块之前先执行清理
add_dependencies(build_module clean_module)