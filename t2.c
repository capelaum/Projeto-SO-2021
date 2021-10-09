#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void busy_waiting();

int main() {
  int i, pid, t;
  clock_t start = clock(), end;

  for (i = 0; i < 3; i++) {
    pid = fork();

    if (pid < 0) {
      printf("Erro no fork\n");
      exit(-1);
    }

    // Processo Filho
    if (pid == 0) {
      printf("Processo Filho | PID = %d\n", pid);
      busy_waiting();
      exit(1);

    } else {
      wait(NULL);
      printf("Processo Pai | PID = %d\n", pid);
    }
  }

  t = (end - start) / CLOCKS_PER_SEC;
  printf("PID = %d | TIME: %d", pid, t);
  return 0;
}

void busy_waiting() {
  long int i;
  /* busy waiting com 100% de CPU – demora 25s */
  for (i = 0; i < 20000000000; i++) {
  }
}