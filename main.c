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
         case 2:/*write_file_1();*/
         case 3:/*read_file_1();*/break;
         case 4:
         case 5:break;
      }
   }
}








