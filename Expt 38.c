
#include <stdio.h>
#include <string.h>

int mod(int a) {
    return (a % 26 + 26) % 26;
}

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int inverse(int a) {
    for (int i = 1; i < 26; i++) {
        if ((a * i) % 26 == 1)
            return i;
    }
    return -1;
}

int main() {
    char plain[100], cipher[100];
    int p[2][2], c[2][2];
    int key[2][2];
    int det, inv, i, j;

    printf("Enter 4 plaintext letters: ");
    scanf("%4s", plain);

    printf("Enter corresponding 4 ciphertext letters: ");
    scanf("%4s", cipher);

    if (strlen(plain) != 4 || strlen(cipher) != 4) {
        printf("Enter exactly 4 letters for each text.\n");
        return 1;
    }

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            char x = plain[i * 2 + j];
            char y = cipher[i * 2 + j];

            if (x < 'A' || x > 'Z' || y < 'A' || y > 'Z') {
                printf("Use uppercase English letters only.\n");
                return 1;
            }

            p[i][j] = x - 'A';
            c[i][j] = y - 'A';
        }
    }

    det = mod(p[0][0] * p[1][1] - p[0][1] * p[1][0]);

    if (gcd(det, 26) != 1) {
        printf("Plaintext matrix is not invertible modulo 26.\n");
        return 1;
    }

    inv = inverse(det);

    int pinv[2][2];

    pinv[0][0] = mod(inv * p[1][1]);
    pinv[0][1] = mod(-inv * p[0][1]);
    pinv[1][0] = mod(-inv * p[1][0]);
    pinv[1][1] = mod(inv * p[0][0]);

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            key[i][j] = 0;

            for (int k = 0; k < 2; k++) {
                key[i][j] += c[i][k] * pinv[k][j];
            }

            key[i][j] = mod(key[i][j]);
        }
    }

    printf("\nRecovered Key Matrix:\n");

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            printf("%d ", key[i][j]);
        }
        printf("\n");
    }

    printf("\nVerification Ciphertext: ");

    for (i = 0; i < 2; i++) {
        int value = 0;

        for (j = 0; j < 2; j++) {
            value += key[i][j] * p[j][0];
        }

        printf("%c", mod(value) + 'A');
    }

    printf("\n");

    return 0;
}
