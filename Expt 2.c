#include <stdio.h>
#include <ctype.h>
#include <string.h>
int main() {
    char text[100];
    char key[] = "QWERTYUIOPASDFGHJKLZXCVBNM";
    int i, index;
    printf("Enter a message: ");
    fgets(text, sizeof(text), stdin);

    for (i = 0; text[i] != '\0'; i++) {
        if (isupper(text[i])) {
            index = text[i] - 'A';
            text[i] = key[index];
        }
        else if (islower(text[i])) {
            index = text[i] - 'a';
            text[i] = tolower(key[index]);
        }
    }
    printf("Encrypted message: %s", text);
    return 0;
}
