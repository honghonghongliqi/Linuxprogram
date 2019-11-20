#include"my.h"
int main(){
	pid_t pid;
	pid = fork();
	int r,status;
	if(pid<0){
		perror("failed fork!\n");
		return -1;
	}else if(pid==0){
		printf("child %d(pid) is running!\n",getpid());
		printf("child will exit!\n");
		//while(1);
		exit(120);
	}else{
		printf("parent waiting child %d to exit.\n",pid);
		//sleep(10);
		printf("child %d is finished.return code = %d.\n",r,WEXITSTATUS(status));
		printf("parent %d is running!\n",getpid());
		return 0;
	}
}
