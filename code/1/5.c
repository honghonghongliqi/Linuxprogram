#include"my.h"
void *fun(void *arg){
	int k=(int)arg;
	int sum=count(k);
	printf("worker:%d,pthread_self return %p,sum=%d.\n",k,(void*)pthread_self(),sum);
	pthread_exit(NULL);
	return NULL;
}
int count(int i){
	int sum = 0;
	for(int j=0;j<i*100;j++){
		sum+=j;
	}
	return sum;
}
int main(){
	pthread_t tid[NUM];
	int ret[NUM];
	for(int i=0;i<NUM;i++){
		ret[i]=pthread_create(&tid[i],NULL,fun,(void*)i);
		if(ret[i]!=0){
			perror("create thread error!\n");
			return -1;
		}
		pthread_join(tid[i],NULL);
	}
	printf("Master %d",getpid());
	return 0;
}
