#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include  <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

#define MAXDATASIZE 256

#define SERVPORT 4444	/*服务器监听端口号*/
#define BACKLOG 1     	/*最大同时连接请求数*/
#define STDIN 0        	/*标准输入文件描述符*/
	
int main(void)
{
	FILE *fp;		/*定义文件类型指针fp*/
	int sockfd,client_fd;	/*监听socket.sock_fd,数据传输socket.new_fd*/
	int sin_size;
	struct sockaddr_in my_addr, remote_addr;/*本机地址信息,客户地址信息*/
	char buf[256];		/*用于聊天的缓冲区*/

	char buff[256];			/*用于输入用户名的缓冲区*/
	char send_str[256];		/*最多发出的字符不能超过256*/
	int recvbytes;
	fd_set rfd_set, wfd_set, efd_set;/*被select()监视的读、写、异常处理的文件描述符集合*/
	struct timeval timeout;	/*本次select的超时结束时间*/
	int ret;					/*与client连接的结果*/

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) { /*错误检测*/
		perror("socket");
		exit(1);
	}
	/* 端填充 sockaddr结构  */
	bzero(&my_addr, sizeof(struct sockaddr_in));
	my_addr.sin_family=AF_INET;	/*地址族*/
	my_addr.sin_port=htons(SERVPORT);	/*端口号为4444*/
	inet_aton("127.0.0.1", &my_addr.sin_addr);

	if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) {        /*错误检测*/
		perror("bind");
		exit(1);
	}
	if (listen(sockfd, BACKLOG) == -1) {	 /*错误检测*/
		perror("listen");
		exit(1);
	}

	sin_size = sizeof(struct sockaddr_in);
	if ((client_fd = accept(sockfd, (struct sockaddr *)&remote_addr, &sin_size)) == -1) {
	 /*错误检测*/
		perror("accept");
		exit(1);
	}

	fcntl(client_fd, F_SETFD, O_NONBLOCK);/* 服务器设为非阻塞*/
	recvbytes=recv(client_fd, buff, MAXDATASIZE, 0);
	/*接收从客户端传来的用户名*/	
	buff[recvbytes] = '\0';
	fflush(stdout);
	/*强制立即内容*/
	if((fp=fopen("name.txt","a+"))==NULL)
	{
		printf("can not open file,exit...\n");
		return -1;
	}
	fprintf(fp,"%s\n",buff);
	/*将用户名写入name.txt中*/	
	while (1) {
		FD_ZERO(&rfd_set);/*将select()监视的读的文件描述符集合清除*/
		FD_ZERO(&wfd_set);/*将select()监视的写的文件描述符集合清除*/
		FD_ZERO(&efd_set);/*将select()监视的异常的文件描述符集合清除*/
		FD_SET(STDIN, &rfd_set);
	/*将标准输入文件描述符加到seletct()监视的读的文件描述符集合中*/
		FD_SET(client_fd, &rfd_set);
	/*将新建的描述符加到seletct()监视的读的文件描述符集合中*/
		FD_SET(client_fd, &wfd_set);
	/*将新建的描述符加到seletct()监视的写的文件描述符集合中*/
		FD_SET(client_fd, &efd_set);
	/*将新建的描述符加到seletct()监视的异常的文件描述符集合中*/
		timeout.tv_sec = 10;/*select在被监视窗口等待的秒数*/
		timeout.tv_usec = 0;/*select在被监视窗口等待的微秒数*/
		ret = select(client_fd + 1, &rfd_set, &wfd_set, &efd_set, &timeout);
		if (ret == 0) {
			continue;
		}
		if (ret < 0) {
			perror("select error: ");
			exit(-1);
		}
	/*判断是否已将标准输入文件描述符加到seletct()监视的读的文件描述符集合中*/
		if(FD_ISSET(STDIN, &rfd_set))
		{
			fgets(send_str, 256, stdin);/*取从输入输入的内容*/
			send_str[strlen(send_str)-1] = '\0';
		if (strncmp("quit", send_str, 4) == 0) {	/*退出程序*/
			close(client_fd);
			close(sockfd);	/*关闭套接字*/
			exit(0);
		}
		send(client_fd, send_str, strlen(send_str), 0);
	}
	/*判断是否已将新建的描述符加到seletct()监视的读的文件描述符集合中*/
	if (FD_ISSET(client_fd, &rfd_set))
	{
		recvbytes=recv(client_fd, buf, MAXDATASIZE, 0);/*接收从客户端传来的聊天内容*/
		if (recvbytes == 0) {
			close(client_fd);
			close(sockfd);	/*关闭套接字*/
			exit(0);
		}
		buf[recvbytes] = '\0';
		printf("%s:%s\n",buff,buf);
		printf("Server: ");
		fflush(stdout);
	}
	/*判断是否已将新建的描述符加到seletct()监视的异常的文件描述符集合中*/
	if (FD_ISSET(client_fd, &efd_set)) {
		close(client_fd);	/*关闭套接字*/
		exit(0);
	}
	}
}

