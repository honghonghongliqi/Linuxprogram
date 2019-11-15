#include"myhead.h"
void modi_file_1()//修改文件权限函数,版本号为:1
{
   int handle;
   int mode;
   int mode_u;
   int mode_g;
   int mode_o;
   char file_name[20];
   printf("请选择您要进行操作的文件名:");
   scanf("%s",file_name);
   if((handle=open(file_name,O_RDONLY,S_IWRITE|S_IREAD))==-1)
   {
      perror("find fail无此文件");
      exit(1);
   }
   printf("请输入您要修改的权限(以整数形式型如：777):");
   scanf("%d",&mode);
   if(mode > 777 || mode< 0)
      exit(0);
   mode_u=mode/100;
   mode_g=(mode-(mode_u*100))/10;
   mode_o=mode-(mode_u*100)-(mode_g*10);
   mode=(mode_u*8*8)+(mode_g*8)+mode_o;
   if(fchmod(handle,mode)== -1)
      exit(0);
   printf("\n修改成功!按任意键返回主菜单!");
   getchar();
   getchar();
   close(handle);
}
