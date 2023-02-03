#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* temp_p;
int shmid;

struct sharedData{
	int num1;
	int num2;
  int sum;
	int write_by;
};

void input_data(struct sharedData *shm){
	char input[1000];
	int First = 1;	
    key_t key = ftok("shmpath",29);
    shmid = shmget(key, 1024, 0666);
	if(shmid < 0){
		perror("shmget");
    	exit(1);
	}

    shm = (struct sharedData *) shmat(shmid,(void*)0,0);
	shm->sum = 0;
	shm->num1 = 0;
	shm->num2 = 0;
	shm->write_by = 0;

	while(1){
		if(shm->write_by==1 && shm->sum == 0){
			sleep(1);
			continue;
		}
		if(shm->write_by == 0 && !First){
			printf("The sum is: %d\n", shm->sum);
		}
		shm->sum = 0;
    	printf("Input two numbers: ");
		temp_p=fgets(input, 100, stdin);
		if(strcmp(input, "quit\n") == 0){
			printf("leaving\n");
			exit(0);
		}
		sscanf(input, "%d %d", &(shm->num1), &(shm->num2));
		shm->write_by = 1;
		First = 0;
		printf("calculating now in p2\n");
	}
}

int main()
{
	struct sharedData *shm;
	printf("pid %d\n", getpid());
	printf("p1\n");
	input_data(shm);
  	shmdt(shm);						
    shmctl(shmid,IPC_RMID,NULL);	
    return 0;
}
