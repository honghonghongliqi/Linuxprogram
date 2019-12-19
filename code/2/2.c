#include"../my.h"
int shareData=100;
pthread_mutex_t mutex;
void *worker0(void *arg){
	while(1){
		pthread_mutex_lock(&mutex);
		if(shareData>0){
			usleep(1000);//毫秒
			//sleep(1);
			printf("work0 read data:%d\n",shareData--);
			pthread_mutex_unlock(&mutex);
		}else{
			pthread_mutex_unlock(&mutex);
			break;
		}
		//pthread_yield();
	}
	return NULL;
}
void *worker1(void *arg){
        while(1){
                pthread_mutex_lock(&mutex);
                if(shareData>0){
			//sleep(1);
                        usleep(1000);//毫秒
                        printf("work1 read data:%d\n",shareData--);
			pthread_mutex_unlock(&mutex);
                }else{
			pthread_mutex_unlock(&mutex);
                        break;
                }
                //pthread_yield();
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
