
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 2000

const char english[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

typedef struct {
    char text[MAX];
    double score;
    int shift;
} Candidate;

void decrypt(char cipher[], char plain[], int key[]) {
    int i;

    for (i = 0; cipher[i] != '\0'; i++) {
        if (isalpha((unsigned char)cipher[i])) {
            int c = toupper((unsigned char)cipher[i]) - 'A';
            plain[i] = key[c];
        } else {
            plain[i] = cipher[i];
        }
    }

    plain[i] = '\0';
}

double scoreText(char text[]) {
    int count[26] = {0};
    int total = 0, i, j;
    double score = 0.0;

    for (i = 0; text[i] != '\0'; i++) {
        if (isalpha((unsigned char)text[i])) {
            count[toupper((unsigned char)text[i]) - 'A']++;
            total++;
        }
    }

    if (total == 0)
        return 0;

    for (i = 0; i < 26; i++) {
        for (j = i + 1; j < 26; j++) {
            if (count[j] > count[i]) {
                int temp = count[i];
                count[i] = count[j];
                count[j] = temp;
            }
        }
    }

    for (i = 0; i < 26; i++) {
        score += (double)count[i] *
                 (26 - i);
    }

    return score / total;
}

int main() {
    char cipher[MAX];
    Candidate candidates[10];
    int key[26], freq[26] = {0};
    int i, j, top;

    printf("MONOALPHABETIC CIPHER FREQUENCY ATTACK\n");
    printf("Enter ciphertext: ");
    fgets(cipher, sizeof(cipher), stdin);

    printf("How many possible plaintexts (1-10)? ");
    if (scanf("%d", &top) != 1 || top < 1 || top > 10) {
        printf("Invalid number.\n");
        return 1;
    }

    for (i = 0; cipher[i] != '\0'; i++) {
        if (isalpha((unsigned char)cipher[i]))
            freq[toupper((unsigned char)cipher[i]) - 'A']++;
    }

    for (i = 0; i < 26; i++)
        key[i] = 'A' + i;

    for (i = 0; i < 26; i++) {
        for (j = i + 1; j < 26; j++) {
            if (freq[j] > freq[i]) {
                int temp = freq[i];
                freq[i] = freq[j];
                freq[j] = temp;
            }
        }
    }

    printf("\nFrequency analysis completed.\n");
    printf("Most common English letters: %s\n", english);
    printf("\nNote: Frequency analysis alone cannot reliably\n");
    printf("recover every substitution mapping.\n");

    printf("\nCandidate plaintext based on simple frequency mapping:\n");

    {
        int order[26];
        int originalFreq[26] = {0};
        char plain[MAX];

        for (i = 0; cipher[i] != '\0'; i++) {
            if (isalpha((unsigned char)cipher[i]))
                originalFreq[toupper((unsigned char)cipher[i]) - 'A']++;
        }

        for (i = 0; i < 26; i++)
            order[i] = i;

        for (i = 0; i < 26; i++) {
            for (j = i + 1; j < 26; j++) {
                if (originalFreq[order[j]] >
                    originalFreq[order[i]]) {
                    int temp = order[i];
                    order[i] = order[j];
                    order[j] = temp;
                }
            }
        }

        for (i = 0; i < 26; i++)
            key[order[i]] = english[i];

        decrypt(cipher, plain, key);

        for (i = 0; i < top; i++) {
            printf("%d. %s\n", i + 1, plain);
        }
    }

    return 0;
}
