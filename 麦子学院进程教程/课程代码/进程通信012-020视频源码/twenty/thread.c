#include "stdio.h"
#include "stdlib.h"
#include "pthread.h"
#include "semaphore.h"
sem_t sem;
void *fun(void *var)//child thread code
{
  int j;
  //p  wait
  sem_wait(&sem);  //sleep
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
  sem_init(&sem,0,0);//sem=0
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
  sem_post(&sem);
  while(1);
  return 0;
}
