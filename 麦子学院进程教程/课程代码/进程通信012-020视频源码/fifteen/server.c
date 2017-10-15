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
    

	signal(SIGUSR2,myfun);
    p=(struct mybuf *)shmat(shmid,NULL,0);
    if(p == NULL)
    {
	 printf("parent process:shmat function failure\n");
	 return -3;
    }
     //get client pid
     p->pid=getpid();//write server pid to share memory

	 pause();//wait client read server pid;
     
	 pid=p->pid;


    //write

    while(1)
    {
      //write share memory
	  printf("parent process start write share memory:\n");
      fgets(p->buf,128,stdin);
	  kill(pid,SIGUSR1);// client process read data 
	  pause();// wait client process read
	}

  
  shmdt(p);
  shmctl(shmid,IPC_RMID,NULL);
  system("ipcs -m ");

  return 0;
}
