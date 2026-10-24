#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main() {
    int key[2][2] = {{9, 4}, {5, 7}};
    int inverse[2][2] = {{5, 12}, {15, 25}};
    char text[500], input[500], output[500];
    int i, n = 0, a, b, choice;
    printf("HILL CIPHER ENCRYPTION AND DECRYPTION\n");
    printf("1. Encrypt\n");
    printf("2. Decrypt\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    getchar();
    if (choice != 1 && choice != 2) {
        printf("Invalid choice!\n");
        return 1;
    }
    if (choice == 1) {
        strcpy(text,
            "meet me at the usual place at ten rather than eight oclock");
        printf("Plaintext: %s\n", text);
    } else {
        printf("Enter ciphertext: ");
        fgets(text, sizeof(text), stdin);
    }
    for (i = 0; text[i] != '\0'; i++) {
        if (isalpha((unsigned char)text[i]))
            input[n++] = toupper((unsigned char)text[i]);
    }
    if (choice == 1 && n % 2 != 0)
        input[n++] = 'X';

    if (n % 2 != 0) {
        printf("Error: Ciphertext must have an even number of letters.\n");
        return 1;
    }
    input[n] = '\0';
    for (i = 0; i < n; i += 2) {
        a = input[i] - 'A';
        b = input[i + 1] - 'A';
        if (choice == 1) {
            output[i] = (key[0][0] * a +
                         key[0][1] * b) % 26 + 'A';
            output[i + 1] = (key[1][0] * a +
                             key[1][1] * b) % 26 + 'A';
        } else {
            output[i] = (inverse[0][0] * a +
                         inverse[0][1] * b) % 26 + 'A';
            output[i + 1] = (inverse[1][0] * a +
                             inverse[1][1] * b) % 26 + 'A';
        }
    }
    output[n] = '\0';
    if (choice == 1)
        printf("Encrypted ciphertext: %s\n", output);
    else
        printf("Decrypted plaintext: %s\n", output);

    return 0;
}
