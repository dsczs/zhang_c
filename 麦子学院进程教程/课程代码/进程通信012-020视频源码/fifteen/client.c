#include "sys/types.h"
#include "sys/shm.h"
#include "signal.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
struct mybuf
{
  int pid;
  char buf[124];
};
void myfun(int signum)
{
  return ;
}
int main()
{
  int shmid;
  int key;
  struct mybuf  *p;
  int pid;
  key=ftok("./a.c",'a');
  if(key < 0)
  {
    printf("creat key failure\n");
	return -1;
  }
  printf("creat key sucess\n");
  shmid=shmget(key,128,IPC_CREAT | 0777);
  if(shmid <0)
  {
	printf("creat share memory failure\n");
	return -1;
  }
  printf("creat share memory sucess shmid=%d\n",shmid);
    

	signal(SIGUSR1,myfun);
    p=(struct mybuf *)shmat(shmid,NULL,0);
    if(p == NULL)
    {
	 printf("parent process:shmat function failure\n");
	 return -3;
    }
     //get server pid
     //read share memory 
	 pid=p->pid;
	 //write client pid to share memory 
	 p->pid=getpid(); 
	 //kill signal
	 kill(pid,SIGUSR2);
  
    //client start read data from share memory
    while(1)
    {
	  pause();//wait server write data to share memory;
	  printf("client process receve data from share memory:%s",p->buf);//read data 
	  kill(pid,SIGUSR2);//server may write share memory
	}

  
  shmdt(p);
  shmctl(shmid,IPC_RMID,NULL);
  system("ipcs -m ");

  return 0;
}
