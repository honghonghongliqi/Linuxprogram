#include"ourhead.h"
int main(){
    int fdsrc,fddes,nbytes;
    int flags=O_CREAT | O_TRUNC | O_WRONLY;
    int z;
    char buf[20],src[20],des[20];
    printf("请输入目标文件名:");
    scanf("%s",des);
    fdsrc=open("/etc/passwd",O_RDONLY);
    if(fdsrc<0){
        exit(1);
    }
    fddes=open(des,flags,0644);
    if(fddes<0){
        exit(1);
    }
    while((nbytes=read(fdsrc,buf,20))>0){
        z=write(fddes,buf,nbytes);
        if(z<0){
            perror("写目标文件出错");/*此函数可以用来输出“错误原因信息”字符串*/
        }
    }
    close(fdsrc);
    close(fddes);
    printf("复制“/etc/passwd”文件为“%s”文件成功!\n",des);
    exit(0);
}
