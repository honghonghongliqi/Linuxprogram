//#include"myhead.h"
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<math.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
int main(int argc, char *argv[])
{
   while(1)
   {
      //system("clear");
      int choice;
      print_menu();
      scanf("%d",&choice);
      switch(choice)
      {
         case 0:exit(0);break;
         case 1:/*create_file_1();*/break;
         case 2:write_file_1();
         case 3:/*read_file_1();*/break;
         case 4:
         case 5:break;
      }
   }
}

void print_menu()
{
   printf("****************************\n");
   printf("0.退出\n");
   printf("1.创建新文件\n");
   printf("2.写文件\n");
   printf("3.读文件\n");
   printf("4.修改文件权限\n");
   printf("5.查看当前文件的权限修改文件权限\n");
   printf("****************************\n");
   printf("Please input your choice(0-6):");
}

void write_file_1(){//文件读写函数版本号:1
    char file_name[20];
    int flag=1;
    printf("请输入您想要写入内容的文件名:\n");
    scanf("%s",file_name);
    int handle;
    if((handle=open(file_name,O_WRONLY | O_CREAT | O_TRUNC ,0664))==-1){
        printf("Error!\n");
        exit(1);
    }
    printf("确认文件打开成功或创建成功，可以开始写入!\n");
    printf("请输入您想要写入的内容,一次性只能输出20个字符的内容,退出输入请输入空格+回车\n");
    while(flag!=0){
        char write_mes[20];
        printf("您本次的输入:\n");
        scanf("%s",write_mes);
        if(write_mes[0]=' ')
           flag=0;
        write(handle,write_mes,sizeof(write_mes));
    }
    close(handle);
    printf("文件写入操作成功！，按任意键回到主菜单！\n");
    getchar();
}




