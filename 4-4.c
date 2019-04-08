#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/stat.h> 
#include <sys/ipc.h> 
#include <fcntl.h> 
#define FIFO "/home/lh/my_fifo" int main()
{
    char buf[20] ;
    memset(buf, '\0', sizeof(buf));
    
    int ret;
    ret = access(FIFO, F_OK);//查看文件是否存在
    if(ret != 0)
    {
        fprintf(stderr, "FIFO %s does not existed", FIFO);
        exit(EXIT_FAILURE);
    }  
    int fifo_fd;
    fifo_fd = open(FIFO, O_RDONLY);//只读方式打开文件FIFO
    if(-1 == fifo_fd)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    int num = 0;
    num = read(fifo_fd, buf, sizeof(buf)); //读取文件
    printf("Read %d words: %s\n", num, buf);
    close(fifo_fd);
    return 0;
}