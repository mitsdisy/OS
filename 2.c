#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>
#include <assert.h>

int ticket = 1000;	//票的总数为1000张
int temp = 0;
int i=100;//执行次数
sem_t blanks;	//退票余量
sem_t datas;	//售票余量

void *sold(void *arg){
	while(i--){
	sem_wait(&blanks);	
	temp = ticket;
	temp = temp - 1;
	ticket = temp;
	printf("we have %d tickets now\n",ticket);
	sem_post(&datas);	//卖完一张票后 售票数增加1
	}
	return NULL;
}

void *back(void *arg){
	while(i--){
	sem_wait(&datas);	
	temp = ticket;
	temp = temp + 1;
	ticket = temp;
	printf("we have %d tickets now\n",ticket);
	sem_post(&blanks);	//退完一张票后，票余量增加1
	}
	return NULL;
}

int main(int argc, char *argv[]){	
	sem_init(&blanks, 0, 1000);
	sem_init(&datas, 0, 0);
	pthread_t p1, p2;//创建进程
	pthread_create(&p1, NULL, sold, NULL);
	pthread_create(&p2, NULL, back, NULL);
	pthread_join(p1, NULL);
	pthread_join(p2, NULL); //运行
	sem_destroy(&blanks);
	sem_destroy(&datas);
        printf("we have %d tickets now\n",ticket);
	return 0;
}
