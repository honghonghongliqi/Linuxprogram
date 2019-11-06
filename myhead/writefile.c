#include"myhead.h"
void write_file_1(){
    void uwrite(const char *file_name,int *array,int size){
    char file_name[20];
    printf("请输入您想要写入内容的文件名:\n");
    scanf("%s",file_name);
    int handle;
    if((handle=open(file_name,O_WRONLY | O_CREAT | O_TRUNC ,0664))==-1){
        printf("Error!\n");
        exit(1);
    }
    printf("确认文件打开成功或创建成功，可以开始写入!\n");
    printf("请输入您想要写入的内容,一次性只能输出20个字符的内容,退出输入请输入空格+回车\n");
    while(1){
        char write_mes[20];
        printf("您本次的输入:\n");
        scanf("%s",write_mes);
        write(handle,write_mes,20);
    }
    close(handle);
}
