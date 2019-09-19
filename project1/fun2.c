#include"uhead.h"

int comp(const void *a,const void *b){
    const int *p=a;
    const int *q=b;
    return *p-*q;
}

struct result uoprater(int *array,int size){
    struct result ret;
    ret.sum=0;
    for(int x=0;x<size;x++){
        ret.sum+=array[x];
    }
    ret.average=ret.sum/size;
    return ret;
}


void syssort(int *array,int size){
    qsort(array,size,sizeof(*array),comp);
}

void usort(int *array,int size){
    int num=0;
    for(int x=0;x<size-1;x++){
        for(int y=x;y<size;y++){
            if(array[x]>array[y]){
                num=array[y];
                array[y]=array[x];
                array[x]=num;
            }
        }
    }
}

double calculate_time(){
    struct timeval t;
    gettimeofday(&t,0);
    return t.tv_sec + 1E-6 * t.tv_usec;
}