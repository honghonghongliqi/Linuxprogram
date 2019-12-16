#include"../my.h"
#include <pthread.h>
pthread_rwlock_t rwlock;
int global=0;
void *function(void *param){
	pthread_rwlock_rdlock(&rwlock);
	for(int i=0;i<LOOP;i++){
		global++;
	}
	pthread_rwlock_unlock(&rwlock);
	return NULL;
}
int main(){
	pthread_t tid[NUM];
	char err[1024];
	int ret;
	ret=pthread_rwlock_init(&rwlock,NULL);
	if(ret!=0){
		fprintf(stderr,"init rw lock failed.%d\n",strerror_r(ret,err,sizeof(err)));
		return -1;
	}
	pthread_rwlock_wrlock(&rwlock);
	for(int i=0;i<NUM;i++){
		ret=pthread_create(&tid[i],NULL,function,NULL);
		if(ret!=0){
			perror("create thread failed!\n");
			return -1;
		}
	}
	pthread_rwlock_unlock(&rwlock);
	//等待4个子线程结束,且4个子线程中的顺序不定,将pthread_join写入上一个循环中就会有一致的顺序.
	for(int i=0;i<NUM;i++){
		pthread_join(tid[i],NULL);
	}
	pthread_rwlock_destroy(&rwlock);
	printf("thread count is %d,each thread loop time is %d.\n",NUM,LOOP);
	printf("expect result :%d\n",LOOP*NUM);
	printf("actual result :%d\n",global);
}
