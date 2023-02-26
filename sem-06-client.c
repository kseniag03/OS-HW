// shared-memory-client.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "message.h"

void sys_err (char *msg) {
  puts (msg);
  exit (1);
}

int main () {
  int shmid;            // идентификатор разделяемой памяти
  message_t *share;     // адрес сообщения в разделяемой памяти
  int num;   // число

  // получение доступа к сегменту разделяемой памяти
  if ((shmid = shmget (SHM_ID, sizeof (message_t), 0)) < 0) {
    sys_err ("client: can not get shared memory segment");
  }

  // получение адреса сегмента
  if ((share = (message_t *) shmat (shmid, 0, 0)) == NULL) {
    sys_err ("client: shared memory attach error");
  }

  // Организация передаци сообщений
  while (1) {
    num = random() % 1000;
    share->value = num;
    if (share->value > 0) {
      // Не прощаемся.
      // Записать сообщение о передаче строки
      share->type = MSG_TYPE_STRING;
      printf("write a random number %d\n", num);
      sleep(5);
    } else {
      // Записать сообщение о завершении обмена
      share->type = MSG_TYPE_FINISH;
    }
    if (share->type == MSG_TYPE_FINISH) {
      break;
    }
  }
  // Окончание цикла передачи сообщений
  shmdt (share);  // отсоединить сегмент разделяемой памяти
  exit (0);
}
