
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 1000
#define TOP 10

char english[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

void frequencyAttack(char cipher[], int top) {
    int freq[26] = {0};
    int used[26] = {0};
    char result[26];
    char temp[MAX];
    int n = strlen(cipher);

    for (int i = 0; i < n; i++) {
        if (isalpha((unsigned char)cipher[i]))
            freq[toupper((unsigned char)cipher[i]) - 'A']++;
    }

    for (int i = 0; i < 26; i++) {
        int max = -1, index = -1;

        for (int j = 0; j < 26; j++) {
            if (!used[j] && freq[j] > max) {
                max = freq[j];
                index = j;
            }
        }

        if (index != -1) {
            used[index] = 1;
            result[index] = english[i];
        }
    }

    printf("\nTop %d Possible Plaintexts:\n", top);

    for (int k = 0; k < top; k++) {
        int shift = k;

        for (int i = 0; i < 26; i++) {
            temp[i] = result[i];
        }

        for (int i = 0; i < n; i++) {
            char ch = cipher[i];

            if (isalpha((unsigned char)ch)) {
                int index = toupper((unsigned char)ch) - 'A';
                char decoded = temp[index];

                if (islower((unsigned char)ch))
                    decoded = tolower((unsigned char)decoded);

                printf("%c", decoded);
            } else {
                printf("%c", ch);
            }
        }

        printf("  (Candidate %d)\n", k + 1);

        if (shift < 25) {
            char first = temp[0];
            for (int i = 0; i < 25; i++)
                temp[i] = temp[i + 1];
            temp[25] = first;
        }
    }
}

int main() {
    char cipher[MAX];
    int top;

    printf("Enter ciphertext: ");
    fgets(cipher, MAX, stdin);

    cipher[strcspn(cipher, "\n")] = '\0';

    printf("Enter number of possible plaintexts: ");
    scanf("%d", &top);

    if (top < 1 || top > 10) {
        printf("Enter a number between 1 and 10.\n");
        return 1;
    }

    frequencyAttack(cipher, top);

    return 0;
}
