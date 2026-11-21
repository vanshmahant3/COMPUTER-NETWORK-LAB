#include <stdio.h>

int main(void) {
    int B, R, N, P[100];
    int stored = 0, overflow, sent, i;

    printf("Enter bucket capacity: ");
    scanf("%d", &B);
    printf("Enter outgoing rate: ");
    scanf("%d", &R);
    printf("Enter number of time units: ");
    scanf("%d", &N);

    for (i = 0; i < N; i++) {
        printf("Enter incoming packets: ");
        scanf("%d", &P[i]);
    }

    for (i = 0; i < N; i++) {
        if (stored + P[i] > B) {
            overflow = stored + P[i] - B;
            stored = B;
        } else {
            overflow = 0;
            stored = stored + P[i];
        }

        if (stored <= R) {
            sent = stored;
            stored = 0;
        } else {
            sent = R;
            stored = stored - R;
        }

        printf("\nTime %d", i + 1);
        printf("\nIncoming = %d", P[i]);
        printf("\nOverflow = %d", overflow);
        printf("\nSent = %d", sent);
        printf("\nPackets left = %d\n", stored);
    }

    while (stored > 0) {
        if (stored <= R) {
            sent = stored;
            stored = 0;
        } else {
            sent = R;
            stored = stored - R;
        }

        printf("\nSent = %d", sent);
        printf("\nPackets left = %d\n", stored);
    }

    return 0;
}
