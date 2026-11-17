
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 1000

char english[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

int main() {
    char cipher[MAX], plaintext[MAX];
    int freq[26] = {0};
    int used[26] = {0};
    char mapping[26];
    int top;

    printf("Enter ciphertext: ");
    fgets(cipher, MAX, stdin);

    cipher[strcspn(cipher, "\n")] = '\0';

    printf("Enter number of possible plaintexts (1-10): ");
    scanf("%d", &top);

    if (top < 1 || top > 10) {
        printf("Invalid input! Enter between 1 and 10.\n");
        return 1;
    }

    for (int i = 0; cipher[i] != '\0'; i++) {
        if (isalpha((unsigned char)cipher[i]))
            freq[toupper((unsigned char)cipher[i]) - 'A']++;
    }

    int sorted[26];

    for (int i = 0; i < 26; i++)
        sorted[i] = i;

    for (int i = 0; i < 26; i++) {
        for (int j = i + 1; j < 26; j++) {
            if (freq[sorted[j]] > freq[sorted[i]]) {
                int temp = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = temp;
            }
        }
    }

    for (int i = 0; i < 26; i++)
        mapping[sorted[i]] = english[i];

    printf("\nTop %d Possible Plaintexts:\n", top);

    for (int k = 0; k < top; k++) {
        printf("\nCandidate %d:\n", k + 1);

        for (int i = 0; cipher[i] != '\0'; i++) {
            char ch = cipher[i];

            if (isalpha((unsigned char)ch)) {
                char decoded = mapping[toupper((unsigned char)ch) - 'A'];

                plaintext[i] = islower((unsigned char)ch)
                    ? tolower((unsigned char)decoded)
                    : decoded;
            } else {
                plaintext[i] = ch;
            }
        }

        plaintext[strlen(cipher)] = '\0';
        printf("%s\n", plaintext);

        char temp = mapping[0];

        for (int i = 0; i < 25; i++)
            mapping[i] = mapping[i + 1];

        mapping[25] = temp;
    }

    return 0;
}
