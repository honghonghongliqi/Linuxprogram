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
      system("clear");
      int choice;
      print_menu();
      scanf("%d",&choice);
      switch(choice)
      {
         case 0:exit(0);break;
         case 1:/*create_file_1();*/break;
         case 2:
         case 3:read_file_1();
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

void read_file_1(){//文件读函数版本号为:1
    char file_name[20];
    char buf[1024];
    int handle;
    printf("请输入您想要读取的文件名:");
    scanf("%s",buf);
    if((handle=open(file_name,O_RDONLY,S_IWRITE|S_IREAD))==-1)
    {
       perror("read fail");
       exit(1);
    }
    if(read(handle,buf,sizeof(buf))==-1)
    {
       perror("read fail");
       exit(1);
    }
    printf("读取成功！,文件内容如下:\n");
    printf("---------------------------------------------\n");
    printf("%s",buf);
    printf("---------------------------------------------\n");
    close(handle);
}


