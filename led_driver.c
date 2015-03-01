/* 

// to build
sudo make all

// to clean
sudo make clean

// register driver
sudo insmod ./led_driver.ko

// create device file
sudo mknod -m 666 /dev/test_led c 324 0 

//test
echo 1 > /dev/test_led // turns on
echo 0 > /dev/test_led // turns off
*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>

#include <asm/io.h>
#include <mach/platform.h>
#include <linux/device.h>

#include <linux/timer.h>

#include "bcm_2835_arm.h"

#define TARGET_MAJOR_NUMBER			324


Bcm2835GpioRegisters_t *s_pBcm;
static const int DefaultPinNo = 18;

static struct timer_list m_timer;
static const int timerPeriod = 75;


MODULE_LICENSE("GPL");

static void SetPinMode(int pinNumber, Bcm2835GpioFunctionModes_t mode) {
	int index = pinNumber / NUMBER_OF_PINS_PER_REGISTER;
	int offset = (pinNumber % NUMBER_OF_PINS_PER_REGISTER) * CONTROLLING_BITS_PER_PIN;

	unsigned currentValue = s_pBcm->GPFSEL[index];
	unsigned mask = 0b111 << offset;	
	s_pBcm->GPFSEL[index] = (currentValue & ~mask) | ((mode << offset) & mask);
}

static void SetPinValue(int pinNumber, bool isSet) {
	if (isSet) {
		s_pBcm->GPSET[pinNumber / SIZE_OF_EACH_REGISTER] = (1 << (pinNumber % SIZE_OF_EACH_REGISTER));
	} else {
		s_pBcm->GPCLR[pinNumber / SIZE_OF_EACH_REGISTER] = (1 << (pinNumber % SIZE_OF_EACH_REGISTER));
	}
}

int m_open(struct inode *pinode, struct file *pfile) {	
	return 0;
}

ssize_t m_read(struct file *pfile, char __user *buffer, size_t length, loff_t *offset) {	
	SetPinValue(DefaultPinNo, false);
	return 0;
}

ssize_t m_write (struct file *pfile, const char __user *buffer, size_t length, loff_t *offset) {	
	if(buffer && buffer[0] == '1') {
		SetPinValue(DefaultPinNo, true);
	} else {
		SetPinValue(DefaultPinNo, false);
	}	

	return length;
}

int m_release (struct inode *pinode, struct file *pfile) {	
	return 0;
}

struct file_operations f_operations = {
	.owner = THIS_MODULE,
	.open = m_open,
	.read = m_read,
	.write = m_write,
	.release = m_release
};

static void handleTimerEvent(unsigned long data) {
	static bool on = false;
	on = !on;
	SetPinValue(DefaultPinNo, on);
	mod_timer(&m_timer, jiffies + msecs_to_jiffies(timerPeriod));
}


int m_init(void) {	
	register_chrdev(TARGET_MAJOR_NUMBER, "LED Driver", &f_operations);	
	s_pBcm = (Bcm2835GpioRegisters_t *)__io_address(GPIO_BASE);
	SetPinMode(DefaultPinNo, Function_Mode_Output);

	setup_timer(&m_timer, handleTimerEvent, 0);
	mod_timer(&m_timer, jiffies + msecs_to_jiffies(timerPeriod));

	return 0;
}

void m_exit(void) {	
	unregister_chrdev(TARGET_MAJOR_NUMBER, "LED Driver");
	SetPinValue(DefaultPinNo, false);
	SetPinMode(DefaultPinNo, Function_Mode_Input);

	del_timer(&m_timer);
}


module_init(m_init);
module_exit(m_exit);