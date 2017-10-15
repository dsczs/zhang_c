#include "stdio.h"
#include "stdlib.h"
#include "sys/sem.h"
#include "sys/ipc.h"
int semid;
union semun 
{
  int   val;    /* Value for */
  struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET*/
  unsigned short  *array;  /* Array for GETALL, SETALL */
  struct seminfo  *__buf;  /* Buffer for IPC_INFO																							                                           (Linux-specific) */
};
struct sembuf mysembuf;
void *fun(void *var)//child thread code
{
  int j;
  //sem_wait(&sem);//p
  mysembuf.sem_op=-1;
  semop(semid,&mysembuf,1);
  for(j=0;j<10;j++)
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
  union semun mysemun;
  mysembuf.sem_num=0;
  mysembuf.sem_flg=0;
  semid=semget(IPC_PRIVATE,3,0777);
  if(semid < 0) 
	 {
	   printf("creat semaphore failure\n");
	   return -1;
	 }
  printf("creat semaphore sucess\n");
 // sem_init(&sem,0,0);
  mysemun.val=0;
  semctl(semid,0,SETVAL,mysemun);
  ret=pthread_create(&tid,NULL,fun,(void *)str);
  if(ret<0)
  {
	printf("creat thread failure\n");
	return -1;
  }
  for(i=0;i<10;i++)
  {
	usleep(100);
	printf("this is main fun i=%d\n",i);
  }
  mysembuf.sem_op=1;
  semop(semid,&mysembuf,1);
  //sem_post(&sem);
  while(1);
  return 0;
}
