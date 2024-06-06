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


module_srcs := $(filter-out %app.c, $(wildcard *.c))
module_objs := $(patsubst %.c, %.o, $(module_srcs))
$(module_name)-y := $(module_objs)
obj-m += $(module_name).o

app_srcs := $(filter %app.c, $(wildcard *.c))
# ab-y := a.o b.o
# obj-m += ab.o

# 构建所有目标
all: modules app

modules:
	$(MAKE) -C $(KERN_DIR) M=$(PWD) modules 
app:
	$(CROSS_COMPILE)gcc -o $(test_name) $(app_srcs)

# 清理生成的文件
clean:
	$(MAKE) -C $(KERN_DIR) M=$(PWD) clean
	rm -rf modules.order Module.symvers $(module_name).mod.c
	rm -f $(module_name).ko $(test_name)

# 拷贝模块到指定目录
cp: cp_app cp_drv
cp_app:
	cp $(test_name) $(mnt_directory)
cp_drv:
	cp $(module_name).ko $(mnt_directory)
	




