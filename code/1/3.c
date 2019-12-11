#include"my.h"
int i=0;
void fun(){
	int buffer[256];
	printf("i=%d.\n",i);
	i++;
	fun();
}
int main(){
	fun();
	sleep(10);
}
