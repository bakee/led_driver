obj-m := led_driver.o

all:
#	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
    make -C /usr/src/linux-headers-3.18.8+/ M=$PWD modules  

clean:
#	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
    make -C /usr/src/linux-headers-3.18.8+/ M=$PWD clean  