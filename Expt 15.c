#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 1000
double frequency[26] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228,
    2.015, 6.094, 6.966, 0.153, 0.772, 4.025,
    2.406, 6.749, 7.507, 1.929, 0.095, 5.987,
    6.327, 9.056, 2.758, 0.978, 2.360, 0.150,
    1.974, 0.074
};
typedef struct {
    int shift;
    double score;
    char text[MAX];
} Candidate;
void decrypt(char cipher[], char plain[], int shift) {
    int i;

    for (i = 0; cipher[i] != '\0'; i++) {
        if (isalpha((unsigned char)cipher[i])) {
            char base = isupper((unsigned char)cipher[i]) ? 'A' : 'a';
            plain[i] = (cipher[i] - base - shift + 26) % 26 + base;
        } else {
            plain[i] = cipher[i];
        }
    }

    plain[i] = '\0';
}

double scoreText(char text[]) {
    int counts[26] = {0};
    int total = 0, i;
    double score = 0.0;

    for (i = 0; text[i] != '\0'; i++) {
        if (isalpha((unsigned char)text[i])) {
            counts[tolower((unsigned char)text[i]) - 'a']++;
            total++;
        }
    }

    if (total == 0)
        return -1.0;

    for (i = 0; i < 26; i++) {
        score += counts[i] * frequency[i];
    }

    return score / total;
}

int main() {
    char cipher[MAX];
    Candidate candidates[26], temp;
    int top, i, j;

    printf("ADDITIVE CIPHER FREQUENCY ATTACK\n");
    printf("Enter ciphertext: ");
    fgets(cipher, sizeof(cipher), stdin);

    printf("How many possible plaintexts do you want (1-26)? ");
    if (scanf("%d", &top) != 1 || top < 1 || top > 26) {
        printf("Invalid number. Enter a value from 1 to 26.\n");
        return 1;
    }

    for (i = 0; i < 26; i++) {
        candidates[i].shift = i;
        decrypt(cipher, candidates[i].text, i);
        candidates[i].score = scoreText(candidates[i].text);
    }

    for (i = 0; i < 25; i++) {
        for (j = i + 1; j < 26; j++) {
            if (candidates[j].score > candidates[i].score) {
                temp = candidates[i];
                candidates[i] = candidates[j];
                candidates[j] = temp;
            }
        }
    }

    printf("\nTop %d possible plaintexts:\n\n", top);

    for (i = 0; i < top; i++) {
        printf("%d. Shift = %d | Score = %.3f\n",
               i + 1, candidates[i].shift,
               candidates[i].score);
        printf("   %s\n\n", candidates[i].text);
    }

    return 0;
}
