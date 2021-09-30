#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>


struct msgbuf{
  long mtype;
  char mtext[10];
};



int main(){
  key_t keyMsg = 0x1234;
  int id_msg;
  id_msg = msgget(keyMsg, IPC_CREAT | 0x1FF);
  pid_t PID;
  PID = fork();

  if(PID){
    //processo pai
    //printf("Sou o processo pai\n");
    struct msgbuf mensagem;
    mensagem.mtype = PID;
    //strcpy(mensagem.mtext,"1");
    for(int i=0;i<10;++i){
      //mensagem.mtype = i;
      sprintf(mensagem.mtext,"%d",i+1);
      printf("antes de enviar: %s\n", mensagem.mtext);
      msgsnd(id_msg, &mensagem, sizeof(mensagem)-sizeof(long),0);
    }
  } else{
    //processo filho
    //
    //sleep(5);
    //printf("Sou o processo filho\n");
    struct msgbuf buff;
    for(int i = 0;i < 10;++i){
      msgrcv(id_msg, &buff,sizeof(buff)-sizeof(long),getpid(),0);
      printf("o que recebi: %s\n",buff.mtext);
      sleep(5);
    }
    msgctl(id_msg, IPC_RMID, NULL);
  }
}

