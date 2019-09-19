#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<math.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
struct result{
    long sum;
    float average;
}


void show(int *,int);//打印结果
void uround(int *,int);//产生随机数,size为数量
stuct result uoprater(int *,int);//计算总数和平均数
int comp(const void *a,const void *b);//qsort()用函数
void syssort(int *,int);//系统的排序
void usort(int *,int);//自己的排序
double calculate_time();//计算时间差的函数
void uwrite(char *);//写文件的函数
int* uread(char *);//读文件的函数

