

这是我自己学习写的代码: 线程级加上读写锁,静态库链接,写/读文件 命令: gcc -c abase.c aoperand.c(将两个.c文件转换为.o文件) ar crs -o libstatic.a abase.o aperand.o(将两个.o文件合并成一个.a文件[静态库文件]) gcc localstatictest.c -o localstatictest -L. -lstatic(-L后面.a文件所在路径;-l后是.a文件名去除lib部分) -I头文件所在路径

gcc -c IOFunction.c ar crs -o libstatic.a IOFunction.o gcc useThread.c -o useThread -lpthread -L. -lstatic

