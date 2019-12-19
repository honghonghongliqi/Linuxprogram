#include"../my.h"
int shareData=100;
pthread_mutex_t mutex;
pthread_cond_t q=PTHREAD_COND_INITIALIZER;
void *worker0(void *arg){
	pthread_mutex_lock(&mutex);
	while(shareData>0){
		if(shareData%2==0){
			usleep(1000);
			printf("work0 read data:%d\n",shareData);
			shareData--;
			//向另一个线程中有q等待的发出执行信号
			pthread_cond_signal(&q);
		}else{
			//进入等待状态
			pthread_cond_wait(&q,&mutex);
		}
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}
void *worker1(void *arg){
        pthread_mutex_lock(&mutex);
        while(shareData>0){
                if(shareData%2!=0){
                        usleep(1000);
                        printf("work1 read data:%d\n",shareData);
                        shareData--;
                        pthread_cond_signal(&q);
                }else{
                        pthread_cond_wait(&q,&mutex);
                }
                pthread_mutex_unlock(&mutex);
        }
        return NULL;
}
int main(){
	pthread_t tid[2];
	int ret;
	void *(*pt[2])();
	pt[0]=worker0;
	pt[1]=worker1;
	pthread_mutex_init(&mutex,NULL);
	for(int i=0;i<2;i++){
		ret=pthread_create(&tid[i],NULL,pt[i],NULL);
		if(ret!=0){
			perror("create thread failed!\n");
			exit(1);
		}
	}
	for(int i=0;i<2;i++){
		pthread_join(tid[i],NULL);
	}
	return 0;
}
