#include"../my.h"
//标准流管道
#define BUFSIZE 1024
int main(){
//定义文件指针
FILE *fpr = NULL;
FILE *fpw = NULL;
//保存要执行的命令串
const char *cmdr = "ps x";
const char *cmdw = "grep pts";
//定义缓存区并初始化
char buf[BUFSIZE] = {0};
memset(buf, 0x00, BUFSIZE);
//创建标准流管道，将执行命令的结果装入管道
//参数1：执行的命令字符串
//参数2：打开的形式（只识别第一个字符）
//返回文件指针
if (NULL == (fpr = popen(cmdr, "r"))){perror("popen");exit(EXIT_FAILURE);}
if (NULL == (fpw = popen(cmdw, "w"))){perror("popen");exit(EXIT_FAILURE);}
int readlen = 0;
//从管道中读取数据存入buf中
while ((readlen = fread(buf, sizeof(char), BUFSIZE, fpr)) > 0){
buf[readlen] = '\0';
//将buf中的数据写入fpw对应的管道中，作为cmdw命令的输入数据
fwrite(buf, sizeof(char), readlen, fpw);
}
//关闭文件指针
pclose(fpr);
pclose(fpw);
return 0;
