#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>

int main(){
  key_t key;
  int shmid;
  char *data;
  char in[100];
  
  key = ftok("j", 'R');
  shmid = shmget(key, 200, 0644 | IPC_CREAT);
  data = shmat(shmid, (void *)0, 0);
  while(1){

    if(!strlen(data)) 
      printf("created new shared memory\n");
    else
      printf("data: %s", data);

    printf("Do you want to edit the shared mem?(y/n): ");
    fgets(in, 100, stdin);
    if(!strncmp(in,"y", 1)){
      printf("Enter new data: ");
      fgets(data, 100, stdin);
    }

    printf("Do you want to delete the shared memory?(y/n): ");
    fgets(in, 100, stdin);
    if(!strncmp(in, "y", 1)){
      shmdt(data);
      shmctl(shmid, IPC_RMID, 0);
      return 0;
    }
  }
} 
