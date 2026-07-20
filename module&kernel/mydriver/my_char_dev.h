#ifndef MY_CHAR_DEV_H
#define MY_CHAR_DEV_H

#include <linux/ioctl.h>


#define MAGIC_NUM 'M'

#define CMD_CLEAR_BUFFER _IO(MAGIC_NUM, 0)

#endif