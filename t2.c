#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void busy_waiting();

int main() {
  int i;
  double t;
  pid_t pid;
  time_t start = time(NULL), end;

  for (i = 0; i < 3; i++) {
    pid = fork();

    if (pid < 0) {
      printf("Erro no fork\n");
      exit(-1);
    }

    // Processo Filho
    if (pid == 0) {
      printf("Comecou: Processo Filho | PID = %d\n", getpid());
      busy_waiting();
      printf("Terminou: Processo Filho | PID = %d\n", getpid());
      break;

    } else {
      printf("\nSou o pai esperando a execucao dos filhos terminar..\n");
      wait(NULL);
      printf("Processo Pai | PID = %d\n", getpid());
    }
  }

  end = time(NULL);
  t = difftime(end, start);
  printf("PID = %d | Tempo de execução: %fs\n", getpid(), t);
  return 0;
}

void busy_waiting() {
  long int i;
  /* busy waiting com 100% de CPU – demora 25s */
  for (i = 0; i < 20000000000; i++) {
  }
}