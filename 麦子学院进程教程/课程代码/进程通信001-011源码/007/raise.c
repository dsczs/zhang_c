#include "stdio.h"
#include "sys/types.h"
#include "signal.h"
#include "stdio.h"
#include "stdlib.h"
int main()
{ 
  printf("raise before");
  raise(9);// _exit()    exit()
  printf("raise after\n");
  return 0;
}
