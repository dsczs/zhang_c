#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
int main()
{
  int fd[2];
  int ret;
  ret=pipe(fd);
  if(ret <0)
  {
	printf("creat pipe failure\n");
	return -1;
  }
  printf("creat pipe sucess fd[0]=%d,fd[1]=%d\n",fd[0],fd[1]);
  return 0;
}
