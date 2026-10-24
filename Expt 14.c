#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main() {
    char text[500], result[500];
    int key[500], n = 0, i, choice;
    printf("ONE-TIME PAD VIGENERE CIPHER\n");
    printf("1. Encryption\n");
    printf("2. Decryption\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();
    if (choice != 1 && choice != 2) {
        printf("Invalid choice!\n");
        return 1;
    }

    printf("Enter message: ");
    fgets(text, sizeof(text), stdin);

    for (i = 0; text[i] != '\0'; i++) {
        if (isalpha((unsigned char)text[i])) {
            text[n++] = toupper((unsigned char)text[i]);
        }
    }
    text[n] = '\0';

    if (n == 0) {
        printf("No letters entered.\n");
        return 1;
    }

    printf("Enter %d key numbers (0-25):\n", n);

    for (i = 0; i < n; i++) {
        if (scanf("%d", &key[i]) != 1 ||
            key[i] < 0 || key[i] > 25) {
            printf("Invalid key! Enter numbers from 0 to 25.\n");
            return 1;
        }
    }

    for (i = 0; i < n; i++) {
        int value = text[i] - 'A';

        if (choice == 1)
            result[i] = (value + key[i]) % 26 + 'A';
        else
            result[i] = (value - key[i] + 26) % 26 + 'A';
    }

    result[n] = '\0';

    if (choice == 1)
        printf("Encrypted message: %s\n", result);
    else
        printf("Decrypted message: %s\n", result);

    return 0;
}
