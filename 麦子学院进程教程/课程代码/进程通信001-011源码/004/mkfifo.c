#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
int main()
{
  int ret;
  ret=mkfifo("./myfifo",0777);
  if(ret <0)
  { 
	printf("creat myfifo failure\n");
	return -1;
  }
  printf("creat myfifo sucess\n");

  return 0;
}
