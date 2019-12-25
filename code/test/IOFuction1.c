#include"IOlib.h"
/*void sleep( clock_t wait )
{
   clock_t goal;
   goal = wait + clock();
   while( goal > clock());
}*/
//1. 创建新文件
int createNewFile(char *fileName){
	char *str=fileName;
	FILE *fp;
        if(str==NULL){
           printf("input fileName is NULL!\n");
           return -1;
        }
	//打开或者创建文件读写文件
        fp=fopen(str,"w");
        if(fp==NULL){
		printf("create file fail!\n");
	       	return -1;
	}
	if(fp!=NULL){
		fclose(fp);
        }
	printf("create file %s is successed!\n",str);
	return 0;
}
//2. 写文件:不处理input和字符串同时输入的情况
int writeFile(char *fileName,int num,int input,char *inputString){
	FILE *fp;
        char *str=fileName;
	char data[1024];
	int count;
        if(str==NULL){
           printf("input fileName is NULL!\n");
           return -1;
        }
        printf("thread:%d,文件名:%s\n",num,str);
	//在文件末尾追加内容：
	fp=fopen(str,"a+");
	//打开可读写文件,长度清零
	//fp=fopen(str,"w+");
        if(fp==NULL){
                printf("open file %s fail.\n",str);
                return -1;
        }
	printf("open file success.\n");
	if(inputString!=NULL){
		sprintf(data,"%s",inputString);
	}else{
		sprintf(data,"%d",input);
	}
	strcat(data, "\n");
	count = strlen(data);
	if (fwrite(data,count,1,fp) != 1) {
		printf("write data fail!\n");
		return -1;
           }
	//fflush(fp);
	if(fp!=NULL){
		fclose(fp);
        }
	printf("结束文本写入!\n");
	return 0;
}
//3. 获取系统时间
void getNowDate(){
	char *str;
	str=(char*)calloc(250,sizeof(char));
	printf("before function\n");
	struct timespec time;
     clock_gettime(CLOCK_REALTIME, &time);  //获取相对于1970到现在的秒数
     struct tm nowTime;
     localtime_r(&time.tv_sec, &nowTime);
     
     printf("%d\n",nowTime.tm_sec);
     sprintf(str,"%04d年%02d月%02d日%02d时%02d分%02d秒",nowTime.tm_year+1900,nowTime.tm_mon+1,nowTime.tm_mday,nowTime.tm_hour,nowTime.tm_min,nowTime.tm_sec);
     printf("function:date:%s\n",str);
     strcpy(nowDate,str);
     sleep(1);//000000
     free(str);
}
void *serviceThread(void *param){
	pthread_detach(pthread_self());
	int new_server_socket =(int)param;
	fd_set rfd_set, wfd_set, efd_set;/*被select()监视的读、写、异常处理的文件描述符集合*/
	struct timeval timeout;	/*本次select的超时结束时间*/
        char buf[256];		/*用于聊天的缓冲区*/
	char send_str[256];    /*最多发出的字符不能超过256*/
	int recvbytes;
        int ret;
	while(1){
	FD_ZERO(&rfd_set);/*将select()监视的读的文件描述符集合清除*/
	FD_ZERO(&wfd_set);/*将select()监视的写的文件描述符集合清除*/
	FD_ZERO(&efd_set);/*将select()监视的异常的文件描述符集合清除*/
	/*将标准输入文件描述符加到seletct()监视的读的文件描述符集合中*/
	FD_SET(new_server_socket, &rfd_set);
	/*将新建的描述符加到seletct()监视的读的文件描述符集合中*/
	FD_SET(new_server_socket, &wfd_set);
	/*将新建的描述符加到seletct()监视的写的文件描述符集合中*/
	FD_SET(new_server_socket, &efd_set);
	/*将新建的描述符加到seletct()监视的异常的文件描述符集合中*/
	timeout.tv_sec = 10;/*select在被监视窗口等待的秒数*/
	timeout.tv_usec = 0;/*select在被监视窗口等待的微秒数*/
	ret = select(new_server_socket + 1, &rfd_set, &wfd_set, &efd_set, &timeout);
	if (ret < 0) {
			perror("select error: ");
			break;
	}
        /*判断是否已将新建的描述符加到seletct()监视的读的文件描述符集合中*/
	if (FD_ISSET(new_server_socket, &rfd_set)){
		printf("in FD_ISSET\n");
		recvbytes=recv(new_server_socket , buf, MAXDATASIZE, 0);/*接收从客户端传来的聊天内容*/
                if(recvbytes<0){
                      perror("Server Recieve Data Failed!\n");
                      break;
                }else if (recvbytes == 0) {
                         printf("auto close\n");
                         break;
                }
		buf[recvbytes] = '\0';
		writeFile(FILENAME,new_server_socket ,0,buf);
                //发送到客户端
	         strcpy(send_str,"999");
		 send_str[strlen(send_str)] = '\0';
		 printf("send_str:%s\n",send_str);
		 send(new_server_socket , send_str, strlen(send_str), 0);
                 break;
	}
	/*判断是否已将新建的描述符加到seletct()监视的异常的文件描述符集合中*/
	if (FD_ISSET(new_server_socket, &efd_set)) {
		printf("in FD_ISSET error\n");
		break;
	}
	}
	close(new_server_socket);
	pthread_exit(NULL);
}
void *clientThread(void *param){
        getNowDate();
	int sockfd;			/*套接字描述符*/
	int recvbytes;
        char getData[100];
	char buf[MAXDATASIZE];		/*用于处理输入的缓冲区*/
	char ip[20];
	char send_str[MAXDATASIZE];	/*最多发出的字符不能超过MAXDATASIZE*/
	struct sockaddr_in serv_addr, local_addr;		/*Internet套接字地址结构*/
	fd_set rfd_set, wfd_set, efd_set;/*被select()监视的读、写、异常处理的文件描述符集合*/
	struct timeval timeout;/*本次select的超时结束时间*/
	int ret;				/*与server连接的结果*/
	int time = 0;//发送信息次数
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) { /*错误检测*/
		perror("socket");
		return NULL;
	}
	/* 填充 sockaddr结构  */
	bzero(&serv_addr, sizeof(struct sockaddr_in));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERVPORT);
	inet_aton("127.0.0.1", &serv_addr.sin_addr);
	/*serv_addr.sin_addr.s_addr=inet_addr("192.168.0.101");*/
	/*错误检测*/
	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)) == -1) {
		perror("connect");
		return NULL;
	}
	int len = sizeof(local_addr);
	memset(&local_addr, 0, sizeof(local_addr));
	ret = getsockname(sockfd, (struct sockaddr*)&local_addr, &len);
        printf("before getIP\n");
	if (ret == 0)
	{
		strcpy(ip, inet_ntop(AF_INET, &local_addr.sin_addr, buf, sizeof(buf)));
		printf("localhost ip=%s\n", ip);
	}
	else
	{
		printf("getsockname failed, error=%d\n", errno);
	}
	while (1) {
		FD_ZERO(&rfd_set);/*将select()监视的读的文件描述符集合清除*/
		FD_ZERO(&wfd_set);/*将select()监视的写的文件描述符集合清除*/
		FD_ZERO(&efd_set);/*将select()监视的异常的文件描述符集合清除*/
		FD_SET(sockfd, &wfd_set);/*将新建的描述符加到seletct()监视的写的文件描述符集合中*/
		FD_SET(sockfd, &rfd_set);/*将新建的描述符加到seletct()监视的读的文件描述符集合中*/
		FD_SET(sockfd, &efd_set);/*将新建的描述符加到seletct()监视的异常的文件描述符集合中*/
		timeout.tv_sec = 10;/*select在被监视窗口等待的秒数*/
		timeout.tv_usec = 0;/*select在被监视窗口等待的微秒数*/
		ret = select(sockfd + 1, &rfd_set, &wfd_set, &efd_set, &timeout);
                if (ret == 0) {
			continue;
		}
		if (ret < 0) {
			perror("select error: ");
                        break;
		}
		if (time ==0) {
			strcpy(send_str, "客户端系统时间:");
			//printf("len:date=%ld\n", strlen(getNowDate()));
			strcat(send_str, nowDate);
			printf("after getNowDate\n");
			strcat(send_str, ".客户端IP:");
                        printf("send0:%s\n", send_str);
			strcat(send_str, ip);
			send_str[strlen(send_str)] = '\0';
                        printf("send_str:len%ld\n",strlen(send_str));
			printf("send:%s\n", send_str);
			send(sockfd, send_str, strlen(send_str), 0);
		}
		time++;

		/*判断是否已将新建的描述符加到seletct()监视的读的文件描述符集合中,&& send_str != NULL*/
		if (FD_ISSET(sockfd, &rfd_set)) {
			recvbytes = recv(sockfd, buf,MAXDATASIZE, 0);
			if (recvbytes == 0) {
                                printf("time:%d\n",time);
                                printf("auto close\n");
				close(sockfd);
				break;
			}
			printf("before getData\n");
                        strncpy(getData,buf,3);
			printf("after getData\n");
			printf("%s\n", getData);
			fflush(stdout);
			/*退出程序*/
			if (strncmp("999", buf, 3) == 0) {
                                printf("time:%d\n",time);
                                printf("get 999 to exit\n");
				close(sockfd);
				break;
			}
		}
		/*判断是否已将新建的描述符加到seletct()监视的异常的文件描述符集合中*/
		if (FD_ISSET(sockfd, &efd_set))
		{
			close(sockfd);
			break;
		}
	}
	return NULL;
}
