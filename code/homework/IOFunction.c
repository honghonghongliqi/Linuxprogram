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
	int fd = 0;
        if(str==NULL){
           printf("input fileName is NULL!\n");
           return -1;
        }
	// 创建一个新的文件
        fd = open(str,O_CREAT,0644);
	if( fd == -1 ){
		perror("create file failed!\n");
		return -1;
	}
	close(fd);
	printf("create file %s is successed!\n",str);
	return 0;
}
//2. 写文件:不处理input和字符串同时输入的情况
int writeFile(char *fileName,int num,int input,char *inputString){
        char *str=fileName;
	char data[1024];
	int count;
	int fd;
        if(str==NULL){
           printf("input fileName is NULL!\n");
           return -1;
        }
        printf("thread:%d,文件名:%s\n",num,str);
	if((fd=open(str,O_RDWR))==-1){
			printf("open file %s fail.\n",str);
			return -1;
	}
	printf("open file success.\n");
	lseek(fd , 0 , SEEK_SET); //文件开始位置
	//可重定位到文件尾
	//lseek(fd,0,SEEK_END);
	//写入文件内容str可修改
	//--------------------------
	/*while(1){
	scanf("%s",str);
	if(strcmp(str,"exit") == 0){
	break;
	}*/
	//将整型转换为字符串:itoa(input,data,10);#include <ctype.h>
	//sprintf(data,"%s",str);
	if(inputString!=NULL){
		sprintf(data,"%s",inputString);
	}else{
		sprintf(data,"%d",input);
	}
	count = strlen(data);
        data[count] = '\n';//结尾增加换行符。
        data[count+1] = '\0';//赋值新的结束符。
	count = strlen(data);
	if (write(fd, data, count) == -1) {
		printf("write data fail!\n");
		return -1;
           }
	//}
	close(fd);
	printf("结束文本写入!\n");
	return 0;
}
//3. 读文件
int readFile(char *fileName,int num){
        char *str=fileName;
        char data[1024];
        int fd;
        if(str==NULL){
           printf("input fileName is NULL!\n");
           return -1;
        }
	if ((fd = open(str, O_RDONLY)) == -1) {
		printf("open file fail\n");
		return -1;
        }
        printf("open file success\n");
	lseek(fd , 0 , SEEK_SET); //文件开始位置
	printf("thread:%d,文本内容为:\n",num);
	//一次只读3个字符
	while(read(fd, data, 3*sizeof(char))!=0){
		printf("%s\n", data);
	}
        printf("thread:%d,文本内容为:\n%s\n",num, data);
        close(fd);
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

