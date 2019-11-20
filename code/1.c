#include"my.h"
int main(){
	pid_t pid;
	pid = fork();
	if(pid<0){
		perror("failed fork!\n");
		return -1;
	}else if(pid==0){
		printf("child %d(pid) is running!\n",getpid());
		printf("child will exit!\n");
		exit(120);
	}else{
		printf("parent waiting child %d to exit.\n",pid);
		sleep(10);
		printf("parent %d is running!\n",getpid());
	}
}
