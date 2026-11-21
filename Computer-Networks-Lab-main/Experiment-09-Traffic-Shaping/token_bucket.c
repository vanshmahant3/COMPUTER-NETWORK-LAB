#include <stdio.h>

int main(void) {
    int cap, rate, n, i, packets;
    int token = 0, wait = 0, send;

    printf("Enter bucket capacity: ");
    scanf("%d", &cap);
    printf("Enter token rate: ");
    scanf("%d", &rate);
    printf("Enter number of time units: ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++) {
        printf("Enter incoming packets: ");
        scanf("%d", &packets);

        wait = wait + packets;
        token = token + rate;

        if (token > cap)
            token = cap;

        if (wait <= token) {
            send = wait;
            wait = 0;
            token = token - send;
        } else {
            send = token;
            wait = wait - send;
            token = 0;
        }

        printf("Time %d\n", i);
        printf("Sent = %d\n", send);
        printf("Queued = %d\n", wait);
        printf("Tokens left = %d\n", token);
    }

    while (wait > 0) {
        token = token + rate;
        if (token > cap)
            token = cap;

        if (wait <= token) {
            send = wait;
            wait = 0;
            token = token - send;
        } else {
            send = token;
            wait = wait - send;
            token = 0;
        }

        printf("Sent = %d\n", send);
        printf("Queued = %d\n", wait);
    }

    return 0;
}
