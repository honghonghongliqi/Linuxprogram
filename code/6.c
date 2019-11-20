#include<stdio.h>
#include<time.h>
void init_daemon();
int main(){
	FILE* fp;
	time_t t;
	init_daemon();
	while(1){
		if((fp=fopen("6.log","a"))>=0){
			t = time(0);
			fprintf(fp,"守护进程还在运行,时间是:%s.\n",asctime(localtime(&t)));
			fclose(fp);
		}
	}
}
