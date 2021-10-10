#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void execute_child_process();
void busy_waiting();
void stop_process() {
  double t = clock() / CLOCKS_PER_SEC;
  // Descomente para ver o quantum de cada processo
  // printf("PID: %d - QUANTUM %.fs\n", getpid(), t);
  kill(getpid(), SIGSTOP);  // para o processo filho corrente
  alarm(5);                 // reseta o alarme do processo filho corrente
}

int main() {
  int i, queue_size = 3;
  time_t start_total = time(NULL);
  pid_t pid, process_queue[queue_size];
  signal(SIGALRM, stop_process);

  for (i = 0; i < queue_size; i++) {
    pid = fork();

    if (pid < 0) {
      printf("Erro no fork\n");
      exit(-1);
    }

    if (pid == 0) {
      execute_child_process(start_total);
      exit(0);
    } else {
      process_queue[i] = pid;
      kill(pid, SIGSTOP);  // para a execução dos filhos
    }
  }

  // Comeca o escalonamento com quantum de 5s
  int p_index = 0, p_count = 0;
  printf("\n");

  while (p_count != queue_size) {
    kill(process_queue[p_index], SIGCONT);

    int wait_status;
    int wait_finish = waitpid(process_queue[p_index], &wait_status, WNOHANG);
    int wait_stop = waitpid(process_queue[p_index], &wait_status, WUNTRACED);

    // Checa se processo acabou e incrementa contador
    if (wait_finish != 0) {
      p_count++;
    }

    // Checa se processo parou e atualiza o indice do processo a executar
    if (wait_stop) {
      p_index++;
      if (p_index == queue_size) {
        p_index = p_count;
      }
    }
  }

  return 0;
}

void execute_child_process(time_t start_total) {
  alarm(5);  // seta o alarme inicial
  clock_t start = clock(), end;
  time_t end_total;
  double t;

  printf("Iniciou: Processo Filho | PID = %d\n", getpid());
  busy_waiting();

  end = clock();
  t = (end - start) / CLOCKS_PER_SEC;
  printf("PID = %d | Tempo de execução: %.1fs\n", getpid(), t);

  end_total = time(NULL);
  t = difftime(end_total, start_total);

  // Descomente para ver o tempo desde o início do programa
  // até o fim da execução do processo
  // printf("PID = %d | Tempo de execução total: %.1fs\n", getpid(), t);
}

void busy_waiting() {
  long int i;
  /* busy waiting com 100% de CPU – demora 25s */
  for (i = 0; i < 20000000000; i++) {
  }
}