#include <stdio.h>
#include <string.h>
#include <ctype.h>

char matrix[5][5] = {
    {'M', 'F', 'H', 'I', 'K'},
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
};

void findPosition(char ch, int *row, int *col) {
    int i, j;

    if (ch == 'J')
        ch = 'I';

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void encryptPair(char a, char b, char *x, char *y) {
    int r1, c1, r2, c2;

    findPosition(a, &r1, &c1);
    findPosition(b, &r2, &c2);

    if (r1 == r2) {
        *x = matrix[r1][(c1 + 1) % 5];
        *y = matrix[r2][(c2 + 1) % 5];
    } else if (c1 == c2) {
        *x = matrix[(r1 + 1) % 5][c1];
        *y = matrix[(r2 + 1) % 5][c2];
    } else {
        *x = matrix[r1][c2];
        *y = matrix[r2][c1];
    }
}

int main() {
    char message[] = "Must see you over Cadogan West. Coming at once.";
    char clean[200], prepared[200], encrypted[200];
    int i, n = 0, p = 0;

    for (i = 0; message[i] != '\0'; i++) {
        if (isalpha((unsigned char)message[i])) {
            char ch = toupper((unsigned char)message[i]);
            if (ch == 'J')
                ch = 'I';
            clean[n++] = ch;
        }
    }
    clean[n] = '\0';

    for (i = 0; i < n; i++) {
        prepared[p++] = clean[i];

        if (i + 1 < n && clean[i] == clean[i + 1]) {
            prepared[p++] = 'X';
        }
    }

    if (p % 2 != 0)
        prepared[p++] = 'X';

    prepared[p] = '\0';

    for (i = 0; i < p; i += 2) {
        encryptPair(prepared[i], prepared[i + 1],
                    &encrypted[i], &encrypted[i + 1]);
    }
    encrypted[p] = '\0';

    printf("PLAYFAIR CIPHER ENCRYPTION\n");

    printf("\nPlayfair Matrix:\n");
    for (i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++)
            printf("%c ", matrix[i][j]);
        printf("\n");
    }

    printf("\nPlaintext: %s\n", message);
    printf("Prepared Text: %s\n", prepared);
    printf("Encrypted Text: ");

    for (i = 0; i < p; i++) {
        printf("%c", encrypted[i]);
        if (i % 2 == 1)
            printf(" ");
    }

    printf("\n");
    return 0;
}
