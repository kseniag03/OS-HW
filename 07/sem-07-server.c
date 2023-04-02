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
    // проверка на корректный формат входных данных
    if (argc < 2) {
        printf("No arguments\n");
        exit(1);
    } else {
        loop_count = atoi(argv[1]);
    }

    // создание и инициализация объекта общей памяти
    int shm_id = shm_open(shar_object, O_CREAT | O_RDWR, 0666);
    if (shm_id == -1) {
        perror("shm_open error");
        exit(1);
    } else {
    	printf("Object is open: name = %s, id = 0x%x\n", shar_object, shm_id);
    }

    // задание размера объекта памяти
    if (ftruncate(shm_id, SHARED_MEM_SIZE) == -1) {
        perror("ftruncate error");
        exit(1);
    }

    // получение доступа к памяти
    int *ptr = mmap(0, SHARED_MEM_SIZE, PROT_WRITE|PROT_READ, MAP_SHARED, shm_id, 0);
    if (ptr == (int*)-1) {
        perror("mmap error");
        exit(1);
    }

    // чтение случайных чисел из общей памяти и их вывод
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

    // ожидание завершения работы клиента
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
