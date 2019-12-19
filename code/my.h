#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<pthread.h>
#include<sys/time.h>
#include<sys/types.h>
#include<limits.h>
#include<semaphore.h>
#define LENGTH 100
#define LOOP 1000
#define NUM 2
#define TN 100
#define WRITER_FIRST
int getMax(int *);
