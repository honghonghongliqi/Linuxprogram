#include"../my.h"
int shared=1;//表示共享资源
void* thread_function(void *arg){
	int function_count=0;
	while(function_count++<5){
		if(shared==2){
			printf("thread function is running.\n");
			shared=1;
		}else{
			printf("thread function is sleeping!\n");
			sleep(1);
		}
	}
	pthread_exit(NULL);
}
int main(){
	int main_count=0;
	pthread_t tid;
	if(pthread_create(&tid,NULL,thread_function,NULL)!=0){
		perror("create thread failed!\n");
		return -1;
	}
	while(main_count++<5){
		if(shared==1){
			printf("main thread is running!\n");
			shared=2;
		}else{
			printf("main thread is sleeping!\n");
			sleep(1);
		}
	}
	pthread_join(tid,NULL);//等待子线程结束
	return 0;
}
