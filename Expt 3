#include <stdio.h>
#include <string.h>
#include <ctype.h>
char matrix[5][5];
char key[] = "MONARCHY";
void createMatrix() {
    int used[26] = {0};
    int i, j, k = 0;
    char c;
    used['J' - 'A'] = 1;
    for (i = 0; key[i] != '\0'; i++) {
        c = toupper(key[i]);
        if (c == 'J')
            c = 'I';
        if (!used[c - 'A']) {
            matrix[k / 5][k % 5] = c;
            used[c - 'A'] = 1;
            k++;
        }
    }
    for (c = 'A'; c <= 'Z'; c++) {
        if (!used[c - 'A']) {
            matrix[k / 5][k % 5] = c;
            k++;
        }
    }
}
void findPosition(char c, int *row, int *col) {
    int i, j;
    if (c == 'J')
        c = 'I';
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (matrix[i][j] == c) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
int main() {
    char text[200], plain[200], encrypted[200];
    int i, n = 0, r1, c1, r2, c2;
    printf("Enter plaintext: ");
    fgets(text, sizeof(text), stdin);
    for (i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char c = toupper(text[i]);
            if (c == 'J')
                c = 'I';
            plain[n++] = c;
        }
    }
    plain[n] = '\0';
    createMatrix();
    for (i = 0; i < n; i++) {
        encrypted[i] = plain[i];
        if (i + 1 < n && plain[i] == plain[i + 1]) {
            memmove(&plain[i + 1], &plain[i], n - i);
            plain[i + 1] = 'X';
            n++;
        }
    }
    if (n % 2 != 0)
        plain[n++] = 'X';
    plain[n] = '\0';
    for (i = 0; i < n; i += 2) {
        findPosition(plain[i], &r1, &c1);
        findPosition(plain[i + 1], &r2, &c2);
        if (r1 == r2) {
            encrypted[i] = matrix[r1][(c1 + 1) % 5];
            encrypted[i + 1] = matrix[r2][(c2 + 1) % 5];
        }
        else if (c1 == c2) {
            encrypted[i] = matrix[(r1 + 1) % 5][c1];
            encrypted[i + 1] = matrix[(r2 + 1) % 5][c2];
        }
        else {
            encrypted[i] = matrix[r1][c2];
            encrypted[i + 1] = matrix[r2][c1];
        }
    }
    encrypted[n] = '\0';
    printf("Encrypted message: %s\n", encrypted);
    return 0;
}
