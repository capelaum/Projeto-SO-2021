# Trabalho Prático 1

Os alunos devem confeccionar um programa com 2 processos da seguinte maneira:

**Processo 1**: Cria o processo 2 e envia 10 mensagens por fila de mensagens numeradas (1 a 10) para o processo 2. Quando o processo 2 morrer, remove a fila de mensagem e termina a execução.

**Processo 2**: Executa um loop para receber 10 mensagens, onde

- Recebe mensagem,
- Imprime o numero da mensagem e
- Dorme 5 segundos.

Ao final do loop, termina a execução.

`Observação`: Devem ser usadas chamadas de sistema Unix para criação e término de processos e chamadas de sistema do mecanismo IPC fila de mensagens.

`Observação`: Deve ser entregue o programa fonte em C no formato .txt

# Trabalho Prático 2

Os alunos devem implementar um escalonador round-robin (RR) em modo usuário da seguinte maneira:

## O processo pai

a) Cria três processos filhos e imediatamente para a execução dos filhos.

b) O processo pai implementa um escalonador RR com quantum de 5 segundos.

`Atenção`: em um dado momento, deve haver somente um processo no estado R.

c) Após o término da execução dos três processos filhos, o processo pai termina a sua execução.

## Os processos filho

a) Vão executar o seguinte código:

```C
long int i;
/* busy waiting com 100% de CPU – demora 25s */
for(i=0; i<20000000000; i++);
```

b) Ao término do “for”, o processo filho imprime o seu pid e o tempo de execução. Depois disso, termina a execução.
