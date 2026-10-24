#include <stdio.h>
#include <string.h>

#define N 4
#define SIZE 4

int main(void)
{
    unsigned char plaintext[N][SIZE] = {
        "ABCD", "EFGH", "IJKL", "MNOP"
    };

    unsigned char ecb[N][SIZE];
    unsigned char cbc[N][SIZE];

    memcpy(ecb, plaintext, sizeof(plaintext));
    memcpy(cbc, plaintext, sizeof(plaintext));

    printf("Original Plaintext Blocks:\n");
    for (int i = 0; i < N; i++)
        printf("P%d: %s\n", i + 1, plaintext[i]);

    /* Simulate a one-bit error in transmitted ciphertext C1 */
    ecb[0][0] ^= 0x01;
    cbc[0][0] ^= 0x01;

    printf("\nECB Mode:\n");
    printf("An error in C1 affects only P1.\n");
    printf("P2, P3 and P4 remain unchanged.\n");

    printf("\nCBC Mode:\n");
    printf("An error in transmitted C1 corrupts P1.\n");
    printf("The corresponding bit in P2 is flipped.\n");
    printf("P3 and P4 remain unchanged.\n");

    printf("\nPlaintext error propagation in CBC:\n");
    printf("An error in source P1 affects C1 and all later ciphertext blocks.\n");
    printf("At the receiver, plaintext blocks from P1 onward may be corrupted.\n");

    return 0;
}
