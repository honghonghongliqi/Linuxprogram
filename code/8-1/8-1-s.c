#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#define SERVPORT 3333 /*服务器监听端口号 */
#define BACKLOG 10 /* 最大同时连接请求数 */

int main()
{
	int sockfd,client_fd; /*sock_fd：监听socket；client_fd：数据传输socket */
	struct sockaddr_in my_addr; /* 本机地址信息 */
	struct sockaddr_in remote_addr; /* 客户端地址信息 */
	int sin_size;
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket 创建失败！"); exit(1);
	}
	my_addr.sin_family=AF_INET;
	my_addr.sin_port=htons(SERVPORT);/* htons()把16位值从主机字节序转换成网络字节序*/
	my_addr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(my_addr.sin_zero),8); /*保持与struct sockaddr同样大小 */

	if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
	{
		perror("bind 出错！");
		exit(1);
	}
	if (listen(sockfd, BACKLOG) == -1) {
		perror("listen 出错！");
		exit(1);
	}
	while(1) {
		sin_size = sizeof(struct sockaddr_in);
		if ((client_fd = accept(sockfd, (struct sockaddr *)&remote_addr, &sin_size)) == -1) {
			perror("accept error");
			continue;
		}
		printf("收到一个连接来自： %s\n", inet_ntoa(remote_addr.sin_addr));
		if (!fork()) { /* 子进程代码段 */
			if (send(client_fd, "连接上了 \n", 26, 0) == -1)
				perror("send 出错！");
			close(client_fd);
			exit(0);
		}
	close(client_fd);
	}
}

