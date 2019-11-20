#include"my.h"
FILE* openFile(){
	FILE *fp;
	//打开或者创建文件读写文件,文件存在则清零.
        fp=fopen("file.dat","w+");
	return fp;
}
int writeFile(FILE* fp){
	char buf[]={"0 1 2 3 4 5 6 7 8 9\n"};
	/*fp=fopen("file.dat","a+");*/
        if(fp==NULL){
                perror("failed to open file!\n");
                return -1;
        }
	printf("open file success.\n");
	int count = strlen(buf);
	fwrite(buf,count,1,fp);
	return 0;
}
