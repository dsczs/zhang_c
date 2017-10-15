#include "sys/types.h"
#include "sys/sem.h"
#include "signal.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
int main()
{
  int semid;
  semid=semget(IPC_PRIVATE,3,0777);
  if(semid <0)
  {
	printf("creat semaphore failure\n");
	return -1;
  }
  printf("creat semaphore   sucess semid=%d\n",semid);
  system("ipcs -s");
  //while(1);
  // delete semaphore
  semctl(semid,0,IPC_RMID,NULL);
  system("ipcs -s");
  return 0;
}
