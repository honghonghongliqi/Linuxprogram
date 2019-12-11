#include"my.h"
void signalCatch(int signalValue){
	switch(signalValue){
		case 1:
			printf("Catch SIGUP\n");
			signal(1,SIG_DFL);
			break;
		case 2:
                        printf("Catch SIGINT\n");
                        break;
		case 3:
                        printf("Catch QUIT\n");
                        break;
	}
}
int main(){
	printf("pid=%d.\n",getpid());
	signal(1,signalCatch);
	signal(2,signalCatch);
	signal(3,signalCatch);
	while(1);
	return 0;
}
