#include"staticlib.h"
void showarray(int * a,int n)
{
   int i;
   for(i=0;i<n;i++)
      printf("%4d  :  %4d\n",i,a[i]);
}

void initarray(int * a,int n)
{
   int num;
   srand((unsigned)time(NULL));
   for(int x=0;x<n;x++){
        num=rand()%1000;
        a[x]=num;
    }
}
