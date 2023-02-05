#  ДЗ №3 #
## Markdown report <br> ##

### 1. Ганина Ксения Андреевна (тг для вопросов: @kgnn47) <br> ###
### 2. БПИ212 <br> ###

<img width="878" alt="image" src="https://user-images.githubusercontent.com/114473740/216283903-3707388c-5ff2-4a46-8011-39a500330864.png">
________________________

### 3. Код. <br> ###

```с
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int fibonacci(int n) {
    if (n <= 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

int factorial(int n) {
    if (n == 0) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

int main(int argc, char* argv[]) {
    int n = atoi(argv[1]);
    pid_t pid = fork();
    if (pid == -1) {
        printf("Error");
    } else if (pid == 0) {
        printf("Child process %d with parent %d\nFactorial of %d is %d\n", (int)getpid(), (int)getppid(), n, factorial(n));
    } else {
        printf("Parent process %d\nFibonacci of %d is %d\n", (int)getpid(), n, fibonacci(n));
    }
    return 0;
}

```
________________________

### 4. Немного улучшенный код. <br> ###

```с
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int64_t fibonacci(int64_t n) {
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else if (n > 0) {
        return fibonacci(n - 1) + fibonacci(n - 2);
    } else {
        return fibonacci(n + 2) - fibonacci(n + 1);
    }
}

int64_t factorial(int64_t n) {
    if (n == 0) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        printf("No arguments\n");
        return 0;
    }
    int n = atoi(argv[1]);
    pid_t pid = fork();
    if (pid == -1) {
        printf("Error: incorrect fork syscall\n");
    } else if (pid == 0) {
        printf("Child process %d with parent %d\n", (int)getpid(), (int)getppid());
        if (n < 0) {
            printf("Cannot calculate factorial of negative number\n");
            return 0;
        }
        printf("Factorial of %d is %lld\n", n, factorial(n));
    } else {
        printf("Parent process %d\n", (int)getpid());
        printf("Fibonacci of %d is %lld\n", n, fibonacci(n));
    }
    return 0;
}

```
________________________

### 5. Примеры вывода. <br> ###

1. На MacOS, 1-я версия
<img width="573" alt="Снимок экрана 2023-02-02 в 12 27 37" src="https://user-images.githubusercontent.com/114473740/216285314-efc03bd7-a3d9-49c0-9798-f5b3b9a4f6fa.png">
2. Virtual Ubuntu, улучшенная версия
![image](https://user-images.githubusercontent.com/114473740/216815665-74f2724d-dc74-441a-a325-10b291acbb6e.png)


