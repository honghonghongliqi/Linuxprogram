#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<pthread.h>
#include<sys/time.h>
#include<sys/types.h>
#include <sys/stat.h>
#define FILENAME "file.data"
#define TN 10
//1. 创建新文件
int  createNewFile(char *);
//2. 写文件
int writeFile(char *,int,int,char*);
//3. 读文件
int readFile(char *,int);
//4. 修改文件权限
char* updateFilePower(char *);
//5. 查看当前文件的权限修改文件权限
void seekFilePower(char*);
