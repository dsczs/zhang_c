#include "sys/types.h"
#include "sys/shm.h"
#include "signal.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
void myfun(int signum)
{
  return ;
}
int main()
{
  int shmid;
  int key;
  char *p;
  int pid;
  shmid=shmget(IPC_PRIVATE,128,IPC_CREAT | 0777);
  if(shmid <0)
  {
	printf("creat share memory failure\n");
	return -1;
  }
  printf("creat share memory sucess shmid=%d\n",shmid);
 
  pid=fork();
  if(pid > 0)//parent process 
  { 
	signal(SIGUSR2,myfun);
    p=(char *)shmat(shmid,NULL,0);
    if(p == NULL)
    {
	 printf("parent process:shmat function failure\n");
	 return -3;
    }
    while(1)
    {
      //write share memory
	  printf("parent process start write share memory:\n");
      fgets(p,128,stdin);
	  kill(pid,SIGUSR1);// child process read data 
	  pause();// wait child process read
	}
  }
  if(pid == 0)//child process 
  {
	signal(SIGUSR1,myfun);
	p=(char *)shmat(shmid,NULL,0);
	if(p == NULL)
	{
     printf("child process shmat function failure\n");
	 return -3;
	}
    while(1)
	{
	 pause();// wait parent process write
     //start read share memory
     printf("share memory data:%s",p);
	 kill(getppid(),SIGUSR2);
	}
  }
  
  shmdt(p);
  shmctl(shmid,IPC_RMID,NULL);
  system("ipcs -m ");

  return 0;
}
