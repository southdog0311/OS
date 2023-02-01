#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int shellcmd(char input[]) {
  if (strcmp(input, "tree") == 0) {
    system("tree");
    return 1;
  }
  if (strcmp(input, "sort") == 0) {
    system("sort");
    return 1;
  }
  if (strcmp(input, "clear") == 0) {
    system("clear");
    return 1;
  }
  if (strcmp(input, "exit") == 0) {
    exit(0);
    return 1;
  }
  if (strcmp(input, "pwd") == 0) {
    system("pwd");
    return 1;
  }
  if (strcmp(input, "ls") == 0) {
    system("ls");
    return 1;
  }
  if (strcmp(input, "ps axe") == 0) {
    system("ps axe");
    return 1;
  } else
    return 0;
}

int childcmd(char input[]) {
  if (strcmp(input, "child") == 0)
    return 1;
  else if (strcmp(input, "child &") == 0)
    return 1;
  else
    return 0;
}

int main(void) {
  int pid;
  char *args[] = {"./child", NULL};
  char inputs[10];
  char child_cmd[] = "child";
  char parent[] = "child &";
  printf("parent pid is: %d\n", getpid());
  while (1) {
    printf("1092929_my_shell>");
    fgets(inputs, sizeof(inputs), stdin);
    inputs[strcspn(inputs, "\n")] = '\0';
    if (shellcmd(inputs)) {
      continue;
    }
    if (childcmd(inputs)) {
      pid = fork();
    }
    if (pid == 0 && childcmd(inputs)) {
      int msg = execvp(args[0], args);
      printf("exec() error: %d\n", msg);
    } else if (pid > 0 && childcmd(inputs)) {
      if (strcmp(inputs, parent) != 0)
        wait(NULL);
      printf("back to parent process\n");
    } else {
      printf("wrong commend\n");
    }
  }
}
