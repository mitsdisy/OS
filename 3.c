#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>
#include <assert.h>

char buf[10] = {0};//初始化

sem_t blanks;	
sem_t datas;	
int readnum =0;//输入字符个数
int writenum =0;//写出字符个数

void *doread(void *arg){
	while(readnum<10) {
	sem_wait(&blanks);	//空闲内存判断
	scanf("%c",&buf[readnum]);
	readnum++;
	readnum %= 10;	//超过10 自动消掉十位数
	sem_post(&datas);	//输入字符个数加1
	}
	return NULL;
}

void *dowrite(void *arg){
	while(writenum<10) {
	sem_wait(&datas);	//判断是否有输入字符
	printf("%c ",buf[writenum]);
	sleep(1);			//sleep（1）
	writenum++;
	writenum %= 10;//超过10 自动消掉十位数
	sem_post(&blanks);	//空余内存加1	
	return NULL;
}

int main(int argc, char *argv[]){	
	sem_init(&blanks, 0, 10);
	sem_init(&datas, 0, 0);

	pthread_t p1, p2;//创建线程p1p2
	pthread_create(&p1, NULL, doread, NULL);	
	pthread_create(&p2, NULL, dowrite, NULL);

	pthread_join(p1, NULL);
	pthread_join(p2, NULL);

	sem_destroy(&blanks);
	sem_destroy(&datas);

	return 0;
}
