#include "my.h"

int g=10;

int main()
{
    int t=20;
    static s=30;
    pid_t pid;
    pid=vfork();
    if(pid<0)
    {
	perror("vfork failed!\n");
	exit(-1);
    }
    else if(pid==0)
    {
	printf
    }
}
