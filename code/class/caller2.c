#include "my.h"
int main()
{
    printf("caller2:pid = %d,ppid = %d\n",getpid(),getppid());
    execl("/home/wyz/linuxprogram/code/test","./test","123","hello","World",NULL);
    printf("excel after calling!\n");
    return 0;
}
