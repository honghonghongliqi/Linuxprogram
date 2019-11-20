#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include"string.h"
FILE* openFile();
int writeFile(FILE* fd);
