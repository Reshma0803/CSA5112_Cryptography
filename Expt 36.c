
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int modInverse(int a) {
    for (int i = 1; i < 26; i++) {
        if ((a * i) % 26 == 1)
            return i;
    }
    return -1;
}

int main() {
    char plaintext[100], ciphertext[100], decrypted[100];
    int a, b, inverse, n;

    printf("Enter plaintext: ");
    scanf("%99s", plaintext);

    printf("Enter value of a: ");
    scanf("%d", &a);

    printf("Enter value of b: ");
    scanf("%d", &b);

    a = (a % 26 + 26) % 26;
    b = (b % 26 + 26) % 26;

    if (gcd(a, 26) != 1) {
        printf("Invalid key! Value of a must be relatively prime to 26.\n");
        return 1;
    }

    inverse = modInverse(a);
    n = strlen(plaintext);

    for (int i = 0; i < n; i++) {
        char ch = toupper(plaintext[i]);

        if (ch < 'A' || ch > 'Z') {
            printf("Enter alphabetic plaintext only.\n");
            return 1;
        }

        int p = ch - 'A';
        int c = (a * p + b) % 26;

        ciphertext[i] = c + 'A';
    }

    ciphertext[n] = '\0';

    for (int i = 0; i < n; i++) {
        int c = ciphertext[i] - 'A';
        int p = (inverse * (c - b + 26)) % 26;

        decrypted[i] = p + 'A';
    }

    decrypted[n] = '\0';

    printf("\nPlaintext  : %s", plaintext);
    printf("\nCiphertext : %s", ciphertext);
    printf("\nDecrypted  : %s\n", decrypted);

    return 0;
}
