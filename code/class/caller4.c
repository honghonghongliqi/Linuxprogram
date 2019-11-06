#include "my.h"
int main()
{
    char *arg[]={"./test","123","hello","World",NULL};
    printf("caller2:pid = %d,ppid = %d\n",getpid(),getppid());
    execv("/home/wyz/linuxprogram/code/test",arg);
    printf("excel after calling!\n");
    return 0;
}
