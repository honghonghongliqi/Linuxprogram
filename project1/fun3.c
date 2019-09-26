#include"uhead.h"

void uwrite(const char *file_name,int *array,int size){
    int handle;
    if((handle=open(file_name,O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO))==-1){
        printf("Error!\n");
        exit(1);
    }
    for(int x=0;x<size;x++){
        write(handle,array+x,sizeof(*array));
    }
    close(handle);
}

void uread(const char *file_name,int *array,int size){
    int handle;
    if((handle=open(file_name,O_RDONLY,S_IWRITE|S_IREAD))==-1){
        printf("Error!\n");
        exit(1);
    }
    for(int x=0;x<size;x++){
        read(handle,array+x,sizeof(*array));
    }
    close(handle);
}