#include"IOlib.h"
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
static pthread_rwlock_t rwlock;
static int share=0;
void *reader(void *param){
	int i=(int)param;
	int time=0;
	while(time++<100){
		pthread_rwlock_rdlock(&rwlock);
		pthread_mutex_lock(&mutex);
		readFile(FILENAME,i);
		pthread_mutex_unlock(&mutex);
		pthread_rwlock_unlock(&rwlock);
		sleep(1);
		}
	return NULL;
}
void *writer(void *param){
        int i=(int)param;
	int time=0;
        while(time++<100){
                pthread_rwlock_rdlock(&rwlock);
		pthread_mutex_lock(&mutex);
		share++;
                writeFile(FILENAME,i,share,NULL);
		pthread_mutex_unlock(&mutex);
                pthread_rwlock_unlock(&rwlock);
		sleep(1);
        }
        return NULL;
}
int main(){
	pthread_t tid[TN];
	pthread_rwlockattr_t rwlock_attr;
	pthread_rwlockattr_init(&rwlock_attr);
#ifdef WRITER_FIEST
	ptherad_rwlockattr_sekind_np(&rwlock_attr,PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP);
#endif
	pthread_rwlock_init(&rwlock,&rwlock_attr);
	int ret=0;
	createNewFile(FILENAME);
	pthread_rwlock_rdlock(&rwlock);
	for(int i=0;i<TN;i++){
		if(i%2==0){
			ret=pthread_create(&tid[i],NULL,reader,(void*)i);
		}else{
			ret=pthread_create(&tid[i],NULL,writer,(void*)i);
		}
		if(ret!=0){
			perror("create thread failed!\n");
			return 1;
		}
	}
	pthread_rwlock_unlock(&rwlock);
	int i=TN;
	while(i-->0){
		pthread_join(tid[i],NULL);
	}
	pthread_rwlockattr_destroy(&rwlock_attr);
	pthread_rwlock_destroy(&rwlock);
	return 0;
}
