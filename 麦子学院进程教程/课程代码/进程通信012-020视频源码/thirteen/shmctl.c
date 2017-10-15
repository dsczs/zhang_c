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
  char *p;
  key=ftok("./a.c",'b');
  if(key <0 )
  {
	printf("creat key fialure\n");
	return -2;
  }
  printf("creat key sucess key=%X\n",key);
  shmid=shmget(key,128,IPC_CREAT | 0777);
  if(shmid <0)
  {
	printf("creat share memory failure\n");
	return -1;
  }
  printf("creat share memory sucess shmid=%d\n",shmid);
  system("ipcs -m");

  p=(char *)shmat(shmid,NULL,0);
  if(p == NULL)
  {
	printf("shmat function failure\n");
	return -3;
  }
  //write share memory
  fgets(p,128,stdin);

  //start read share memory
  printf("share memory data:%s",p);

  printf("second read share memory data:%s",p);
  
  shmdt(p);
 // memcpy(p,"abcd",4);
  shmctl(shmid,IPC_RMID,NULL);
  system("ipcs -m ");

  return 0;
}
