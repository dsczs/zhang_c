#include "sys/types.h"
#include "sys/shm.h"
#include "signal.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
int main()
{
  int shmid;
  int key;
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
 // system("ipcrm -m shmid");
  return 0;
}
