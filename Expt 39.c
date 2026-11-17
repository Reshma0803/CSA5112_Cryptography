
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 1000

int main() {
    char cipher[MAX];
    char plaintext[MAX];
    int freq[26] = {0};
    int shift[26];
    int top;

    printf("Enter ciphertext: ");
    fgets(cipher, MAX, stdin);

    cipher[strcspn(cipher, "\n")] = '\0';

    printf("Enter number of possible plaintexts (1-10): ");
    scanf("%d", &top);

    if (top < 1 || top > 10) {
        printf("Invalid number! Enter between 1 and 10.\n");
        return 1;
    }

    for (int i = 0; cipher[i] != '\0'; i++) {
        if (isalpha((unsigned char)cipher[i]))
            freq[toupper((unsigned char)cipher[i]) - 'A']++;
    }

    printf("\nTop %d Possible Plaintexts:\n", top);

    for (int s = 0; s < 26; s++) {
        shift[s] = s;
    }

    for (int i = 0; i < 26; i++) {
        int max = i;

        for (int j = i + 1; j < 26; j++) {
            if (freq[j] > freq[max])
                max = j;
        }

        int temp = freq[i];
        freq[i] = freq[max];
        freq[max] = temp;
    }

    for (int k = 0; k < top; k++) {
        int key = k;

        printf("\nCandidate %d:\n", k + 1);

        for (int i = 0; cipher[i] != '\0'; i++) {
            char ch = cipher[i];

            if (isupper((unsigned char)ch))
                plaintext[i] = (ch - 'A' - key + 26) % 26 + 'A';
            else if (islower((unsigned char)ch))
                plaintext[i] = (ch - 'a' - key + 26) % 26 + 'a';
            else
                plaintext[i] = ch;
        }

        plaintext[strlen(cipher)] = '\0';

        printf("%s\n", plaintext);
    }

    return 0;
}
