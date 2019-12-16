#include"../my.h"
int r=0;
void *fun(void *arg){
	int k=(int)arg;
	int *sum;
	sum=(int*)malloc(sizeof(int));
	*sum=count(k);
	printf("worker:%d,pthread_self return %p,sum=%d.global:%d\n",k,(void*)pthread_self(),*sum,r);
	r++;
	pthread_exit((void*)sum);
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
	int **getResult;
	for(int i=0;i<NUM;i++){
		ret[i]=pthread_create(&tid[i],NULL,(void *(*)())fun,(void*)i);
		if(ret[i]!=0){
			perror("create thread error!\n");
			return -1;
		}
		pthread_join(tid[i],(void**)&getResult);
		printf("the child %d return: %d\n",i,*getResult);
	}
	printf("Master %d",getpid());
	return 0;
}
