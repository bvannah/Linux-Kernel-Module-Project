CONFIG_MODULE_SIG=n


obj-m += jif.o
obj-m += test1.o
obj-m += test2.o
obj-m += test3.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
