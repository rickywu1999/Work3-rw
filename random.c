#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>


int myrand(){
    //OPEN
  int f = open("/dev/random",O_RDONLY);
  if (f< 0){
    printf("Failed to open file, error: %s\n",strerror(errno));
    return -1;
  }
  void * p = malloc(sizeof(int));
    //READ
  if (read(f,p,sizeof(int)) < 0){
    printf("Failed to read file, error: %s\n",strerror(errno));
    return -1;
  }

  srand(*((int*)p));
  free(p);
  return rand();
}


int main(){
  int arr[10];
  int c = 0;
  printf("Generating Numbers:\n");
  while (c<10){
    int n = myrand();
    if (n < 0){
        return 0;
    }
    arr[c] = n;
    printf("random#%d - %d\n",c+1,n );
    c++;
  }

  printf("\nWriting into randomList \n");
    //OPEN
  int fd = open("randomList",O_CREAT|O_RDWR|O_TRUNC,0644);
  if (fd< 0){
    printf("Failed to open file, error: %s\n",strerror(errno));
    return 0;
  }
  //WRITE
  if(write(fd,arr,sizeof(int)*10) < 0){
    printf("Failed to write to file, error %s\n",strerror(errno));
    return 0;
  }
  close(fd);
  printf("\nWriting Complete\n");

  printf("Reading randList into new array\n");
  int arr2[10];
    //OPEN
  int nf = open("randomList", O_RDONLY);
  if (nf< 0){
    printf("Failed to open file, error: %s\n",strerror(errno));
    return 0;
  }
    //READ
  if (read(nf, arr2, sizeof(int)*10)< 0){
    printf("Failed to read file, error: %s\n",strerror(errno));
    return 0;
  }
  close(nf);

  printf("Result from read:\n");
  c = 0;
  while(c<10){
    printf("random#%d - %d\n", c+1, arr2[c]);
    c++;
  }
  return 0;
}
