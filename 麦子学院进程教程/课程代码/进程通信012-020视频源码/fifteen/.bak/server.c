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
  struct mybuf *p;
  int client_pid;
  key=ftok("./a.c",'a');
  if(key < 0)
  {
	printf("creat key failure\n");
	return -1;
  }
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
	p->pid=getpid();//write pid to share memory
	pause();
    client_pid=p->pid;
    while(1)
    {
      //write share memory
	  printf("parent process start write share memory:\n");
      fgets(p->buf,128,stdin);
	  kill(client_pid,SIGUSR1);// child process read data 
	  pause();// wait child process read
	}
 
  
  shmdt(p);
  shmctl(shmid,IPC_RMID,NULL);
  system("ipcs -m ");

  return 0;
}
