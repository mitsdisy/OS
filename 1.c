#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void){
pthread_mutex_t mutex;//创建互斥锁


pid_t pid1 = fork();	//创建p1
if(pid1 == 0){
	printf("I am the process P1\n");
	return 0;
}

pthread_mutex_init(&mutex,NULL); //初始化p2p3互斥锁
waitpid(pid1, NULL, 0);	//等P1进程结束
pid_t pid2 = fork();//创建p2
if(pid2 == 0){
	pthread_mutex_lock(&mutex);	//加互斥锁
	printf("I am the process P2\n");
	pthread_mutex_unlock(&mutex);
	return 0;
}

waitpid(pid1, NULL, 0);//等p1进程结束
pid_t pid3 = fork();//创建p3
if(pid3 == 0){
	pthread_mutex_lock(&mutex);
	printf("I am the process P3\n");//加互迟锁
	pthread_mutex_unlock(&mutex);
	return 0;
}

waitpid(pid2, NULL, 0);
waitpid(pid3, NULL, 0);//等p2p3结束
pid_t pid4 = fork();//创建p4
if(pid4 == 0){
	printf("I am the process P4\n");
	return 0;
}


 
pthread_mutex_destroy(&mutex);//销毁互斥锁
return 0;
}
