#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct sharedData{
	int num1;
	int num2;
  int sum;
	int write_by;
};

void get_Sum(struct sharedData *shm){
    key_t key = ftok("shmpath",29);
    int shmid = shmget(key,1024,0666|IPC_CREAT);
    shm = (struct sharedData *) shmat(shmid,(void*)0,0);
	shm->write_by = 0;

	while(1){
		if(shm->write_by==0){
			printf("waiting client's data or type ctrl-c to exit\n");
			sleep(2);
			continue;
		}
		shm->sum = shm->num1 + shm->num2;
		shm->write_by = 0;
		printf("complete\n");
    printf("send back the answer\n");
	}
}

int main()
{
	struct sharedData *shm;
	printf("pid %d\n", getpid());
	get_Sum(shm);
  	shmdt(shm);	
    return 0;
}
