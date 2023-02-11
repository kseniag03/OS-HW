#  ДЗ №4 #
## Markdown report <br> ##

### 1. Ганина Ксения Андреевна (тг для вопросов: @kgnn47) <br> ###
### 2. БПИ212 <br> ###

![image](https://user-images.githubusercontent.com/114473740/218279924-187caf3b-eb1f-4872-8b40-77c6e92cb6d7.png)
________________________

### 3. Код с комментариями, поясняющими работу функций. <br> ###

```с
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// Размер буфера
const int size = 1024;

// Аргументы командной строки: имя исполняемого, входного и выходного файла
int main(int argc, char *argv[]) {

    // Буфер для чтения
    char buffer[size];
    // Количество прочитанных байтов
    ssize_t read_bytes;

    // Недостаточно аргументов командной строки (имя входного и выходного файла)
    if (argc < 3) {
        printf("Error: not enough arguments (need to enter input and output file names)\n");
        return 1;
    }
    // Получаем имена входного и выходного файлов
    char *input_file = argv[1];
    char *output_file = argv[2];

    // Открываем файл на чтение, флаги: только для чтения
    int in_fd = open(input_file, O_RDONLY);
    if (in_fd == -1) {
        printf("Error: cannot open input file\n");
        return 1;
    }
    // Открываем файл на запись, флаги: только для записи, создание
    // Если файла для записи не существует, он создаётся, иначе содержимое перезаписывается
    int out_fd = open(output_file, O_WRONLY | O_CREAT);
    if (out_fd == -1) {
        printf("Error: cannot open output file\n");
        return 1;
    }

    // Читаем файл по 1024 байт и записываем в выходной файл, используя цикл
    while ((read_bytes = read(in_fd, buffer, size)) > 0) {
        if (write(out_fd, buffer, read_bytes) != read_bytes) {
            printf("Writing to output file error\n");
            return 1;
        }
    }
    // Проверяем, что файл был прочитан полностью
    if (read_bytes == -1) {
        printf("Reading input file error\n");
        return 1;
    }

    // Закрываем файлы
    if (close(in_fd) == -1) {
        printf("Error: cannot close input file\n");
        return 1;
    }
    if (close(out_fd) == -1) {
        printf("Error: cannot close output file\n");
        return 1;
    }

    return 0;
}

```
________________________

### 4. Примеры вывода. <br> ###

Virtual Ubuntu <br>
![image](https://user-images.githubusercontent.com/114473740/218282219-c71b1e5b-2f26-4206-9f34-0093015b098b.png) <br>
![image](https://user-images.githubusercontent.com/114473740/218282352-d690a8a6-04fe-4b1a-adf3-7f5188209206.png)


