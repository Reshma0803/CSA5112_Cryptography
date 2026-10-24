#include <stdio.h>
#include <string.h>
#include <ctype.h>

void cleanText(char text[], char result[]) {
    int i, j = 0;

    for (i = 0; text[i] != '\0'; i++) {
        if (isalpha((unsigned char)text[i]))
            result[j++] = tolower((unsigned char)text[i]);
    }

    result[j] = '\0';
}

void encrypt(char text[], int key[], char result[]) {
    int i;

    for (i = 0; text[i] != '\0'; i++) {
        result[i] = (text[i] - 'a' + key[i]) % 26 + 'a';
    }

    result[i] = '\0';
}

void decrypt(char text[], int key[], char result[]) {
    int i;

    for (i = 0; text[i] != '\0'; i++) {
        result[i] = (text[i] - 'a' - key[i] + 26) % 26 + 'a';
    }

    result[i] = '\0';
}

int main() {
    char plaintext[] = "send more money";
    char target[] = "cash not needed";
    char cleanPlain[100], cleanTarget[100];
    char ciphertext[100], recovered[100];
    int keyA[13] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    int keyB[13];
    int i, n;

    cleanText(plaintext, cleanPlain);
    cleanText(target, cleanTarget);

    n = strlen(cleanPlain);

    printf("ONE-TIME PAD VIGENERE CIPHER\n");
    printf("----------------------------\n");

    printf("\n(a) Encryption\n");
    printf("Plaintext: %s\n", plaintext);
    printf("Key stream: ");

    for (i = 0; i < n; i++)
        printf("%d ", keyA[i]);

    encrypt(cleanPlain, keyA, ciphertext);
    printf("\nCiphertext: %s\n", ciphertext);

    printf("\n(b) Finding a key for the target plaintext\n");
    printf("Target plaintext: %s\n", target);
    printf("Ciphertext used: %s\n", ciphertext);
    printf("Required key stream: ");

    for (i = 0; i < n; i++) {
        keyB[i] = (ciphertext[i] - 'a' -
                   cleanTarget[i] + 26) % 26;
        printf("%d ", keyB[i]);
    }

    decrypt(ciphertext, keyB, recovered);

    printf("\nDecrypted plaintext: ");
    for (i = 0; i < n; i++) {
        putchar(recovered[i]);
        if (i == 3 || i == 6)
            putchar(' ');
    }

    printf("\n");
    return 0;
}
