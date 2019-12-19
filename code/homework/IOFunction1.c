#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
//1. 创建新文件
int createNewFile(char *fileName){
	char *str=fileName;
	FILE *fp;
        if(str==NULL){
           printf("input fileName is NULL!\n");
           return -1;
        }
	//打开或者创建文件读写文件
        fp=fopen(str,"w");
        if(fp==NULL){
		printf("create file fail!\n");
	       	return -1;
	}
	if(fp!=NULL){
		fclose(fp);
        }
	printf("create file %s is successed!\n",str);
	return 0;
}
//2. 写文件:不处理input和字符串同时输入的情况
int writeFile(char *fileName,int num,int input,char *inputString){
	FILE *fp;
        char *str=fileName;
	char data[1024];
	int count;
        if(str==NULL){
           printf("input fileName is NULL!\n");
           return -1;
        }
        printf("thread:%d,文件名:%s\n",num,str);
	//在文件末尾追加内容：
	fp=fopen(str,"a+");
	//打开可读写文件,长度清零
	//fp=fopen(str,"w+");
        if(fp==NULL){
                printf("open file %s fail.\n",str);
                return -1;
        }
	printf("open file success.\n");
	if(inputString!=NULL){
		sprintf(data,"%s",inputString);
	}else{
		sprintf(data,"%d",input);
	}
	strcat(data, "\n");
	count = strlen(data);
	if (fwrite(data,count,1,fp) != 1) {
		printf("write data fail!\n");
		return -1;
           }
	//fflush(fp);
	if(fp!=NULL){
		fclose(fp);
        }
	printf("结束文本写入!\n");
	return 0;
}
//3. 读文件
int readFile(char *fileName,int num){
        char *str=fileName;
        char data[1024];
	FILE *fp;
        if(str==NULL){
           printf("input fileName is NULL!\n");
           return -1;
        }
	fp=fopen(str,"r");
        if(fp==NULL){
                printf("open file fail!\n");
                return -1;
        }
        printf("open file success\n");
	printf("thread:%d,文本内容为:\n",num);
	//读一行
	while(!feof(fp)){
		fgets(data,30,fp);
		printf("%s\n", data);
         }
	//fflush(fp);
	if(fp!=NULL){
		fclose(fp);
        }
	return 0;
}
//4. 修改文件权限
void updateFilePower(char *fileName){
        char *str=fileName;
        //所有的用户都可以进行查看，修改，执行.
	if(chmod( str, 0777)==-1){
		printf("Permission modification failed!\n");
	}
	printf("权限修改成功!\n");
}
//5. 查看当前文件的权限修改文件权限
void seekFilePower(char*fileName){
        /*printf("stdlen:%ld\n",strlen(fileName));
       
        printf("fileName:%s\n",fileName);*/
        //ascll:1->标题开始
        int c=(int)(fileName[0]);
	if(strlen(fileName)==1&&c==1){
		printf("没有进行权限修改,无文件查看.\n");
	}else{
		printf("查看那个修改权限之后的文件权限\n");
                char sysInstructions[20]="ls -l ";
                //printf("sysInstructions:%s\n",sysInstructions);
                strcat(sysInstructions,fileName);
                //printf("sysInstructions1:%s\n",sysInstructions);
                system(sysInstructions);
	}
}
