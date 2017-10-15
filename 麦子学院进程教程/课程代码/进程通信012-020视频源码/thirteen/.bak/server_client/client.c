#include "sys/types.h"
#include "sys/shm.h"
#include "signal.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
int main()
{
  int shmid;
  int key;
  int pid;
  char *p;
  key=ftok("./a.c",'b');
  if(key <0 )
  {
	printf("creat key fialure\n");
	return -2;
  }
  printf("creat key sucess key=%X\n",key);
  shmid=shmget(key,128, IPC_CREAT | 0777);
  if(shmid <0)
  {
	printf("creat share memory failure\n");
	return -1;
  }
  printf("creat share memory sucess shmid=%d\n",shmid);
  system("ipcs -m");
  
    //start read share memory
	p=(char *)shmat(shmid,NULL,0);
	if(p==NULL)
	{
       printf("child process shmat failure\n");
	   return -4;
	}
    printf("share memory data:%s\n",p);
    printf("second read share memory data:%s\n",p);
	while(1);
  shmdt(p);
  p=NULL;
  
  system("ipcs -m");
  return 0;
}
