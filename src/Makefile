# 设置默认内核路径，可以在调用 make 时覆盖
KERN_DIR ?= /home/book/100ask_imx6ull-sdk/Linux-4.9.88

# 获取当前路径
PWD := $(shell pwd)

# 模块名和测试名
module_name = drv
test_name = drv_test

# 挂载目录路径
mnt_directory = /home/book/remote/mnt_imx6ull

# 环境变量设置
ARCH ?= arm
CROSS_COMPILE ?= arm-buildroot-linux-gnueabihf-

# 构建所有目标
all:
	$(MAKE) -C $(KERN_DIR) M=$(PWD) modules 
	$(CROSS_COMPILE)gcc -o $(test_name) $(test_name).c 

# 清理生成的文件
clean:
	$(MAKE) -C $(KERN_DIR) M=$(PWD) clean
	rm -rf modules.order Module.symvers $(module_name).mod.c
	rm -f $(module_name).ko $(test_name)

# 拷贝模块到指定目录
cp:
	mkdir -p $(mnt_directory)
	cp $(module_name).ko $(mnt_directory)

# 模块编译配置
obj-m += $(module_name).o
