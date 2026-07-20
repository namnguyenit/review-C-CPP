#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>      
#include <unistd.h>
#include <sys/ioctl.h>    /* BẮT BUỘC: Thư viện chứa hàm ioctl cho User Space */

#include "../mydriver/my_char_dev.h"  /* Kéo từ điển mã lệnh vào */

#define DEVICE_PATH "/dev/my_char_dev"

int main() {
    int fd;
    char write_buf[] = "Xin chao Kernel!";
    char read_buf[1024];

    fd = open(DEVICE_PATH, O_RDWR); 
    if (fd < 0) {
        perror("Loi mo thiet bi"); return -1;
    }

    /* 1. Ghi và Đọc thử như bình thường */
    write(fd, write_buf, strlen(write_buf));
    read(fd, read_buf, sizeof(read_buf));
    printf("Truoc khi xoa, doc duoc: '%s'\n", read_buf);

    /* 2. RA LỆNH IOCTL XÓA BỘ ĐỆM */
    printf("\n>>> Gui lenh CMD_CLEAR_BUFFER xuong Kernel...\n");
    if (ioctl(fd, CMD_CLEAR_BUFFER) < 0) {
        perror("Loi gui lenh IOCTL");
    } else {
        printf(">>> Da gui lenh thanh cong!\n");
    }

    /* 3. Đọc lại để nghiệm thu */
    memset(read_buf, 0, sizeof(read_buf)); 
    int bytes = read(fd, read_buf, sizeof(read_buf));
    printf("Sau khi xoa, doc duoc %d bytes. Noi dung: '%s'\n", bytes, read_buf);

    close(fd);
    return 0;
}
