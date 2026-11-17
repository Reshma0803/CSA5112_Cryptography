#include <stdio.h>

int gcd(int a, int b)
{
    while (b != 0)
    {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int extended_gcd(int a, int b, int *x, int *y)
{
    if (b == 0)
    {
        *x = 1;
        *y = 0;
        return a;
    }

    int x1, y1;
    int g = extended_gcd(b, a % b, &x1, &y1);

    *x = y1;
    *y = x1 - (a / b) * y1;

    return g;
}

int mod_inverse(int e, int phi)
{
    int x, y;
    extended_gcd(e, phi, &x, &y);
    return (x % phi + phi) % phi;
}

int main()
{
    int n = 3599;
    int e = 31;
    int p = 59;
    int q = 61;

    int phi = (p - 1) * (q - 1);
    int d = mod_inverse(e, phi);

    printf("RSA ENCRYPTION AND DECRYPTION\n");
    printf("-----------------------------\n");

    printf("Public Key (e, n): (%d, %d)\n", e, n);
    printf("Prime number p: %d\n", p);
    printf("Prime number q: %d\n", q);
    printf("Phi(n): %d\n", phi);
    printf("Private Key (d, n): (%d, %d)\n", d, n);

    int message = 123;
    long long ciphertext = 1;
    long long decrypted = 1;

    for (int i = 0; i < e; i++)
        ciphertext = (ciphertext * message) % n;

    for (int i = 0; i < d; i++)
        decrypted = (decrypted * ciphertext) % n;

    printf("\nOriginal Message: %d\n", message);
    printf("Encrypted Message: %lld\n", ciphertext);
    printf("Decrypted Message: %lld\n", decrypted);

    return 0;
}
