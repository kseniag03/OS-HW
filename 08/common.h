#include <time.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <signal.h>

#define BUF_SIZE 10     // Размер буфера ячеек

///////////////////////////////////////////////////////////////////////////////////////

typedef struct {
    int have_reader;      // индикатор наличия читателя
    int reader_pid;       // идентификатор процесса читателя
    int have_writer;      // индикатор наличия писателя
    int writer_pid;       // идентификатор процесса писателя

    int data[BUF_SIZE];
    int start;		// указатель 1 (для читателя)
    int end;		// указатель 2 (для писателя)
} buffer_t;

///////////////////////////////////////////////////////////////////////////////////////

// имя области разделяемой памяти
extern const char* shar_object ;
extern int buf_id;        // дескриптор объекта памяти
extern buffer_t *buffer;    // указатель на разделямую память, хранящую буфер

// имя семафора для занятых ячеек
extern const char *full_sem_name;
extern sem_t *full;   // указатель на семафор занятых ячеек

// имя семафора для свободных ячеек
extern const char *empty_sem_name;
extern sem_t *empty;   // указатель на семафор свободных ячеек

// имя семафора (мьютекса) для критической секции,
// обеспечивающей доступ к буферу
extern const char *mutex_sem_name;
extern sem_t *mutex;   // указатель на семафор читателей


// Имя семафора для управления доступом.
// Позволяет читателю дождаться разрешения от читателя.
// Даже если читатель стартовал первым
extern const char *admin_sem_name;
extern sem_t *admin;   // указатель на семафор читателей

// Функция осуществляющая при запуске общие манипуляции с памятью и семафорами
// для децентрализованно подключаемых процессов читателей и писателей.
void init(void);

// Функция закрывающая семафоры общие для писателей и читателей
void close_common_semaphores(void);

// Функция, удаляющая все семафоры и разделяемую память
void unlink_all(void);
