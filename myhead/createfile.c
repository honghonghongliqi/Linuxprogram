void create_file_1()//当前版本号为1
{
   int fd;
   char str[10];
   printf("请输入您想要创建的文件名称:\n");
   scanf("%s",str);
   if((fd=open(str,O_WRONLY | O_CREAT |O_TRUNC,0664))==-1)
   {
      printf("Error create file");
      exit(0);
   }
   printf("创建文件成功或文件已存在。\n");
   close(fd);
}

