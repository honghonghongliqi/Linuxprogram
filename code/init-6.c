#include<signal.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/param.h>
#include<sys/stat.h>
#include<unistd.h>
#include<sys/types.h>
//生成守护进程
void init_daemon(){
	pid_t child1,child2;
	int i ;
	child1 = fork();          //创建子进程
	if(child1>0){             //父进程结束
		exit(0);
	}else if(child1<0){
		perror("创建子进程失败.\n");
		exit(1);
	}
	setsid();               //在子进程中创建新会话
	chdir("/tmp");          //改变工作目录到“/tmp”
	umask(0);               //重设文件创建掩码
	for(int i=0;i<NOFILE;++i){   //关闭文件描述符
		close(i);
	}
	return;
}
