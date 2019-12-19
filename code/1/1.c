#include"../my.h"
pthread_rwlock_t rwlock;
int global=0;
void *fun(void *pram){
        pthread_rwlock_rdlock(&rwlock);
        for(int i=0;i<LENGTH;i++){
                global++;
        }
        pthread_rwlock_unlock(&rwlock);
        return NULL;
}
int main(){
	pthread_t tid[LOOP];
	int ret;
	ret=pthread_rwlock_init(&rwlock,NULL);
	if(ret!=0){
		perror("rwlock init failed!\n");
		exit(1);
	}
	pthread_rwlock_wrlock(&rwlock);
	for(int i=0;i<LOOP;i++){
		ret=pthread_create(&tid[i],NULL,fun,NULL);
		if(ret!=0){
			perror("rwlock init failed!\n");
			exit(2);
		}
	}
	pthread_rwlock_unlock(&rwlock);
        for(int i=0;i<LOOP;i++){
                pthread_join(tid[i],NULL);
        }
	pthread_rwlock_destroy(&rwlock);
	printf("expected global:%d.\n",LOOP*LENGTH);
	printf("actual global:%d.\n",global);
	return 0;
}
