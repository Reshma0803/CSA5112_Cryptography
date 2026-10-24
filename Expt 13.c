#include <stdio.h>
#define MOD 26
int mod(int x) {
    return (x % MOD + MOD) % MOD;
}
int modInverse(int a) {
    int i;
    for (i = 1; i < MOD; i++) {
        if (mod(a * i) == 1)
            return i;
    }
    return -1;
}
int main() {
    int P[2][2] = {{2, 4}, {1, 3}};
    int C[2][2] = {{22, 16}, {21, 18}};
    int Pinv[2][2], K[2][2];
    int det, invDet;
    int i, j;
    printf("HILL CIPHER KNOWN-PLAINTEXT ATTACK\n");
    printf("----------------------------------\n");
    printf("Known Plaintext Matrix:\n");
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++)
            printf("%d ", P[i][j]);
        printf("\n");
    }
    printf("\nKnown Ciphertext Matrix:\n");
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }
    det = mod(P[0][0] * P[1][1] -
              P[0][1] * P[1][0]);

    invDet = modInverse(det);

    if (invDet == -1) {
        printf("\nPlaintext matrix is not invertible modulo 26.\n");
        return 1;
    }

    Pinv[0][0] = mod(invDet * P[1][1]);
    Pinv[0][1] = mod(-invDet * P[0][1]);
    Pinv[1][0] = mod(-invDet * P[1][0]);
    Pinv[1][1] = mod(invDet * P[0][0]);

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            K[i][j] = mod(
                C[i][0] * Pinv[0][j] +
                C[i][1] * Pinv[1][j]
            );
        }
    }

    printf("\nRecovered Key Matrix:\n");
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++)
            printf("%d ", K[i][j]);
        printf("\n");
    }

    printf("\nResult: Key recovered successfully.\n");

    return 0;
}
