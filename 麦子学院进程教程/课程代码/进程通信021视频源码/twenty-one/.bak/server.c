#include "stdio.h"
#include "stdlib.h"
#include "pthread.h"
//#include "semaphore.h"
#include "sys/ipc.h"
#include "sys/sem.h"
//sem_t sem;
union semun 
{	                
	int  val;  	/* Value for SETVAL*/
	struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
								                  
	unsigned short  *array;  /* Array for GETALL, SETALL */
												                 
	struct seminfo  *__buf;  /* Buffer for IPC_INFO(Linux-specific) */
};

int semid;
union semun mysemun;
struct sembuf mysembuf;

int main()//main thread code
{
  int i;
  int key;
  key=ftok("./a.c",'a');
  semid=semget(key,3,0777);
  if(semid < 0)
  {
	printf("creat semaphore failure\n");
	return -1;
  }
  printf("creat semaphore sucess,semid=%d\n",semid);
  system("ipcs -s");
  mysemun.val=0;
  semctl(semid,0,SETVAL,mysemun);
  //sem_init(&sem,0,0);//sem=0
  mysembuf.sem_num=0;
  mysembuf.sem_flg=0;
  for(i=0;i<10;i++)//first 
  {
	usleep(100);
	printf("this is main fun i=%d\n",i);
  }
  //v
 // sem_post(&sem);
  mysembuf.sem_op=1;
  semop(semid,&mysembuf,1);
  while(1);
  return 0;
}
