#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>


int main(void){
    char buf1[]="abcdefghij";
    char buf2[]="ABCDEFGHIJ";
    int fd;
    if((fd=creat("file.hole",FILE_MODE))<0){
        err_sys("creat error");
    }
    if(wrtie(fd,buf1,10)!=10){
        err_sys("buf1 write error");
    }
    if(lseek(fd,40,SEEK_SET)==-1){
        err_sys("lseek error");
    }
    if(write(fd,buf2,10)!=10){
        err_sys("buf2 write error");
    }
    exit(0);
}