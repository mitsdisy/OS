#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/msg.h> 
#include <sys/ipc.h> 
#include <signal.h> 
#define BUF_SIZE 128    
struct msgbuf
{
    long mtype;
    char mtext[BUF_SIZE];
};
int main(int argc, char *argv[])
{
    key_t key;
    int msgId;
    key = ftok(".", 0xFF);
    msgId = msgget(key, IPC_CREAT|0644);
    if(-1 == msgId)
    {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
    printf("Process (%s) is started, pid=%d\n", argv[0], getpid());
    while(1)
    {
        alarm(0);
        alarm(600);    
        struct msgbuf rcvBuf;
        memset(&rcvBuf, '\0', sizeof(struct msgbuf));
        msgrcv(msgId, &rcvBuf, BUF_SIZE, 1, 0);   //读取消息          
        printf("Receive msg: %s\n", rcvBuf.mtext);
        struct msgbuf sndBuf;
        memset(&sndBuf, '\0', sizeof(sndBuf));
        strncpy((sndBuf.mtext), (rcvBuf.mtext),strlen(rcvBuf.mtext)+1);
        sndBuf.mtype = 2;
        if(-1 == msgsnd(msgId, &sndBuf, strlen(rcvBuf.mtext)+1, 0))//发送消息
        {
            perror("msgsnd");
            exit(EXIT_FAILURE);
        }
         if(!strcmp("end~", rcvBuf.mtext))
             break;
    }
    printf("THe process(%s),pid=%d exit~\n", argv[0], getpid());
    return 0;
}