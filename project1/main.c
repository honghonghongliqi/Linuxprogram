#include"uhead.h"

int main(){
    struct result ret;
    int a[100],b[100],c[100];
    double t1,t2;
    char str1[]="./randow.dat";//用来存放随机之后的数组的文件名
    char str2[]="./syssort.dat";//用来存放系统排序之后的数组的文件名
    char str3[]="./usort.dat";//用来存放冒泡排序之后的数组的文件名
    uround(a,100);
    printf("------生成随机数开始-----\n");
    ret=uoprater(a,100);
    printf("------生成随机数结束-----\n");
    show(a,100);
    printf("\n平均数为:%f,所有随机数的和为:%ld\n",ret.average,ret.sum);
    uwrite("random.dat",a,100);
    uread("random.dat",b,100);
    printf("------开始系统内置排序------\n");
    t1=calculate_time();
    syssort(b,100);
    t1=calculate_time()-t1;
    printf("------系统内置排序结束------用时:%f secs\n",t1);
    uwrite("syssort.dat",b,100);
    uread("random.dat",c,100);
    printf("------开始自写冒泡排序------\n");
    t2=calculate_time();
    usort(c,100);
    t2=calculate_time()-t2;
    printf("------自写冒泡排序结束------用时:%f secs\n",t2);
    uwrite("usort.dat",c,100);
    printf("\n------开始查看文件中数组------\n");
    system("cat random.dat");
    system("cat syssort.dat");
    system("cat usort.dat");
    printf("\n------查看文件动作结束------\n");
    printf("\n------");
    return 0;
}
