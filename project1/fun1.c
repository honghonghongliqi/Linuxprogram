#include"uhead.h"

void show(int *array,int size){
    for(int x=0;x<size;x++){
        printf("%d    ",*(array+x));
    }
}

void uround(int *array,int size){
    int num;
    srand((unsigned)time(NULL));
    for(int x=0;x<size;x++){
        num=rand()%1000;
        array[x]=num;
    }
}