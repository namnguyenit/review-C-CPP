#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define DEVICE_PATH "/dev/my_char_dev"


int main(){
    int fd  = open(DEVICE_PATH, O_RDWR);
    char write_buf[] = "Hello, Kernel!, day la app User Space";
    char read_buf[100];
    int byt_read, byt_write;
    
    printf("dang mo file device: %s\n", DEVICE_PATH);
    if (fd < 0) {
        perror("Loi mo file device");
        return EXIT_FAILURE;
    }
    printf("Mo file device thanh cong\n");
    printf("dang ghi du lieu vao device: %s\n", write_buf);
    byt_write = write(fd, write_buf, strlen(write_buf));
    if (byt_write < 0) {
        perror("Loi ghi du lieu vao device");
        close(fd);
        return EXIT_FAILURE;
    }else{
        printf("Ghi du lieu vao device thanh cong, so byte ghi: %d\n", byt_write);
    }
    printf("dang doc du lieu tu device\n");
    memset(read_buf, 0, sizeof(read_buf));
    byt_read = read(fd, read_buf, sizeof(read_buf));
    if (byt_read < 0) {
        perror("Loi doc du lieu tu device");
        close(fd);
        return EXIT_FAILURE;
    }else{
        printf("Doc du lieu tu device thanh cong, so byte doc: %d\n", byt_read);
        printf("Du lieu doc duoc: %s\n", read_buf); 
    }
    printf("dang dong file device\n");
    close(fd);
    return 0;
}


