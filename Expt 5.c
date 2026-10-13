#include <stdio.h>
#include <ctype.h>
int main() {
    char text[100];
    int a, b, i, p, c;
    printf("Enter plaintext: ");
    fgets(text, sizeof(text), stdin);
    printf("Enter value of a: ");
    scanf("%d", &a);
    printf("Enter value of b: ");
    scanf("%d", &b);
    if (a < 1 || a > 25 || b < 0 || b > 25) {
        printf("Invalid key values!\n");
        return 0;
    }
    int x = a, y = 26;

    while (y != 0) {
        int r = x % y;
        x = y;
        y = r;
    }
    if (x != 1) {
        printf("Invalid value of a! GCD(a, 26) must be 1.\n");
        return 0;
    }
    for (i = 0; text[i] != '\0'; i++) {
        if (isupper(text[i])) {
            p = text[i] - 'A';
            c = (a * p + b) % 26;
            text[i] = c + 'A';
        }
        else if (islower(text[i])) {
            p = text[i] - 'a';
            c = (a * p + b) % 26;
            text[i] = c + 'a';
        }
    }
    printf("Encrypted message: %s", text);
    return 0;
}
