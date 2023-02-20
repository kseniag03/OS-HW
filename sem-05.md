#  ДЗ №5 #
## Markdown report <br> ##

### 1. Ганина Ксения Андреевна (тг для вопросов: @kgnn47) <br> ###
### 2. БПИ212 <br> ###

![image](https://user-images.githubusercontent.com/114473740/219975613-a4d4aeba-7419-43b9-b520-47e1cac55bcd.png)
________________________

### 3. Код с комментариями. <br> ###

#1

```с
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("No arguments\n");
        return 0;
    }

    int fd;
    char *fifo = argv[1];

    // create the FIFO (named pipe)
    mkfifo(fifo, 0666);

    // open, write, and close the file
    fd = open(fifo, O_WRONLY);
    char *message = "Hello from process 1!";
    write(fd, message, strlen(message) + 1);
    close(fd);

    // open, read, and close the file
    fd = open(fifo, O_RDONLY);
    char buffer[100];
    read(fd, buffer, sizeof(buffer));
    printf("Received from process 2: %s\n", buffer);
    close(fd);

    // remove the FIFO
    unlink(fifo);
    return 0;
}
```

#2

```с
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("No arguments\n");
        return 0;
    }
    
    int fd;
    char *fifo = argv[1];

    // open, read, and close the file
    fd = open(fifo, O_RDONLY);
    char buffer[100];
    read(fd, buffer, sizeof(buffer));
    printf("Received from process 1: %s\n", buffer);
    close(fd);

    // open, write, and close the file
    fd = open(fifo, O_WRONLY);
    char *message = "Hello from process 2!";
    write(fd, message, strlen(message) + 1);
    close(fd);

    return 0;
}

```
________________________

### 4. Примеры вывода. <br> ###

Virtual Ubuntu <br>



