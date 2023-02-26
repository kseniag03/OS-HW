#  ДЗ №6 #
## Markdown report <br> ##

### 1. Ганина Ксения Андреевна (тг для вопросов: @kgnn47) <br> ###
### 2. БПИ212 <br> ###

![image](https://user-images.githubusercontent.com/114473740/221374584-dc337947-df3e-4d68-8e08-40ab8fd5fdc3.png)
________________________

### 3. Код с комментариями. <br> ###

#1. Client

```с
// shmem-gen.c
// write a random number between 0 and 999 to the shm every 1 second
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>
#include <error.h>

int main() {
    int shm_id;         // идентификатор разделяемой памяти
    int *share;         // адрес сообщения в разделяемой памяти
    key_t key = 0x2FF;  // ключ System V IPC

    // получение доступа к сегменту разделяемой памяти
    shm_id = shmget (key, getpagesize(), 0666 | IPC_CREAT);
    if (shm_id < 0) {
        perror("client: can not get shared memory segment");
        exit(1);
    }
    printf("shm_id = %d\n", shm_id);

    // получение адреса сегмента
    // подключение сегмента к адресному пространству процесса
    share = (int *)shmat(shm_id, 0, 0);
    if (share == NULL) {
        perror("client: shared memory attach error");
        exit(2);
    }
    printf("share = %p\n", share);

    int num;
    srand(time(NULL));
    while (1) {
        num = random() % 1000;
        *share = num;
        printf("write a random number %d\n", num);
        sleep(1);
    }
    
    return 0;
}
```

#2. Server

```с
// shmem-out.c
// read from the shm every 1 second
#include<stdio.h>
#include<unistd.h>
#include<sys/shm.h>
#include<stdlib.h>
#include<error.h>

int main() {
    int shm_id;         // идентификатор разделяемой памяти
    int *share;         // адрес сообщения в разделяемой памяти
    key_t key = 0x2FF;  // ключ System V IPC

    // получение доступа к сегменту разделяемой памяти
    shm_id = shmget (key, getpagesize(), 0666 | IPC_CREAT);
    if (shm_id == -1) {
        perror("server: can not get shared memory segment");
        exit(1);
    }

    // получение адреса сегмента
    share = (int *)shmat(shm_id, 0, 0);
    if (share == NULL) {
        perror("server: shared memory attach error");
        exit(2);
    }

    while (1) {
        sleep(1);
        printf("%d\n", *share);
    }

    // удаление сегмента разделяемой памяти
    shmdt (share);
    if (shmctl (shmid, IPC_RMID, (struct shmid_ds *) 0) < 0) {
        sys_err ("eraser: shared memory remove error");
    }
    // Сообщение об удалении сегмента разделяемой памяти
    printf("eraser: shared memory using key = %x deleted\n", SHM_ID);

    return 0;
}
```
________________________

### 4. Примеры вывода. <br> ###

MacOS <br>


Virtual Ubuntu <br>


