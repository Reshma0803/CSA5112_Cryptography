#include <stdio.h>
#include <string.h>
#include <ctype.h>
char matrix[5][5];
void createMatrix(char key[]) {
    int used[26] = {0};
    int i, j, k = 0;
    char ch;
    used['J' - 'A'] = 1;
    for (i = 0; key[i] != '\0'; i++) {
        ch = toupper((unsigned char)key[i]);
        if (ch >= 'A' && ch <= 'Z') {
            if (ch == 'J')
                ch = 'I';
            if (!used[ch - 'A']) {
                matrix[k / 5][k % 5] = ch;
                used[ch - 'A'] = 1;
                k++;
            }
        }
    }
    for (i = 0; i < 26; i++) {
        if (!used[i]) {
            matrix[k / 5][k % 5] = 'A' + i;
            k++;
        }
    }
}
void findPosition(char ch, int *r, int *c) {
    int i, j;
    if (ch == 'J')
        ch = 'I';
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (matrix[i][j] == ch) {
                *r = i;
                *c = j;
                return;
            }
        }
    }
}
void decryptPair(char a, char b, char *x, char *y) {
    int r1, c1, r2, c2;
    findPosition(a, &r1, &c1);
    findPosition(b, &r2, &c2);
    if (r1 == r2) {
        *x = matrix[r1][(c1 + 4) % 5];
        *y = matrix[r2][(c2 + 4) % 5];
    } else if (c1 == c2) {
        *x = matrix[(r1 + 4) % 5][c1];
        *y = matrix[(r2 + 4) % 5][c2];
    } else {
        *x = matrix[r1][c2];
        *y = matrix[r2][c1];
    }
}
int main() {
    char key[] = "ROYAL NEW ZEALAND NAVY";
    char ciphertext[] =
        "KXJEY UREBE ZWEHE WRYTU HEYFS "
        "KREHE GOYFI WTTTU OLKSY CAJPO "
        "BOTEI ZONTX BYBNT GONEY CUZWR "
        "GDSON SXBOU YWRHE BAAHY USEDQ";
    char clean[200], plaintext[200];
    int i, n = 0, j;
    createMatrix(key);
    printf("PLAYFAIR CIPHER DECRYPTION\n");
    printf("Keyword: %s\n", key);
    printf("\nKey Matrix:\n");
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++)
            printf("%c ", matrix[i][j]);
        printf("\n");
    }
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha((unsigned char)ciphertext[i]))
            clean[n++] = toupper((unsigned char)ciphertext[i]);
    }
    clean[n] = '\0';
    for (i = 0; i < n; i += 2)
        decryptPair(clean[i], clean[i + 1],
                    &plaintext[i], &plaintext[i + 1]);
    plaintext[n] = '\0';
    printf("\nCiphertext:\n%s\n", ciphertext);
    printf("\nDecrypted Text:\n%s\n", plaintext);
    return 0;
}
