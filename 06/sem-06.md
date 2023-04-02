#  ДЗ №6 #
## Markdown report <br> ##

### 1. Ганина Ксения Андреевна (тг для вопросов: @kgnn47) <br> ###
### 2. БПИ212 <br> ###

![image](https://user-images.githubusercontent.com/114473740/221374584-dc337947-df3e-4d68-8e08-40ab8fd5fdc3.png)
________________________

### 3. Код с комментариями. <br> ###

#1. Client

```с
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
      share->type = MSG_TYPE_INT;
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
```

#2. Server

```с
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
      if (share->type == MSG_TYPE_INT) {
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
```

#3. Message

```с
// message.h
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>

#define SHM_ID  0x777     // ключ разделяемой памяти
#define PERMS   0666      // права доступа

// коды сообщений
#define MSG_TYPE_EMPTY  0     // сообщение о завершении обмена при пустой строке
#define MSG_TYPE_INT 1        // сообщение о передаче строки
#define MSG_TYPE_FINISH 2     // сообщение о том, что пора завершать обмен

// структура сообщения, помещаемого в разделяемую память
typedef struct {
  int type;
  int value;
} message_t;

```
________________________

### 4. Примеры вывода. <br> ###

Virtual Ubuntu <br>
![image](https://user-images.githubusercontent.com/114473740/221436302-0a56083a-f558-4b61-b775-4fb521b32c0f.png)
![image](https://user-images.githubusercontent.com/114473740/221436353-e184940d-6355-46e4-9fe6-983b2d01a53c.png)
![image](https://user-images.githubusercontent.com/114473740/221436405-3ab3d722-a04e-495e-9c71-c10d26526040.png)


