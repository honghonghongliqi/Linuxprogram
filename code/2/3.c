#include"../my.h"
int shareData=100;
sem_t full,empty;
void *worker0(void *arg){
	while(1){
		sem_wait(&full);
		if(shareData>0){
			//usleep(1000);//毫秒
			//sleep(1);
			printf("work0 read data:%d\n",shareData--);
			sem_post(&empty);
		}else{
			sem_post(&empty);
			break;
		}
	}
	return NULL;
}
void *worker1(void *arg){
        while(1){
                sem_wait(&empty);
                if(shareData>0){
                        printf("work1 read data:%d\n",shareData--);
			sem_post(&full);
                }else{
			sem_post(&full);
                        break;
                }
        }
        return NULL;
}
int main(){
	pthread_t tid[2];
	int ret;
	void *(*pt[2])();
	pt[0]=worker0;
	pt[1]=worker1;
	ret = sem_init(&empty,0,1);
	ret = sem_init(&full,1,0);
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
