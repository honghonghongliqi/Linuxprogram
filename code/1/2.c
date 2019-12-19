#include"../my.h"
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_rwlock_t rwlock;
int a[LENGTH];
int b[LENGTH];
int max=0;
int maxA=0;
int maxB=0;
int result=0;
int judge=0;
int getMax(int *numbers){
	//使用的numbers不能是和已有的全局变量数组名相同
	result=numbers[0];
	for(int i=0;i<LENGTH;i++){
		if(result<numbers[i]){
			result=numbers[i];
		}
	}
	return result;
}
void *fun(void *pram){
	srand((unsigned int)time(NULL));//随机数rand
	pthread_rwlock_rdlock(&rwlock);
	pthread_mutex_lock(&mutex);
	judge++;
	for(int i=0;i<LENGTH;i++){
		int n = rand()%99+1; //产生1~100的随机数
		if(judge==1){
			a[i] = n;
		}else{
			b[i]=n;
		}
	}
	if(judge==1){
		maxA=getMax(a);
	}else{
		maxB=getMax(b);
	}
	pthread_mutex_unlock(&mutex);
	pthread_rwlock_unlock(&rwlock);
	return NULL;
}
int main(){
	pthread_t tid[NUM];
	int ret;
	ret=pthread_rwlock_init(&rwlock,NULL);
	if(ret!=0){
                perror("rwlock init failed!\n");
                exit(1);
        }
        pthread_rwlock_wrlock(&rwlock);
        for(int i=0;i<NUM;i++){
                ret=pthread_create(&tid[i],NULL,fun,NULL);
                if(ret!=0){
                        perror("rwlock init failed!\n");
                        exit(2);
                }
        }
	pthread_rwlock_unlock(&rwlock);
	for(int i=0;i<NUM;i++){
		pthread_join(tid[i],NULL);
	}
	pthread_rwlock_destroy(&rwlock);
	printf("maxA=%d.\n",maxA);
	printf("maxB=%d.\n",maxB);
	max=maxA?maxB:maxA>maxB;
	printf("max=%d.\n",max);
        return 0;
}
