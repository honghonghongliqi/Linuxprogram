#include<stdio.h>
#include<stdlib.h>
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
         case 1:
         case 2:
         case 3:
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
