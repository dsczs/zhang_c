#include "unistd.h"
#include "stdio.h"
#include "sys/types.h"
#include "stdlib.h"
int main()
{
  pid_t pid;
  int fd[2];
  int ret;
  char process_inter=0;
  ret=pipe(fd);
  if(ret < 0)
  {
	printf("creat pipe failure\n");
	return -1;
  }
  printf("creat pipe sucess\n");
  pid = fork();
  if(pid ==0)//child process code   second
  {
    int i=0;
	read(fd[0],&process_inter,1);//if pipe empty   sleep
    while(process_inter ==0);
	 for(i=0;i<5;i++)
	 {
      printf("this is child process i=%d\n",i);
	  usleep(100);
	 }
  }
  if(pid >0)//parent process code   first
  {
	int i=0;
	for(i=0;i<5;i++)
	{
	  printf("this is parent process i=%d\n",i);
	  usleep(100);
	}
	process_inter=1;
	sleep(5);
	write(fd[1],&process_inter,1);
  }
  while(1);
  return 0;
   
}
