#include <stdio.h>
#include <string.h>
#include <ctype.h>
int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
int modInverse(int a)
{
    for (int i = 1; i < 26; i++)
    {
        if ((a * i) % 26 == 1)
            return i;
    }
    return -1;
}
int main()
{
    char cipher[1000];
    int a, b, inv;
    printf("Enter the ciphertext: ");
    fgets(cipher, sizeof(cipher), stdin);
    printf("\nPossible decrypted messages:\n\n");
    for (a = 1; a < 26; a++)
    {
        if (gcd(a, 26) != 1)
            continue;
        inv = modInverse(a);
        for (b = 0; b < 26; b++)
        {
            printf("Key (a=%d, b=%d): ", a, b);
            for (int i = 0; cipher[i] != '\0'; i++)
            {
                if (isalpha((unsigned char)cipher[i]))
                {
                    int c = toupper((unsigned char)cipher[i]) - 'A';
                    int p = (inv * (c - b + 26)) % 26;
                    putchar(p + 'A');
                }
                else
                {
                    putchar(cipher[i]);
                }
            }
            printf("\n");
        }
    }
    return 0;
}
