#include"./myhead/myhead.h"
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
         case 1:create_file_1();break;
         case 2:write_file_1();break;
         case 3:read_file_1();break;
         case 4:modi_file_1();break;
         case 5:modi_file_1();break;
      }
   }
}








