# 设置默认内核路径，可以在调用 make 时覆盖
KERN_DIR ?= /home/book/100ask_imx6ull-sdk/Linux-4.9.88

# 获取当前路径
PWD := $(shell pwd)

# 模块名和测试名
module_name := drv
test_name := drv_test
reserved_line := 25
# 挂载目录路径
mnt_directory := /home/book/remote/mnt_imx6ull

# 环境变量设置
ARCH ?= arm
CROSS_COMPILE ?= arm-buildroot-linux-gnueabihf-

# 获取所有以 _drv.c 结尾的文件
module_srcs := $(filter %_drv.c, $(wildcard *.c))
# 将这些源文件转成对应的 .o 目标文件
module_objs := $(patsubst %.c, %.o, $(module_srcs))

# 设置编译内核模块的目标
drv-y := $(module_objs)
drv-y :=  add_drv.o  hello_drv.o
$(info drv-y: $(drv-y))
obj-m += $(module_name).o
# 将模块的所有对象文件加到模块名下

# 获取所有以 _app.c 结尾的文件
app_srcs := $(filter %_app.c, $(wildcard *.c))

# 默认目标
.PHONY: all modules app clean cp cp_app cp_drv

# 顶层构建调试信息
ifneq ($(KERNELRELEASE),)
    # 内核构建系统中执行
    # 内核模块构建规则已定义
else
# 顶层构建系统中执行
$(info Current directory: $(PWD))
$(info Module sources: $(module_srcs))
$(info Application sources: $(app_srcs))
$(info Module objects: $(module_objs))
$(info drv-y: $(drv-y))
# 构建所有目标
all: modules app

modules:
	sed -i '$(reserved_line)s/.*/drv-y := $(module_objs)/' $(PWD)/Makefile
	$(MAKE) -C $(KERN_DIR) M=$(PWD) modules

app:
	$(CROSS_COMPILE)gcc -o $(test_name) $(app_srcs)

# 清理生成的文件
clean:
	$(MAKE) -C $(KERN_DIR) M=$(PWD) clean
	rm -rf modules.order Module.symvers $(module_name).mod.c
	rm -f $(module_name).ko $(test_name)
	rm -f $(module_objs)

# 拷贝模块到指定目录
cp: cp_app cp_drv

cp_app:
	cp $(test_name) $(mnt_directory)

cp_drv:
	cp $(module_name).ko $(mnt_directory)
endif


































