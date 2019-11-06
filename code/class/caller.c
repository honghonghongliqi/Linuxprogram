#include "my.h"
int main()
{
    int ret;
    printf("caller:pid = %d,ppid = %d\n",getpid(),getppid());
    ret=system("./test 123 445 hello world");
    printf("After calling!\n");
    sleep(1);
    return 0;
}
