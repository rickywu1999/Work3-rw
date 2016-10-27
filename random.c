#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

int myrand(){
  int f = open("/dev/random",O_RDONLY);
  void * p = malloc(sizeof(int));
  read(f,p,sizeof(int));
  //printf("%d\n",*((int*)p));
  srand(*((int*)p));
  free(p);
  return rand();
}

int main(){
  umask(0);
  int arr[10];
  int c = 0;
  printf("Generating Numbers:\n");
  while (c<10){
    int n = myrand();
    arr[c] = n;
    printf("random#%d - %d\n",c+1,n );
    c++;
  }
  printf("\nWriting into randomList \n");
  int fd = open("randomList",O_CREAT|O_RDWR|O_APPEND,0644);
  write(fd,arr,sizeof(int)*10);
  close(fd);
  printf("\nWriting Complete\n");

  printf("Reading randList into new array\n");
  int arr2[10];
  int nf = open("randomList", O_RDONLY);
  read(nf, arr2, sizeof(int)*10);
  close(nf);

  printf("Result from read:\n");
  c = 0;
  while(c<10){
    printf("random#%d - %d\n", c+1, arr2[c]);
    c++;
  }
  return 0;
}
