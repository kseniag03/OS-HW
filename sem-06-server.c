// shared-memory-server.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "message.h"

void sys_err (char *msg) {
  puts (msg);
  exit (1);
}

int main () {
  int shmid;             // идентификатор разделяемой памяти
  message_t *share;      // адрес сообщения в разделяемой памяти
//  char s[MAX_STRING];

  // создание сегмента разделяемой памяти
  if ((shmid = shmget (SHM_ID, sizeof (message_t), PERMS | IPC_CREAT)) < 0) {
    sys_err ("server: can not create shared memory segment");
  }
  printf("Shared memory %d created\n", SHM_ID);

  // подключение сегмента к адресному пространству процесса
  if ((share = (message_t *) shmat (shmid, 0, 0)) == NULL) {
    sys_err ("server: shared memory attach error");
  }
  printf("Shared memory pointer = %p\n", share);

  share->type = MSG_TYPE_EMPTY;
  while (1) {
    if (share->type != MSG_TYPE_EMPTY) {
      // обработка сообщения
      if (share->type == MSG_TYPE_STRING) {
        printf ("%d\n", share->value);
      } else if (share->type == MSG_TYPE_FINISH) {
        break;
      }
      share->type = MSG_TYPE_EMPTY; // сообщение обработано
    }
  }

  // удаление сегмента разделяемой памяти
  shmdt (share);
  if (shmctl (shmid, IPC_RMID, (struct shmid_ds *) 0) < 0) {
    sys_err ("server: shared memory remove error");
  }
  exit (0);
}
