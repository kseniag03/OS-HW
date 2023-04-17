#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int receiver_pid;

// отправка бита приёмнику
// чтобы приёмник различал биты, отправляем их по разным сигналам
void send(int bit) {
    if (bit == 0) {
        kill(receiver_pid, SIGUSR1);
    } else {
        kill(receiver_pid, SIGUSR2);
    }
}

void handler_wait(int nsig) {
    // waiting...
}

int main(void) {
    // установка обработчика сигнала
    (void) signal(SIGUSR1, handler_wait);

    // ввод
    int sender_pid = getpid(), num;
    printf("Sender pid = %d\n\n", sender_pid);
        
    printf("Enter receiver pid: ");
    scanf("%d", &receiver_pid);
    printf("Enter decimal integer number: ");
    scanf("%d", &num);
    
    printf("\nInput receiver pid: %d\n", receiver_pid);
    printf("Input decimal integer number: %d\n", num);

    if (num >= 0) {
        send(0);
    } else {
 	// учитываем доп бит для поддержки отрицательных чисел
        send(1);
    }

    // отправляем приёмнику число по одному биту
    int n = num;
    for (int i = 0; i < 32; ++i) {
        //printf("cur n = %d, cur bit = %d\n", n, n & 1);
	send(n & 1);
	n >>= 1;
        sleep(10);
    }
    
    printf("\nResult = %d\n", num);
    
    return 0;
}