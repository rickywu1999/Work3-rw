#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

int myrand(){
  int f = open("/dev/random",O_RDONLY);
  void * p;
  read(f,p,4);
  printf("%d\n",*((int*)p));
  srand(*((int*)p));
  return rand();
}

int main(){
  printf("%d\n",myrand());
  return 0;
}
