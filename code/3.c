/**要求：
 *一个父进程,三个子进程
 *管道p1:child1,child2
 *管道p2:child2,child3
 *child1写入65535个数字
 *child2读出p1数据再写入p2中
 *child3从p2中读出数据并求和
 */
#include"my.h"
char* itoa(int num,char* str,int radix)
{
	char index[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";//索引表
	unsigned unum;//存放要转换的整数的绝对值,转换的整数可能是负数
	int i=0,j,k;//i用来指示设置字符串相应位，转换之后i其实就是字符串的长度；转换后顺序是逆序的，有正负的情况，k用来指示调整顺序的开始位置;j用来指示调整顺序时的交换。

	//获取要转换的整数的绝对值
	if(radix==10&&num<0)//要转换成十进制数并且是负数
	{
		unum=(unsigned)-num;//将num的绝对值赋给unum
		str[i++]='-';//在字符串最前面设置为'-'号，并且索引加1
	}
	else unum=(unsigned)num;//若是num为正，直接赋值给unum

	//转换部分，注意转换后是逆序的
	do
	{
		str[i++]=index[unum%(unsigned)radix];//取unum的最后一位，并设置为str对应位，指示索引加1
		unum/=radix;//unum去掉最后一位

	}while(unum);//直至unum为0退出循环

	str[i]='\0';//在字符串最后添加'\0'字符，c语言字符串以'\0'结束。

	//将顺序调整过来
	if(str[0]=='-') k=1;//如果是负数，符号不用调整，从符号后面开始调整
	else k=0;//不是负数，全部都要调整

	char temp;//临时变量，交换两个值时用到
	for(j=k;j<=(i-1)/2;j++)//头尾一一对称交换，i其实就是字符串的长度，索引最大值比长度少1
	{
		temp=str[j];//头部赋值给临时变量
		str[j]=str[i-1+k-j];//尾部赋值给头部
		str[i-1+k-j]=temp;//将临时变量的值(其实就是之前的头部值)赋给尾部
	}

	return str;//返回转换后的字符串
}
int main(){
	pid_t child1,child2,child3;
	int fd1[2],fd2[2];
	char rbuf[30],wbuf[30];
	memset(rbuf,0,sizeof(rbuf));
	memset(wbuf,0,sizeof(wbuf));
	pipe(fd1);
	pipe(fd2);
	child1 = fork();
	if(child1<0){
		perror("child1 failed to fork!\n");
	}else if(child1==0){
		printf("child1 pid :%d.begin to running.write to p1.\n",getpid());
		//child1的工作:
		srand((unsigned)time(NULL));
		close(fd2[0]);
		close(fd2[1]);
		close(fd1[0]);
		for(int i=0;i<65535;i++){
			//将num:0-9 转换为wbuf字符串,10进制
			int num=rand()%9;
			//printf("child1 getNUM:%d.\n",num);
			itoa(num,wbuf,10);
			write(fd1[1],wbuf,sizeof(wbuf));
		}
		close(fd1[1]);
		exit(1);
	}else{
		child2 = fork();
		if(child2<0){
                        perror("child2 failed to fork!\n");
                }else if(child2==0){
                        printf("child2 pid :%d.begin to running.read form p1,write to p2.\n",getpid());
			//child2的工作:
			//p1:read
			//p2:write
			close(fd1[1]);
			close(fd2[0]);
			for(int i=0;i<65535;i++){
				read(fd1[0],rbuf,sizeof(rbuf));
				//printf("child2:rbuf %s.\n",rbuf);
				strcpy(wbuf,rbuf);
				write(fd2[1],wbuf,sizeof(wbuf));
				//printf("child2:%d,wbuf:%s.\n",getpid(),wbuf);
			}
			close(fd1[0]);
                        close(fd2[1]);
			exit(2);
                }else{
			child3 = fork();
			if(child3<0){
				perror("child3 failed to fork!\n");
			}else if(child3==0){
				printf("child3 pid :%d.begin to running.read from p2.\n",getpid());
				//child3的工作:
				close(fd1[0]);
				close(fd1[1]);
				close(fd2[1]);
				int sum=0;
				for(int i=0;i<65535;i++){
					read(fd2[0],rbuf,sizeof(rbuf));
					//printf("child3:%d,rbuf:%s.\n",getpid(),rbuf);
					int num=atoi(rbuf);
					sum+=num;
				}
				printf("child3:pid %d,sum=%d.\n",getpid(),sum);
				close(fd2[0]);
				exit(3);
			}else{
				//等待所以的子进程结束
                                while(wait(NULL)!=-1);
                                printf("this is parent process,pid:%d.\n",getpid());		
				return 0;
			}
		}
	}
}
