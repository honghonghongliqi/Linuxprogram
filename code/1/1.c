#include"my.h"
void * threadfunction(){
	pthread_exit(NULL);
}
int main(){
	pthread_t tid;
	int ret;
	struct timeval tv1,tv2;
	struct timezone tz;
	gettimeofday(&tv1,&tz);
	for(int i=0;i<1000;i++){
		ret=pthread_create(&tid,NULL,threadfunction,NULL);
		if(ret!=0){
			perror("create thread failed!\n");
			return -1;
		}
	}
	gettimeofday(&tv2,&tz);
	printf("run time is %ld ms.\n",tv2.tv_usec-tv1.tv_usec);
	return 0;
}
