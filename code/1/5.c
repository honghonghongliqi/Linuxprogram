#include"my.h"
void usage(){
	fprintf(stderr,"USAGE:\n");
	fprintf(stderr,"-----------------------\n");
	fprintf(stderr,"signal_sender pid signo times\n");
}
int main(int argc,char *argv[]){
	pid_t pid=-1;
	int signo = -1;
	int times = -1;
	if(argc<4){
		usage();
		return -1;
	}
	//传入的第二个参数:进程4的pid号
	pid = atol(argv[1]);
	//传入的信号
	signo = atoi(argv[2]);
	//传入信号的次数
	times = atoi(argv[1]);
	if(pid<=0||times<0||signo<1||signo>=64||signo==32||signo==33){
		usage();
		return -2;
	}
	printf("pid=%d,signo=%d,times=%d\n",pid,signo,times);
	for(int i=0;i<times;i++){
		if(kill(pid,signo)==-1){
	fprintf(stderr,"send signo(%d) to pid(%d) failed,reason:%s.\n",signo,pid,strerror(errno));
			return -3;
		}
	}
	printf("done.\n");
	return 0;
}
