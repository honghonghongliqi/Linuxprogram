#include"IOlib.h"
int main(){
	pthread_t tid[TN];
        createNewFile(FILENAME);   //创建一个文件
	struct sockaddr_in my_addr;/*本机地址信息,客户地址信息*/
	
	
	int ret;
        int serverSocket = socket(AF_INET,SOCK_STREAM,0);					
	if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) { /*错误检测*/
		perror("socket");
		exit(1);
	}
	/* 端填充 sockaddr结构  */
	bzero(&my_addr, sizeof(struct sockaddr_in));
	my_addr.sin_family=AF_INET;	/*地址族*/
	my_addr.sin_port=htons(SERVPORT);	/*端口号为SERVPORT*/
	inet_aton("127.0.0.1", &my_addr.sin_addr);

	if (bind(serverSocket, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) {/*错误检测*/
		perror("bind");
		exit(1);
	}
	if (listen(serverSocket, BACKLOG) == -1) {	 /*错误检测*/
		perror("listen");
		exit(1);
	}
	
	for(int i=0;i<TN;i++){
          struct sockaddr_in clientArr;
int   ilength=sizeof(clientArr);
int client_fd=accept(serverSocket, (struct sockaddr *)&clientArr, &ilength);
                /*错误检测*/
	if (client_fd  == -1){
		perror("Server Accept Failed!\n");
		exit(1);
	}
                ret=pthread_create(&tid[i],NULL,serviceThread,(void*)client_fd);
		printf("create thread %d\n",i);
                if(ret!=0){
                        perror("create thread failed!\n");
                        exit(1);
                }
                pthread_join(tid[i],NULL);
        }
	/*for(int i=0;i<TN;i++){
                pthread_join(tid[i],NULL);
        }*/
        close(serverSocket);
	return 0;
}
