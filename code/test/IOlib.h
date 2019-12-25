#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<pthread.h>
#include<sys/time.h>
#include<sys/types.h>
#include <sys/stat.h>
#include<semaphore.h>
#define MAXDATASIZE 256

#define SERVPORT 4545	/*服务器监听端口号*/
#define BACKLOG 10     	/*最大同时连接请求数*/
#define FILENAME "service.log"
#define TN 4
char nowDate[100];
sem_t serviceMutex;
pthread_mutex_t mutex;
//void sleep(clock_t);
//1. 创建新文件
int  createNewFile(char *);
//2. 写文件
int writeFile(char *,int,int,char*);
//4. 获取现在的时间:年月日时分秒
void getNowDate();
//5. service线程
void *serviceThread(void *param);
//6. 获取client线程
void *clientThread(void *param);
