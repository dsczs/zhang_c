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
void *fun(void *var)//child thread code
{
  int j;
  //p  wait
 // sem_wait(&sem);  //sleep
  mysembuf.sem_op=-1;
  semop(semid,&mysembuf,1);
  for(j=0;j<10;j++)//second
  {
    usleep(100);
	printf("this is fun j=%d\n",j);
  }
 
}
int main()//main thread code
{
  int i;
  char str[]="hello linux\n";
  pthread_t tid;
  int ret;
  semid=semget(IPC_PRIVATE,3,0777);
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
  ret=pthread_create(&tid,NULL,fun,(void *)str);
  if(ret<0)
  {
	printf("creat thread failure\n");
	return -1;
  }
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
