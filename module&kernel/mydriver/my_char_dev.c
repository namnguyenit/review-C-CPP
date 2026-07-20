#include "asm/stat.h"
#include "linux/err.h"
#include "linux/types.h"
#define pr_fmt(fmt) "[My Char Dev]" fmt

#include "linux/module.h"
#include "linux/init.h"
#include "linux/fs.h"
#include "linux/cdev.h"
#include "linux/device.h"
#include "linux/uaccess.h"

#define DEVICE_NAME "my_char_dev"
#define CLASS_NAME "my_char_class"
#define MAX_SIZE 1024

static char kernel_buffer[MAX_SIZE]; // bộ nhớ đệm trong ram
static int current_size = 0; // kích thước hiện tại của bộ nhớ đệm


// biến quản lý trạng thái
static dev_t dev_number;
static struct cdev my_cdev;
static struct class *my_class;


static int my_open(struct inode *inode, struct file *file) {
    pr_info("UserSpace mo thiet bi\n");
    return 0;
}

static int my_release(struct inode *inode, struct file *file) {
    pr_info("UserSpace dong thiet bi\n");
    return 0;
}


static ssize_t my_read(struct file *file, char __user *user_buf, size_t size, loff_t *offset) {
    //  Tránh đọc vượt quá dữ liệu hiện có 
    if (*offset >= current_size) {
        return 0; // Báo hiệu EOF (End of File) 
    }

    if (size > current_size - *offset) {
        size = current_size - *offset;
    }

    // Đẩy dữ liệu từ kernel_buffer lên user_buf 
    if (copy_to_user(user_buf, kernel_buffer + *offset, size)) {
        pr_err("Loi doc du lieu!\n");
        return -EFAULT;
    }

    *offset += size;
    pr_info("User Space da doc %zu bytes\n", size);
    return size;
}

static ssize_t my_write(struct file *file, const char __user *user_buf, size_t size, loff_t *offset) {
    /* Chống ghi tràn bộ đệm (Buffer Overflow) */
    if (size > MAX_SIZE) {
        size = MAX_SIZE;
    }

    /* Kéo dữ liệu từ user_buf xuống kernel_buffer */
    if (copy_from_user(kernel_buffer, user_buf, size)) {
        pr_err("Loi ghi du lieu!\n");
        return -EFAULT;
    }

    current_size = size;
    pr_info("User Space da ghi %zu bytes\n", size);
    return size;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_release,
    .read = my_read,
    .write = my_write,

};


static int __init my_char_dev_init(void) {
    int ret;
    // 1. Cap phat so hieu thiet bi
    ret  = alloc_chrdev_region(&dev_number, 0, 1, DEVICE_NAME);
    if (ret < 0) {
        pr_err("Khong the cap phat so hieu thiet bi\n");
        return -1;
    }
    pr_info("So hieu thiet bi: %d:%d\n", MAJOR(dev_number), MINOR(dev_number));

    // 2. Khoi tao cdev
    cdev_init(&my_cdev, &fops);

    ret = cdev_add(&my_cdev, dev_number, 1);
    if (ret < 0) {
        pr_err("Khong the them cdev\n");
        unregister_chrdev_region(dev_number, 1);
        return -1;
    }

    // 3. Tao class va device
    my_class = class_create(CLASS_NAME);
    if (IS_ERR(my_class)) {
        pr_err("Khong the tao class\n");
        cdev_del(&my_cdev);
        unregister_chrdev_region(dev_number, 1);
        return PTR_ERR(my_class);
    }

    if (IS_ERR(device_create(my_class, NULL, dev_number, NULL, DEVICE_NAME))) {
        pr_err("Khong the tao device\n");
        class_destroy(my_class);
        cdev_del(&my_cdev);
        unregister_chrdev_region(dev_number, 1);
        return -1;
    }

    pr_info("Module my_char_dev da duoc nap thanh cong\n");
    return 0;

}

static void __exit my_char_dev_exit(void) {
    device_destroy(my_class, dev_number);
    class_destroy(my_class);
    cdev_del(&my_cdev);
    unregister_chrdev_region(dev_number, 1);
    pr_info("Module my_char_dev da duoc go bo\n");
}



module_init(my_char_dev_init);
module_exit(my_char_dev_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Trung");
MODULE_DESCRIPTION("Project Character Device");
