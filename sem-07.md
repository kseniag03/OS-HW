#  ДЗ №7 #
## Markdown report <br> ##

### 1. Ганина Ксения Андреевна (тг для вопросов: @kgnn47) <br> ###
### 2. БПИ212 <br> ###

![image](https://user-images.githubusercontent.com/114473740/222980531-2fa4c553-29e6-48e3-add5-98e4d8bdfa9e.png)
________________________

### 3. Код с комментариями. <br> ###

В аргументах командной строки передаётся конечное число итераций цикла. Более прямолинейным способом было бы определение кол-ва итераций за одинаковую константу в обоих программах.

#1. Client

```с
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>

#define SHARED_MEM_SIZE sizeof(int)

const char* shar_object = "posix-shar";

int main(int argc, char *argv[]) {
    int loop_count;
    if (argc < 2) {
        printf("No arguments\n");
        exit(1);
    } else {
        loop_count = atoi(argv[1]);
    }

    // Create and initialize the shared memory object
    int shm_id = shm_open(shar_object, O_CREAT | O_RDWR, 0666);
    if (shm_id == -1) {
        perror("shm_open error");
        exit(EXIT_FAILURE);
    } else {
    	printf("Object is open: name = %s, id = 0x%x\n", shar_object, shm_id);
    }

    // Задание размера объекта памяти
    if (ftruncate(shm_id, SHARED_MEM_SIZE) == -1) {
        perror("ftruncate error");
        exit(1);
    }

    int *ptr = mmap(0, SHARED_MEM_SIZE, PROT_WRITE|PROT_READ, MAP_SHARED, shm_id, 0);
    if (ptr == (int*)-1) {
        perror("mmap error");
        exit(1);
    }

    // Seed the random number generator
    srand(time(NULL));

    // Write random numbers to the shared memory
    int i = 0;
    *ptr = -1;
    while (i < loop_count && *ptr != -3) {
	if (*ptr == -3) {
            break;
        }
        int random_num = rand() % 1000;
        while (*ptr != -1 && *ptr != -3) {
            usleep(1000);
        }
	if (*ptr == -3) {
            break;
        }
        *ptr = random_num;
        printf("Generated number: %d\n", random_num);
        i++;
    }

    // Signal the server to terminate
    *ptr = -2;

    // удаление разделяемой памяти
    if (shm_unlink(shar_object) == -1) {
        perror("shm_unlink error");
        exit(1);
    }

    exit(0);
}

```

#2. Server

```с
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define SHARED_MEM_SIZE sizeof(int)

const char* shar_object = "posix-shar";

int main(int argc, char *argv[]) {
    int loop_count;
    if (argc < 2) {
        printf("No arguments\n");
        exit(1);
    } else {
        loop_count = atoi(argv[1]);
    }

    // Create and initialize the shared memory object
    int shm_id = shm_open(shar_object, O_CREAT | O_RDWR, 0666);
    if (shm_id == -1) {
        perror("shm_open error");
        exit(1);
    } else {
    	printf("Object is open: name = %s, id = 0x%x\n", shar_object, shm_id);
    }

    // Задание размера объекта памяти
    if (ftruncate(shm_id, SHARED_MEM_SIZE) == -1) {
        perror("ftruncate error");
        exit(1);
    }

    int *ptr = mmap(0, SHARED_MEM_SIZE, PROT_WRITE|PROT_READ, MAP_SHARED, shm_id, 0);
    if (ptr == (int*)-1) {
        perror("mmap error");
        exit(1);
    }

    // Read random numbers from the shared memory and output them
    int i = 0;
    int cnt = 0;
    while (i < loop_count) {
	if (cnt > 10) {
	    *ptr = -3;
            break;
        }
	int num = *ptr;
        if (num == -1) {
            usleep(1000);
	    cnt++;
            continue;
        } else if (num == -2) {
            break;
        }
        printf("Received number: %d\n", num);
        *ptr = -1;
        i++;
	cnt = 0;
    }
    if (*ptr != -2) {
	*ptr = -3;
    }

    // Wait for the client to terminate
    while (*ptr != -2) {
        usleep(1000);
    }

    // удаление разделяемой памяти
    if (shm_unlink(shar_object) == -1) {
        perror("shm_unlink error");
        exit(1);
    }

    exit(0);
}

```
________________________

### 4. Примеры вывода. <br> ###

Virtual Ubuntu <br>
![image](https://user-images.githubusercontent.com/114473740/222988436-59a4863c-711e-447f-bef7-e3d6658db6ef.png)



