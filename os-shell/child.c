#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
char input;

void *mythread(void *vargp) {
  while (1) {
    input = getchar();
    sleep(500);
  }
  return NULL;
}

int main() {
  int cnt = 1, start_time, end_time;

  end_time = start_time = time(NULL);
  pthread_t thread_id;
  pthread_create(&thread_id, NULL, mythread, NULL);
  while (1) {
    if (input == 'q')
      break;
    if (difftime(end_time, start_time) >= 3) {
      printf("child currently running, ");
      printf("pid: %d\n", getpid());
      printf("%d continue, Type q to quit\n", cnt++);
      start_time = time(NULL);
    }
    end_time = time(NULL);
  }
}
