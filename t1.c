#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

struct msgbuf {
  long mtype;
  char mtext[10];
};

int main() {
  key_t key = 0x1234;
  pid_t PID = fork();
  struct msgbuf msg_send, msg_rcv;
  int queue_id = msgget(key, IPC_CREAT | 0x1FF);

  if (queue_id < 0) {
    printf("Erro na criacao da fila\n");
    exit(1);
  }

  if (PID) {
    /* processo pai */
    // printf("Sou o processo pai | PID = %d\n", PID);
    msg_send.mtype = PID;

    for (int i = 0; i < 10; ++i) {
      sprintf(msg_send.mtext, "%d", i + 1);
      printf("Mensagem enviada: %s\n", msg_send.mtext);
      msgsnd(queue_id, &msg_send, sizeof(msg_send) - sizeof(long), 0);
    }
    exit(0);
  }

  /* processo filho */
  // printf("Sou o processo filho | PID = %d\n", PID);

  for (int i = 0; i < 10; ++i) {
    msgrcv(queue_id, &msg_rcv, sizeof(msg_rcv) - sizeof(long), getpid(), 0);
    printf("Mensagem recebida: %s\n", msg_rcv.mtext);
    sleep(5);
  }

  msgctl(queue_id, IPC_RMID, NULL);
  return 0;
}
