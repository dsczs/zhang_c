#include "unistd.h"
#include "stdio.h"
#include "sys/types.h"
#include "stdlib.h"
#include "fcntl.h"
int main()
{
 int fd;
 int i;
 int process_inter=0;
 fd=open("./myfifo",O_RDONLY);
 if(fd <0)
 {
   printf("open myfifo failure\n");
   return -1;
 }
 printf("open myfifo sucess\n");

 read(fd,&process_inter,1);
 while(process_inter == 0);

 for(i=0;i<5;i++)
 {
   printf("this is second process i=%d\n",i);
   usleep(100);
 }
 while(1);
 return 0;  
}
