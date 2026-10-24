#include <stdio.h>
#include <ctype.h>
#include <string.h>
int main() {
char plain[1000], cipher[1000];
char key[] = "CIPHER";
char map[26];
int used[26] = {0};
    int i, j = 0, choice;

    for (i = 0; key[i] != '\0'; i++) {
        char ch = toupper(key[i]);
        if (!used[ch - 'A']) {
            map[j++] = ch;
            used[ch - 'A'] = 1;
        }
    }

    for (i = 0; i < 26; i++) {
        if (!used[i]) {
            map[j++] = 'A' + i;
        }
    }

    printf("Monoalphabetic Cipher using Keyword CIPHER\n");
    printf("1. Encryption\n");
    printf("2. Decryption\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();

    if (choice == 1) {
        printf("Enter plaintext: ");
        fgets(plain, sizeof(plain), stdin);

        for (i = 0; plain[i] != '\0'; i++) {
            char ch = toupper(plain[i]);

            if (ch >= 'A' && ch <= 'Z') {
                cipher[i] = map[ch - 'A'];
            } else {
                cipher[i] = plain[i];
            }
        }

        cipher[i] = '\0';
        printf("Ciphertext: %s", cipher);
    } else if (choice == 2) {
        printf("Enter ciphertext: ");
        fgets(cipher, sizeof(cipher), stdin);

        for (i = 0; cipher[i] != '\0'; i++) {
            char ch = toupper(cipher[i]);

            if (ch >= 'A' && ch <= 'Z') {
                for (j = 0; j < 26; j++) {
                    if (map[j] == ch) {
                        plain[i] = 'A' + j;
                        break;
                    }
                }
            } else {
                plain[i] = cipher[i];
            }
        }

        plain[i] = '\0';
        printf("Plaintext: %s", plain);
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}
