#include"../my.h"
#include<pthread.h>
int arg = 0;
void foo(void *v){
	int n=(int)v;
	arg++;
	printf("%d:global arg=%d.\n",n,arg);
}
int main(){
	pthread_t tid[NUM];
	int ret[NUM];
	for(int i=0;i<NUM;i++){
		ret[i]=pthread_create(&tid[i],NULL,(void *(*)())foo,(void *)&i);
		if(ret[i]!=0){
			perror("create thread error!\n");
			return -1;
		}
		pthread_join(tid[i],NULL);
	}
	printf("Master %d",getpid());
	return 0;
}
