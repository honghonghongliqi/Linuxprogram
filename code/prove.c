#include<stdio.h>
#include<stdlib.h>
int main (){
  int *p = malloc(sizeof(int));
  *p = 0;
  printf("start main()\n");
  int pid = fork();
  
  if (pid == 0) {
    printf("i am child, my pid is %d\n", getpid());
    printf("%d\n", p); 
    *p += 5;
  } else {
    printf("i am parent, my pid is %d\n", getpid());
    printf("%d\n", p); 
    *p += 2;
  }
  printf("%d\n", *p); 
  return 0;
}
