
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char plaintext[100], ciphertext[100], decrypted[100];
    int key[100], n;

    printf("Enter plaintext: ");
    scanf("%99s", plaintext);

    n = strlen(plaintext);

    printf("Enter %d key values (0-25):\n", n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &key[i]);

        if (key[i] < 0 || key[i] > 25) {
            printf("Invalid key! Enter values between 0 and 25.\n");
            return 1;
        }
    }

    for (int i = 0; i < n; i++) {
        plaintext[i] = toupper(plaintext[i]);

        if (plaintext[i] < 'A' || plaintext[i] > 'Z') {
            printf("Enter alphabetic plaintext only.\n");
            return 1;
        }

        ciphertext[i] = ((plaintext[i] - 'A' + key[i]) % 26) + 'A';
    }

    ciphertext[n] = '\0';

    for (int i = 0; i < n; i++) {
        decrypted[i] = ((ciphertext[i] - 'A' - key[i] + 26) % 26) + 'A';
    }

    decrypted[n] = '\0';

    printf("\nPlaintext  : %s", plaintext);
    printf("\nKey        : ");

    for (int i = 0; i < n; i++) {
        printf("%d ", key[i]);
    }

    printf("\nCiphertext : %s", ciphertext);
    printf("\nDecrypted  : %s\n", decrypted);

    return 0;
}
