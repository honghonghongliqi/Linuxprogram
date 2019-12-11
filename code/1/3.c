#include"my.h"
#define PROMPT "Do you want terminate program?"
char *prompt=PROMPT;
void ctrl_c(signo){
	fprintf(stderr,"%s.\n",prompt);
}

int main(){
	struct sigaction act;
	act.sa_handler=ctrl_c;
	sigemptyset(&act.sa_mask);
	//传入该进程信号:SIGINT(2)执行该操作.
	if(sigaction(SIGINT,&act,NULL)<0){
		fprintf(stderr,"Install Signal Action Error:%s.\n",strerror(errno));
	}
	printf("process pid is %d.\n",getpid());
	while(1);
	return 0;
}
