#include"staticlib.h"
int max(int * a,int n)
{
   int m,i;
   m=a[0];
   for(i=0;i<n;i++)
      if(a[i]>m)
         m=a[i];
   return m;
}
int sum(int * a,int n)
{
   int s,i;
   s=0;
   for(i=0;i<n;i++)
      s+=a[i];
   return s;
}
