#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void busy_waiting();
void execute_parent_process(pid_t process_queue[], int queue_size);
void execute_child_process();
void signal_handler() {}
void change_process(pid_t pid) {
  printf("ALARME DISPARADO!\n");
  kill(getpid(), SIGSTOP);
}

int main() {
  int i;
  double t;
  int queue_size = 3;
  pid_t pid, process_queue[queue_size];

  // signal(SIGUSR1, signal_handler);
  siginterrupt(SIGALRM, 1);
  signal(SIGALRM, change_process);

  for (i = 0; i < queue_size; i++) {
    pid = fork();

    if (pid < 0) {
      printf("Erro no fork\n");
      exit(-1);
    }

    if (pid == 0) {
      execute_child_process();
      exit(0);
    } else {
      process_queue[i] = pid;
      kill(pid, SIGSTOP);
    }
  }

  execute_parent_process(process_queue, queue_size);

  return 0;
}

void execute_parent_process(pid_t process_queue[], int queue_size) {
  printf("\nIniciou: Processo Pai | PID = %d\n", getpid());
  int p_index = 0, p_count = 0;

  while (p_count != queue_size) {
    alarm(0);
    kill(process_queue[p_index], SIGCONT);

    // Check whether the process ended
    int waitStatus;
    int waitReturn = waitpid(process_queue[p_index], &waitStatus, WNOHANG);
    if (waitReturn != 0 && WIFEXITED(waitStatus)) {
      p_count++;  // Process ended, increase process count
      printf("Terminou: PID = %d | COUNT = %d\n", process_queue[p_index],
             p_count);
    }

    p_index++;
    if (p_index == queue_size) {
      p_index = 0 + p_count;
    }
  }
}

void execute_child_process() {
  alarm(5);  // espera 5s ate disparar o alarme

  time_t start = time(NULL), end;
  double t;
  printf("Iniciou: Processo Filho | PID = %d\n", getpid());
  busy_waiting();
  printf("Terminou: Processo Filho | PID = %d\n", getpid());

  end = time(NULL);
  t = difftime(end, start);
  printf("PID = %d | Tempo de execução: %fs\n", getpid(), t);
}

void busy_waiting() {
  long int i;
  /* busy waiting com 100% de CPU – demora 25s */
  for (i = 0; i < 20000000000; i++) {
  }
}