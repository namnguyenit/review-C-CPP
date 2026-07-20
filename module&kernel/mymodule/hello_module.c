#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Trung Cao");
MODULE_DESCRIPTION("A simple Hello World Kernel Module with Parameters");

// 1. Khai bao bien toan cuc
static int my_number = 10;
static char *my_name = "Trung Cao";

// 2. Kich hoat Phep thuat Macro
module_param(my_number, int, 0644);
module_param(my_name, charp, 0644);

// 3. Mo ta tham so
MODULE_PARM_DESC(my_number, "Mot con so bat ky do ban nhap vao");
MODULE_PARM_DESC(my_name, "Ten cua ban");

static int __init hello_init(void) {
    pr_info("Hello Kernel: Xin chao %s! So ban nhap la: %d\n", my_name, my_number);
    return 0;
}

static void __exit hello_exit(void) {
    pr_info("Goodbye Kernel: Tam biet %s!\n", my_name);
}

module_init(hello_init);
module_exit(hello_exit);
