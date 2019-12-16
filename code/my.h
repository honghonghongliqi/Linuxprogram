#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<limits.h>
#include<string.h>
#include<sys/time.h>
#include<sys/types.h>
#include<syscall.h>
#include<errno.h>
#define NUM 4
#define LOOP 1000000
int count(int);
void *thread_function(void *arg);
