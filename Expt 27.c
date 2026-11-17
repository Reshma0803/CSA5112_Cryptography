
#include <stdio.h>
#include <string.h>
#include <ctype.h>

long long power(long long base, long long exp, long long mod)
{
    long long result = 1;

    while (exp > 0)
    {
        if (exp % 2 == 1)
            result = (result * base) % mod;

        base = (base * base) % mod;
        exp /= 2;
    }

    return result;
}

int main()
{
    char message[100];
    int e = 7;
    int d = 103;
    int n = 143;

    long long encrypted[100];
    int length;

    printf("RSA CHARACTER ENCRYPTION\n");
    printf("------------------------\n");

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);

    length = strlen(message);

    if (length > 0 && message[length - 1] == '\n')
        message[--length] = '\0';

    printf("\nOriginal Message: %s\n", message);

    printf("\nEncrypted Values:\n");

    for (int i = 0; i < length; i++)
    {
        if (isalpha((unsigned char)message[i]))
        {
            int value = toupper((unsigned char)message[i]) - 'A';

            encrypted[i] = power(value, e, n);

            printf("%lld ", encrypted[i]);
        }
        else
        {
            encrypted[i] = -1;
            printf("%c ", message[i]);
        }
    }

    printf("\n\nDecrypted Message:\n");

    for (int i = 0; i < length; i++)
    {
        if (encrypted[i] != -1)
        {
            int value = power(encrypted[i], d, n);
            printf("%c", value + 'A');
        }
        else
        {
            printf("%c", message[i]);
        }
    }

    printf("\n");

    return 0;
}
