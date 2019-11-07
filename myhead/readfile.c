#include"myhead.h"
void read_file_1(const char *file_name,int *array,int size){//文件读函数版本号为:1
    char file_name[20];
    char buf[20];
    int handle;
    if((handle=open(file_name,O_RDONLY,S_IWRITE|S_IREAD))==-1){
        printf("Error!\n");
        exit(1);
    }
    for(int x=0;x<size;x++){
        read(handle,array+x,sizeof(*array));
    }
    close(handle);
    system("PAUSE");
}
