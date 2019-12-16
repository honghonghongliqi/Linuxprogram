#include"../my.h"
void *foo(void *arg){
	printf("thread is running!\n");
	return (void*)0;
}
int main(){
	pthread_t tid;
	int ret;
	ret=pthread_create(&tid,NULL,foo,NULL);
	if(ret!=0){
			perror("create thread failed!\n");
			return -1;
		}
	//异步
	pthread_detach(tid);
	//同步
	//pthread_join(tid,NULL);
	printf("master done!\n");
	sleep(1);
	return 0;
}
