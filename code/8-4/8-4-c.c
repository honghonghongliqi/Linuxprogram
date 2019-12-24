#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#define SERVPORT 4444		/*服务器监听端口号*/
#define MAXDATASIZE 256 	/*最大同时连接请求数*/
#define STDIN 0				/*标准输入文件描述符*/

int main(void)
{
int sockfd;			/*套接字描述符*/
int recvbytes;
char buf[MAXDATASIZE];		/*用于处理输入的缓冲区*/
char *str;
	
char name[MAXDATASIZE];		/*定义用户名*/
char send_str[MAXDATASIZE];	/*最多发出的字符不能超过MAXDATASIZE*/
struct sockaddr_in serv_addr;		/*Internet套接字地址结构*/
fd_set rfd_set, wfd_set, efd_set;
/*被select()监视的读、写、异常处理的文件描述符集合*/
struct timeval timeout;/*本次select的超时结束时间*/
int ret;				/*与server连接的结果*/
if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) { /*错误检测*/
perror("socket");
exit(1);
}
/* 填充 sockaddr结构  */
bzero(&serv_addr, sizeof(struct sockaddr_in));
serv_addr.sin_family=AF_INET;
serv_addr.sin_port=htons(SERVPORT);
inet_aton("127.0.0.1", &serv_addr.sin_addr);
/*serv_addr.sin_addr.s_addr=inet_addr("192.168.0.101");*/

if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)) == -1) 
{
/*错误检测*/
perror("connect");
exit(1);
}
fcntl(sockfd, F_SETFD, O_NONBLOCK);
	
printf("要聊天首先输入你的名字:");

scanf("%s",name);
name[strlen(name)] = '\0';
	
printf("%s: ",name);

fflush(stdout);
	
send(sockfd, name, strlen(name), 0);
/*发送用户名到sockfd*/

while (1)
    {
FD_ZERO(&rfd_set);/*将select()监视的读的文件描述符集合清除*/
FD_ZERO(&wfd_set);/*将select()监视的写的文件描述符集合清除*/
FD_ZERO(&efd_set);/*将select()监视的异常的文件描述符集合清除*/
FD_SET(STDIN, &rfd_set);
/*将标准输入文件描述符加到seletct()监视的读的文件描述符集合中*/
FD_SET(sockfd, &rfd_set);
/*将新建的描述符加到seletct()监视的读的文件描述符集合中*/
FD_SET(sockfd, &efd_set);
/*将新建的描述符加到seletct()监视的异常的文件描述符集合中*/
timeout.tv_sec = 10;/*select在被监视窗口等待的秒数*/
timeout.tv_usec = 0;/*select在被监视窗口等待的微秒数*/
ret = select(sockfd + 1, &rfd_set, &wfd_set, &efd_set, &timeout);
if (ret == 0) {
continue;
}
if (ret < 0) {
perror("select error: ");
exit(-1);
}
/*判断是否已将标准输入文件描述符加到seletct()监视的读的文件描述符集合中*/
if (FD_ISSET(STDIN, &rfd_set))
{
fgets(send_str, 256, stdin);
send_str[strlen(send_str)-1] = '\0';
if (strncmp("quit", send_str, 4) == 0) { /*退出程序*/
close(sockfd);
exit(0);
}
send(sockfd, send_str, strlen(send_str), 0);
}
/*判断是否已将新建的描述符加到seletct()监视的读的文件描述符集合中*/
if (FD_ISSET(sockfd, &rfd_set)) 
{
recvbytes=recv(sockfd, buf, MAXDATASIZE, 0);
if (recvbytes == 0) 
{
close(sockfd);
exit(0);
}
buf[recvbytes] = '\0';
printf("Server: %s\n", buf);
	
printf("%s: ",name);
fflush(stdout);
}
/*判断是否已将新建的描述符加到seletct()监视的异常的文件描述符集合中*/
if (FD_ISSET(sockfd, &efd_set))
{
close(sockfd);
exit(0);
}
}
}

