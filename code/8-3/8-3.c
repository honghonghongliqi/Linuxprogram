#include <sys/time.h> 
#include <sys/types.h> 
#include <unistd.h>
#define STDIN 0  /* 标准输入设备的描述字为0*/

int main()
{
	struct timeval tv;
	fd_set readfds;
	tv.tv_sec = 10;
	tv.tv_usec = 500000; /* tv_use设置成需要等待的微秒数,一秒中包括100000微秒 */
	FD_ZERO (&readfds) ;
	FD_SET(STDIN, &readfds);
	/* don't care about writefds and exceptfds: */
	select(STDIN+1, &readfds, NULL, NULL, &tv);
	if (FD_ISSET(STDIN, &readfds))
		printf("输入了\n");
	else
		printf ("超时\n");
}
