#include <stdio.h>

int main(void) {
    int total_frames, window_size;
    int current = 0;
    int ack;

    printf("Enter total number of frames: ");
    scanf("%d", &total_frames);

    printf("Enter window size: ");
    scanf("%d", &window_size);

    printf("\nStarting transmission...\n");

    while (current < total_frames) {
        for (int i = 0; i < window_size && (current + i) < total_frames; i++) {
            printf("Sent Frame %d\n", current + i + 1);
        }

        printf("Enter the last successful frame number acknowledged: ");
        scanf("%d", &ack);

        if (ack > current && ack <= total_frames) {
            printf("ACK for frame %d received. Moving window forward.\n", ack);
            current = ack;
        } else {
            printf("Error! Going back to Frame %d\n", current + 1);
        }
    }

    printf("\nAll frames sent successfully!\n");
    return 0;
}
