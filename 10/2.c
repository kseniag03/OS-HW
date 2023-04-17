#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int sender_pid;
int received_bit = -1;

void handler(int nsig) {
    if (nsig == SIGUSR1) {
        received_bit = 0;
    } else if (nsig == SIGUSR2) {
        received_bit = 1;
    }
}

int main(void) {
    // установка обработчиков сигнала
    (void) signal(SIGUSR1, handler);
    (void) signal(SIGUSR2, handler);

    int receiver_pid = getpid();
    printf("Receiver pid = %d\n\n", receiver_pid);

    printf("Enter sender pid: ");
    scanf("%d", &sender_pid);

    printf("\nInput sender pid: %d\n", sender_pid);

    // notify sender
    kill(sender_pid, SIGUSR1);

    int bits[32];
    for (int i = 0; i < 32; ++i) {
        //pause();
sleep(10);
	bits[i] = received_bit;
	printf("%d", received_bit);
	kill(sender_pid, SIGUSR1);
    }

    int num = 0;
    for (int i = 0; i < 32; ++i) {
        num |= bits[i] << i;
    }

    printf("\nResult = %d\n", num);

    return 0;
}
