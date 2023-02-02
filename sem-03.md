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

