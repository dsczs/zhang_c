#include "sys/types.h"
#include "sys/msg.h"
#include "signal.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
struct msgbuf
{
  long type;
  char voltage[124];
  char ID[4];
};
int main()
{
  int msgid;
  int readret;
  int key;
  int pid;
  struct msgbuf sendbuf,recvbuf;
  key=ftok("./a.c",'a');
  if(key < 0)
  {
	 printf("creat key failure\n");
	 return -2;
  }
  msgid=msgget(key,IPC_CREAT|0777);
  if(msgid <0)
  {
	printf("creat message queue failure\n");
	return -1;
  }
  printf("creat message queue  sucess msgid=%d\n",msgid);
  system("ipcs -q");
  
  pid=fork();
  if(pid > 0) //parent process   write 100
  {
   sendbuf.type=100; 
   //write message queue
   while(1)
   {
    memset(sendbuf.voltage,0,124);//clear send buffer
    printf("please input message:\n");
    fgets(sendbuf.voltage,124,stdin);
    //start write message to message queue
    msgsnd(msgid,(void *)&sendbuf,strlen(sendbuf.voltage),0);
   }
  }
  if(pid == 0)//child process read 200
  {
	while(1)
	{
	 memset(recvbuf.voltage,0,124);
	 msgrcv(msgid,(void *)&recvbuf,124,200,0);
	 printf("receive message from message queue:%s",recvbuf.voltage);
	}
  }
  msgctl(msgid,IPC_RMID,NULL);
  system("ipcs -q");
  return 0;
}
