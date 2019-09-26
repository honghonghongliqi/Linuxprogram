#include"ourhead.h"
int main(){
    FILE *fp_new,*fp_old;//fp_new为新文件,fp_old为老文件
    int nbytes;
    int z;
    char buf[20],src[20],des[20];
    printf("请输入目标文件名:");
    scanf("%s",des);
    ;
    if((fp_old=fopen("/etc/passwd","r"))==NULL){//利用fopen以只读形式打开文件
        exit(1);
    }
    if((fp_new=fopen(des,"a+"))==NULL){//以可读可写追加方式打开一个文本文件若文件不存在，则会建立该文件。
        exit(1);
    }
    while((nbytes=fread(buf,sizeof(*buf),20,fp_old))>0){//fread(保存数据的指针,每个数据类型的大小,数据的数量,文件指针).
        z=fwrite(buf,sizeof(*buf),nbytes,fp_new);//fwrite(保存数据的指针,每个数据类型的大小,数据的数量,文件指针).
        if(z<0){
            perror("写目标文件出错");/*此函数可以用来输出“错误原因信息”字符串*/
        }
    }
    fclose(fp_old);
    fclose(fp_new);
    printf("复制“/etc/passwd”文件为“%s”文件成功!\n",des);
    exit(0);
}