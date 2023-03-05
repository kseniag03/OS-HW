#  ДЗ №7 #
## Markdown report <br> ##

### 1. Ганина Ксения Андреевна (тг для вопросов: @kgnn47) <br> ###
### 2. БПИ212 <br> ###

![image](https://user-images.githubusercontent.com/114473740/222980531-2fa4c553-29e6-48e3-add5-98e4d8bdfa9e.png)
________________________

### 3. Код с комментариями. <br> ###

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

int main(int argc, char *argv[]) {
    int loop_count;
    if (argc < 2) {
        printf("Usage: %s <loop_count>\n", argv[0]);
        exit(EXIT_FAILURE);
    } else {
        loop_count = atoi(argv[1]);
    }

    // Create and initialize the shared memory object
    int shm_fd = shm_open("/my_shared_mem", O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    if (ftruncate(shm_fd, SHARED_MEM_SIZE) == -1) {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    int *ptr = mmap(NULL, SHARED_MEM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Seed the random number generator
    srand(time(NULL));

    // Write random numbers to the shared memory
    int i = 0;
    while (i < loop_count) {
	printf("#client 1");
	if (*ptr == -2) {
            break;
        }
        int random_num = rand() % 1000;
        while (*ptr != -1 || *ptr != -2) {
	    printf("#client 2");
            usleep(1000);
        }
	if (*ptr == -2) {
            break;
        }
        *ptr = random_num;
        printf("Generated number: %d\n", random_num);
        i++;
    }

    // Signal the server to terminate
    *ptr = -2;

    // Unmap the shared memory object
    if (munmap(ptr, SHARED_MEM_SIZE) == -1) {
        perror("munmap");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
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

int main(int argc, char *argv[]) {
    int loop_count;
    if (argc < 2) {
        printf("Usage: %s <loop_count>\n", argv[0]);
        exit(EXIT_FAILURE);
    } else {
        loop_count = atoi(argv[1]);
    }

    // Create and initialize the shared memory object
    int shm_fd = shm_open("/my_shared_mem", O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    if (ftruncate(shm_fd, SHARED_MEM_SIZE) == -1) {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    int *ptr = mmap(NULL, SHARED_MEM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Read random numbers from the shared memory and output them
    int i = 0;
    int cnt = 0;
    while (i < loop_count) {
	printf("#server 1");
	if (cnt > 3) {
	    *ptr = -2;
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
    *ptr = -2;

    // Wait for the client to terminate
    while (*ptr != -2) {
        usleep(1000);
    }

    // Unmap and remove the shared memory object
    if (munmap(ptr, SHARED_MEM_SIZE) == -1) {
        perror("munmap");
        exit(EXIT_FAILURE);
    }

    if (shm_unlink("/my_shared_mem") == -1) {
        perror("shm_unlink");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}

```
________________________

### 4. Примеры вывода. <br> ###

Virtual Ubuntu <br>



